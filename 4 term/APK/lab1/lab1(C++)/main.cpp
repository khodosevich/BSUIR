
#include <windows.h>
#include <iostream>
#include <string>

using namespace std;

int main()
{
    HANDLE COM_1;
    LPCTSTR Port_1 = L"COM7";
    HANDLE COM_2;
    LPCTSTR Port_2 = L"COM8";

    COM_1 = CreateFile(Port_1,
                       GENERIC_WRITE,
                       0,
                       0,
                       OPEN_EXISTING,
                       FILE_ATTRIBUTE_NORMAL,
                       0);


    if (COM_1 == INVALID_HANDLE_VALUE)
    {
        DWORD dw = GetLastError();
        cout << "Error opening com 1, error code: " << dw << endl;
        return 1;
    }

    COM_2 = CreateFile(Port_2,
                       GENERIC_READ,
                       0,
                       0,
                       OPEN_EXISTING,
                       FILE_ATTRIBUTE_NORMAL,
                       0);

    if (COM_2 == INVALID_HANDLE_VALUE)
    {
        DWORD dw = GetLastError();
        cout << "Error opening com 2, error code: " << dw << endl;
        return 1;
    }

    string messege = "Default messege";

    cout << "Enter the string to share" << endl;
    cin >> messege;

    DCB Serial_Params = { 0 };
    Serial_Params.DCBlength = sizeof(Serial_Params);
    if (!GetCommState(COM_1, &Serial_Params))
    {
        cout << "Getting state error.\n";
    }
    Serial_Params.BaudRate = CBR_9600;
    Serial_Params.ByteSize = 8;
    Serial_Params.StopBits = ONESTOPBIT;
    Serial_Params.Parity = NOPARITY;
    if (!SetCommState(COM_2, &Serial_Params))
    {
        cout << "Error setting serial port state.\n";
    }


    DWORD Size = sizeof(messege);
    DWORD Bytes_Written;

    BOOL Ret = WriteFile(COM_1, &messege, Size, &Bytes_Written, NULL);

    messege.clear();

    cout << Size << " Bytes in string. " << Bytes_Written << " Bytes sended. " << endl;

    if (ReadFile(COM_2, &messege, sizeof(messege), &Size, 0)) {
        cout << endl << "Data from COM2: '" << messege << "'";
    }


    return 0;
}

