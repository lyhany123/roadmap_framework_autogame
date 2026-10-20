#pragma once
class CWndManager
{
public:
	CWndManager();
	~CWndManager();

	int GetWndList(CArray<tagWndInfo>& arrWnd);
	int GetLDList(CArray<tagWndInfo>& arrWnd);

private:
	CString ListVM();
	CString ExeCmd(CString pszCmd);

};

