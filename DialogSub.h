#pragma once


// CDialogSub ��ȭ �����Դϴ�.

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
	CDialogSub(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CDialogSub();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOG_SUB };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

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
