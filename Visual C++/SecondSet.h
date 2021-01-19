#if !defined(AFX_SECONDSET_H__ADCCA81D_5B2B_4A12_9ED0_5723C92F4EDE__INCLUDED_)
#define AFX_SECONDSET_H__ADCCA81D_5B2B_4A12_9ED0_5723C92F4EDE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SecondSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSecondSet dialog

class CSecondSet : public CDialog
{
// Construction
public:
	CSecondSet(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSecondSet)
	enum { IDD = IDD_Second };
	CEdit	m_Jo;
	CEdit	m_Fin;
	CEdit	m_Finger;
	CEdit	m_Job;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSecondSet)
	public:
	virtual int DoModal();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSecondSet)
	afx_msg void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SECONDSET_H__ADCCA81D_5B2B_4A12_9ED0_5723C92F4EDE__INCLUDED_)
