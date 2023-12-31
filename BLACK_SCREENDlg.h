// BLACK_SCREENDlg.h : header file
//

#pragma once


// CBLACK_SCREENDlg dialog
class CBLACK_SCREENDlg : public CDialog
{
// Construction
public:
	CBLACK_SCREENDlg(CWnd* pParent = NULL);	// standard constructor
	COLORREF m_crBack;
	int m_nR;
	int m_nG;
	int m_nB;
	int m_nC;
	int m_nCurrentMonitor;
	CPtrArray m_aryDlg;
// Dialog Data
	enum { IDD = IDD_BLACK_SCREEN_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnPaint();
};
