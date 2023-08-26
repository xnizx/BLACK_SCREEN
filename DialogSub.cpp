// DialogSub.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "BLACK_SCREENApp.h"
#include "DialogSub.h"


// CDialogSub 대화 상자입니다.

IMPLEMENT_DYNAMIC(CDialogSub, CDialog)
CDialogSub::CDialogSub(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogSub::IDD, pParent)
{
	m_crBack = RGB(0, 0, 0);
	m_nR = 0;
	m_nG = 0;
	m_nB = 0;
	m_nC = 0;
}

CDialogSub::~CDialogSub()
{
}

void CDialogSub::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDialogSub, CDialog)
	ON_WM_ERASEBKGND()
	ON_WM_SETCURSOR()	
	ON_WM_DESTROY()
	ON_WM_TIMER()
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CDialogSub 메시지 처리기입니다.

BOOL CDialogSub::Create(CWnd* pParentWnd)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	
	return CDialog::Create(CDialogSub::IDD, pParentWnd);
}

BOOL CDialogSub::OnInitDialog()
{
	CDialog::OnInitDialog();
	if (theApp.m_nUseRandom == 1)
	{
		SetTimer(100, theApp.m_nTimeMinor, NULL);
		SetTimer(200, theApp.m_nTimeMajor, NULL);
	}
	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}



BOOL CDialogSub::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CRect rect;
	GetClientRect(&rect);
	pDC->FillSolidRect(rect, RGB(0, 0, 0));
	return FALSE;
}


BOOL CDialogSub::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	SetCursor(theApp.LoadCursor(IDC_CURSOR_DEFAULT));
	return TRUE;
}


BOOL CDialogSub::PreTranslateMessage(MSG* pMsg)
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
		GetParent()->SendMessage(WM_COMMAND,IDOK,0);
		return TRUE;
	}
	return CDialog::PreTranslateMessage(pMsg);
}

void CDialogSub::OnDestroy()
{
	CDialog::OnDestroy();
	if (theApp.m_nUseRandom == 1)
	{
		KillTimer(100);
		KillTimer(200);
	}	
}

void CDialogSub::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (nIDEvent == 100)
	{
		Random<int> genR(0, 255);
		Random<int> genG(0, 255);
		Random<int> genB(0, 255);
		auto numR = genR();
		auto numG = genG();
		auto numB = genB();
		if (m_nC == 0)
			m_nR = numR;
		else if (m_nC == 1)
			m_nG = numG;
		else if (m_nC == 2)
			m_nB = numB;
		else
			m_nR = numR;

		m_crBack = RGB(m_nR, m_nG, m_nB);
		Invalidate(FALSE);
	}
	if (nIDEvent == 200)
	{
		Random<int> genR(0, 255);
		Random<int> genG(0, 255);
		Random<int> genB(0, 255);
		Random<int> genC(0, 2);
		auto numR = genR();
		auto numG = genG();
		auto numB = genB();
		auto numC = genC();
		m_nR = numR;
		m_nG = numG;
		m_nB = numB;
		m_nC = numC;
		m_crBack = RGB(m_nR, m_nG, m_nB);
		Invalidate(FALSE);
	}
	CDialog::OnTimer(nIDEvent);
}


void CDialogSub::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	CRect rect;
	GetClientRect(&rect);
	dc.FillSolidRect(rect, m_crBack);
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	// 그리기 메시지에 대해서는 CDialog::OnPaint()을(를) 호출하지 마십시오.
}
