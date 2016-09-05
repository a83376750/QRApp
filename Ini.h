#pragma once

#define INI_PATH "./Sand.ini"

#include <string>

class CIni
{
public:
	CIni();
	~CIni();
	void Init();
	BOOL WriteString(LPCTSTR sAppName, LPCTSTR sKey, LPCTSTR sValue);
	DWORD ReadString(LPCTSTR sAppName, LPCTSTR sKey, LPSTR sOutput, LPCTSTR sDefault = "");
	LONG ReadInt(LPCTSTR sAppName, LPCTSTR sKey, LONG nDefault = 0);
	void CheckPath();
	void SetPath(const char *sPath);
private:
	std::string m_sPath;
};

