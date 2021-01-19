#if !defined(AFX_MYLIST_H__383B40B9_27C0_4B89_9103_6544D86CCA60__INCLUDED_)
#define AFX_MYLIST_H__383B40B9_27C0_4B89_9103_6544D86CCA60__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyList.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMyList form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CMyList : public CFormView
{
protected:
	CMyList();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CMyList)

// Form Data
public:
	//{{AFX_DATA(CMyList)
	enum { IDD = IDD_MYLIST_FORM };
	CListBox	m_List;
	//}}AFX_DATA
	void CMyList::DisplayMsg( LPCSTR lpFormat, ... );

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyList)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CMyList();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CMyList)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYLIST_H__383B40B9_27C0_4B89_9103_6544D86CCA60__INCLUDED_)
