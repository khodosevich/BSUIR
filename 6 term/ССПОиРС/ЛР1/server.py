import socket
import os
import time

start_time = time.time()

UPLOADS_DIR = 'uploads'


def handle_command(comm, client_socket):
    global start_time
    global UPLOADS_DIR

    if comm.startswith("ECHO"):
        return comm[5:] + '\n'
    elif comm.startswith("TIME"):
        uptime_seconds = int(time.time() - start_time)
        uptime_str = time.strftime('%H:%M:%S', time.gmtime(uptime_seconds))
        return "Server uptime: {}\n".format(uptime_str)
    elif comm.startswith("CLOSE") or comm.startswith("EXIT") or comm.startswith("QUIT"):
        return "Closing connection\n"
    elif comm.startswith("UPLOAD"):
        file_name = comm.split()[1]
        file_path = os.path.join(UPLOADS_DIR, file_name)

        with open(file_path, 'wb') as file:
            while True:
                data = client_socket.recv(1024)
                if not data:
                    break
                file.write(data)

        return f"File '{file_name}' uploaded successfully\n"
    elif comm.startswith("DOWNLOAD"):
        file_name = comm.split()[1]
        file_path = os.path.join(UPLOADS_DIR, file_name)

        if os.path.exists(file_path):
            with open(file_path, 'rb') as file:
                for data in file:
                    client_socket.sendall(data)
            return f"File '{file_name}' sent to the client\n"
        else:
            return "File not found on the server\n"
    else:
        return "Unknown command\n"


server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_address = ('', 3000)
server_socket.bind(server_address)
server_socket.listen(1)


if not os.path.exists(UPLOADS_DIR):
    os.makedirs(UPLOADS_DIR)

print("Waiting for a connection...\n")

try:
    while True:
        client_socket, client_address = server_socket.accept()
        print("Connection from:", client_address)

        while True:
            try:
                data = client_socket.recv(1024)
                if not data:
                    break

                command = data.decode().strip()
                response = handle_command(command, client_socket)

                client_socket.sendall(response.encode())

                if command.startswith("CLOSE") or command.startswith("EXIT") or command.startswith("QUIT"):
                    break
            except ConnectionResetError:
                print("Connection reset by peer")
                break
        client_socket.close()

except KeyboardInterrupt:
    print("Server interrupted. Closing...")
finally:
    server_socket.close()
