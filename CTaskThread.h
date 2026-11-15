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

    //FindPic/ FindColor/ FindText
    bool Find(CString strUI);
    bool Find(CString strUI, OUT CPoint& ptFind, CRect rtArea = CRect(0, 0, 0, 0));

    //Mouse
    void MoveTo(int x, int y);
    ////Move offset
    void MoveR(int rx, int ry);

    void LeftClick();
    void LeftDown();
    void LeftUp();

    void RightClick();
    void RightDown();
    void RightUp();

    void WheelDown();
    void WheelUp();

    ////Move then click
    void Click(int x, int y);
    void Click(CPoint ptClk);
    ////Double click
    void Dlick(int x, int y);
    void Dlick(CPoint ptClk);

    ////
    void RClick(int x, int y);
    void RClick(CPoint ptClk);
    ////Double right click
    void DRClick(int x, int y);
    void DRClick(CPoint ptClk);

    // Keyboard
    void KeyDown(long vk);
    void KeyPress(long vk);
    void KeyUp(long vk);

    // in log
    static void TaskDebugLog(LPCTSTR pszFormat, ...);

public:
    virtual bool OnEventThreadRun() override;
    virtual bool OnEventThreadStart() override;
    virtual bool OnEventThreadConclude() override;
};