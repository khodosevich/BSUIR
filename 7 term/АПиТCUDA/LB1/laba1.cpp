#include <iostream>
#include <chrono>
#include <intrin.h> 


class Timer {
public:
    void start()
    {
        m_StartTime = __rdtsc();
        m_bRunning = true;
    }

    void stop()
    {
        m_EndTime = __rdtsc();
        m_bRunning = false;
    }

    unsigned long long elapsedCycles() const {
        if (m_bRunning) {
            return __rdtsc() - m_StartTime;
        }
        return m_EndTime - m_StartTime;
    }

private:
    unsigned long long m_StartTime = 0;  
    unsigned long long m_EndTime = 0;
    bool m_bRunning = false;
};


bool isMultiplying(int C1, int R2) {
    return C1 == R2;
}

int** fillMatrix(int** matrix, int R, int C) {
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            matrix[i][j] = (int)(rand());
        }
    }

    return matrix;
}

int** createMatrix(int R, int C) {
    int** matrix = new int* [R];

    for (int i = 0; i < R; i++) {
        matrix[i] = new int[C];
    }

    for (int i = 0; i < R; ++i) {
        for (int j = 0; j < C; ++j) {
            matrix[i][j] = 0;
        }
    }

    return matrix;
}

int** variant1(int** A, int** B, int R1, int R2, int C1, int C2, bool writeConsole = false) {
    auto timer = new Timer();


    int** result = createMatrix(R1, C2);
    timer->start();


    for (int row = 0; row < R1; row++) {
        for (int col = 0; col < C2; col++) {
            for (int inner = 0; inner < C1; inner++) {
                result[row][col] += A[row][inner] * B[inner][col];
            }
        }
    }

    timer->stop();

    if (writeConsole)
        for (int row = 0; row < R1; ++row) {
            for (int col = 0; col < C2; ++col) {
                std::cout << result[row][col] << " ";
            }
            std::cout << "\n";
        }

    double elapsedTimeInSeconds = static_cast<double>(timer->elapsedCycles()) / (1.19 * 1e9);
    std::cout << "\nMatrix multiplication time: " << timer->elapsedCycles() << " cycles.\n";
    std::cout << "\nMatrix multiplication time: " << elapsedTimeInSeconds << " seconds.\n\n";


    return result;
}

int** variant2(int** A, int** B, int R1, int R2, int C1, int C2, int block_size, bool writeConsole = false) {
    auto timer2 = new Timer();

    
    int** result = createMatrix(R1, C2);
    timer2->start();


    // Итерируемся по блокам
    for (int block_row = 0; block_row < R1; block_row += block_size) {
        for (int block_col = 0; block_col < C2; block_col += block_size) {
            for (int inner_block = 0; inner_block < C1; inner_block += block_size) {
                // Высчитываем размер текущего блока
                int block_row_end = std::min(block_row + block_size, R1);
                int block_col_end = std::min(block_col + block_size, C2);
                int inner_block_end = std::min(inner_block + block_size, C1);

                // Перемножаем блоки
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

    timer2->stop();

    if (writeConsole)
        for (int row = 0; row < R1; ++row) {
            for (int col = 0; col < C2; ++col) {
                std::cout << result[row][col] << " ";
            }
            std::cout << "\n";
        }
    double elapsedTimeInSeconds = static_cast<double>(timer2->elapsedCycles()) / (1.19 * 1e9);
    std::cout << "\nMatrix multiplication time: " << timer2->elapsedCycles() << " cycles.\n";
    std::cout << "\nMatrix multiplication time: " << elapsedTimeInSeconds << " seconds.\n\n";


    return result;
}

bool isMatrixCompare(int** A, int** B, int R, int C) {
    for (int row = 0; row < R; row++) {
        for (int col = 0; col < C; col++) {
            if (A[row][col] != B[row][col]) {
                std::cout << "\nMatrix error: " << A[row][col] << "  " << B[row][col] << "\n\n\n";

                return false;
            }
        }
    }

    return true;
}



void MultiplyWithOutAMP() {
    //1254*1254 максимальная матрица влезающая в 3кэш
    const int R1 = 2180;
    const int C1 = 2200;

    const int R2 = 2200;
    const int C2 = 2300;

    int L1 = 128; // 156 ячеек - тоесть 156*156*4 байта - 95 КБ.  L1 кеш - 320 КБ (320/3*0,9=96)
    int L2 = 384; // 396 ячеек - тоесть 396*396*4 байта - 612 КБ. L2 кеш - 2 МБ (2/3*0,9=0,6)
    int L3 = 640; // 686 ячеек - тоесть 686*686*4 байта - 1.79 МБ.  L3 кеш - 6 МБ (6*3*0,9=1,8)

    //int block_size = (int)((L3 / 3) * 0.9);
    //std::cout << "\nBlock size " << block_size << std::endl << std::endl;

    int** A = createMatrix(R1, C1);
    A = fillMatrix(A, R1, C1);

    int** B = createMatrix(R2, C2);
    B = fillMatrix(B, R2, C2);

    if (isMultiplying(C1, R2)) {
        int** one = variant1(A, B, R1, R2, C1, C2);
        int** two = variant2(A, B, R1, R2, C1, C2, L1);

        variant2(A, B, R1, R2, C1, C2, L2);
        variant2(A, B, R1, R2, C1, C2, L3);

        bool equal = isMatrixCompare(one, two, R1, C2);

        std::cout << "\nIs matrix equal: " << equal << std::endl;
    }
    else {
        std::cout << "\nMatrix CAN'T be multiplying" << std::endl;
    }
}

int main() {
    MultiplyWithOutAMP();
}

