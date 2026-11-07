#include "pch.h"
#include "CBBAEngine.h"
#include "CWndManager.h"
#include "CTaskThread.h"


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
	m_WndIni.strLDPath = ini.ReadString(_T("WindowConfig"), _T("LDPath"));

	//m_wndMgr->GetWndList(m_arrWnd);
	
}

int CBBAEngine::GetWndList()
{
	if (m_WndIni.strLDPath.GetLength() > 5)
	{
		return m_wndMgr->GetLDList(m_arrWnd);
	}
	else
	{
		return m_wndMgr->GetWndList(m_arrWnd);
	}
	
}

void CBBAEngine::Start()
{
	for (int i = 0; i < m_arrWnd.GetCount(); i++)
	{
		tagWndInfo* pInfo = m_arrWnd[i];
		if (pInfo->strTitle.Find(_T("LDPlayer-1")) != -1)
		{
			tagTaskInfo* pTask = new tagTaskInfo;
			pTask->id = pInfo->id;
			pTask->pWnd = pInfo;
			pTask->pTask = new CTaskThread(pInfo);
			pTask->pTask->StartThread();

			m_arrTask.Add(pTask);
		}

	}
}