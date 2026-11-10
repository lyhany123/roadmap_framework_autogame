#pragma once

struct tagWndInfo
{
	int  id;
	HWND hWnd;
	CRect rtWnd;
	CString strTitle;

	tagWndInfo()
	{
		id = 0;
		hWnd = NULL;
		rtWnd = CRect(0, 0, 0, 0);
		strTitle = _T("");
	}

};


struct tagWndIni {
	CString strProc; 
	CString strTitle;  
	CString strClz;  
	CString strLDPath;  

	CString strDisplay;
	CString strMouse;
	CString strKeypad;
	CString strPublic;
	CString		iMode;


	tagWndIni()
	{
		strProc = _T("");
		strTitle = _T("");
		strClz = _T("");
		strLDPath = _T("");

		strDisplay = _T("");
		strMouse = _T("");
		strKeypad = _T("");
		strPublic = _T("");
		iMode = _T("");
	}

};

class CTaskThread;
struct tagTaskInfo {
	int           id;
	tagWndInfo* pWnd;
	CTaskThread* pTask;

	tagTaskInfo()
	{
		id = 0;
		pWnd = NULL;
		pTask = NULL;
	}
};