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

int CWndManager::GetWndList(CArray<tagWndInfo>& arrWnd)
{
	CArray<tagEnumExeWndParam> arrEnumWnd;
	GetProcessWnd(g_pEngine->m_WndIni.strProc, g_pEngine->m_WndIni.strTitle, g_pEngine->m_WndIni.strClz, arrEnumWnd);
	//for (int i = 0; i < arrEnumWnd.GetSize(); i++)
	//{
	//	LogD(_T("%d - %s - %s"), arrEnumWnd[i].hWnds[0], arrEnumWnd[i].szTitleWord, arrEnumWnd[i].szClzWord);
	//}

    for (int i = 0; i < arrEnumWnd.GetSize(); i++)
    {
        tagWndInfo info;
        info.hWnd = arrEnumWnd[i].hWnds[0];
        info.strTitle = arrEnumWnd[i].szTitleWord;
        ::GetWindowRect(info.hWnd, &info.rtWnd);

        bool bExist = false;
        for (int j = 0; j < arrWnd.GetCount(); j++)
        {
            if (info.hWnd == arrWnd[j].hWnd)
            {
                arrWnd[j].rtWnd = info.rtWnd;
                arrWnd[j].strTitle = info.strTitle;
                bExist = true;
            }
        }
        if (!bExist)
            arrWnd.Add(info);
    }

	return arrWnd.GetCount();
}