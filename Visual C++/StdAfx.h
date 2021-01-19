// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__B8D0332E_DB63_495F_9941_72BD0BB3C58E__INCLUDED_)
#define AFX_STDAFX_H__B8D0332E_DB63_495F_9941_72BD0BB3C58E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers
#include <afxcview.h>
#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT
#import "C:\windows\system32\msxml4.dll"
using namespace MSXML2;
#import "C:\Program Files\Common Files\MSSoap\Binaries\mssoap30.dll" exclude("IStream", "IErrorInfo", "ISequentialStream", "_LARGE_INTEGER","_ULARGE_INTEGER", "tagSTATSTG", "_FILETIME")
using namespace MSSOAPLib30;
#include <vector>
using namespace std; 
typedef struct _tagFingerTemplate
{
	CString Id;
	CString Fid;
	CString Size;
	CString Template;
	CString Valid;
}FingerTemplate;

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__B8D0332E_DB63_495F_9941_72BD0BB3C58E__INCLUDED_)
