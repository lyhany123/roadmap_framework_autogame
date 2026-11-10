#pragma once

#include "WHThread.h"
#include "LeWanHelper.h"

class CTaskThread : public CWHThread
{
public:
    CTaskThread(tagWndInfo* pWnd);
    virtual ~CTaskThread();

private:
    // Thông tin cửa sổ
    tagWndInfo* m_pWnd = nullptr;

    // Trạng thái
    bool m_bind = false;
    bool m_bInitialized = false;

    // Quản lý đối tượng LeWan
    CLeWanHelper m_Lewan;

private:
    bool Bind();
    bool OpenRoleInfo();

public:
    virtual bool OnEventThreadRun() override;
    virtual bool OnEventThreadStart() override;
    virtual bool OnEventThreadConclude() override;
};