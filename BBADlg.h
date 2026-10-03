
// BBADlg.h : header file
//

#pragma once


// CBBADlg dialog
class CBBADlg : public CDialogEx
{
// Construction
public:
	CBBADlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_BBA_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation

private:
	CListCtrl m_listWnd; // sinh t? ??ng khi chu?t ph?i ?? add bi?n
	CListCtrl m_listTask; // sinh t? ??ng khi chu?t ph?i ?? add bi?n
	CListCtrl m_listTaskRun; // sinh t? ??ng khi chu?t ph?i ?? add bi?n
	CTraceServiceControl m_TraceServiceControl; // bi?n Rich Edit control, vi?t th? công


protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()


public:

	afx_msg void OnBnClickedButtonStart();
	afx_msg void OnBnClickedButtonStop();
};
