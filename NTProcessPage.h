#if !defined(AFX_NTPROCESSPAGE_H__CCB1C644_9421_11D2_AEB2_0000E8D7EAF2__INCLUDED_)
#define AFX_NTPROCESSPAGE_H__CCB1C644_9421_11D2_AEB2_0000E8D7EAF2__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// NTProcessPage.h : header file
//

#include "WindowInfo.h"
#include <windows.h>
#include <vdmdbg.h>
#include <string.h>
#include <afxtempl.h>
#include "StaticEx.h"

#include "psapi.h"

typedef BOOL (WINAPI *GETPROCESSMEMORYINFO)
(
    HANDLE	Process,
    PPROCESS_MEMORY_COUNTERS ppsmemCounters,
    DWORD cb
);

//Windows NT Functions
typedef BOOL (WINAPI *ENUMPROCESSES)
(
	DWORD*	lpidProcess,  // array to receive the process identifiers
	DWORD	cb,           // size of the array
	DWORD*	cbNeeded      // receives the number of bytes returned
);

typedef BOOL (WINAPI *ENUMPROCESSMODULES)
(
	HANDLE		hProcess,   // handle to the process
	HMODULE*	lphModule,  // array to receive the module handles
	DWORD		cb,         // size of the array
	LPDWORD		lpcbNeeded  // receives the number of bytes returned
);

typedef DWORD (WINAPI *GETMODULEFILENAME)
(
	HANDLE	hProcess,		// handle to the process
	HMODULE	hModule,		// handle to the module
	LPTSTR	lpstrFileName,	// array to receive filename
	DWORD	nSize			// size of filename array.
);

typedef DWORD (WINAPI *GETMODULEBASENAME)
(
	HANDLE	hProcess,		// handle to the process
	HMODULE	hModule,		// handle to the module
	LPTSTR	lpstrFileName,	// array to receive base name of module
	DWORD	nSize			// size of module name array.
);

typedef INT (WINAPI *VDMENUMTASKWOWEX)
(
	DWORD			dwProcessId,	// ID of NTVDM process
	TASKENUMPROCEX	fp,				// address of our callback function
	LPARAM			lparam			// anything we want to pass to the callback function.
);

/////////////////////////////////////////////////////////////////////////////
// CNTProcessPage dialog

class CNTProcessPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CNTProcessPage)

// Construction
public:
	CNTProcessPage();
	~CNTProcessPage();

// Dialog Data
	//{{AFX_DATA(CNTProcessPage)
	enum { IDD = IDD_NTPROCESSES };
	CStaticEx	m_InvalidWindow;
	CString	m_pid;
	CString	m_tid;
	CString	m_ExeName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CNTProcessPage)
	public:
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CNTProcessPage)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	HANDLE m_psapiHandle;
	HANDLE m_vdmdbgHandle;

	WindowInfo* m_pWindowInfo;

    ENUMPROCESSES       m_pFnEnumProcesses;
    GETMODULEFILENAME   m_pFnGetModuleFileName;
    ENUMPROCESSMODULES  m_pFnEnumProcessModules;  
	VDMENUMTASKWOWEX	m_pFnVDMEnumTaskWOWEx;
	GETMODULEBASENAME	m_pFnGetModuleBaseName;
	GETPROCESSMEMORYINFO m_pFnGetProcessMemoryInfo;

public:
	void updateDialog();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NTPROCESSPAGE_H__CCB1C644_9421_11D2_AEB2_0000E8D7EAF2__INCLUDED_)
