// SoapSettingView.h : interface of the CSoapSettingView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SOAPSETTINGVIEW_H__46DAB40D_46C7_46D4_9EF2_2E79FE9FED34__INCLUDED_)
#define AFX_SOAPSETTINGVIEW_H__46DAB40D_46C7_46D4_9EF2_2E79FE9FED34__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CSoapSettingView : public CView
{
protected: // create from serialization only
	CSoapSettingView();
	DECLARE_DYNCREATE(CSoapSettingView)

// Attributes
public:
	CSoapSettingDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSoapSettingView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSoapSettingView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CSoapSettingView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in SoapSettingView.cpp
inline CSoapSettingDoc* CSoapSettingView::GetDocument()
   { return (CSoapSettingDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SOAPSETTINGVIEW_H__46DAB40D_46C7_46D4_9EF2_2E79FE9FED34__INCLUDED_)
