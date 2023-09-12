#include <iostream>
#include <windows.h>
#include <powrprof.h>
#include <winbase.h>
#include <batclass.h>
#include <cstdlib>
#include <windows.h>
#include <setupapi.h>
#include <devguid.h>

#pragma comment(lib, "setupapi.lib")
#pragma comment(lib, "Powrprof.lib")

using namespace std;

void printInfo() {
    cout << "1 - charging status" << endl;
    cout << "2 - battary status" << endl;
    cout << "3 - battary procent % " << endl;
    cout << "4 - status of battary" << endl;
    cout << "5 - sleeping mode" << endl;
    cout << "6 - hibernation" << endl;
    cout << "7 - the number of seconds of battery life remaining" << endl;
    cout << "8 - the number of seconds of battery life when at full charge" << endl;
    cout << "9 - update state" << endl;
    cout << "10 - battery type" << endl;
    cout << "0 - the end" << endl;
}

void chargingStatus(int state) {

    switch (state) {
    case 0:
        cout << "dont connect to charge" << endl;
        break;
    case 1:
        cout << "connect to charge" << endl;
        break;
    case 255:
        cout << "Unknown status" << endl;
        break;
    default:
        break;
    }
}
void battaryState(int battaryStatus) {

    switch (battaryStatus) {
    case 1:
        cout << "High the battery capacity is at more than 66 percent" << endl;
        break;
    case 2:
        cout << "Low the battery capacity is at less than 33 percent" << endl;
        break;
    case 4:
        cout << "Critical the battery capacity is at less than five percent" << endl;
        break;
    case 8:
    case 9:
        cout << "Charging" << endl;
        break;
    case 128:
        cout << "No system battery" << endl;
        break;
    case 255:
        cout << "Unknown status—unable to read the battery flag information" << endl;
        break;
    default:
        cout << "nothing" << endl;
        break;
    }
}
void battaryProcent(int procent) {
    if (procent != 255) {
        cout << "Battary is " << procent << " %" << endl;
    }
    else {
        cout << "Unknown this parametr" << endl;
    }
}
void statusOfBattary(int statusBattary) {

    switch (statusBattary) {
    case 0:
        cout << "Battery saver is off." << endl;
        break;
    case 1:
        cout << "Battery saver on." << endl;
        break;
    default:
        break;
    }
}

void displayInformationAboutBatteryType() {

    HDEVINFO hdev =
        SetupDiGetClassDevs(&GUID_DEVCLASS_BATTERY,
            0,
            0,
            DIGCF_PRESENT | DIGCF_DEVICEINTERFACE);
    if (INVALID_HANDLE_VALUE == hdev)
    {
        cout << "INVALID_HANDLE_VALUE";
        return;
    }

    SP_DEVICE_INTERFACE_DATA did = { 0 };
    did.cbSize = sizeof(did);
    if (!SetupDiEnumDeviceInterfaces(hdev,
        0,
        &GUID_DEVCLASS_BATTERY,
        0,
        &did))
    {
        cout << "unknown error 1";
        return;
    }
    DWORD cbRequired = 0;
    SetupDiGetDeviceInterfaceDetail(hdev,
        &did,
        0,
        0,
        &cbRequired,
        0);
    if (ERROR_INSUFFICIENT_BUFFER != GetLastError())
    {
        cout << "ERROR_INSUFFICIENT_BUFFER";
        SetupDiDestroyDeviceInfoList(hdev);
        return;
    }
    PSP_DEVICE_INTERFACE_DETAIL_DATA pdidd =
        (PSP_DEVICE_INTERFACE_DETAIL_DATA)LocalAlloc(LPTR,
            cbRequired);
    if (!pdidd)
    {
        cout << "unknown error 3";
        SetupDiDestroyDeviceInfoList(hdev);
        return;
    }
    pdidd->cbSize = sizeof(*pdidd);
    if (!SetupDiGetDeviceInterfaceDetail(hdev,
        &did,
        pdidd,
        cbRequired,
        &cbRequired,
        0))
    {
        cout << "unknown error 4";
        return;
    }
    HANDLE hBattery =
        CreateFile(pdidd->DevicePath,
            GENERIC_READ | GENERIC_WRITE,
            FILE_SHARE_READ | FILE_SHARE_WRITE,
            NULL,
            OPEN_EXISTING,
            FILE_ATTRIBUTE_NORMAL,
            NULL);
    if (INVALID_HANDLE_VALUE == hBattery)
    {
        cout << "ERROR_INSUFFICIENT_BUFFER";
        LocalFree(pdidd);
        SetupDiDestroyDeviceInfoList(hdev);
        return;
    }

    BATTERY_QUERY_INFORMATION bqi ={ 0 };
    DWORD dwWait = 0;
    DWORD dwOut;

    if (!DeviceIoControl(hBattery,
        IOCTL_BATTERY_QUERY_TAG,
        &dwWait,
        sizeof(dwWait),
        &bqi.BatteryTag,
        sizeof(bqi.BatteryTag),
        &dwOut,
        NULL)
        && bqi.BatteryTag)
    {
        cout << "unknown error 5";
        CloseHandle(hBattery);
        LocalFree(pdidd);
        SetupDiDestroyDeviceInfoList(hdev);
        return;
    }

    BATTERY_INFORMATION bi = { 0 };
    bqi.InformationLevel = BatteryInformation;

    if (!DeviceIoControl(hBattery,
        IOCTL_BATTERY_QUERY_INFORMATION,
        &bqi,
        sizeof(bqi),
        &bi,
        sizeof(bi),
        &dwOut,
        NULL))
    {
        cout << "unknown error 6";
        CloseHandle(hBattery);
        LocalFree(pdidd);
        SetupDiDestroyDeviceInfoList(hdev);
        return;
    }

    cout << "Type of battary: " << bi.Chemistry;
    CloseHandle(hBattery);
    LocalFree(pdidd);
    SetupDiDestroyDeviceInfoList(hdev);
    return;
}


SYSTEM_POWER_STATUS getState(SYSTEM_POWER_STATUS &computer) {


    if (!GetSystemPowerStatus(&computer)) {
        cout << "truble with getting data from powrprof" << endl;
        exit(1);
    }

    return computer;

}

int main()
{
    SYSTEM_POWER_STATUS computer {};


    computer = getState(computer);


    cout << endl;
    cout << "\t";
    battaryProcent(computer.BatteryLifePercent);
    cout << "\t";
    chargingStatus(computer.ACLineStatus);
    cout << "\t";
    battaryState(computer.BatteryFlag);
    cout << "\t";
    statusOfBattary(computer.SystemStatusFlag);
    cout << endl;

    int work = 1000;
    while (1)
    {
        printInfo();

        cout << "\nchoose a operation: ";
        cin >> work;

        switch (work)
        {
        case 1:
            chargingStatus(computer.ACLineStatus);
            break;
        case 2:
            battaryState(computer.BatteryFlag);
            break;
        case 3:
            battaryProcent(computer.BatteryLifePercent);
            break;
        case 4:
            statusOfBattary(computer.SystemStatusFlag);
            break;
        case 5: {
            SetSuspendState(FALSE, FALSE, FALSE);
            break;
        }
        case 6:
            SetSuspendState(TRUE, FALSE, FALSE);
            break;
        case 7: {
            cout << "hours until the end of work: " << (double)computer.BatteryLifeTime / 60 / 60 << endl;
            break;
        }
        case 8: {
            cout << "the number of days of battery life when at full charge: " << (double)computer.BatteryFullLifeTime / 60 / 60 /24 << endl;
            break;
        }
        case 9: {
            cout << "update" << endl;
            computer = getState(computer);
        }
        case 10:
            displayInformationAboutBatteryType();
            break;
        default:
            break;
        }

        if (work == 0) {
            break;
        }
    }
}

