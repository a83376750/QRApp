#include "stdafx.h"
#include "Communication.h"
#include <iostream>

Communication::Communication()
{
}


Communication::~Communication()
{
}


ComConnect::ComConnect()
{

}

ComConnect::~ComConnect()
{

}

void ComConnect::InitConfig()
{
	if (!SetupComm(hCom, 1024, 1024))
	{
		printf("SetupComm fail!\n");
		Close();
	}
	COMMTIMEOUTS TimeOuts; //设定读超时
	TimeOuts.ReadIntervalTimeout = 100;

	TimeOuts.ReadTotalTimeoutMultiplier = 0;

	TimeOuts.ReadTotalTimeoutConstant = 0; //设定写超时

	TimeOuts.WriteTotalTimeoutMultiplier = 1;

	TimeOuts.WriteTotalTimeoutConstant = 1;

	SetCommTimeouts(hCom, &TimeOuts); //设置超时

	DCB dcb;

	dcb.BaudRate = 9600;

	dcb.ByteSize = 8;

	dcb.Parity = 0;

	dcb.StopBits = 1;

	SetCommState(hCom, &dcb);
	PurgeComm(hCom, PURGE_TXCLEAR | PURGE_RXCLEAR);
}

bool ComConnect::CheckInvalid()
{
	bool bValid = true;
	if (hCom == INVALID_HANDLE_VALUE)
		bValid = false;
	if (bValid)
		printf("Succee\n");
	else
		printf("Error OpenCom\n");
	return bValid;
}

void ComConnect::Open()
{
	char ComName[5];
	memcpy(ComName, "COM2", 4);
	ComName[sizeof(ComName) - 1] = '\0';
	hCom = CreateFile(ComName, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
	if (!CheckInvalid())
		return;
	InitConfig();
}

void ComConnect::Close()
{
	if (CloseHandle(hCom))
		printf("Com is close\n");
	else
		printf("Com is not close\n");
	delete this;
}

bool ComConnect::Write(void *buffer, size_t len)
{

	printf("Start Write\n");
	DWORD wCount = 0;
	PurgeComm(hCom, PURGE_RXCLEAR);
	if (WriteFile(hCom, buffer, len, &wCount, NULL))
	{
		printf("send succee\n");
		if (!buffer)
		{
			std::cout << "读取包有误" << std::endl;
			return false;
		}
		unsigned char *ucBuffer = (unsigned char*)buffer;
		for (size_t i = 0; i < len; ++i)
		{
			printf("%02x ", ucBuffer[i]);
		}
		printf("Write buffer count:%d\n", wCount);
		printf("End Write\n");
		return true;
	}
	else
	{
		printf("send error\n");
		return false;
	}
}

DWORD ComConnect::Read(void *buffer, size_t len)
{
	printf("Start Read\n");
	DWORD wCount = 0;
	PurgeComm(hCom, PURGE_TXCLEAR);
	ReadFile(hCom, buffer, len, &wCount, NULL);
	return wCount;
}
