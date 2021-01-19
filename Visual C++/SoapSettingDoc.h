// SoapSettingDoc.h : interface of the CSoapSettingDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SOAPSETTINGDOC_H__8A65A23F_F1A5_419D_BF1B_8EE396557580__INCLUDED_)
#define AFX_SOAPSETTINGDOC_H__8A65A23F_F1A5_419D_BF1B_8EE396557580__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CSoapSettingDoc : public CDocument
{
protected: // create from serialization only
	CSoapSettingDoc();
	DECLARE_DYNCREATE(CSoapSettingDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSoapSettingDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSoapSettingDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CSoapSettingDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SOAPSETTINGDOC_H__8A65A23F_F1A5_419D_BF1B_8EE396557580__INCLUDED_)
