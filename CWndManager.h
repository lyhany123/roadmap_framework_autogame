#pragma once
class CWndManager
{
public:
	CWndManager();
	~CWndManager();

	bool GetWndList(CArray<tagWndInfo>& arrWnd);

};

