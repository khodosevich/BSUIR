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


def blocking_mode(client_socket, size):
    """Блокирующий режим: умножение матриц"""
    A = np.frombuffer(receive_full(client_socket, size * size * 8), dtype=np.float64).reshape((size, size))
    B = np.frombuffer(receive_full(client_socket, size * size * 8), dtype=np.float64).reshape((size, size))

    print("Матрицы A и B успешно получены.")

    start_time = time.time()
    result = np.dot(A, B)
    end_time = time.time()

    client_socket.sendall(result.tobytes())
    print("Результат отправлен.")
    print(f"Время выполнения в блокирующем режиме: {end_time - start_time:.2f} секунд")


def non_blocking_mode(client_socket, size):
    """Неблокирующий режим: умножение матриц в отдельном потоке"""
    A = np.frombuffer(receive_full(client_socket, size * size * 8), dtype=np.float64).reshape((size, size))
    B = np.frombuffer(receive_full(client_socket, size * size * 8), dtype=np.float64).reshape((size, size))

    print("Матрицы A и B успешно получены.")

    def multiply_and_send():
        start_time = time.time()
        result = np.dot(A, B)
        end_time = time.time()

        client_socket.sendall(result.tobytes())
        print("Результат отправлен.")
        print(f"Время выполнения в неблокирующем режиме: {end_time - start_time:.2f} секунд")

    thread = threading.Thread(target=multiply_and_send)
    thread.start()

    thread.join()


def main(mode='blocking'):
    """Главная функция клиента"""
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as client_socket:
        client_socket.connect(('192.168.197.165', PORT))  # подключаемся к серверу

        size = int.from_bytes(client_socket.recv(4), byteorder='big')
        print(f"Получен размер матриц: {size}")

        if mode == 'blocking':
            blocking_mode(client_socket, size)
        elif mode == 'non-blocking':
            non_blocking_mode(client_socket, size)
        else:
            print("Неправильный режим. Убедитесь, что вы используете 'blocking' или 'non-blocking'.")


if __name__ == '__main__':
    mode = input("Введите режим (blocking/non-blocking): ").strip()
    main(mode)

