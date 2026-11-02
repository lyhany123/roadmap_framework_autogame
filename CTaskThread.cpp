#include "pch.h"
#include "CTaskThread.h"

CTaskThread::CTaskThread(CString strTitle)
{
    m_strTitle = strTitle;
}

CTaskThread::~CTaskThread()
{
}

bool CTaskThread::OnEventThreadRun()
{
    LogN(_T("%s: Task thread is running"), m_strTitle);
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
    LogN(_T("%s: Task thread ended"), m_strTitle);
    return true;
}