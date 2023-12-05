#include <iostream>
#include <fstream>
#include <vector>
#include <Winsock2.h>
#include <Ws2bth.h>
#include <BluetoothAPIs.h>
#include <conio.h>
#include <map>
#include <sstream>
#include <iomanip>
#include <filesystem>
#include <stdlib.h>

#pragma comment(lib, "Ws2_32.lib")
#pragma comment(lib, "Bthprops.lib")
using namespace std;
namespace fs = std::filesystem;
vector<BLUETOOTH_DEVICE_INFO> devices;
vector<pair<string,string>> file_names;

bool flag = false;
SOCKET clientSocket;

void menu() {
    cout << "\n\t\t\t================== Menu ==================\n";
    cout << "\n\t\t\t[p] - Вывод доступных устройств";
    cout << "\n\t\t\t[s] - connect + send";
    cout << "\n\t\t\t[e] - Конец программы\n";
    cout << "\n\t\t\t==========================================\n\n";
}

void printMusicFromDir(const std::wstring& folder_path) {
    
    for (const auto& entry : fs::directory_iterator(folder_path)) {
        pair<string, string> files("","");
        files.first = entry.path().filename().string();

        files.second = entry.path().string();
        file_names.push_back(files);
    }
}

void findBluetoothDevices() {
    devices.clear();
    BLUETOOTH_DEVICE_SEARCH_PARAMS searchParams = { sizeof(BLUETOOTH_DEVICE_SEARCH_PARAMS) };
    searchParams.dwSize = sizeof(BLUETOOTH_DEVICE_SEARCH_PARAMS);
    searchParams.fReturnAuthenticated = TRUE;
    searchParams.fReturnConnected = TRUE;
    searchParams.fReturnRemembered = TRUE;
    searchParams.fReturnUnknown = TRUE;
    searchParams.cTimeoutMultiplier = 8;

    BLUETOOTH_DEVICE_INFO deviceInfo = { sizeof(BLUETOOTH_DEVICE_INFO), 0 };

    HBLUETOOTH_DEVICE_FIND hFind;
    hFind = BluetoothFindFirstDevice(&searchParams, &deviceInfo);

    if (hFind == NULL) {
        cerr << "Устройства не найдены. Проверьте, что блютуз включен на устройстве" << endl;
        return;
    }

    do 
    {
        devices.push_back(deviceInfo);
    } while (BluetoothFindNextDevice(hFind, &deviceInfo));

    BluetoothFindDeviceClose(hFind);
}

void printDevices() {

    findBluetoothDevices();
    for (int i = 0; i < devices.size(); i++){
        wcout << std::left;
        wcout << i << ". " << devices[i].szName << " - " << devices[i].Address.ullLong << endl;
    }
}

void printMusic() {
    file_names.clear();

    wstring path = L".\\files";
    printMusicFromDir(path);
    int i = 0;
    for (const auto& file_name : file_names) {
        cout <<i++ <<". " << file_name.first << endl;
    }
}

int sendFile() {

   int temp = 0;

    while (true)
    {
        std::cout << endl;
        printMusic();
        int pickFile;

        std::cout << "Выберите файл для отправки: ";
        std::cin >> pickFile;

        std::cout << endl;
        string pathToFile = file_names[pickFile].second;

        std::ifstream fileToSend(pathToFile, std::ios::binary);

        int begin = fileToSend.tellg();
        fileToSend.seekg(0, ios::end);
        int end = fileToSend.tellg();
        int fsize = (end - begin);
        char file_size[100];
        _itoa_s(fsize, file_size, 10);

        send(clientSocket, file_size, 100, 0);
        fsize = 0;
        fileToSend.seekg(0);
        char buffer[1024];
        while (!fileToSend.eof()) {
            fileToSend.read(buffer, sizeof(buffer));
            int bytes = send(clientSocket, buffer, sizeof(buffer), 0);
            if (bytes == -1) {
                cerr << "Error writing to socket!";
                return 0;
            }
        }
        fileToSend.close();

        std::cout << "Продолжить? 1 - yes, 0 - no : ";
        std::cin >> temp;
        if (temp == 0) break;

    }
}



void initSocketToSend() {

    cout << "Введите номер устройства: " << endl;
    int choice;
    cin >> choice;
    BLUETOOTH_DEVICE_INFO deviceInfo = devices.at(choice);
    BTH_ADDR addr = deviceInfo.Address.ullLong;

    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        cerr << "Failed to initialize Winsock!" << endl;
        exit(1);
    }

    SOCKADDR_BTH sockaddrBthServer = { 0 }; 
    sockaddrBthServer.addressFamily = AF_BTH;
    sockaddrBthServer.serviceClassId = RFCOMM_PROTOCOL_UUID; 
    sockaddrBthServer.port = 4;
    sockaddrBthServer.btAddr = addr;


    clientSocket = socket(AF_BTH, SOCK_STREAM, BTHPROTO_RFCOMM);
    if (clientSocket == INVALID_SOCKET) {
        cerr << "Error creating client socket!" << endl;
        WSACleanup();
        exit(1);
    }


    if (connect(clientSocket, reinterpret_cast<sockaddr*>(&sockaddrBthServer), sizeof(sockaddrBthServer)) == SOCKET_ERROR) {
        cerr << "Error connecting to the server!" << endl;
        closesocket(clientSocket);
        WSACleanup();
        exit(1);
    }
    wcout << L"Подключено к серверу." << endl;

    flag = false;

    cout << endl;
    sendFile();

    closesocket(clientSocket);
    WSACleanup();
}


int main() {

    setlocale(LC_ALL, "Russian");
    char i = 0;
   
    menu();

    while (true) {

        cin >> i;
        getchar();
       

        switch (i)
        {
        case 'p':
        {
            system("cls");
            menu();
            cout << endl;
            printDevices();
            cout << endl;
            break;
        }
        case 's':
        {
            system("cls");
            menu();
            cout << endl;
            printDevices();
            initSocketToSend();
            cout << endl;
            break;
        }
        case 'e':
        {
            system("cls");
            devices.clear();
            file_names.clear();
            flag = true;
            exit(0);
            break;
        }
        default:
            break;
        }

    }
    return 0;
}
