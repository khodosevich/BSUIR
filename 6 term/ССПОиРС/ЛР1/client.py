import socket
import os


def send_command(sock, command):
    sock.sendall(command.encode())
    response = sock.recv(1024).decode()
    print(response)


def receive_file(sock, file_name):
    with open(file_name, 'wb') as file:
        while True:
            data = sock.recv(1024)
            if not data:
                break
            file.write(data)
    print(f"File '{file_name}' received from the server")


def send_file(sock, file_path):
    file_name = os.path.basename(file_path)
    with open(file_path, 'rb') as file:
        sock.sendall(file_name.encode())
        while True:
            data = file.read(1024)
            if not data:
                break
            sock.sendall(data)
    print(f"File '{file_name}' sent to the server")


HOST = '127.0.0.1'
PORT = 3000

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as client_socket:
    client_socket.connect((HOST, PORT))
    print("Connected to the server")

    while True:
        command = input("Enter a command (UPLOAD, DOWNLOAD, ECHO, TIME, CLOSE): ").strip().upper()

        if command == 'CLOSE':
            send_command(client_socket, command)
            break
        elif command == 'UPLOAD':
            file_path = input("Enter the path of the file to upload: ").strip()
            if os.path.exists(file_path):
                send_command(client_socket, command)
                send_file(client_socket, file_path)
            else:
                print("File does not exist.")
        elif command == 'DOWNLOAD':
            file_name = input("Enter the name of the file to download: ").strip()
            send_command(client_socket, f"{command} {file_name}")
            receive_file(client_socket, file_name)
        else:
            send_command(client_socket, command)
