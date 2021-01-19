#if !defined(AFX_USERINFO_H__04BA05EC_9A85_4A89_AD0B_07517550054A__INCLUDED_)
#define AFX_USERINFO_H__04BA05EC_9A85_4A89_AD0B_07517550054A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// UserInfo.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CUserInfo dialog

class CUserInfo : public CDialog
{
// Construction
public:
	CUserInfo(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CUserInfo)
	enum { IDD = IDD_UserInfo };
	CEdit	m_TZ3;
	CEdit	m_TZ2;
	CEdit	m_TZ1;
	CEdit	m_Group;
	CComboBox	m_Privilege;
	CEdit	m_Card;
	CEdit	m_Name;
	CEdit	m_Pass;
	CEdit	m_ID;
	int		m_Groupi;
	int		m_TZ1i;
	int		m_TZ2i;
	int		m_TZ3i;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUserInfo)
	public:
	virtual int DoModal();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CUserInfo)
	afx_msg void OnOk();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_USERINFO_H__04BA05EC_9A85_4A89_AD0B_07517550054A__INCLUDED_)
