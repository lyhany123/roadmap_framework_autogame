#include "pch.h"
#include "CTaskThread.h"
#include "CBBAEngine.h"

extern CBBAEngine* g_pEngine;


CTaskThread::CTaskThread(tagWndInfo* pWnd)
    : m_pWnd(pWnd)
{
    if (m_pWnd == nullptr)
    {
        TaskDebugLog(_T("CTaskThread: Invalid window pointer"));
        return;
    }

    TaskDebugLog(_T("%s: Task thread created"), m_pWnd->strTitle);
}


CTaskThread::~CTaskThread()
{
    StopThread(INFINITE);
}


bool CTaskThread::OnEventThreadStart()
{
    if (m_pWnd == nullptr)
        return false;

    TaskDebugLog(
        _T("%s: Initializing LeWan"),
        m_pWnd->strTitle
    );

    if (!m_Lewan.Initialize())
    {
        TaskDebugLog(
            _T("%s: LeWan initialization failed"),
            m_pWnd->strTitle
        );

        return false;
    }

    m_bInitialized = true;

    TaskDebugLog(
        _T("%s: LeWan initialized"),
        m_pWnd->strTitle
    );

    return true;
}


bool CTaskThread::OnEventThreadRun()
{
    if (!m_bInitialized || m_pWnd == nullptr)
        return false;

    TaskDebugLog(_T("%s: Task thread is running"), m_pWnd->strTitle);

    // Bind cửa sổ
    if (!m_bind)
    {
        TaskDebugLog(_T("%s: Start binding window"), m_pWnd->strTitle);

        if (!Bind())
        {
            TaskDebugLog(_T("%s: Window binding failed"), m_pWnd->strTitle);
            return false;
        }

        m_bind = true;

        TaskDebugLog(_T("%s: Window bound successfully"), m_pWnd->strTitle);
    }

    // Thực hiện thao tác
    if (!OpenRoleInfo())
    {
        TaskDebugLog(_T("%s: OpenRoleInfo failed"), m_pWnd->strTitle);
        return false;
    }

    Sleep(5000);

    return false;
}


bool CTaskThread::OnEventThreadConclude()
{
    TaskDebugLog(
        _T("%s: Releasing LeWan"),
        m_pWnd ? m_pWnd->strTitle : _T("Unknown")
    );

    m_Lewan.Uninitialize();

    m_bInitialized = false;
    m_bind = false;

    return true;
}


bool CTaskThread::Bind()
{
    if (!m_bInitialized ||
        g_pEngine == nullptr ||
        m_pWnd == nullptr)
        return false;

    HWND hWnd = m_pWnd->hWnd;

    if (!::IsWindow(hWnd))
    {
        TaskDebugLog(_T("Invalid HWND: %p"), hWnd);
        return false;
    }

    IlwsoftPtr& lw = m_Lewan.GetObject();

    if (lw == nullptr)
    {
        TaskDebugLog(_T("LeWan object is null"));
        return false;
    }

    int display = _ttoi(g_pEngine->m_WndIni.strDisplay);
    int mouse = _ttoi(g_pEngine->m_WndIni.strMouse);
    int keypad = _ttoi(g_pEngine->m_WndIni.strKeypad);
    int added = _ttoi(g_pEngine->m_WndIni.strPublic);
    int mode = _ttoi(g_pEngine->m_WndIni.iMode);

    TaskDebugLog(
        _T("BindWindow: HWND=%p, display=%d, mouse=%d, keypad=%d, added=%d, mode=%d"),
        hWnd, display, mouse, keypad, added, mode
    );

    long ret = lw->BindWindow(
        (int)hWnd,
        display,
        mouse,
        keypad,
        added,
        mode
    );

    TaskDebugLog(_T("BindWindow result: %ld"), ret);

    return ret == 1;
}


bool CTaskThread::OpenRoleInfo()
{
    if (!m_bInitialized)
        return false;

    IlwsoftPtr& lw = m_Lewan.GetObject();

    if (lw == nullptr)
        return false;

    TaskDebugLog(_T("Starting mouse test"));

    Sleep(5000);

    long moveRet = lw->MoveTo(204, 126);

    TaskDebugLog(
        _T("MoveTo(97,101): %ld"),
        moveRet
    );

    Sleep(500);

    long clickRet = lw->LeftClick();

    TaskDebugLog(
        _T("LeftClick: %ld"),
        clickRet
    );

    return true;
}

// Ghi log trực tiếp ra Visual Studio Output
void CTaskThread::TaskDebugLog(LPCTSTR pszFormat, ...)
{
    TCHAR szBuffer[2048] = { 0 };

    va_list args;
    va_start(args, pszFormat);

    _vstprintf_s(
        szBuffer,
        _countof(szBuffer),
        pszFormat,
        args
    );

    va_end(args);

    OutputDebugString(szBuffer);
    OutputDebugString(_T("\r\n"));
}

bool CTaskThread::Find(CString strUI)
{
    return false;
}