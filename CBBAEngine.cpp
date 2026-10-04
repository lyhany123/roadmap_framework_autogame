#include "pch.h"
#include "CBBAEngine.h"
#include "CWndManager.h"


CBBAEngine::CBBAEngine()
{
	m_wndMgr = new CWndManager();
}


CBBAEngine::~CBBAEngine()
{

}

void CBBAEngine::Init()
{
	TCHAR szPath[256] = { 0 };
	CWHService::GetWorkDirectory(szPath, 256);
	m_strWorkPath = szPath;

	//D:\programming\BBA\Debug
	CWHIniData ini;  
	ini.SetIniFilePath(m_strWorkPath + _T("/GlobalConfig.ini")); // or use "\\GlobalConfig.ini"
	m_WndIni.strProc = ini.ReadString(_T("WindowConfig"), _T("ProcessName"));
	m_WndIni.strTitle = ini.ReadString(_T("WindowConfig"), _T("WindowTitle"));
	m_WndIni.strClz = ini.ReadString(_T("WindowConfig"), _T("ClassName"));

	CArray<tagWndInfo> arrWnd;
	m_wndMgr->GetWndList(arrWnd);
}