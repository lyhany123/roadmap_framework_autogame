#pragma once
#include "WHThread.h"
class CTaskThread :
    public CWHThread
{
public:
    CTaskThread(tagWndInfo* pWnd);
    ~CTaskThread();

private:
    tagWndInfo* m_pWnd;
    bool m_bind;

public:
    // Run event
    virtual bool OnEventThreadRun();
    // Start event
    virtual bool OnEventThreadStart();
    // Termination event
    virtual bool OnEventThreadConclude();


};

