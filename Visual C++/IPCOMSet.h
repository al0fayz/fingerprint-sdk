#if !defined(AFX_IPCOMSET_H__21CF1332_2B90_4980_B9B6_855D42CB07BF__INCLUDED_)
#define AFX_IPCOMSET_H__21CF1332_2B90_4980_B9B6_855D42CB07BF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// IPCOMSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CIPCOMSet dialog

class CIPCOMSet : public CDialog
{
// Construction
public:
	CIPCOMSet(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CIPCOMSet)
	enum { IDD = IDD_IPCom };
	CEdit	m_Com;
	CIPAddressCtrl	m_IP;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIPCOMSet)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CIPCOMSet)
	afx_msg void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IPCOMSET_H__21CF1332_2B90_4980_B9B6_855D42CB07BF__INCLUDED_)
