#include "pch.h"
#include "CBBAEngine.h"
#include "CWndManager.h"
#include "CTaskThread.h"
#include "locale.h"


CBBAEngine::CBBAEngine()
{
	m_wndMgr = new CWndManager();
}


CBBAEngine::~CBBAEngine()
{

}

void CBBAEngine::Init()
{
	TCHAR szPath[256] = { 0 };
	CWHService::GetWorkDirectory(szPath, 256);
	m_strWorkPath = szPath;

	CWHIniData ini;
	ini.SetIniFilePath(m_strWorkPath + _T("/GlobalConfig.ini"));

	auto ReadIni = [&](LPCTSTR key, CString& value)
		{
			TCHAR szBuffer[1024] = { 0 };

			ini.ReadString(
				_T("WindowConfig"),
				key,
				_T(""),
				szBuffer,
				_countof(szBuffer)
			);

			value = szBuffer;
		};

	ReadIni(_T("ProcessName"), m_WndIni.strProc);
	ReadIni(_T("WindowTitle"), m_WndIni.strTitle);
	ReadIni(_T("ClassName"), m_WndIni.strClz);
	ReadIni(_T("LDPath"), m_WndIni.strLDPath);

	ReadIni(_T("display"), m_WndIni.strDisplay);
	ReadIni(_T("mouse"), m_WndIni.strMouse);
	ReadIni(_T("keypad"), m_WndIni.strKeypad);
	ReadIni(_T("public"), m_WndIni.strPublic);
	ReadIni(_T("mode"), m_WndIni.iMode);

	LoadRes();
}

int CBBAEngine::GetWndList()
{
	if (m_WndIni.strLDPath.GetLength() > 5)
	{
		return m_wndMgr->GetLDList(m_arrWnd);
	}
	else
	{
		return m_wndMgr->GetWndList(m_arrWnd);
	}
	
}

void CBBAEngine::Start()
{
	for (int i = 0; i < m_arrWnd.GetCount(); i++)
	{
		tagWndInfo* pInfo = m_arrWnd[i];

		tagTaskInfo* pTask = new tagTaskInfo;

		pTask->id = pInfo->id;
		pTask->pWnd = pInfo;
		pTask->pTask = new CTaskThread(pInfo);

		// Lưu task trước để đảm bảo đối tượng
		// tồn tại trong suốt quá trình khởi chạy.
		m_arrTask.Add(pTask);

		// Gọi StartThread trên luồng trung gian.
		m_startLaunchers.emplace_back(
			[pTask]()
			{
				pTask->pTask->StartThread();
			}
		);
	}
}

bool CBBAEngine::LoadRes()
{
	// Build resource file path
	CString strResFile = m_strWorkPath + _T("/res/res.txt");
	if (!PathFileExists(strResFile))
	{
		LogE(_T("res.txt file does not exist"));
		return false;
	}

	char* old_locale = _strdup(setlocale(LC_CTYPE, NULL));
	setlocale(LC_CTYPE, "chs");

	CStdioFile file;

	if (!file.Open(strResFile, CFile::modeRead))
	{
		LogE(_T("Failed to open res.txt file"));
		return false;
	}

	CString strRead = _T("");
	while (file.ReadString(strRead))
	{
		LogD(_T("%s"), strRead);
	}

	setlocale(LC_CTYPE, old_locale);
	free(old_locale);

	file.Close();
	return true;
}
