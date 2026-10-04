#include "pch.h"
#include "CWndManager.h"
#include "CBBAEngine.h"

extern CBBAEngine* g_pEngine;

CWndManager::CWndManager()
{



}

CWndManager::~CWndManager()
{



}

bool CWndManager::GetWndList(CArray<tagWndInfo>& arrWnd)
{
	CArray<tagEnumExeWndParam> arrEnumWnd;
	GetProcessWnd(g_pEngine->m_WndIni.strProc, g_pEngine->m_WndIni.strTitle, g_pEngine->m_WndIni.strClz, arrEnumWnd);
	for (int i = 0; i < arrEnumWnd.GetSize(); i++)
	{
		LogD(_T("%d - %s - %s"), arrEnumWnd[i].hWnds[0], arrEnumWnd[i].szTitleWord, arrEnumWnd[i].szClzWord);
	}
	return false;
}