#include <format>
#include <mutex>
#include <thread>
#include <windows.h>
#include <cstdio>
#include <iostream>
#include <setupapi.h>
#include <devguid.h>
#include <direct.h>
#include <conio.h>
#include <opencv2\opencv.hpp>
#include <ctime>
#pragma comment(lib, "setupapi.lib")

using namespace cv;
using namespace std;

#define EXT_KEY VK_MENU
#define CAPTURE 0x43
#define EXIT 0x51
#define INFO 0x58

mutex cap_mutex;

string randomStr() {
	
	SYSTEMTIME time;
	GetSystemTime(&time);

	std::string result = std::to_string(time.wDay) + "-" +
		std::to_string(time.wMonth) + "-" +
		std::to_string(time.wYear)  + "-" +
		std::to_string(time.wHour) + "-" +
		std::to_string(time.wMinute) + "-" +
		std::to_string(time.wSecond) + "-";

	return 	result;
}

void capture()
{
	Mat frame;

	cap_mutex.lock();

	try
	{
		VideoCapture cap(0);

		if (cap.isOpened())
		{
			cap.set(CAP_PROP_FRAME_WIDTH, 1280);
			cap.set(CAP_PROP_FRAME_HEIGHT, 720);

			cap.read(frame);


		}
	}
	catch (...) {}

	cap_mutex.unlock();

	if (!frame.empty())
	{
		string random = randomStr();

		cv::String fileName = random + "image.png";

		imwrite(fileName, frame);
	}
}


void printCameraInfo()
{
	SP_DEVINFO_DATA DeviceInfoData;
	ZeroMemory(&DeviceInfoData, sizeof(SP_DEVINFO_DATA));
	DeviceInfoData.cbSize = sizeof(SP_DEVINFO_DATA);
	HDEVINFO DeviceInfoSet = SetupDiGetClassDevs(&GUID_DEVCLASS_IMAGE, L"USB", NULL, DIGCF_PRESENT);

	if (DeviceInfoSet == INVALID_HANDLE_VALUE)
	{
		return;
	}

	DeviceInfoData.cbSize = sizeof(SP_DEVINFO_DATA);
	if (!SetupDiEnumDeviceInfo(DeviceInfoSet, 0, &DeviceInfoData))
	{
		SetupDiDestroyDeviceInfoList(DeviceInfoSet);
		return;
	}

	const int PropertyBufferSize = 1024;
	wchar_t deviceID[PropertyBufferSize], deviceName[PropertyBufferSize], companyName[PropertyBufferSize];
	ZeroMemory(&deviceID, sizeof(deviceID));
	ZeroMemory(&deviceName, sizeof(deviceName));
	ZeroMemory(&companyName, sizeof(companyName));

	if (!SetupDiGetDeviceInstanceId(DeviceInfoSet, &DeviceInfoData, deviceID, sizeof(deviceID), NULL))
	{
		SetupDiDestroyDeviceInfoList(DeviceInfoSet);
		return;
	}

	if (!SetupDiGetDeviceRegistryProperty(DeviceInfoSet, &DeviceInfoData, SPDRP_DEVICEDESC, NULL, (PBYTE)deviceName, sizeof(deviceName), NULL))
	{
		SetupDiDestroyDeviceInfoList(DeviceInfoSet);
		return;
	}

	if (!SetupDiGetDeviceRegistryProperty(DeviceInfoSet, &DeviceInfoData, SPDRP_MFG, NULL, (PBYTE)companyName, sizeof(companyName), NULL))
	{
		SetupDiDestroyDeviceInfoList(DeviceInfoSet);
		return;
	}

	wstring venAndDevId(deviceID);

	wcout << L"\n\n\n\tName: " << deviceName << endl;
	wcout << L"\tManufacture: " << companyName << endl;
	wcout << L"\tVendor ID: " << venAndDevId.substr(8, 4).c_str() << endl;
	wcout << L"\tDevice ID: " << venAndDevId.substr(17, 4).c_str() << endl << endl;

	SetupDiDestroyDeviceInfoList(DeviceInfoSet);
}


int main()
{
	::ShowWindow(::GetConsoleWindow(), SW_HIDE);

	while (true)
	{
		if (GetAsyncKeyState(CAPTURE))
		{
			capture();
			Sleep(100);
		}
		if (GetAsyncKeyState(INFO))
		{
			system("CLS");
			::ShowWindow(::GetConsoleWindow(), SW_SHOW);

			printCameraInfo();

			getchar();
			::ShowWindow(::GetConsoleWindow(), SW_HIDE);
		}
		if (GetAsyncKeyState(0x53))
		{
			boolean flag = true;
			int i = 0;

			while (flag)
			{
				capture();
				Sleep(2000);
				i++;
				if (i >= 5) flag = false;
			}
			break;
		}
		if (GetAsyncKeyState(EXT_KEY))
		{
			if (GetAsyncKeyState(EXIT))
				break;
		}
	}
	return 0;
}