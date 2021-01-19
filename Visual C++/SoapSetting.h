// SoapSetting.h : main header file for the SOAPSETTING application
//

#if !defined(AFX_SOAPSETTING_H__E8DB4E02_DE0E_476F_9AC4_14C3451AD074__INCLUDED_)
#define AFX_SOAPSETTING_H__E8DB4E02_DE0E_476F_9AC4_14C3451AD074__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CSoapSettingApp:
// See SoapSetting.cpp for the implementation of this class
//

class CSoapSettingApp : public CWinApp
{
public:
	CSoapSettingApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSoapSettingApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL
	CString strIP,strCom,strJob,strFinger,Idd;
	CString strID,strPass,strName,strPrivilege,strCard,strDate,strTime,strGroup,strTZ1,strTZ2,strTZ3;

// Implementation
	//{{AFX_MSG(CSoapSettingApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SOAPSETTING_H__E8DB4E02_DE0E_476F_9AC4_14C3451AD074__INCLUDED_)
