#include "pch.h"
#include "CTaskThread.h"
#include "CBBAEngine.h"

extern CBBAEngine* g_pEngine;


CTaskThread::CTaskThread(tagWndInfo* pWnd)
    : m_pWnd(pWnd)
{
    if (m_pWnd == nullptr)
    {
        LogE(_T("CTaskThread: Invalid window pointer"));
        return;
    }

    LogN(_T("%s: Task thread created"), m_pWnd->strTitle);
}


CTaskThread::~CTaskThread()
{
    // CLeWanHelper tự quản lý việc giải phóng đối tượng.
}


bool CTaskThread::OnEventThreadStart()
{
    if (m_pWnd == nullptr)
        return false;

    // Khởi tạo LeWan trên chính luồng công việc
    if (!m_Lewan.Initialize())
    {
        LogE(_T("%s: LeWan initialization failed"),
            m_pWnd->strTitle);

        return false;
    }

    m_bInitialized = true;

    LogN(_T("%s: LeWan initialized successfully"),
        m_pWnd->strTitle);

    LogN(_T("%s: Task thread started"),
        m_pWnd->strTitle);

    return true;
}


bool CTaskThread::OnEventThreadRun()
{
    if (!m_bInitialized || m_pWnd == nullptr)
        return false;

    LogN(_T("%s: Task thread is running"), m_pWnd->strTitle);

    // Bind cửa sổ
    if (!m_bind)
    {
        LogN(_T("%s: Start binding window"), m_pWnd->strTitle);

        if (!Bind())
        {
            LogE(_T("%s: Window binding failed"), m_pWnd->strTitle);
            return false;
        }

        m_bind = true;

        LogN(_T("%s: Window bound successfully"), m_pWnd->strTitle);
    }

    // Thực hiện thao tác
    if (!OpenRoleInfo())
    {
        LogE(_T("%s: OpenRoleInfo failed"), m_pWnd->strTitle);
        return false;
    }

    Sleep(5000);

    return true;
}


bool CTaskThread::OnEventThreadConclude()
{
    LogN(_T("%s: Task thread ended"),
        m_pWnd ? m_pWnd->strTitle : _T("Unknown"));

    // Giải phóng LeWan trên chính luồng công việc
    m_Lewan.Uninitialize();

    m_bInitialized = false;
    m_bind = false;

    return true;
}


bool CTaskThread::Bind()
{
    if (!m_bInitialized || g_pEngine == nullptr || m_pWnd == nullptr)
        return false;

    IlwsoftPtr& lw = m_Lewan.GetObject();

    long ret = lw->BindWindow(
        (int)m_pWnd->hWnd,
        _ttoi(g_pEngine->m_WndIni.strDisplay),
        _ttoi(g_pEngine->m_WndIni.strMouse),
        _ttoi(g_pEngine->m_WndIni.strKeypad),
        _ttoi(g_pEngine->m_WndIni.strPublic),
        _ttoi(g_pEngine->m_WndIni.iMode)
    );

    return ret == 1;
}


bool CTaskThread::OpenRoleInfo()
{
    if (!m_bInitialized)
        return false;

    IlwsoftPtr& lw = m_Lewan.GetObject();
    Sleep(5000);

    lw->MoveTo(97, 101);

    Sleep(500);

    lw->LeftClick();

    return true;
}