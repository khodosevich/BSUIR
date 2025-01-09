#include <cuda_runtime.h>
#include "device_launch_parameters.h"
#include <chrono>
#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>

#define MASK_WIDTH 5
#define MASK_RADIUS (MASK_WIDTH / 2)
#define THREADS_PER_BLOCK 32

template <typename T>
T clamp(T val, T minVal, T maxVal) {
    return (val < minVal) ? minVal : (val > maxVal ? maxVal : val);
}

bool loadImage(const std::string& filename, int& width, int& height, std::vector<unsigned char>& data, bool& isGrayscale) {
    cv::Mat img = cv::imread(filename, cv::IMREAD_UNCHANGED);
    if (img.empty()) return false;

    isGrayscale = (img.channels() == 1);
    width = img.cols;
    height = img.rows;

    if (!isGrayscale) {
        cv::cvtColor(img, img, cv::COLOR_BGR2RGB);
    }

    data.assign(img.data, img.data + img.total() * img.elemSize());
    return true;
}

bool saveImage(const std::string& filename, int width, int height, const std::vector<unsigned char>& data, bool isGrayscale) {

    cv::Mat img(height, width, isGrayscale ? CV_8UC1 : CV_8UC3, const_cast<unsigned char*>(data.data()));
    if (!isGrayscale) {
        cv::cvtColor(img, img, cv::COLOR_RGB2BGR);
    }
    return cv::imwrite(filename, img);
}

void applyMinFilterCPU(const std::vector<unsigned char>& input, std::vector<unsigned char>& output, int width, int height) {
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            for (int c = 0; c < 3; ++c) {
                int min_val = 255;

                for (int dy = -MASK_RADIUS; dy <= MASK_RADIUS; ++dy) {
                    for (int dx = -MASK_RADIUS; dx <= MASK_RADIUS; ++dx) {
                        int ny = clamp(y + dy, 0, height - 1);
                        int nx = clamp(x + dx, 0, width - 1);
                        int pixel = input[(ny * width + nx) * 3 + c];
                        min_val = std::min(min_val, pixel);
                    }
                }

                output[(y * width + x) * 3 + c] = static_cast<unsigned char>(min_val);
            }
        }
    }
}

void applyMinFilterCPU_Grayscale(const std::vector<unsigned char>& input, std::vector<unsigned char>& output, int width, int height) {
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int min_val = 255;

            for (int dy = -MASK_RADIUS; dy <= MASK_RADIUS; ++dy) {
                for (int dx = -MASK_RADIUS; dx <= MASK_RADIUS; ++dx) {
                    int ny = clamp(y + dy, 0, height - 1);
                    int nx = clamp(x + dx, 0, width - 1);
                    int pixel = input[ny * width + nx];
                    min_val = std::min(min_val, pixel);
                }
            }

            output[y * width + x] = static_cast<unsigned char>(min_val);
        }
    }
}

__global__ void applyMinFilterCUDA(unsigned char* input, unsigned char* output, int width, int height) {
    int x = blockIdx.x * blockDim.x + threadIdx.x;
    int y = blockIdx.y * blockDim.y + threadIdx.y;

    if (x < width && y < height) {
        for (int c = 0; c < 3; ++c) {
            int min_val = 255;

            for (int dy = -MASK_RADIUS; dy <= MASK_RADIUS; ++dy) {
                for (int dx = -MASK_RADIUS; dx <= MASK_RADIUS; ++dx) {
                    int nx = min(max(x + dx, 0), width - 1);
                    int ny = min(max(y + dy, 0), height - 1);
                    int pixel = input[(ny * width + nx) * 3 + c];
                    min_val = min(min_val, pixel);
                }
            }

            output[(y * width + x) * 3 + c] = min_val;
        }
    }
}

__global__ void applyMinFilterCUDA_Grayscale(unsigned char* input, unsigned char* output, int width, int height) {
    int x = blockIdx.x * blockDim.x + threadIdx.x;
    int y = blockIdx.y * blockDim.y + threadIdx.y;

    if (x < width && y < height) {
        int min_val = 255;

        for (int dy = -MASK_RADIUS; dy <= MASK_RADIUS; ++dy) {
            for (int dx = -MASK_RADIUS; dx <= MASK_RADIUS; ++dx) {
                int nx = min(max(x + dx, 0), width - 1);
                int ny = min(max(y + dy, 0), height - 1);
                int pixel = input[ny * width + nx];
                min_val = min(min_val, pixel);
            }
        }

        output[y * width + x] = min_val;
    }
}

int main() {
    int width, height;
    bool isGrayscale;
    std::string path = "2.jpg";
    std::vector<unsigned char> image;

    if (!loadImage(path, width, height, image, isGrayscale)) {
        std::cerr << "Failed to load image!" << std::endl;
        return -1;
    }

    std::vector<unsigned char> outputCPU(image.size());
    std::vector<unsigned char> outputGPU(image.size());

    auto startCPU = std::chrono::high_resolution_clock::now();
    if (isGrayscale) {
        applyMinFilterCPU_Grayscale(image, outputCPU, width, height);
    }
    else {
        applyMinFilterCPU(image, outputCPU, width, height);
    }
    auto endCPU = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> durationCPU = endCPU - startCPU;
    std::cout << "CPU time: " << durationCPU.count() << " seconds\n";

    unsigned char* d_input, * d_output;
    cudaMalloc(&d_input, image.size());
    cudaMalloc(&d_output, image.size());

    auto startGPUcpy = std::chrono::high_resolution_clock::now();
    cudaMemcpy(d_input, image.data(), image.size(), cudaMemcpyHostToDevice);

    dim3 blockSize(THREADS_PER_BLOCK, THREADS_PER_BLOCK);
    dim3 gridSize((width + THREADS_PER_BLOCK - 1) / THREADS_PER_BLOCK, (height + THREADS_PER_BLOCK - 1) / THREADS_PER_BLOCK);

    auto startGPU = std::chrono::high_resolution_clock::now();
    if (isGrayscale) {
        applyMinFilterCUDA_Grayscale << <gridSize, blockSize >> > (d_input, d_output, width, height);
    }
    else {
        applyMinFilterCUDA << <gridSize, blockSize >> > (d_input, d_output, width, height);
    }
    cudaDeviceSynchronize();
    auto endGPU = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> durationGPU = endGPU - startGPU;
    std::cout << "GPU time: " << durationGPU.count() << " seconds\n";

    cudaMemcpy(outputGPU.data(), d_output, image.size(), cudaMemcpyDeviceToHost);

    auto endGPUcpy = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> durationGPUcpy = endGPUcpy - startGPUcpy;
    std::cout << "GPU memcpy time: " << durationGPUcpy.count() << " seconds\n";

    bool match = true;
    for (size_t i = 0; i < image.size(); ++i) {
        if (outputCPU[i] != outputGPU[i]) {
            match = false;
            std::cout << "Mismatch at pixel " << i << ": CPU = " << static_cast<int>(outputCPU[i]) << ", GPU = " << static_cast<int>(outputGPU[i]) << "\n";
            break;
        }
    }
    if (match) {
        std::cout << "CPU and GPU results match.\n";
    }
    else {
        std::cout << "CPU and GPU results do not match.\n";
    }

    saveImage("outputCPU.jpg", width, height, outputCPU, isGrayscale);
    saveImage("outputGPU.jpg", width, height, outputGPU, isGrayscale);

    cudaFree(d_input);
    cudaFree(d_output);

    return 0;
}
