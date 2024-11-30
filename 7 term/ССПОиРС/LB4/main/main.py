import socket
import numpy as np
import time
import threading

PORT = 65432

def receive_full(sock, size):
    """Функция для получения полного количества байтов"""
    data = b''
    while len(data) < size:
        packet = sock.recv(size - len(data))
        if not packet:
            raise ConnectionError("Connection lost")
        data += packet
    return data


def handle_multiplication(A_part, B_part, result_part):
    """Функция для выполнения умножения части матрицы"""
    print(f"Выполняется умножение на потоке {threading.current_thread().name}...")
    result_part[:] = np.dot(A_part, B_part)
    print(f"Поток {threading.current_thread().name} завершил умножение.")


def handle_multiplication_all(client_socket):
    # Получаем размеры матриц
    rows_a = int.from_bytes(client_socket.recv(4), byteorder='big')
    cols_a = int.from_bytes(client_socket.recv(4), byteorder='big')
    rows_b = int.from_bytes(client_socket.recv(4), byteorder='big')
    cols_b = int.from_bytes(client_socket.recv(4), byteorder='big')

    print(f"Получены размеры: A_part ({rows_a}x{cols_a}), B_part ({rows_b}x{cols_b})")

    # Получаем подматрицы A и B
    A_part = np.frombuffer(receive_full(client_socket, rows_a * cols_a * 8), dtype=np.float64).reshape((rows_a, cols_a))
    B_part = np.frombuffer(receive_full(client_socket, rows_b * cols_b * 8), dtype=np.float64).reshape((rows_b, cols_b))

    print("Подматрица A и матрица B получены.")

    # Создадим пустой массив для результата
    result_part = np.zeros((rows_a, cols_b), dtype=np.float64)

    # Начало времени вычислений
    start_time = time.time()

    # Создаем два потока, которые будут выполнять умножение
    thread1 = threading.Thread(target=handle_multiplication,
                               args=(A_part[:rows_a // 2, :], B_part, result_part[:rows_a // 2, :]), name="Thread-1")
    thread2 = threading.Thread(target=handle_multiplication,
                               args=(A_part[rows_a // 2:, :], B_part, result_part[rows_a // 2:, :]), name="Thread-2")

    thread3 = threading.Thread(target=handle_multiplication,
                               args=(A_part[:rows_a // 2, :], B_part, result_part[:rows_a // 2, :]), name="Thread-3")
    thread4 = threading.Thread(target=handle_multiplication,
                               args=(A_part[rows_a // 2:, :], B_part, result_part[rows_a // 2:, :]), name="Thread-4")

    # Запуск потоков
    thread1.start()
    thread2.start()
    thread3.start()
    thread4.start()

    # Ожидание завершения всех потоков
    thread1.join()
    thread2.join()
    thread3.join()
    thread4.join()

    # Конец времени вычислений
    end_time = time.time()

    # Результат отправляем обратно на сервер

    print(result_part)

    client_socket.sendall(result_part.tobytes())
    print(f"Результат отправлен обратно серверу. Время выполнения на клиенте: {end_time - start_time:.2f} секунд")


def main():
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as client_socket:
        client_socket.connect(('192.168.134.165', PORT))  # Подключение к серверу
        handle_multiplication_all(client_socket)


if __name__ == "__main__":
    main()
