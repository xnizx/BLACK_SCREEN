// BLACK_SCREENApp.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "BLACK_SCREENApp.h"
#include "BLACK_SCREENDlg.h"
#include "OtherInstance.h"

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


// CBLACK_SCREENApp

BEGIN_MESSAGE_MAP(CBLACK_SCREENApp, CWinApp)
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()


// CBLACK_SCREENApp construction

CBLACK_SCREENApp::CBLACK_SCREENApp()
{
	m_strCurrentDir=_T(".");
	m_nCurrentMonitor = 0;
	m_nUseRandom = 0;
	m_nTimeMajor = 10000;
	m_nTimeMinor = 1000;
	m_nUseMultiMonitor = 1;
}


// The one and only CBLACK_SCREENApp object

CBLACK_SCREENApp theApp;


// CBLACK_SCREENApp initialization

BOOL CBLACK_SCREENApp::InitInstance()
{
	CString str;str.LoadString(AFX_IDS_APP_TITLE);XLOGDBG( _T("%s %s - %s"), str , GetVersion(), _T("InitInstance"));
	SetCurrentDirectoryToExistsFolder();

	// InitCommonControls() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	InitCommonControls();

	CWinApp::InitInstance();

	AfxEnableControlContainer();

	TCHAR	szCurPath[_MAX_PATH];
	GetCurrentDirectory(255, szCurPath);
	m_strCurrentDir = szCurPath;
	if(m_strCurrentDir.GetAt(m_strCurrentDir.GetLength()-1)!=TEXT('\\'))
		m_strCurrentDir+=TEXT('\\');

	CString s = _strRegstryEntry;
	s.Delete(0,9); 
	SetRegistryKey(s);

	theApp.GetMonitorInformation();
	
	CString strIni;
	strIni.Format(_T("%s%s.ini"), m_strCurrentDir, _T("BLACK_SCREEN"));//2022.05.23
	CString strDefault = _T("");
	TCHAR WriteString[255];
	memset(WriteString, 0, sizeof(WriteString));
	int nSize = 0;
	
	strDefault.Format(_T("%d"), m_nUseRandom);
	memset(WriteString, 0, sizeof(WriteString));
	nSize = GetPrivateProfileString(_T("SYSTEM"), _T("UseRandom"), strDefault, WriteString, sizeof(WriteString), strIni);
	if (nSize > 0)
	{
		m_nUseRandom = _ttoi(WriteString);
	}

	strDefault.Format(_T("%d"), m_nUseMultiMonitor);
	memset(WriteString, 0, sizeof(WriteString));
	nSize = GetPrivateProfileString(_T("SYSTEM"), _T("UseMultiMonitor"), strDefault, WriteString, sizeof(WriteString), strIni);
	if (nSize > 0)
	{
		m_nUseMultiMonitor = _ttoi(WriteString);
	}

	strDefault.Format(_T("%d"), m_nTimeMajor);
	memset(WriteString, 0, sizeof(WriteString));
	nSize = GetPrivateProfileString(_T("SYSTEM"), _T("TimeMajor"), strDefault, WriteString, sizeof(WriteString), strIni);
	if (nSize > 0)
	{
		m_nTimeMajor = _ttoi(WriteString);
	}

	strDefault.Format(_T("%d"), m_nTimeMinor);
	memset(WriteString, 0, sizeof(WriteString));
	nSize = GetPrivateProfileString(_T("SYSTEM"), _T("TimeMinor"), strDefault, WriteString, sizeof(WriteString), strIni);
	if (nSize > 0)
	{
		m_nTimeMinor = _ttoi(WriteString);
	}

#ifndef _DEBUG
	OtherInstance* pOtherInstance = new OtherInstance();
	if (pOtherInstance)
	{
		if (pOtherInstance->IsThereAnyOtherInstance())// 이미 실행중이면 프로그램 종료
		{
			//2008.12.19
			HWND hWnd = pOtherInstance->GetHwndOtherInstance();
			if (hWnd)
			{
				//SendMessage(hWnd, WM_TRAY_SHOW, 0, 0);
			}
			delete pOtherInstance;
			PostQuitMessage(0);
			return FALSE;
		}
		delete pOtherInstance;
	}
#endif

	CBLACK_SCREENDlg dlg;
	dlg.m_nCurrentMonitor = 0;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

void CBLACK_SCREENApp::SetCurrentDirectoryToExistsFolder()
{
	TCHAR	tszModulePath[_MAX_PATH] = {0,};
	TCHAR	tszNewPath[_MAX_PATH] = {0,};
	TCHAR	c = TEXT('\\');
	LPTSTR	pLastOccur = NULL;
	size_t	nLen = 0;

	VERIFY(GetModuleFileName(NULL, tszModulePath, sizeof(tszModulePath)/sizeof(tszModulePath[0])));

	pLastOccur = _tcsrchr(tszModulePath, c);
	nLen = size_t(pLastOccur - tszModulePath + 1);

	_tcsncpy_s(tszNewPath, _MAX_PATH, tszModulePath, nLen);

	VERIFY(SetCurrentDirectory(tszNewPath));
}

int CBLACK_SCREENApp::ExitInstance()
{
	CString str;str.LoadString(AFX_IDS_APP_TITLE);XLOGDBG( _T("%s %s - %s"), str , GetVersion(), _T("ExitInstance"));

	CString strIni;
	strIni.Format(_T("%s%s.ini"), m_strCurrentDir, _T("BLACK_SCREEN"));//2022.05.23
	
	CString strDefault = _T("");
	char WriteString[10000];
	memset(WriteString, 0, sizeof(WriteString));

	CString strValue;
	strValue.Format(_T("%d"), m_nUseMultiMonitor);
	WritePrivateProfileString(_T("SYSTEM"), _T("UseMultiMonitor"), strValue, strIni); 
	strValue.Format(_T("%d"), m_nUseRandom);
	WritePrivateProfileString(_T("SYSTEM"), _T("UseRandom"), strValue, strIni);
	strValue.Format(_T("%d"), m_nTimeMajor);
	WritePrivateProfileString(_T("SYSTEM"), _T("TimeMajor"), strValue, strIni);
	strValue.Format(_T("%d"), m_nTimeMinor);
	WritePrivateProfileString(_T("SYSTEM"), _T("TimeMinor"), strValue, strIni);

	return CWinApp::ExitInstance();
}
CString GetFileVersionInformation(CString strFileName, CString strFlag)
{
	struct LANGANDCODEPAGE {
		WORD wLanguage;
		WORD wCodePage;
	} *lpTranslate;

	DWORD dwSize = GetFileVersionInfoSize(strFileName, 0);
	_TCHAR* buffer = new _TCHAR[dwSize];
	memset(buffer, 0, dwSize);

	GetFileVersionInfo(strFileName, 0, dwSize, buffer);

	UINT cbTranslate;
	UINT dwBytes;

	LPBYTE lpBuffer = NULL;

	VerQueryValue(buffer, TEXT("\\VarFileInfo\\Translation"), (LPVOID*)&lpTranslate, &cbTranslate);

	if (cbTranslate != 0) // 버전 정보가 없을 경우 "
	{
		CString strSub;
		strSub.Format(_T("\\StringFileInfo\\%04x%04x\\%s"), lpTranslate[0].wLanguage, lpTranslate[0].wCodePage, strFlag);
		VerQueryValue(buffer, (LPTSTR)(LPCTSTR)strSub, (LPVOID*)&lpBuffer, &dwBytes);
	}

	CString strReturn;
	strReturn.Format(_T("%s"), lpBuffer);

	delete[] buffer;

	return strReturn;
}
CString CBLACK_SCREENApp::GetVersion()
{
	CString strVersion=_T("");
	TCHAR szPath[MAX_PATH];
	::GetModuleFileName(::AfxGetInstanceHandle(), szPath, _MAX_PATH);

	CString strTemp1 = GetFileVersionInformation(szPath, _T("FileVersion"));
	CString strTemp2 = GetFileVersionInformation(szPath, _T("InternalName"));
	CString strTemp3 = GetFileVersionInformation(szPath, _T("OriginalFilename"));
	CString strTemp4 = GetFileVersionInformation(szPath, _T("ProductVersion"));
	CString strTemp5 = GetFileVersionInformation(szPath, _T("ProductName"));

	CString strTemp6 = GetFileVersionInformation(szPath, _T("Comments"));
	CString strTemp7 = GetFileVersionInformation(szPath, _T("CompanyName"));
	strVersion=strTemp1;
	strVersion.Replace(_T(","),_T("."));
	return strVersion;
}

BOOL CALLBACK MonitorEnumProc(HMONITOR hMonitor, HDC hdcMonitor, LPRECT lprcMonitor, LPARAM dwData)
{
	MONITORINFOEX mi;

	mi.cbSize = sizeof(MONITORINFOEX);
	GetMonitorInfo(hMonitor, &mi);
	theApp.m_infoMonitor.aryMonitors.Add(mi);	
	
	return TRUE;
}
int CBLACK_SCREENApp::GetMonitorInformation(void)
{
	m_infoMonitor.nMonitor = ::GetSystemMetrics(SM_CMONITORS);
	XLOGDBG(">>GetMonitorInformation : SM_CMONITORS[%d]", m_infoMonitor.nMonitor);
	m_infoMonitor.bSameDisplayFormat = ::GetSystemMetrics(SM_SAMEDISPLAYFORMAT);
	XLOGDBG(">>GetMonitorInformation : SM_SAMEDISPLAYFORMAT[%s]", (m_infoMonitor.bSameDisplayFormat) ? "TRUE" : "FALSE");

	m_infoMonitor.rcVirtual.left = GetSystemMetrics(SM_XVIRTUALSCREEN);
	m_infoMonitor.rcVirtual.top = GetSystemMetrics(SM_YVIRTUALSCREEN);
	m_infoMonitor.rcVirtual.right = m_infoMonitor.rcVirtual.left + GetSystemMetrics(SM_CXVIRTUALSCREEN);
	m_infoMonitor.rcVirtual.bottom = m_infoMonitor.rcVirtual.top + GetSystemMetrics(SM_CYVIRTUALSCREEN);


	m_infoMonitor.nWidth = ::GetSystemMetrics(SM_CXSCREEN);             // ???? ??? x
	XLOGDBG(">>GetMonitorInformation : SM_CXSCREEN[%d]", m_infoMonitor.nWidth);
	m_infoMonitor.nHeight = ::GetSystemMetrics(SM_CYSCREEN);             // ???? ??? y
	XLOGDBG(">>GetMonitorInformation : SM_CYSCREEN[%d]", m_infoMonitor.nHeight);
	m_infoMonitor.nWidthVirtual = ::GetSystemMetrics(SM_CXVIRTUALSCREEN);             // ?????? ??? x
	XLOGDBG(">>GetMonitorInformation : SM_CXVIRTUALSCREEN[%d]", m_infoMonitor.nWidthVirtual);
	m_infoMonitor.nHeightVirtual = ::GetSystemMetrics(SM_CYVIRTUALSCREEN);             // ?????? ??? y
	XLOGDBG(">>GetMonitorInformation : SM_CYVIRTUALSCREEN[%d]", m_infoMonitor.nHeightVirtual);

	m_infoMonitor.nMegaPixel = (m_infoMonitor.nWidth * m_infoMonitor.nHeight) / (1000 * 1000);
	m_infoMonitor.nMegaPixel = max(1, m_infoMonitor.nMegaPixel);

	XLOGDBG(">>GetMonitorInformation : MegaPixel[%d]", m_infoMonitor.nMegaPixel);

	HDC hDC = NULL;
	hDC = CreateDC("DISPLAY", NULL, NULL, NULL);
	if (hDC)
	{
		theApp.m_nDisplayInch = GetDeviceCaps(hDC, LOGPIXELSX);//2009.02.20
		EnumDisplayMonitors(NULL, NULL, MonitorEnumProc, (LPARAM)hDC);
		m_infoMonitor.nBitPerPixel = GetDeviceCaps(hDC, BITSPIXEL);
		XLOGDBG(">>GetMonitorInformation : BITSPIXEL[%d]", m_infoMonitor.nBitPerPixel);
		m_infoMonitor.nRefresh = GetDeviceCaps(hDC, VREFRESH);
		XLOGDBG(">>GetMonitorInformation : VREFRESH[%d]", m_infoMonitor.nRefresh);
		if (theApp.m_infoMonitor.nBitPerPixel == 8)
		{
			SetSystemPaletteUse(hDC, SYSPAL_STATIC);//SYSPAL_NOSTATIC
			//SYSPAL_NOSTATIC256
			//SYSPAL_STATIC
		}
		
		DeleteDC(hDC);
		
	}
	else
	{
		XLOGOUT_LASTERROR;
		return -1;
	}
	for (int i = 0; i < m_infoMonitor.aryMonitors.GetCount(); i++)
	{
		XLOGDBG("MONITORS[%d]", i);
		XLOGDBG("rcMonitor[%d,%d,%d,%d]", ((MONITORINFOEX)m_infoMonitor.aryMonitors.GetAt(i)).rcMonitor.left,
			((MONITORINFOEX)m_infoMonitor.aryMonitors.GetAt(i)).rcMonitor.top,
			((MONITORINFOEX)m_infoMonitor.aryMonitors.GetAt(i)).rcMonitor.right,
			((MONITORINFOEX)m_infoMonitor.aryMonitors.GetAt(i)).rcMonitor.bottom);
		XLOGDBG("rcWork[%d,%d,%d,%d]", ((MONITORINFOEX)m_infoMonitor.aryMonitors.GetAt(i)).rcWork.left,
			((MONITORINFOEX)m_infoMonitor.aryMonitors.GetAt(i)).rcWork.top,
			((MONITORINFOEX)m_infoMonitor.aryMonitors.GetAt(i)).rcWork.right,
			((MONITORINFOEX)m_infoMonitor.aryMonitors.GetAt(i)).rcWork.bottom);
		XLOGDBG("dwFlags[%d]", ((MONITORINFOEX)m_infoMonitor.aryMonitors.GetAt(i)).dwFlags);
		XLOGDBG("szDevice[%s]", ((MONITORINFOEX)m_infoMonitor.aryMonitors.GetAt(i)).szDevice);
	}
	return 0;
}

void CBLACK_SCREENApp::MoveToActiveMonitor(CWnd* pWnd)
{
	if (pWnd && pWnd->GetSafeHwnd())
	{
		CPoint point;
		GetCursorPos(&point);
		CRect rcMonitor;
		if (m_infoMonitor.aryMonitors.GetCount() > m_nCurrentMonitor)
			//for(int i=0;i<m_infoMonitor.aryMonitors.GetCount();i++)
		{
			rcMonitor = ((MONITORINFOEX)m_infoMonitor.aryMonitors.GetAt(m_nCurrentMonitor)).rcMonitor;

			//if(rcMonitor.PtInRect(point)==TRUE)
			{
				CPoint ptCenter;
				ptCenter.x = rcMonitor.left + rcMonitor.Width() / 2;
				ptCenter.y = rcMonitor.top + rcMonitor.Height() / 2;

				CRect rcWnd;
				pWnd->GetWindowRect(rcWnd);
				//theApp.m_pFrame->ScreenToClient(rcWnd);
				CPoint ptCenter2;
				ptCenter2.x = rcWnd.left + rcWnd.Width() / 2;
				ptCenter2.y = rcWnd.top + rcWnd.Height() / 2;
				rcWnd.OffsetRect(ptCenter.x - ptCenter2.x, ptCenter.y - ptCenter2.y);
				//if((m_rcMain.Width()>0)&&(m_rcMain.Height()))//2008.03.17
					//rcWnd.OffsetRect(m_rcMain.left,m_rcMain.top);

				pWnd->MoveWindow(rcWnd);
				return;
			}

		}

	}

}