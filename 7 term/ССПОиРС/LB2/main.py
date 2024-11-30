import socket
import sys
import threading

from utils import *

MULTICAST_GROUPS = ['239.255.0.1', '239.255.0.2', '239.255.0.3']
PORT = 5005
PING_PORT = 5006

ignoreList = set()
currentRoom = None

def ping():
    availableList = []
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM, socket.IPPROTO_UDP)
    sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    sock.bind(("", PING_PORT))

    sock.sendto("PING".encode(), (broadcast, PORT))
    try:
        sock.settimeout(3)
        while True:
            data, addr = sock.recvfrom(4)
            data = data.decode()

            if data == "PONG":
                availableList.append(addr[0])

    except socket.timeout:
        print("\n================")
        print("List of available hosts:")
        for host in availableList:
            print(f"{host}")
        print("================\n")

    finally:
        sock.settimeout(None)

def listener():
    try:
        sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM, socket.IPPROTO_UDP)
        sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        sock.bind(("", PORT))

        prevRoom = currentRoom
        
        while True:
            if prevRoom != currentRoom:
                if prevRoom != None:
                    dropGroup(sock, MULTICAST_GROUPS[prevRoom])
                if currentRoom != None:
                    setGroup(sock, MULTICAST_GROUPS[currentRoom])
                prevRoom = currentRoom

            sock.settimeout(0.1)
            try:
                data, addr = sock.recvfrom(1024)
                data = data.decode()
            except socket.timeout:
                continue
            finally:
                sock.settimeout(None)

            if data.startswith("PING"):
                sock.sendto("PONG".encode(), (addr[0], PING_PORT))
                continue

            if addr[0] in ignoreList:
                print(f"Ignored message from {addr[0]}")
                continue

            print(f"{addr}: {data}") 
            
    except KeyboardInterrupt:
        sys.exit(1)
    

def main():
    global currentRoom

    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM, socket.IPPROTO_UDP)
    sock.setsockopt(socket.IPPROTO_IP, socket.IP_MULTICAST_TTL, 1)

    while True:
        userInput = input("")

        if not userInput:
            continue

        if userInput.startswith("/"):
            command = userInput.split(maxsplit=1)

            match command[0]:
                case "/list":
                    pingChild = threading.Thread(target=ping, daemon=True)
                    pingChild.start()
                    pingChild.join()

                case "/ignore":
                    ignoreList.add(command[1])
                    print(f"Messages from {command[1]} will be ignored")

                case "/ignore-clear":
                    ignoreList.remove(command[1])
                    print(f"Messages from {command[1]} will be remove from ignore list")

                case "/broadcast":
                    sock.sendto(command[1].encode(), (broadcast, PORT))

                case "/room":
                    print(f"You have joined room #{int(command[1])}")
                    currentRoom = int(command[1]) - 1

                case "/leave":
                    print("You have left the room")
                    currentRoom = None

                case "/exit":
                    sys.exit(1)         
        else:
            try:
                sock.sendto(userInput.encode(), (MULTICAST_GROUPS[currentRoom], PORT))
            except (UnboundLocalError, TypeError):
                print("Please, choose any room")
        print()

if __name__ == "__main__":
    try:
        addr, networkAddr, mask, broadcast = getNetworkInfo()

        print("\n================")
        print("Info:")
        print(f"Address: {addr}")
        print(f"Network address: {networkAddr}")
        print(f"Network mask: {mask}")
        print(f"Broadcast address: {broadcast}")
        print("================")

        print("\n================")
        print("Commands:")
        print("/list")
        print("/ignore <addr>")
        print("/ignore-clear <addr>")
        print("/broadcast <msg>")
        print("/room <num, 1-3>")
        print("/leave")
        print("/exit")
        print("================\n")

        listenerChild = threading.Thread(target=listener, daemon=True)
        listenerChild.start()

        main()

    except KeyboardInterrupt:
        print("\nExiting gracefully")
        sys.exit(1)