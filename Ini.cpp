#include "stdafx.h"
#include "Ini.h"

CIni::CIni()
{
	Init();
}


CIni::~CIni()
{
}

void CIni::Init()
{
	m_sPath = INI_PATH;
}

BOOL CIni::WriteString(LPCTSTR sAppName, LPCTSTR sKey, LPCTSTR sValue)
{
	return WritePrivateProfileString(sAppName, sKey, sValue, m_sPath.c_str());
}

DWORD CIni::ReadString(LPCTSTR sAppName, LPCTSTR sKey, LPSTR sOutput, LPCTSTR sDefault)
{
	return GetPrivateProfileString(sAppName, sKey, sDefault, sOutput, 50, m_sPath.c_str());
}

LONG CIni::ReadInt(LPCTSTR sAppName, LPCTSTR sKey, LONG nDefault)
{
	return GetPrivateProfileInt(sAppName, sKey, nDefault, m_sPath.c_str());
}

void CIni::CheckPath()
{
	if (m_sPath == "")
	{
		m_sPath = INI_PATH;
	}
}

void CIni::SetPath(const char *sPath)
{
	m_sPath = sPath;
}

