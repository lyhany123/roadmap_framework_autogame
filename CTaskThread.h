#pragma once
#include "WHThread.h"
class CTaskThread :
    public CWHThread
{
public:
    CTaskThread(CString strTitle);
    ~CTaskThread();

private:
    CString m_strTitle;
    bool m_bind;

public:
    // Run event
    virtual bool OnEventThreadRun();
    // Start event
    virtual bool OnEventThreadStart();
    // Termination event
    virtual bool OnEventThreadConclude();


};

