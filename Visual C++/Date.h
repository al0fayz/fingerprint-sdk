#if !defined(AFX_DATE_H__FCD99B95_125D_47CF_A357_05519DCB5A4B__INCLUDED_)
#define AFX_DATE_H__FCD99B95_125D_47CF_A357_05519DCB5A4B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Date.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDate dialog

class CDate : public CDialog
{
// Construction
public:
	CDate(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDate)
	enum { IDD = IDD_DateTime };
	CDateTimeCtrl	m_Date;
	CDateTimeCtrl	m_Time;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDate)
	public:
	virtual int DoModal();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDate)
	afx_msg void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DATE_H__FCD99B95_125D_47CF_A357_05519DCB5A4B__INCLUDED_)
