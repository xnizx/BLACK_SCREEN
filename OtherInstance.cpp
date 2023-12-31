// OtherInstance.cpp : implementation file
//

#include "stdafx.h"

#include "OtherInstance.h"

#include <windows.h>
#include <tlhelp32.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
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

// 공유 핸들 지정 
#pragma comment(linker, "/SECTION:.shr,RWS")
#pragma data_seg(".shr")
HWND g_BLACK_SCREENApp = NULL;
#pragma data_seg()

/////////////////////////////////////////////////////////////////////////////
// OtherInstance

OtherInstance::OtherInstance()
{
}

OtherInstance::~OtherInstance()
{
}



int OtherInstance::FindProcess(LPCTSTR szToTerminate)
// Created: 6/23/2000  (RK)
// Last modified: 3/30/2001  (RK)
// Last modified: 20/08/2002 (Saeed)
// Please report any problems or bugs to kochhar@physiology.wisc.edu
// The latest version of this routine can be found at:
//     http://www.neurophys.wisc.edu/ravi/software/killproc/
// Terminate the process "szToTerminate" if it is currently running
// This works for Win/95/98/ME and also Win/NT/2000
// The process name is case-insensitive, i.e. "notepad.exe" and "NOTEPAD.EXE"
// will both work (for szToTerminate)
// Return codes are as follows:
//   1   = Process is running
//   603 = Process is not currently running
//   604 = No permission to terminate process
//   605 = Unable to search for process
//   602 = Unable to terminate process for some other reason
//   606 = Unable to identify system type
//   607 = Unsupported OS
//   632 = Invalid process name
{
	BOOL bResult, bResultm;
	DWORD aiPID[5000], iCb=5000, iNumProc, iV2000=0;
	DWORD iCbneeded, i, iFound=0;
	TCHAR szName[MAX_PATH], szToTermUpper[MAX_PATH];
	HANDLE hProc, hSnapShot, hSnapShotm;
	OSVERSIONINFO osvi;
	HINSTANCE hInstLib;
	int iLen, iLenP, indx;
	HMODULE hMod;
	PROCESSENTRY32 procentry;      
	MODULEENTRY32 modentry;
	int Cntr=0;
	// Transfer Process name into "szToTermUpper" and
	// convert it to upper case
	iLenP=_tcsclen(szToTerminate);
	if(iLenP<1 || iLenP>MAX_PATH) return 632;
	for(indx=0;indx<iLenP;indx++)
		szToTermUpper[indx]=toupper(szToTerminate[indx]);
	szToTermUpper[iLenP]=0;


	// First check what version of Windows we're in
	osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	bResult=GetVersionEx(&osvi);
	if(!bResult)     // Unable to identify system version
		return 606;

	// At Present we only support Win/NT/2000 or Win/9x
	if((osvi.dwPlatformId != VER_PLATFORM_WIN32_NT) &&
		(osvi.dwPlatformId != VER_PLATFORM_WIN32_WINDOWS))
		return 607;

	if(osvi.dwPlatformId==VER_PLATFORM_WIN32_NT)
	{
		// Win/NT or 2000

		// Load library and get the procedures explicitly. We do
		// this so that we don't have to worry about modules using
		// this code failing to load under Windows 9x, because
		// it can't resolve references to the PSAPI.DLL.
		hInstLib = LoadLibrary(_T("PSAPI.DLL"));
		if(hInstLib == NULL)
			return 605;


		bResult=EnumProcesses(aiPID, iCb, &iCbneeded);
		if(!bResult)
		{
			// Unable to get process list, EnumProcesses failed
			FreeLibrary(hInstLib);
			return 605;
		}

		// How many processes are there?
		iNumProc=iCbneeded/sizeof(DWORD);

		// Get and match the name of each process
		Cntr=0;
		for(i=0;i<iNumProc;i++)
		{
			// Get the (module) name for this process

			_tcscpy_s(szName, MAX_PATH, _T("Unknown"));
			// First, get a handle to the process
			hProc=OpenProcess(PROCESS_QUERY_INFORMATION|PROCESS_VM_READ, FALSE, 
				aiPID[i]);
			// Now, get the process name
			if(hProc)
			{
				if(EnumProcessModules(hProc, &hMod, sizeof(hMod), &iCbneeded) )
				{
					iLen=GetModuleBaseName(hProc, hMod, szName, MAX_PATH);
				}
			}
			CloseHandle(hProc);
			// We will match regardless of lower or upper case
			if(_tcscmp(_tcsupr(szName), szToTermUpper)==0)
			{
				// Process found, now terminate it
				iFound=1;
				// First open for termination
				hProc=OpenProcess(PROCESS_TERMINATE, FALSE, aiPID[i]);
				if(hProc)
					Cntr++;

				if(Cntr==2)
				{
					FreeLibrary(hInstLib);
					return 1;
				}
			}
		}
		return 0;
	}

	if(osvi.dwPlatformId==VER_PLATFORM_WIN32_WINDOWS)
	{
		// Win/95 or 98 or ME

		hInstLib = LoadLibrary(_T("Kernel32.DLL"));
		if( hInstLib == NULL )
			return FALSE ;

		// Get procedure addresses.
		// We are linking to these functions of Kernel32
		// explicitly, because otherwise a module using
		// this code would fail to load under Windows NT, 
		// which does not have the Toolhelp32
		// functions in the Kernel 32.
		// The Process32.. and Module32.. routines return names in all uppercase

		// Get a handle to a Toolhelp snapshot of all the systems processes.

		hSnapShot = CreateToolhelp32Snapshot(
			TH32CS_SNAPPROCESS, 0 ) ;
		if( hSnapShot == INVALID_HANDLE_VALUE )
		{
			FreeLibrary(hInstLib);
			return 605;
		}

		// Get the first process' information.
		procentry.dwSize = sizeof(PROCESSENTRY32);
		bResult=Process32First(hSnapShot, &procentry);

		// While there are processes, keep looping and checking.
		while(bResult)
		{
			// Get a handle to a Toolhelp snapshot of this process.
			hSnapShotm = CreateToolhelp32Snapshot(
				TH32CS_SNAPMODULE, procentry.th32ProcessID) ;
			if( hSnapShotm == INVALID_HANDLE_VALUE )
			{
				FreeLibrary(hInstLib);
				return 605;
			}
			// Get the module list for this process
			modentry.dwSize=sizeof(MODULEENTRY32);
			bResultm=Module32First(hSnapShotm, &modentry);

			// While there are modules, keep looping and checking
			while(bResultm)
			{
				if(_tcscmp(_tcsupr(modentry.szModule), szToTermUpper)==0)
				{
					// Process found, now terminate it
					Cntr++;
					if(Cntr==2)
					{
						FreeLibrary(hInstLib);
						iFound=1;
						return 1;
					}
				}
				else
				{  // Look for next modules for this process
					modentry.dwSize=sizeof(MODULEENTRY32);
					bResultm=Module32Next(hSnapShotm, &modentry);
				}
			}

			//Keep looking
			procentry.dwSize = sizeof(PROCESSENTRY32);
			bResult = Process32Next(hSnapShot, &procentry);
		}
	}
	if(iFound==0)
	{
		FreeLibrary(hInstLib);
		return 603;
	}
	FreeLibrary(hInstLib);
	return 0;
}

void OtherInstance::get_processname(TCHAR* szProcess, int nSize)
{

	TCHAR szPath[_MAX_PATH];
	_tcscpy_s(szPath, _MAX_PATH, _T(""));
	GetModuleFileName (NULL, szPath, nSize);

	TCHAR fname[_MAX_FNAME];
	TCHAR ext[_MAX_EXT];
	_tsplitpath( szPath, NULL, NULL, fname, ext );
	_stprintf_s(szProcess, nSize, _T("%s%s"), fname, ext );
	
}

//2008.12.19
HWND OtherInstance::GetHwndOtherInstance()
{
	CString szInstance;
	TCHAR szProcess[_MAX_PATH];
	_tcscpy_s(szProcess, _MAX_PATH, _T(""));
	bool AlreadyRunning = false;
	// 유일 값 지정 
	// -15D8B9A6-FCFD-46d0-8B24-A7FE161683A2 이 부분만 님들이 원하는 값으로 변경 하세요..  GUIDGEN 사용 
	get_processname(szProcess, _countof(szProcess));
	szInstance = szProcess;
	szInstance += _T("-12ED4509-ECD6-4AF3-ACD0-C773F527194D");

	if(FindProcess(szProcess) == 1)
		AlreadyRunning = true;
	if ( AlreadyRunning )
	{ /* kill this */
		HWND hOther = g_BLACK_SCREENApp;

		if (hOther != NULL)
		{
			return hOther;
		}

		return NULL; // terminates the creation
	} /* kill this */
	// ... continue with InitInstance
	return NULL;
}
bool OtherInstance::IsThereAnyOtherInstance()
{
	CString szInstance;
	TCHAR szProcess[_MAX_PATH];
	_tcscpy_s(szProcess, _MAX_PATH, _T(""));
	bool AlreadyRunning = false;
	// 유일 값 지정 
	// -15D8B9A6-FCFD-46d0-8B24-A7FE161683A2 이 부분만 님들이 원하는 값으로 변경 하세요..  GUIDGEN 사용 
	get_processname(szProcess, _countof(szProcess));
	szInstance = szProcess;
	szInstance += _T("-DFFABF39-5B05-456E-8167-6CBD5FAC0477");

	if(FindProcess(szProcess) == 1)
		AlreadyRunning = true;
	if ( AlreadyRunning )
	{ /* kill this */
		HWND hOther = g_BLACK_SCREENApp;

		//CString szWarning;
		//szWarning =  get_processname() + _T("- Program is Already Running. ");
		//AfxMessageBox(szWarning);


		if (hOther != NULL)
		{ /* pop up */
			::SetForegroundWindow(hOther);

			if (::IsIconic(hOther))
			{ /* restore */
				::ShowWindow(hOther, SW_RESTORE);
			} /* restore */
		} /* pop up */

		return true; // terminates the creation
	} /* kill this */
	// ... continue with InitInstance
	return false;
}

BEGIN_MESSAGE_MAP(OtherInstance, CWnd)
	//{{AFX_MSG_MAP(OtherInstance)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// OtherInstance message handlers
