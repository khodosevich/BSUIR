#include <cstdio>
#include <cuda_runtime.h>
#include <curand.h>
#include <curand_kernel.h>
#include <chrono>
#include <cmath>

#define BLOCK_SIZE 32
#define GRID_SIZE 256

#define DATA_PACK_SIZE BLOCK_SIZE*BLOCK_SIZE*GRID_SIZE*GRID_SIZE

#define CHECK_CUDA(call) { \
    const cudaError_t error = call; \
    if (error != cudaSuccess) { \
        printf("CUDA Error: %s:%d, %s\n", __FILE__, __LINE__, cudaGetErrorString(error)); \
        exit(EXIT_FAILURE); \
    } \
}

#define CHECK_CURAND(call) { \
    const curandStatus_t error = call; \
    if (error != CURAND_STATUS_SUCCESS) { \
        printf("CURAND Error: %s:%d, %d\n", __FILE__, __LINE__, error); \
        exit(EXIT_FAILURE); \
    } \
}

using data_t = int;

struct dataPack
{
    data_t data[DATA_PACK_SIZE]{};
};

enum class ReductionOp {
    SUM,
    XOR,
    AND,
    OR,
    MIN,
    MAX,
    SUB
};

template<ReductionOp Op>
struct Reducer {
    __host__ __device__ static void reduce(data_t* a, const data_t& b);

    __device__ static void reduceAtomic(data_t* a, const data_t& b);
};

template<>
struct Reducer<ReductionOp::SUM> {
    __host__ __device__ static void reduce(data_t* a, const data_t& b) { *a += b; }

    __device__ static void reduceAtomic(data_t* a, const data_t& b) { atomicAdd(a, b); }
};

template<>
struct Reducer<ReductionOp::XOR> {
    __host__ __device__ static void reduce(data_t* a, const data_t& b) { *a ^= b; }
    __device__ static void reduceAtomic(data_t* a, const data_t& b) { atomicXor(a, b); }
};

template<>
struct Reducer<ReductionOp::AND> {
    __host__ __device__ static void reduce(data_t* a, const data_t& b) { *a &= b; }
    __device__ static void reduceAtomic(data_t* a, const data_t& b) { atomicAnd(a, b); }
};

template<>
struct Reducer<ReductionOp::OR> {
    __host__ __device__ static void reduce(data_t* a, const data_t& b) { *a |= b; }
    __device__ static void reduceAtomic(data_t* a, const data_t& b) { atomicOr(a, b); }
};

template<>
struct Reducer<ReductionOp::MIN> {
    __host__ __device__ static void reduce(data_t* a, const data_t& b) { *a = *a < b ? *a : b; }
    __device__ static void reduceAtomic(data_t* a, const data_t& b) { atomicMin(a, b); }
};

template<>
struct Reducer<ReductionOp::MAX> {
    __host__ __device__ static void reduce(data_t* a, const data_t& b) { *a = *a > b ? *a : b; }
    __device__ static void reduceAtomic(data_t* a, const data_t& b) { atomicMax(a, b); }
};

template<>
struct Reducer<ReductionOp::SUB> {
    __host__ __device__ static void reduce(data_t* a, const data_t& b) { *a -= b; }
    __device__ static void reduceAtomic(data_t* a, const data_t& b) { atomicSub(a, b); }
};

template<ReductionOp Op>
data_t processMatrixCPU(const dataPack& data) {
    data_t output{};
    for (int globalY = 0; globalY < BLOCK_SIZE * GRID_SIZE; globalY++) {
        for (int globalX = 0; globalX < BLOCK_SIZE * GRID_SIZE; globalX++) {
            int globalIdx = globalY * BLOCK_SIZE * GRID_SIZE + globalX;
            Reducer<Op>::reduce(&output, data.data[globalIdx]);
        }
    }
    return output;
}

template<ReductionOp Op>
__global__ void processMatrix(dataPack* input, data_t* result) {
    __shared__ data_t sharedSum[BLOCK_SIZE * BLOCK_SIZE];

    int localX = threadIdx.x;
    int localY = threadIdx.y;
    int blockX = blockIdx.x;
    int blockY = blockIdx.y;

    int globalX = blockX * blockDim.x + localX;
    int globalY = blockY * blockDim.y + localY;

    int localIdx = localY * blockDim.x + localX;
    int globalIdx = globalY * blockDim.x * gridDim.x + globalX;

    sharedSum[localIdx] = input->data[globalIdx];

    __syncthreads();

    for (unsigned int stride = blockDim.x * blockDim.y / 2; stride > 0; stride >>= 1) {
        if (localIdx < stride) {
            Reducer<Op>::reduce(sharedSum + localIdx, sharedSum[localIdx + stride]);
        }
        __syncthreads();
    }

    if (localIdx == 0) {
        Reducer<Op>::reduceAtomic(result, sharedSum[0]);
    }
}


template<ReductionOp Op>
void testReduction(const char* opName) {
    static dataPack inputData;
    dataPack* deviceInputData;
    data_t* deviceResult;

    // Allocate device memory
    CHECK_CUDA(cudaMalloc(&deviceInputData, sizeof(dataPack)));
    CHECK_CUDA(cudaMalloc(&deviceResult, sizeof(data_t)));

    // Generate random data
    curandGenerator_t gen;
    CHECK_CURAND(curandCreateGenerator(&gen, CURAND_RNG_PSEUDO_DEFAULT));
    CHECK_CURAND(curandSetPseudoRandomGeneratorSeed(gen, 1234ULL));
    CHECK_CURAND(curandGenerate(gen, reinterpret_cast<unsigned int*>(deviceInputData), DATA_PACK_SIZE));
    CHECK_CUDA(cudaMemcpy(&inputData, deviceInputData, sizeof(dataPack), cudaMemcpyDeviceToHost));

    // Create events for timing
    cudaEvent_t start_gpu_total, stop_gpu_total, start_gpu, stop_gpu, start_cpu, stop_cpu;
    CHECK_CUDA(cudaEventCreate(&start_gpu_total));
    CHECK_CUDA(cudaEventCreate(&stop_gpu_total));
    CHECK_CUDA(cudaEventCreate(&start_gpu));
    CHECK_CUDA(cudaEventCreate(&stop_gpu));
    CHECK_CUDA(cudaEventCreate(&start_cpu));
    CHECK_CUDA(cudaEventCreate(&stop_cpu));

    // Total GPU computation including data transfer
    CHECK_CUDA(cudaEventRecord(start_gpu_total));

    // Copy data to device
    CHECK_CUDA(cudaMemcpy(deviceInputData, &inputData, sizeof(dataPack), cudaMemcpyHostToDevice));

    dim3 dimBlock(BLOCK_SIZE, BLOCK_SIZE);
    dim3 dimGrid(GRID_SIZE, GRID_SIZE);

    // GPU computation
    CHECK_CUDA(cudaEventRecord(start_gpu));
    processMatrix<Op> << <dimGrid, dimBlock >> > (deviceInputData, deviceResult);
    CHECK_CUDA(cudaGetLastError());
    CHECK_CUDA(cudaEventRecord(stop_gpu));

    data_t gpuResult;
    CHECK_CUDA(cudaMemcpy(&gpuResult, deviceResult, sizeof(data_t), cudaMemcpyDeviceToHost));

    // Stop total GPU timing
    CHECK_CUDA(cudaEventRecord(stop_gpu_total));

    // CPU computation
    CHECK_CUDA(cudaEventRecord(start_cpu));
    data_t cpuResult = processMatrixCPU<Op>(inputData);
    CHECK_CUDA(cudaEventRecord(stop_cpu));

    // Get timing results
    float gpu_milliseconds = 0;
    float gpu_total_milliseconds = 0;
    float cpu_milliseconds = 0;
    CHECK_CUDA(cudaEventSynchronize(stop_gpu));
    CHECK_CUDA(cudaEventSynchronize(stop_gpu_total));
    CHECK_CUDA(cudaEventSynchronize(stop_cpu));
    CHECK_CUDA(cudaEventElapsedTime(&gpu_milliseconds, start_gpu, stop_gpu));
    CHECK_CUDA(cudaEventElapsedTime(&gpu_total_milliseconds, start_gpu_total, stop_gpu_total));
    CHECK_CUDA(cudaEventElapsedTime(&cpu_milliseconds, start_cpu, stop_cpu));

    // Calculate speedups
    float speedup_excluding_data_transfer = cpu_milliseconds / gpu_milliseconds;
    float speedup_including_data_transfer = cpu_milliseconds / gpu_total_milliseconds;

    // Print results
    printf("\n=== Testing %s Operation ===\n", opName);
    printf("GPU Time (Excluding Data Transfer): %f ms\n", gpu_milliseconds);
    printf("GPU Time (Including Data Transfer): %f ms\n", gpu_total_milliseconds);
    printf("CPU Time: %f ms\n", cpu_milliseconds);
    printf("Speedup Excluding Data Transfer: %fx\n", speedup_excluding_data_transfer);
    printf("Speedup Including Data Transfer: %fx\n", speedup_including_data_transfer);
    printf("Result (GPU): %d\n", gpuResult);
    printf("Result (CPU): %d\n", cpuResult);
    printf("Results %s\n", (gpuResult == cpuResult) ? "match" : "don't match");
    printf("============================\n");

    // Cleanup
    CHECK_CUDA(cudaEventDestroy(start_gpu_total));
    CHECK_CUDA(cudaEventDestroy(stop_gpu_total));
    CHECK_CUDA(cudaEventDestroy(start_gpu));
    CHECK_CUDA(cudaEventDestroy(stop_gpu));
    CHECK_CUDA(cudaEventDestroy(start_cpu));
    CHECK_CUDA(cudaEventDestroy(stop_cpu));
    CHECK_CUDA(cudaFree(deviceInputData));
    CHECK_CUDA(cudaFree(deviceResult));
    CHECK_CURAND(curandDestroyGenerator(gen));
}

int main() {
    testReduction<ReductionOp::SUM>("SUM");
    testReduction<ReductionOp::XOR>("XOR");
    testReduction<ReductionOp::AND>("AND");
    testReduction<ReductionOp::OR>("OR");
    testReduction<ReductionOp::MIN>("MIN");
    testReduction<ReductionOp::MAX>("MAX");
    testReduction<ReductionOp::SUB>("SUB");

    return 0;
}
