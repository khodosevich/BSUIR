#include <iostream>
#include <cuda_runtime.h>
#include <curand.h>
#include <curand_kernel.h>
#include <vector>
#include <chrono>

// Вспомогательная функция для проверки ошибок CUDA
void checkCudaError(cudaError_t err, const char* msg) {
    if (err != cudaSuccess) {
        std::cerr << "CUDA Error (" << msg << "): " << cudaGetErrorString(err) << std::endl;
        exit(EXIT_FAILURE);
    }
}

// Ядро CUDA для инициализации матрицы случайными значениями
__global__ void init_random_matrix(int* matrix, int rows, int cols, unsigned long long seed) {
    int idx = blockIdx.x * blockDim.x + threadIdx.x;
    int idy = blockIdx.y * blockDim.y + threadIdx.y;

    // Проверка границ массива
    if (idx < cols && idy < rows) {
        // Создание генератора CURAND
        curandState state;
        curand_init(seed, idy * cols + idx, 0, &state); // Инициализация генератора

        // Генерация случайного числа
        matrix[idy * cols + idx] = curand(&state) % 101; // Случайное значение от 0 до 100
    }
}

// Ядро CUDA для перестановки элементов с шагом N/2 и M/2
__global__ void rearrange_gpu(const int* matrix, int* result, int rows, int cols) {
    int half_rows = rows / 2;
    int half_cols = cols / 2;

    int i = (blockIdx.y * blockDim.y + threadIdx.y) * 2;
    int j = (blockIdx.x * blockDim.x + threadIdx.x) * 2;

    if (i + 1 < rows && j + 1 < cols) {
        // Перестановка элементов из блока 2x2
        result[(i / 2) * cols + (j / 2)] = matrix[i * cols + j];
        result[(i / 2) * cols + (j / 2 + half_cols)] = matrix[i * cols + j + 1];
        result[((i / 2) + half_rows) * cols + (j / 2)] = matrix[(i + 1) * cols + j];
        result[((i / 2) + half_rows) * cols + (j / 2 + half_cols)] = matrix[(i + 1) * cols + j + 1];
    }
}

// Функция для замера времени выполнения на CPU
void measure_cpu(const int* matrix, std::vector<int>& result, int rows, int cols) {
    auto start = std::chrono::high_resolution_clock::now();

    int half_rows = rows / 2;
    int half_cols = cols / 2;

    // Перестановка элементов с шагом N/2 и M/2 на CPU
    for (int i = 0; i < half_rows * 2; i += 2) {
        for (int j = 0; j < half_cols * 2; j += 2) {
            result[i / 2 * cols + j / 2] = matrix[i * cols + j];
            result[i / 2 * cols + (j / 2 + half_cols)] = matrix[i * cols + j + 1];
            result[(i / 2 + half_rows) * cols + j / 2] = matrix[(i + 1) * cols + j];
            result[(i / 2 + half_rows) * cols + (j / 2 + half_cols)] = matrix[(i + 1) * cols + j + 1];
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> duration = end - start;

    std::cout << "\nCPU Time: " << duration.count() * 1000 << " milliseconds" << std::endl; // вывод времени в миллисекундах
}

// Функция для замера времени выполнения на GPU
void measure_gpu(const int* d_matrix, int* d_result_matrix, int rows, int cols) {
    int threads_per_block = 32;
    dim3 threads(threads_per_block, threads_per_block);
    dim3 blocks((cols + threads_per_block * 2 - 1) / (threads_per_block * 2),
        (rows + threads_per_block * 2 - 1) / (threads_per_block * 2));

    cudaEvent_t start, stop;
    checkCudaError(cudaEventCreate(&start), "cudaEventCreate (start)");
    checkCudaError(cudaEventCreate(&stop), "cudaEventCreate (stop)");

    checkCudaError(cudaEventRecord(start), "cudaEventRecord (start)");

    // Запуск CUDA ядра
    rearrange_gpu << <blocks, threads >> > (d_matrix, d_result_matrix, rows, cols);
    checkCudaError(cudaGetLastError(), "Kernel execution"); // Проверка на ошибку ядра
    checkCudaError(cudaDeviceSynchronize(), "cudaDeviceSynchronize");

    checkCudaError(cudaEventRecord(stop), "cudaEventRecord (stop)");
    checkCudaError(cudaEventSynchronize(stop), "cudaEventSynchronize");

    float milliseconds = 0;
    checkCudaError(cudaEventElapsedTime(&milliseconds, start, stop), "cudaEventElapsedTime");
    std::cout << "\nGPU Time: " << milliseconds << " milliseconds" << std::endl; // вывод времени в миллисекундах

    checkCudaError(cudaEventDestroy(start), "cudaEventDestroy (start)");
    checkCudaError(cudaEventDestroy(stop), "cudaEventDestroy (stop)");
}

// Полное поэлементное сравнение матриц
bool compare_results(const std::vector<int>& cpu_matrix, const std::vector<int>& gpu_matrix, int rows, int cols) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (cpu_matrix[i * cols + j] != gpu_matrix[i * cols + j]) { // Проверка на равенство
                return false;
            }
        }
    }
    return true;
}

int main() {
    int rows = 5000, cols = 5000;
    size_t matrix_size = rows * cols * sizeof(int);

    int* d_matrix;
    int* d_matrix_res;
    checkCudaError(cudaMalloc(&d_matrix, matrix_size), "cudaMalloc (d_matrix)");
    checkCudaError(cudaMalloc(&d_matrix_res, matrix_size), "cudaMalloc (d_matrix_res)");

    // Инициализация матрицы случайными значениями на GPU
    dim3 threads(32, 32);
    dim3 blocks((cols + threads.x - 1) / threads.x, (rows + threads.y - 1) / threads.y);
    unsigned long long seed = 1234; // Уникальный сид для генерации случайных чисел
    init_random_matrix << <blocks, threads >> > (d_matrix, rows, cols, seed);
    checkCudaError(cudaGetLastError(), "Kernel execution for init_random_matrix");
    checkCudaError(cudaDeviceSynchronize(), "cudaDeviceSynchronize for init_random_matrix");

    // Копирование данных из GPU в CPU для последующей проверки
    std::vector<int> cpu_matrix(rows * cols);
    checkCudaError(cudaMemcpy(cpu_matrix.data(), d_matrix, matrix_size, cudaMemcpyDeviceToHost), "cudaMemcpy DeviceToHost");

    // Результат на CPU
    std::vector<int> cpu_result(rows * cols);
    measure_cpu(cpu_matrix.data(), cpu_result, rows, cols);

    // Запуск на GPU
    measure_gpu(d_matrix, d_matrix_res, rows, cols);

    // Получение результата с GPU
    std::vector<int> gpu_result(rows * cols);
    checkCudaError(cudaMemcpy(gpu_result.data(), d_matrix_res, matrix_size, cudaMemcpyDeviceToHost), "cudaMemcpy DeviceToHost");

    // Сравнение результатов
    if (compare_results(cpu_result, gpu_result, rows, cols)) {
        std::cout << "CPU and GPU results match!" << std::endl;
    }
    else {
        std::cout << "Results differ!" << std::endl;
    }

    std::cout << "\nPartial Matrix CPU:" << std::endl;
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            std::cout << cpu_result[i * cols + j] << " ";
        }
        std::cout << std::endl;
    }

    std::cout << "\nPartial Matrix GPU:" << std::endl;
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            std::cout << gpu_result[i * cols + j] << " ";
        }
        std::cout << std::endl;
    }

    // Освобождение памяти
    checkCudaError(cudaFree(d_matrix), "cudaFree (d_matrix)");
    checkCudaError(cudaFree(d_matrix_res), "cudaFree (d_matrix_res)");

    return 0;
}
