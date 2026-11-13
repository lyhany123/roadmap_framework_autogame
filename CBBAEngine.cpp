#include "pch.h"
#include "CBBAEngine.h"
#include "CWndManager.h"
#include "CTaskThread.h"
#include "locale.h"


CBBAEngine::CBBAEngine()
{
	m_iWidth = 0;
	m_iHeight = 0;

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

	// Đọc WindowSize: chuỗi -> Width, Height
	CString strWindowSize;
	ReadIni(_T("WindowSize"), strWindowSize);

	CStringArray arrTmp;
	Split(strWindowSize, arrTmp, _T(","));

	if (arrTmp.GetCount() == 2)
	{
		m_iWidth = _ttoi(arrTmp[0]);
		m_iHeight = _ttoi(arrTmp[1]);
	}


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

		CStringArray arrTmp;
		Split(strRead, arrTmp, _T("="));
		if (arrTmp.GetCount() != 2)
		{
			LogE(_T("Unparseable content: %s"), strRead);
			ASSERT(FALSE);
			return false;
		}

		// Character info button
		CString strName = arrTmp[0];
		// 1061, 755, 1067, 775 > CharacterInfoBtn.bmp > 000000 > 0.9 > 0 > FindImage
		CString strValue = arrTmp[1];
		arrTmp.RemoveAll();
		Split(strValue, arrTmp, _T(">"));
		if (arrTmp.GetCount() < 5)
		{
			LogE(_T("Unparseable content: %s"), strRead);

			ASSERT(FALSE);
			return false;
		}

		CStringArray arrRect;
		Split(arrTmp[0], arrRect, _T(","));
		if (arrRect.GetCount() != 4)
		{
			LogE(_T("Unparseable content: %s"), strRead);
			ASSERT(FALSE);
			return false;
		}

		// Character info button.bmp > 000000 > 0.9 > 0 > FindImage
		CString strRes = arrTmp[1];
		CString strDelclr = arrTmp[2];
		CString strSim = arrTmp[3];
		CString strDir = arrTmp[4];
		CString strType = arrTmp[5];

		tagResItem* pItem = new tagResItem;
		pItem->strName = strName;
		pItem->rtArea = CRect(_ttoi(arrRect[0]), _ttoi(arrRect[1]), _ttoi(arrRect[2]), _ttoi(arrRect[3]));

		ASSERT(pItem->rtArea.left >= 0 && pItem->rtArea.left < pItem->rtArea.right);
		ASSERT(pItem->rtArea.right <= m_iWidth);
		ASSERT(pItem->rtArea.top >= 0 && pItem->rtArea.top < pItem->rtArea.bottom);
		ASSERT(pItem->rtArea.bottom <= m_iHeight);

		pItem->strRes = strRes;
		pItem->strDeltaClr = strDelclr;
		pItem->dSim = _ttof(strSim);
		pItem->iDir = _ttoi(strDir);

		if (strType == _T("FindImage"))
		{
			pItem->iType = 0;
		}
		else if (strType == _T("FindColor"))
		{
			pItem->iType = 1;
		}
		else if (strType == _T("FindText"))
		{
			pItem->iType = 2;
		}

		m_arrRes.Add(pItem);
	}

	setlocale(LC_CTYPE, old_locale);
	free(old_locale);

	file.Close();
	return true;
}
