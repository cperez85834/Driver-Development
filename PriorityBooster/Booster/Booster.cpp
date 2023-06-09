#include <Windows.h>
#include <stdio.h>
#include "../PriorityBooster/PriorityBoosterCommon.h"

int Error(const char* message)
{
	printf("%s Error: %d", message, GetLastError());
	return 1;
}

int main(int argc, const char* argv[])
{
	if (argc < 3)
	{
		printf("Usage: Booster <threadid> <priority>\n");
		return 0;
	}

	HANDLE hDevice = CreateFile(L"\\\\.\\PriorityBooster", GENERIC_WRITE, FILE_SHARE_WRITE, nullptr, OPEN_EXISTING, 0, nullptr);
	if (nullptr == hDevice)
	{
		return Error("Failed to open device!");
	}

	ThreadData data;
	data.ThreadId = atoi(argv[1]);
	data.Priority = atoi(argv[2]);

	DWORD returned;

	BOOL success = DeviceIoControl(hDevice, IOCTL_PRIORITY_BOOSTER_SET_PRIORITY, &data, sizeof(data),
		nullptr, 0, &returned, nullptr);
	if (true == success)
	{
		printf("Priority change success!");
	}
	else
	{
		Error("Priority change failed!");
	}

	CloseHandle(hDevice);
}