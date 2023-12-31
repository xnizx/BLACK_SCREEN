// BLACK_SCREENDlg.cpp : implementation file
//

#include "stdafx.h"
#include "BLACK_SCREENApp.h"
#include "BLACK_SCREENDlg.h"
#include "DialogSub.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#include <crtdbg.h>
#ifdef malloc
#undef malloc
#endif
#define malloc(s) (_malloc_dbg(s, _NORMAL_BLOCK, __FILE__, __LINE__ ))
#ifdef calloc
#undef calloc
#endif
#define calloc(c, s) (_calloc_dbg(c, s, _NORMAL_BLOCK, __FILE__, __LINE__ ))
#ifdef realloc
#undef realloc
#endif
#define realloc(p, s) (_realloc_dbg(p, s, _NORMAL_BLOCK, __FILE__, __LINE__ ))
#ifdef _expand
#undef _expand
#endif
#define _expand(p, s) (_expand_dbg(p, s, _NORMAL_BLOCK, __FILE__, __LINE__  ))
#ifdef free
#undef free
#endif
#define free(p) (_free_dbg(p, _NORMAL_BLOCK))
#ifdef _msize
#undef _msize
#endif
#define _msize(p) (_msize_dbg(p, _NORMAL_BLOCK))
#endif

extern HWND g_BLACK_SCREENApp;
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()

BOOL CAboutDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	CString strWindowText;
	CString str;str.LoadString(AFX_IDS_APP_TITLE);strWindowText.Format(_T("%s Ver %s"), str, theApp.GetVersion());
	SetWindowText(strWindowText);GetDlgItem(IDC_STATIC_ABOUT)->SetWindowText(strWindowText);
	return TRUE;
}

// CBLACK_SCREENDlg dialog



CBLACK_SCREENDlg::CBLACK_SCREENDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBLACK_SCREENDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_nCurrentMonitor = 0;
	m_crBack = RGB(0,0,0);
	m_nR = 0;
	m_nG = 0;
	m_nB = 0;
	m_nC = 0;
}

void CBLACK_SCREENDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CBLACK_SCREENDlg, CDialog)
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_ERASEBKGND()
	ON_WM_SETCURSOR()
	ON_WM_DESTROY()
	ON_WM_TIMER()
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CBLACK_SCREENDlg message handlers

BOOL CBLACK_SCREENDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	SetCursor(theApp.LoadCursor(IDC_CURSOR_DEFAULT));
	// Add "About..." menu item to system menu.
	g_BLACK_SCREENApp = GetSafeHwnd();
	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
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
	int nCount = theApp.m_infoMonitor.aryMonitors.GetCount();

	CRect rcRectMain = CRect(0, 0, theApp.m_infoMonitor.nWidth, theApp.m_infoMonitor.nHeight);
	if (nCount > m_nCurrentMonitor)
	{
		rcRectMain.SetRect(
			theApp.m_infoMonitor.aryMonitors.GetAt(m_nCurrentMonitor).rcMonitor.left,
			theApp.m_infoMonitor.aryMonitors.GetAt(m_nCurrentMonitor).rcMonitor.top,
			theApp.m_infoMonitor.aryMonitors.GetAt(m_nCurrentMonitor).rcMonitor.right,
			theApp.m_infoMonitor.aryMonitors.GetAt(m_nCurrentMonitor).rcMonitor.bottom);
	}

	theApp.m_pMainWnd->SetWindowPos(&CWnd::wndTop, rcRectMain.left,
		rcRectMain.top,
		rcRectMain.Width(),
		rcRectMain.Height(), SWP_SHOWWINDOW);
	
	CString strIni;
	strIni.Format(_T("%s%s.ini"), theApp.m_strCurrentDir, _T("BLACK_SCREEN"));//2022.05.23
	CString strDefault = _T("");
	CString strSection = _T("");
	TCHAR WriteString[255];
	memset(WriteString, 0, sizeof(WriteString));
	int nSize = 0;

	

	if(theApp.m_nUseMultiMonitor==1)
	{
		CRect rcMonitor;
		for (int i = 1; i < nCount; i++)
		{
			
			strSection.Format(_T("MonitorEnable%d"), i);
			memset(WriteString, 0, sizeof(WriteString));
			int nMonitorEnable = 1;
			strDefault.Format(_T("%d"), nMonitorEnable);
			nSize = GetPrivateProfileString(_T("SYSTEM"), strSection, strDefault, WriteString, sizeof(WriteString), strIni);
			if (nSize > 0)
			{
				nMonitorEnable = _ttoi(WriteString);
			}
			if (nMonitorEnable == 1)
			{
				CDialogSub* pDlg = new CDialogSub;
				pDlg->m_MonitorInfoEx = ((MONITORINFOEX)theApp.m_infoMonitor.aryMonitors.GetAt(i));
				rcMonitor = pDlg->m_MonitorInfoEx.rcMonitor;

				pDlg->Create(this);
				pDlg->MoveWindow(rcMonitor);
				pDlg->ShowWindow(SW_SHOW);
				m_aryDlg.Add(pDlg);
			}
		}
		
	}
	if (theApp.m_nUseRandom > 0)
	{
		SetTimer(100, theApp.m_nTimeMinor, NULL);
		if(theApp.m_nUseRandom == 1)
			SetTimer(200, theApp.m_nTimeMajor, NULL);
	}
	return TRUE;  // return TRUE  unless you set the focus to a control
}


// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.


// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CBLACK_SCREENDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


BOOL CBLACK_SCREENDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CRect rect;
	GetClientRect(&rect);
	pDC->FillSolidRect(rect, m_crBack);
	return FALSE;
}


BOOL CBLACK_SCREENDlg::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	SetCursor(theApp.LoadCursor(IDC_CURSOR_DEFAULT));
	return TRUE;
}


BOOL CBLACK_SCREENDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	int nClose = 0;
	if (pMsg->message == WM_SYSKEYUP)
	{
		nClose = 1;
	}
	else if (pMsg->message == WM_CHAR)
	{
		nClose = 1;
	}
	else if (pMsg->message == WM_LBUTTONUP)
	{
		nClose = 1;
	}
	else if (pMsg->message == WM_LBUTTONDBLCLK)
	{
		nClose = 1;
	}
	else if (pMsg->message == WM_RBUTTONUP)
	{
		nClose = 1;
	}
	else if (pMsg->message == WM_RBUTTONDBLCLK)
	{
		nClose = 1;
	}
	else
	{
		nClose = 0;
	}
	if (nClose == 1)
	{
		SendMessage(WM_COMMAND, IDOK, 0);
		return TRUE;
	}
	return CDialog::PreTranslateMessage(pMsg);
}


void CBLACK_SCREENDlg::OnDestroy()
{
	CDialog::OnDestroy();
	if (theApp.m_nUseRandom > 0)
	{
		KillTimer(100);
		KillTimer(200);
	}
	int nCount = m_aryDlg.GetCount();
	for (int i = 0; i < nCount; i++)
	{
		CDialogSub* pDlg = (CDialogSub*)m_aryDlg.GetAt(i);
		if (pDlg)
			delete pDlg;
	}
	m_aryDlg.RemoveAll();
	m_aryDlg.FreeExtra();
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}


void CBLACK_SCREENDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if(nIDEvent==100)
	{
		Random<int> genR(0, 30000);
		Random<int> genG(0, 30000);
		Random<int> genB(0, 30000);
		auto numR = genR();
		auto numG = genG();
		auto numB = genB();
		if (theApp.m_nUseRandom == 2)
		{
			m_nR = min(max(numR / 100, 0), 255);
			m_nG = min(max(numG / 100, 0), 255);
			m_nB = min(max(numB / 100, 0), 255);
		}
		else
		{
			if (m_nC == 0)
			{
				m_nR = min(max(numR / 100, 0), 255);
			}
			else if (m_nC == 1)
			{
				m_nG = min(max(numG / 100, 0), 255);
			}
			else if (m_nC == 2)
			{
				m_nB = min(max(numB / 100, 0), 255);
			}
			else
			{
				m_nR = min(max(numR / 100, 0), 255);
			}
		}

		m_crBack = RGB(m_nR, m_nG, m_nB);
		Invalidate(FALSE);
	}
	if (nIDEvent == 200)
	{
		Random<int> genR(0, 30000);
		Random<int> genG(0, 30000);
		Random<int> genB(0, 30000);
		Random<int> genC(0, 300);
		auto numR = genR();
		auto numG = genG();
		auto numB = genB();
		auto numC = genC();
		m_nR = min(max(numR / 100, 0), 255);
		m_nG = min(max(numG / 100, 0), 255);
		m_nB = min(max(numG / 100, 0), 255);
		m_nC = min(max(numC / 100, 0), 2);
		m_crBack = RGB(m_nR, m_nG, m_nB);
		Invalidate(FALSE);
	}
	CDialog::OnTimer(nIDEvent);
}


void CBLACK_SCREENDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	CRect rect;
	GetClientRect(&rect);
	dc.FillSolidRect(rect, m_crBack);
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	// 그리기 메시지에 대해서는 CDialog::OnPaint()을(를) 호출하지 마십시오.
}
