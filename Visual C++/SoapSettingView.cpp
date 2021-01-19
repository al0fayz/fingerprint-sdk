// SoapSettingView.cpp : implementation of the CSoapSettingView class
//

#include "stdafx.h"
#include "SoapSetting.h"

#include "SoapSettingDoc.h"
#include "SoapSettingView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSoapSettingView

IMPLEMENT_DYNCREATE(CSoapSettingView, CView)

BEGIN_MESSAGE_MAP(CSoapSettingView, CView)
	//{{AFX_MSG_MAP(CSoapSettingView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSoapSettingView construction/destruction

CSoapSettingView::CSoapSettingView()
{
	// TODO: add construction code here

}

CSoapSettingView::~CSoapSettingView()
{
}

BOOL CSoapSettingView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CSoapSettingView drawing

void CSoapSettingView::OnDraw(CDC* pDC)
{
	CSoapSettingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CSoapSettingView diagnostics

#ifdef _DEBUG
void CSoapSettingView::AssertValid() const
{
	CView::AssertValid();
}

void CSoapSettingView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSoapSettingDoc* CSoapSettingView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSoapSettingDoc)));
	return (CSoapSettingDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSoapSettingView message handlers
