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

int CWndManager::GetWndList(CArray<tagWndInfo*>& arrWnd)
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
            if (info.hWnd == arrWnd[j]->hWnd)
            {
                arrWnd[j]->rtWnd = info.rtWnd;
                arrWnd[j]->strTitle = info.strTitle;
                bExist = true;
            }
        }
		if (!bExist)
		{
			tagWndInfo* pInfo = new tagWndInfo;
			pInfo->id = (int)info.hWnd;
			pInfo->hWnd = info.hWnd;
			pInfo->rtWnd = info.rtWnd;
			pInfo->strTitle = info.strTitle;

			arrWnd.Add(pInfo);
		}
            
    }

	return arrWnd.GetCount();
}

int CWndManager::GetLDList(CArray<tagWndInfo*>& arrWnd)
{
	CString strRet = ListVM();
	//0, LDPlayer, 0, 0, 0, -1, -1, 1280, 720, 240
	// 1, LDPlayer - 1, 0, 0, 0, -1, -1, 1280, 720, 240
	// 2, LDPlayer - 2, 0, 0, 0, -1, -1, 1280, 720, 240
	if (strRet.GetLength() < 1)
		return 0;

	CStringArray strArray;
	Split(strRet, strArray, _T("\r\n"));

	for (int i = 0; i < strArray.GetSize(); i++)
	{
		//0, LDPlayer, 0, 0, 0, -1, -1
		tagWndInfo info;
		CString strVm = strArray.GetAt(i);

		CString strTmp;

		AfxExtractSubString(strTmp, (LPCTSTR)strVm, 0, _T(','));
		info.id = _ttoi(strTmp);

        AfxExtractSubString(strTmp, (LPCTSTR)strVm, 1, _T(','));
		info.strTitle = strTmp;

        // HWND child windows
        AfxExtractSubString(strTmp, (LPCTSTR)strVm, 3, _T(','));
		info.hWnd = (HWND)_ttoi(strTmp);

        if (info.hWnd != NULL)
            ::GetWindowRect(info.hWnd, info.rtWnd);

        bool bExist = false;
        for (int j = 0; j < arrWnd.GetCount(); j++)
        {
            if (arrWnd[j]->id == info.id)
            {
                bExist = true;
                arrWnd[j]->strTitle = info.strTitle;
                arrWnd[j]->rtWnd = info.rtWnd;
                break;
            }
        }
		if (!bExist)
		{
			tagWndInfo* pInfo = new tagWndInfo;
			pInfo->id = info.id;
			pInfo->hWnd = info.hWnd;
			pInfo->rtWnd = info.rtWnd;
			pInfo->strTitle = info.strTitle;

			arrWnd.Add(pInfo);
		}
            
	}
    return arrWnd.GetCount();
}

CString CWndManager::ExeCmd(CString pszCmd)
{
	SECURITY_ATTRIBUTES sa = { sizeof(SECURITY_ATTRIBUTES), NULL, TRUE };
	HANDLE hRead, hWrite;
	if (!CreatePipe(&hRead, &hWrite, &sa, 0))
	{
		return _T("");
	}

	// 设置命令行进程启动信息(以隐藏方式启动命令并定位其输出到hWrite
	STARTUPINFO si = { sizeof(STARTUPINFO) };
	GetStartupInfo(&si);
	si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;
	si.wShowWindow = SW_HIDE;
	si.hStdError = hWrite;
	si.hStdOutput = hWrite;

	// 启动命令行
	PROCESS_INFORMATION pi;
	if (!CreateProcess(NULL, pszCmd.GetBuffer(), NULL, NULL, TRUE, NULL, NULL, NULL, &si, &pi))
	{
		pszCmd.ReleaseBuffer();
		return _T("");
	}

	pszCmd.ReleaseBuffer();

	CloseHandle(hWrite);

	// 读取命令行返回值
	CStringA strRetTmp;
	char buff[1024 * 2] = { 0 };
	DWORD dwRead = 0;
	strRetTmp = buff;
	while (ReadFile(hRead, buff, 1024 * 2, &dwRead, NULL))
	{
		strRetTmp += buff;
	}
	CloseHandle(hRead);

	LPCSTR pszSrc = strRetTmp.GetString();
	int nLen = MultiByteToWideChar(CP_ACP, 0, buff, -1, NULL, 0);
	if (nLen == 0)
		return _T("");

	wchar_t* pwszDst = new wchar_t[nLen];
	if (!pwszDst)
		return _T("");

	MultiByteToWideChar(CP_ACP, 0, pszSrc, -1, pwszDst, nLen);
	CString strRet(pwszDst);
	delete[] pwszDst;
	pwszDst = NULL;

	return strRet;
}

CString CWndManager::ListVM() 
{
    CString strParam;

    if (g_pEngine->m_WndIni.strLDPath != _T(""))
        strParam.Format(_T("%s\\ldconsole.exe list2"), g_pEngine->m_WndIni.strLDPath); // 构造命令行参数

    return ExeCmd(strParam);
}