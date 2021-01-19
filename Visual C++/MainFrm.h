// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__5A08D02B_047C_4135_AFC3_82D2782619C8__INCLUDED_)
#define AFX_MAINFRM_H__5A08D02B_047C_4135_AFC3_82D2782619C8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CMainFrame : public CFrameWnd
{
	
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:
	CString ssl;
	CSplitterWnd m_Splitter;
	vector <FingerTemplate>  ss;
	FingerTemplate sa;
	CString sIP,sCom;
// Operations
public:

	static UINT MyThread(LPVOID pParam);
	CWinThread* pMyThread;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
public:

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg void OnEDITGetAllUserInfo();
	afx_msg void OnClearAllUserInfo();
	afx_msg void OnFILESet();
	afx_msg void OnEDITGetAttlog();
	afx_msg void OnEDITGetUserInfo();
	afx_msg void OnEDITGetUserTemplate();
	afx_msg void OnEDITGetDate();
	afx_msg void OnEDITGetOption();
	afx_msg void OnEDITSetDate();
	afx_msg void OnEDITSetOption();
	afx_msg void OnEDITRestart();
	afx_msg void OnEDITRefreshDB();
	afx_msg void OnEDITSetUserInfo();
	afx_msg void OnEDITSetUserTemplate();
	afx_msg void OnEDITDeleteUser();
	afx_msg void OnEDITDeleteTemplate();
	afx_msg void OnEDITClearUserPassword();
	afx_msg void OnClearAllAttlog();
	afx_msg void OnClearAllTemplate();
	afx_msg void OnEDITTestTemplate();
	void OnSetAllUserInfo();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__5A08D02B_047C_4135_AFC3_82D2782619C8__INCLUDED_)
