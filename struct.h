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

struct tagWndIni
{
	CString strProc;
	CString strTitle;
	CString strClz;
	CString strLDPath;

	tagWndIni()
	{
		strProc = _T("");
		strTitle = _T("");
		strClz = _T("");
		strLDPath = _T("");
	}
};