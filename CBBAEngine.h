#pragma once
#include <thread>
#include <vector>

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
	std::vector<std::thread> m_startLaunchers;

public:
	void Init();
	int GetWndList();
	// Start thread
	void Start();

public:
	tagWndIni m_WndIni;
	CString m_strWorkPath;

public:
	// list resource
	CArray<tagResItem*> m_arrRes;
	// list windows
	CArray<tagWndInfo*> m_arrWnd;
	// list task
	CArray<tagTaskInfo*> m_arrTask;

private:
	
	bool LoadRes();

};

