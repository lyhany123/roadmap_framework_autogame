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

public:
	tagWndIni m_WndIni;
	CString m_strWorkPath;




};

