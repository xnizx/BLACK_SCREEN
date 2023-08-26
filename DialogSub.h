#pragma once


// CDialogSub 대화 상자입니다.

class CDialogSub : public CDialog
{
	DECLARE_DYNAMIC(CDialogSub)

public:
	COLORREF m_crBack;
	int m_nR;
	int m_nG;
	int m_nB;
	int m_nC;
	MONITORINFOEX m_MonitorInfoEx;
	CDialogSub(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CDialogSub();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG_SUB };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL Create(CWnd* pParentWnd = NULL);
	virtual BOOL OnInitDialog();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnPaint();
};
