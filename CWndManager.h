#pragma once
class CWndManager
{
public:
	CWndManager();
	~CWndManager();

	int GetWndList(CArray<tagWndInfo>& arrWnd);

};

