#pragma once

struct tagWndInfo
{
	HWND hWnd;
	CRect rtWnd;
	CString strTitle;

	tagWndInfo()
	{
		hWnd = NULL;
		rtWnd = CRect(0, 0, 0, 0);
		strTitle = _T("");
	}

};