#if !defined(AFX_MGRID_H__F03B470A_75DF_4B82_8B65_F7B5EE3EE950__INCLUDED_)
#define AFX_MGRID_H__F03B470A_75DF_4B82_8B65_F7B5EE3EE950__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MGrid.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMGrid form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CMGrid : public CFormView
{
protected:
	CMGrid();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CMGrid)

// Form Data
public:
	//{{AFX_DATA(CMGrid)
	enum { IDD = IDD_MGRID_FORM };
	CListCtrl	*pList;
	//}}AFX_DATA

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMGrid)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CMGrid();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CMGrid)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MGRID_H__F03B470A_75DF_4B82_8B65_F7B5EE3EE950__INCLUDED_)
