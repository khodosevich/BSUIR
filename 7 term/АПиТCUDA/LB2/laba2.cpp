#include <iostream>
#include <chrono>
#include <intrin.h> 
#include <immintrin.h>  
#include <omp.h>
#include <string>
#include <cmath>


class Timer {
public:
    void start()
    {
        m_StartTime = std::chrono::high_resolution_clock::now();
        m_bRunning = true;
    }

    void stop()
    {
        m_EndTime = std::chrono::high_resolution_clock::now();
        m_bRunning = false;
    }

    double elapsedCycles() const {
        if (m_bRunning) {
            auto now = std::chrono::high_resolution_clock::now();
            return std::chrono::duration_cast<std::chrono::nanoseconds>(now - m_StartTime).count();
        }
        return std::chrono::duration_cast<std::chrono::nanoseconds>(m_EndTime - m_StartTime).count();
    }

    double elapsedSeconds() const {
        if (m_bRunning) {
            auto now = std::chrono::high_resolution_clock::now();
            return std::chrono::duration_cast<std::chrono::duration<double>>(now - m_StartTime).count();
        }
        return std::chrono::duration_cast<std::chrono::duration<double>>(m_EndTime - m_StartTime).count();
    }

private:
    std::chrono::high_resolution_clock::time_point m_StartTime;
    std::chrono::high_resolution_clock::time_point m_EndTime;
    bool m_bRunning = false;
};



bool isMultiplying(int C1, int R2) {
    return C1 == R2;
}

float** fillMatrix(float** matrix, int R, int C) {
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            matrix[i][j] = (float)(rand());
        }
    }

    return matrix;
}

template <typename T>
T** createMatrix(int R, int C) {
    T** matrix = new T * [R];
    bool isEmpty = false;
    for (int i = 0; i < R; i++) {
        matrix[i] = new T[C];

        if (!isEmpty) {
            for (int j = 0; j < C; j++) {
                matrix[i][j] = static_cast<T>(rand() / 10e3);
            }
        }
    }

    return matrix;
}

float** variant1(float** A, float** B, int R1, int R2, int C1, int C2, bool writeConsole = false) {
    Timer timer;

    float** result = createMatrix<float>(R1, C2);
    timer.start();

    for (int row = 0; row < R1; row++) {
        for (int col = 0; col < C2; col++) {
            for (int inner = 0; inner < C1; inner++) {
                result[row][col] += A[row][inner] * B[inner][col];
            }
        }
    }

    timer.stop();

    if (writeConsole)
        for (int row = 0; row < R1; ++row) {
            for (int col = 0; col < C2; ++col) {
                std::cout << result[row][col] << " ";
            }
            std::cout << "\n";
        }

    double elapsedTimeInCycles = timer.elapsedCycles();
    double elapsedTimeInSeconds = timer.elapsedSeconds();
    std::cout << "\nMatrix multiplication time: " << elapsedTimeInCycles << " nanoseconds (approx "
        << elapsedTimeInSeconds << " seconds).\n";

    return result;
}

float** variant2(float** A, float** B, int R1, int R2, int C1, int C2, int block_size, bool writeConsole = false) {
    Timer timer;

    float** result = createMatrix<float>(R1, C2);
    timer.start();

    for (int block_row = 0; block_row < R1; block_row += block_size) {
        for (int block_col = 0; block_col < C2; block_col += block_size) {
            for (int inner_block = 0; inner_block < C1; inner_block += block_size) {
                int block_row_end = std::min(block_row + block_size, R1);
                int block_col_end = std::min(block_col + block_size, C2);
                int inner_block_end = std::min(inner_block + block_size, C1);

                for (int i = block_row; i < block_row_end; i++) {
                    for (int j = block_col; j < block_col_end; j++) {
                        for (int k = inner_block; k < inner_block_end; k++) {
                            result[i][j] += A[i][k] * B[k][j];
                        }
                    }
                }
            }
        }
    }

    timer.stop();

    if (writeConsole)
        for (int row = 0; row < R1; ++row) {
            for (int col = 0; col < C2; ++col) {
                std::cout << result[row][col] << " ";
            }
            std::cout << "\n";
        }

    double elapsedTimeInCycles = timer.elapsedCycles();
    double elapsedTimeInSeconds = timer.elapsedSeconds();
    std::cout << "\nMatrix multiplication time: " << elapsedTimeInCycles << " nanoseconds (approx "
        << elapsedTimeInSeconds << " seconds).\n";

    return result;
}


double** avx_intrinsics(double** A, double** B, int R1, int R2, int C1, int C2, int block_size, bool writeConsole = false) {
    auto timer3 = new Timer();

    double** result = createMatrix<double>(R1, C2); 
    
    timer3->start();

    for (int block_row = 0; block_row < R1; block_row += block_size) {
        for (int inner_block = 0; inner_block < C1; inner_block += block_size) {
            for (int block_col = 0; block_col < C2; block_col += block_size) {
                int block_row_end = std::min(block_row + block_size, R1);
                int inner_block_end = std::min(inner_block + block_size, C1);
                int block_col_end = std::min(block_col + block_size, C2);

                for (int i = block_row; i < block_row_end; i++) {
                    for (int k = inner_block; k < inner_block_end; k++) {
                        __m256d a_vec = _mm256_set1_pd(A[i][k]); 

                        int j;
                        for (j = block_col; j <= block_col_end - 4; j += 4) {
                            __m256d b_vec = _mm256_loadu_pd(&B[k][j]);
                            __m256d c_vec = _mm256_loadu_pd(&result[i][j]);

                            __m256d res_vec = _mm256_add_pd(c_vec, _mm256_mul_pd(a_vec, b_vec));

                            _mm256_storeu_pd(&result[i][j], res_vec);
                        }

                        for (; j < block_col_end; ++j) {
                            result[i][j] += A[i][k] * B[k][j];
                        }
                    }
                }
            }
        }
    }

    timer3->stop();

    // Вывод матрицы в консоль
    if (writeConsole)
        for (int row = 0; row < R1; ++row) {
            for (int col = 0; col < C2; ++col) {
                std::cout << result[row][col] << " ";
            }
            std::cout << "\n";
        }

    double elapsedTimeInSeconds = timer3->elapsedCycles();
    std::cout << "\nMatrix multiplication time: " << timer3->elapsedCycles() << " cycles.\n";
    std::cout << "\nMatrix multiplication time: " << elapsedTimeInSeconds << " seconds.\n\n";

    return result;
}

double** avx_intrinsics_openMP(double** A, double** B, int R1, int R2, int C1, int C2, int block_size, bool writeConsole = false) {
    auto timer4 = new Timer();

    double** result = createMatrix<double>(R1, C2);  
    timer4->start();


    #pragma omp parallel num_threads(8) 
        {
    #pragma omp for 
            for (int block_row = 0; block_row < R1; block_row += block_size) {
                for (int inner_block = 0; inner_block < C1; inner_block += block_size) {
                    for (int block_col = 0; block_col < C2; block_col += block_size) {
                        int block_row_end = std::min(block_row + block_size, R1);
                        int inner_block_end = std::min(inner_block + block_size, C1);
                        int block_col_end = std::min(block_col + block_size, C2);
                        for (int i = block_row; i < block_row_end; i++) {
                            for (int k = inner_block; k < inner_block_end; k++) {
                                __m256d a_vec = _mm256_set1_pd(A[i][k]);  

                                int j;
                                for (j = block_col; j <= block_col_end - 4; j += 4) {
                                    __m256d b_vec = _mm256_loadu_pd(&B[k][j]);
                                    __m256d c_vec = _mm256_loadu_pd(&result[i][j]);

                                    __m256d res_vec = _mm256_add_pd(c_vec, _mm256_mul_pd(a_vec, b_vec));

                                    _mm256_storeu_pd(&result[i][j], res_vec);
                                }

                                for (; j < block_col_end; ++j) {
                                    result[i][j] += A[i][k] * B[k][j];
                                }
                            }
                        }
                    }
                }
            }
        }
    timer4->stop();


    // Вывод матрицы в консоль
    if (writeConsole)
        for (int row = 0; row < R1; ++row) {
            for (int col = 0; col < C2; ++col) {
                std::cout << result[row][col] << " ";
            }
            std::cout << "\n";
        }

    double elapsedTimeInSeconds = timer4->elapsedCycles();
    std::cout << "\nMatrix multiplication time: " << timer4->elapsedCycles() << " cycles.\n";
    std::cout << "\nMatrix multiplication time: " << elapsedTimeInSeconds << " seconds.\n\n";

    return result;
}

bool isMatrixCompare(float** A, float** B, int R, int C) {
    for (int row = 0; row < R; row++) {
        for (int col = 0; col < C; col++) {
            float res = fabs(A[row][col] - B[row][col]);
            if (res > 0.00001) {
                std::cout << "\nMatrix error: " << A[row][col] << "  " << B[row][col] << "\n\n\n";

                return false;
            }
            
        }
    }

    return true;
}



double** convertFloatMatrixToDouble(float** floatMatrix, int R, int C) {

    double** doubleMatrix = new double* [R];

    for (int i = 0; i < R; i++) {
        doubleMatrix[i] = new double[C];

        for (int j = 0; j < C; j++) {

            doubleMatrix[i][j] = static_cast<float>(floatMatrix[i][j]);
        }
    }

    return doubleMatrix;
}

float** convertDoubleMatrixToFloat(double** doubleMatrix, int R, int C) {

    float** floatMatrix = new float* [R];

    for (int i = 0; i < R; i++) {
        floatMatrix[i] = new float[C];

        for (int j = 0; j < C; j++) {

            floatMatrix[i][j] = static_cast<float>(doubleMatrix[i][j]);
        }
    }

    return floatMatrix;
}

int main() {
    srand(time(0));

    //1254*1254 максимальная матрица влезающая в 3кэш
    const int R1 = 2180;
    const int C1 = 2200;

    const int R2 = 2200;
    const int C2 = 2300;

    int L1 = 128; // 156 ячеек - тоесть 156*156*4 байта - 95 КБ.  L1 кеш - 320 КБ (320/3*0,9=96)
    int L2 = 384; // 396 ячеек - тоесть 396*396*4 байта - 612 КБ. L2 кеш - 2 МБ (2/3*0,9=0,6)
    int L3 = 640; // 686 ячеек - тоесть 686*686*4 байта - 1.79 МБ.  L3 кеш - 6 МБ (6*3*0,9=1,8)

    float** A = createMatrix<float>(R1, C1);
    A = fillMatrix(A, R1, C1);

    float** B = createMatrix<float>(R2, C2);
    B = fillMatrix(B, R2, C2);

    if (isMultiplying(C1, R2)) {
        float** one = variant1(A, B, R1, R2, C1, C2);
        //float** two = variant2(A, B, R1, R2, C1, C2, L1);

        //variant2(A, B, R1, R2, C1, C2, L2);
        //variant2(A, B, R1, R2, C1, C2, L3);

        double** Acopy = convertFloatMatrixToDouble(A, R1, C1);
        double** Bcopy = convertFloatMatrixToDouble(B, R2, C2);

        double** three = avx_intrinsics(Acopy, Bcopy, R1, R2, C1, C2, L1);

        double** four = avx_intrinsics_openMP(Acopy, Bcopy, R1, R2, C1, C2, L1);

        float** fourCopy = convertDoubleMatrixToFloat(four, R1, C2);

        bool equal = isMatrixCompare(one, fourCopy, R1, C2);

        std::cout << "\nIs matrix equal: " << equal << std::endl;
    }
    else {
        std::cout << "\nMatrix CAN'T be multiplying" << std::endl;
    }
}

