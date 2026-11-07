#include "pch.h"
#include "CTaskThread.h"

CTaskThread::CTaskThread(tagWndInfo* pWnd)
{
    m_pWnd = pWnd;
}

CTaskThread::~CTaskThread()
{
}

bool CTaskThread::OnEventThreadRun()
{
    LogN(_T("%s: Task thread is running"), m_pWnd->strTitle);
    if (!m_bind)
    {
        // Execute binding process
    }
    // Normal task logic
    return true;
}

bool CTaskThread::OnEventThreadStart()
{
    return true;
}

bool CTaskThread::OnEventThreadConclude()
{
    LogN(_T("%s: Task thread ended"), m_pWnd->strTitle);
    return true;
}