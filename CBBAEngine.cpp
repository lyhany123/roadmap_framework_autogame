#include "pch.h"
#include "CBBAEngine.h"


CBBAEngine::CBBAEngine()
{

}


CBBAEngine::~CBBAEngine()
{

}

void CBBAEngine::Init()
{
	TCHAR szPath[256] = { 0 };
	CWHService::GetWorkDirectory(szPath, 256);
	m_strWorkPath = szPath;

	CWHIniData ini;  //D:\programming\BBA\Debug
	ini.SetIniFilePath(m_strWorkPath + _T("/GlobalConfig.ini")); // or use "\\GlobalConfig.ini"
	m_WndIni.strProc = ini.ReadString(_T("WindowConfig"), _T("ProcessName"));
	m_WndIni.strTitle = ini.ReadString(_T("WindowConfig"), _T("WindowTitle"));
	m_WndIni.strClz = ini.ReadString(_T("WindowConfig"), _T("ClassName"));


}