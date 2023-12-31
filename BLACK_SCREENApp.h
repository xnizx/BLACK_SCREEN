// BLACK_SCREENApp.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols


// CBLACK_SCREENApp:
// See BLACK_SCREEN.cpp for the implementation of this class
//

class CBLACK_SCREENApp : public CWinApp
{
public:
	CBLACK_SCREENApp();	
	int m_nUseMultiMonitor;
	int m_nUseRandom;
	int m_nTimeMajor;
	int m_nTimeMinor;
	void SetCurrentDirectoryToExistsFolder();
	CString m_strCurrentDir;
	CString GetVersion();
	int m_nCurrentMonitor;
	void MoveToActiveMonitor(CWnd* pWnd);
	TMONITOR m_infoMonitor;
	int m_nDisplayInch;
	int GetMonitorInformation(void);
// Overrides
	public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
	virtual int ExitInstance();
};

extern CBLACK_SCREENApp theApp;
