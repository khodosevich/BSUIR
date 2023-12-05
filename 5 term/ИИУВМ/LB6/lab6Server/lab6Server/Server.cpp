#include <iostream>
#include <fstream>
#include <Winsock2.h>
#include <Ws2bth.h>
#include <BluetoothAPIs.h>
#include <locale.h>

#pragma comment(lib, "Ws2_32.lib")
#pragma comment(lib, "Bthprops.lib")
using namespace std;

int getFile(SOCKET clientSocket)
{
    char fileSize[20];
    memset(fileSize, '\0', 20);
    if (!recv(clientSocket, fileSize, 20, 0))
        return -1;
    int dataSize = atoi(fileSize);

    if (dataSize <= 0)
        return 0;

    cout << "��������� ����� " << endl;

    ofstream outputFile("�:/gettedFile.mp3", ios::out | ios::binary | ios::trunc); 
    while (dataSize > 0)
    {
        char buffer[1024];
        int bytes = recv(clientSocket, buffer, min(1024, dataSize), 0);
        outputFile.write(buffer, bytes);
        dataSize -= bytes;
    }
    outputFile.close();

    system("�:/gettedFile.mp3");

    return 0;
}

SOCKET initServerSocket()
{
    SOCKADDR_BTH sockaddrBthServer = { 0 };
    sockaddrBthServer.addressFamily = AF_BTH;
    sockaddrBthServer.serviceClassId = RFCOMM_PROTOCOL_UUID;
    sockaddrBthServer.port = 6;

    SOCKET serverSocket = socket(AF_BTH, SOCK_STREAM, BTHPROTO_RFCOMM);
    bind(serverSocket, reinterpret_cast<sockaddr*>(&sockaddrBthServer), sizeof(sockaddrBthServer));

    int addrLen = sizeof(sockaddrBthServer);
    getsockname(serverSocket, reinterpret_cast<sockaddr*>(&sockaddrBthServer), &addrLen);

    return serverSocket;
}

SOCKET initClientSocket(SOCKET serverSocket)
{
    SOCKADDR_BTH sockaddrBthClient = { 0 };
    int clientAddrSize = sizeof(sockaddrBthClient);
    SOCKET clientSocket = accept(serverSocket, reinterpret_cast<sockaddr*>(&sockaddrBthClient), &clientAddrSize);

    return clientSocket;
}

int main()
{
    setlocale(LC_ALL, "Russian");

    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    SOCKET serverSocket = initServerSocket();
    listen(serverSocket, SOMAXCONN);
    cout << "������ ����� ������" << endl;

    while (true)
    {
        cout << "�������� �����������" << endl;
        SOCKET clientSocket = initClientSocket(serverSocket);
        cout << "���������� �����������" << endl;

        while (true)
        {
            int result = getFile(clientSocket);
            if (result == -1)
                break;
        }

        cout << "������ �������� ����������" << endl << endl;
        closesocket(clientSocket);
    }

    cout << "������ ������� ������" << endl;
    closesocket(serverSocket);
    WSACleanup();

    return 0;
}