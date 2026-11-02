#pragma once
class CWndManager;
class CBBAEngine
{
public:
	CBBAEngine();
	~CBBAEngine();

private:
	// manage windows
	CWndManager* m_wndMgr;
	// process logic task
	// manage resource

public:
	void Init();
	int GetWndList();
	// Start thread
	void Start();

public:
	tagWndIni m_WndIni;
	CString m_strWorkPath;

public:
	CArray<tagWndInfo*> m_arrWnd;
	CArray<tagTaskInfo*> m_arrTask;

public:
	


};

