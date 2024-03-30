import socket
import asyncio
import os

server_address = ("192.168.83.107", 12345)
client_number = "1"


def resume_data_transfer(connection, response):
    response_parts = response.split(' ', 1)
    cmd = response_parts[0]

    if cmd == "RESUME_DOWNLOAD":
        filename = response_parts[1]
        # получаем размер файла от сервера
        resp = connection.recv(1024).decode("utf-8")
        filesize = int(resp[9:])
        # передаем серверу позицию в файле
        last_data = os.path.getsize(filename)
        # передаём урезанный размер файла и флаг дозаписи
        download_file(connection, filename, filesize-last_data, resume=True)
        print("> Файл успешно скачан с сервера.")

    if cmd == "RESUME_UPLOAD":
        # получаем имя файла который нужно дозаписать
        filename = response_parts[1]
        filesize = os.path.getsize(filename)
        size = str(filesize)
        connection.sendall(("FILESIZE " + size).encode("utf-8"))
        upload_file(connection, filename, resume=True)
        response = connection.recv(1024).decode("utf-8")
        print("> Файл успешно загружен на сервер.")


def download_file(client_socket, filename, filesize, resume=False):
    try:
        file = open(filename, "ab" if resume else "wb")
        received_data = 0
        while filesize-received_data >= 1024:
            data = client_socket.recv(1024)
            if not data:
                break
            received_data += len(data)
            file.write(data)
            percent_complete = (received_data/filesize)*100
            print(f"\r> Прогресс загрузки: {percent_complete:.2f}%", end="")
        if received_data < filesize:  # отделяем последнюю порцию, чтобы не захватить лишние данные
            extra_data = filesize-received_data
            data = client_socket.recv(extra_data)
            file.write(data)
            file.close()
            print(f"\r> Прогресс загрузки: 100.00%\n")
    except Exception as e:
        print(f"> Ошибка при загрузке файла {str(e)}")


def upload_file(connection, filename, resume=False):
    print(filename)
    try:
        if not resume:
            with open(filename, 'rb') as file:
                while True:
                    data = file.read(1024)
                    if not data:
                        break
                    connection.sendall(data)

        else:
            with open(filename, 'rb') as file:
                file.seek(int(connection.recv(1024).decode("utf-8")))
                while True:
                    data = file.read(1024)
                    if not data:
                        break
                    connection.send(data)
        return "Файл успешно отправлен"

    except Exception as e:
        return f"Ошибка при отправке файла: {str(e)}"


def main():

    response = ""
    connected = False

    try:
        print("> ", end="")
        while True:

            user_input = input()

            if user_input == "CONNECT":
                if not connected:
                    try:
                        client_socket = socket.socket(
                            socket.AF_INET, socket.SOCK_STREAM)
                        client_socket.connect(server_address)
                        connected = True

                        # отправляем номер клиента
                        client_socket.sendall(
                            ("CLIENT " + client_number).encode("utf-8"))
                        # получаем ответ о том, было ли разорвано соединение
                        response = client_socket.recv(1024).decode("utf-8")

                        if response == "OK":
                            # если это новый клиент/не было разрыва
                            print(
                                f"> Успешно подключено к серверу {server_address}.")

                        if response.startswith("RESUME"):
                            # если не была закончена передача данных
                            print(f"> Продолжение передачи данных...")
                            resume_data_transfer(client_socket, response)

                    except ConnectionRefusedError:
                        print(f"> В соединении отказано.")
                else:
                    print(f"> Уже подключен к серверу.")

            elif user_input.startswith("DOWNLOAD ") and connected:
                f_name_to_download = user_input[9:]
                # если файл с таким названием существует у клиента
                if os.path.exists(f_name_to_download):
                    # отправляем серверу команду с именем файла
                    client_socket.sendall(
                        ("DOWNLOAD_RESUME " + f_name_to_download).encode("utf-8"))
                    response = client_socket.recv(1024).decode(
                        "utf-8")  # получаем от сервера размер
                    print(">", response, "\n> ", end="")
                    filesize = int(response[9:])
                    last_data = os.path.getsize(f_name_to_download)
                    download_file(client_socket, f_name_to_download,
                                  filesize-last_data, resume=True,)
                else:
                    client_socket.sendall(
                        ("DOWNLOAD " + f_name_to_download).encode("utf-8"))
                    response = client_socket.recv(1024).decode("utf-8")
                    print(">", response, "\n> ", end="")
                    filesize = int(response[9:])
                    download_file(client_socket, f_name_to_download, filesize)
                response = client_socket.recv(1024).decode("utf-8")

            elif user_input.startswith("UPLOAD ") and connected:
                f_name_to_upload = user_input[7:]
                if os.path.exists(f_name_to_upload):
                    filesize = os.path.getsize(f_name_to_upload)
                    size = str(filesize)
                    client_socket.sendall(
                        (user_input + ' ' + size).encode("utf-8)"))
                    upload_file(client_socket, f_name_to_upload)
                    response = client_socket.recv(1024).decode("utf-8")
                else:
                    print(f"> Файл с таким именем не существует.")

            elif user_input == "CLOSE" and connected:
                client_socket.sendall(user_input.encode("utf-8"))
                client_socket.close()
                connected = False
                print(f"> Cоединение закрыто.")

            elif user_input == "Q":
                break

            else:
                if connected:
                    client_socket.sendall(user_input.encode("utf-8"))
                    response = client_socket.recv(1024).decode("utf-8")

            print("> ", response, "\n> ", end="")

    finally:
        client_socket.close()


if __name__ == "__main__":
    main()
