#if !defined(AFX_OTHERINSTANCE_H__66456775_42AC_45CE_BCB6_7D75E94A1A7D__INCLUDED_)
#define AFX_OTHERINSTANCE_H__66456775_42AC_45CE_BCB6_7D75E94A1A7D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OtherInstance.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// OtherInstance window

class OtherInstance : public CWnd
{
// Construction
public:
	OtherInstance();
	int FindProcess(LPCTSTR szToTerminate);
	void get_processname(TCHAR* szProcess, int nSize);
	bool IsThereAnyOtherInstance();
	HWND GetHwndOtherInstance();//2008.12.19

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(OtherInstance)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~OtherInstance();

	// Generated message map functions
protected:
	//{{AFX_MSG(OtherInstance)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OTHERINSTANCE_H__66456775_42AC_45CE_BCB6_7D75E94A1A7D__INCLUDED_)
