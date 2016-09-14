#include "stdafx.h"
#include "Communication.h"
#include <iostream>
#include "Ini.h"

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
	CIni ini;
	COMMTIMEOUTS TimeOuts; //设定读超时
	TimeOuts.ReadIntervalTimeout = 100;

	TimeOuts.ReadTotalTimeoutMultiplier = 1;

	TimeOuts.ReadTotalTimeoutConstant = ini.ReadInt(INI_COMDEF, "ReadTimeOut"); //设定写超时

	TimeOuts.WriteTotalTimeoutMultiplier = 1;

	TimeOuts.WriteTotalTimeoutConstant = ini.ReadInt(INI_COMDEF, "WriteTimeOut");

	SetCommTimeouts(hCom, &TimeOuts); //设置超时

	DCB dcb;

	dcb.BaudRate = ini.ReadInt(INI_COMDEF, "BaudRate");

	dcb.ByteSize = (BYTE)ini.ReadInt(INI_COMDEF, "ByteSize");

	dcb.Parity = (BYTE)ini.ReadInt(INI_COMDEF, "Parity");

	dcb.StopBits = (BYTE)ini.ReadInt(INI_COMDEF, "StopBit");

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

void ComConnect::SetReadTimeout(unsigned int second)
{
	COMMTIMEOUTS TimeOuts;
	GetCommTimeouts(hCom, &TimeOuts);
	TimeOuts.ReadTotalTimeoutConstant = second * 1000; //设定写超时
	SetCommTimeouts(hCom, &TimeOuts);
}

bool ComConnect::Open()
{
	char ComName[5];
	CIni ini;
	if (!ini.ReadString("COMDEF", "com", ComName))
	{
		memcpy(ComName, "COM1", 4);
		ComName[sizeof(ComName) - 1] = '\0';
	}
	else
	{
		std::string sCom = "COM";
		sCom.push_back(ComName[0]);
		strcpy_s(ComName, sCom.c_str());
	}

	hCom = CreateFile(ComName, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
	if (!CheckInvalid())
	{
		AfxMessageBox("打开串口失败,请检查串口设置");
		return false;
	}
	InitConfig();
	
	return true;
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
	Sleep(2000);

	printf("Start Read\n");
	DWORD wCount = 0;
	PurgeComm(hCom, PURGE_TXCLEAR);
	ReadFile(hCom, buffer, len, &wCount, NULL);
	return wCount;
}
