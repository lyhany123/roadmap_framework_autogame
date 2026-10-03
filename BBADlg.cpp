
// BBADlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "BBA.h"
#include "BBADlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CBBADlg dialog



CBBADlg::CBBADlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_BBA_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CBBADlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_WND, m_listWnd);
	DDX_Control(pDX, IDC_LIST_TASK, m_listTask);
	DDX_Control(pDX, IDC_LIST_TASK_RUN, m_listTaskRun);

	DDX_Control(pDX, IDC_TRACE_MESSAGE, m_TraceServiceControl);
}

BEGIN_MESSAGE_MAP(CBBADlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_START, &CBBADlg::OnBnClickedButtonStart)
	ON_BN_CLICKED(IDC_BUTTON_STOP, &CBBADlg::OnBnClickedButtonStop)
END_MESSAGE_MAP()


// CBBADlg message handlers

BOOL CBBADlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	DWORD dwStyle = m_listWnd.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;
	dwStyle |= LVS_EX_GRIDLINES;
	dwStyle |= LVS_EX_CHECKBOXES;
	m_listWnd.SetExtendedStyle(dwStyle);

	m_listWnd.InsertColumn(0, _T("Windows handle"), LVCFMT_CENTER, 90); // insert a column


	int iRow = m_listWnd.GetItemCount();
	m_listWnd.InsertItem(iRow, _T(""));

	CString strId;
	strId.Format(_T("%d"), 1);

	m_listWnd.SetItemText(iRow, 0, strId);

	// TASK
	dwStyle = m_listTask.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;
	dwStyle |= LVS_EX_GRIDLINES;
	m_listTask.SetExtendedStyle(dwStyle);

	m_listTask.InsertColumn(0, _T("Task"), LVCFMT_CENTER, 170); // insert a column



	// RUN TASK
	dwStyle = m_listTaskRun.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;
	dwStyle |= LVS_EX_GRIDLINES;
	m_listTaskRun.SetExtendedStyle(dwStyle);

	m_listTaskRun.InsertColumn(0, _T("Task Run"), LVCFMT_CENTER, 170); // insert a column


	// Rich edit control
	CTraceService::TraceString(_T("Test message"), TraceLevel_Normal); // TraceLevel_Debug, TraceLevel_WWarning


	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CBBADlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CBBADlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CBBADlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CBBADlg::OnBnClickedButtonStart()
{
	// TODO: Add your control notification handler code here
	CTraceService::TraceString(_T("Test message"), TraceLevel_Debug); // TraceLevel_Debug, TraceLevel_WWarning

}

void CBBADlg::OnBnClickedButtonStop()
{
	// TODO: Add your control notification handler code here
	CTraceService::TraceString(_T("Test message"), TraceLevel_Warning); // TraceLevel_Debug, TraceLevel_WWarning

}
