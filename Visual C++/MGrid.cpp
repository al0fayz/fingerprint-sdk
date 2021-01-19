// MGrid.cpp : implementation file
//

#include "stdafx.h"
#include "soapsetting.h"
#include "MGrid.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMGrid

IMPLEMENT_DYNCREATE(CMGrid, CFormView)

CMGrid::CMGrid()
	: CFormView(CMGrid::IDD)
{
	 pList=0;
	//{{AFX_DATA_INIT(CMGrid)
	//}}AFX_DATA_INIT
}

CMGrid::~CMGrid()
{
	 delete   pList;
}

void CMGrid::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMGrid)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMGrid, CFormView)
	//{{AFX_MSG_MAP(CMGrid)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMGrid diagnostics

#ifdef _DEBUG
void CMGrid::AssertValid() const
{
	CFormView::AssertValid();
}

void CMGrid::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMGrid message handlers



void CMGrid::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();
	CRect   rect;   
	GetClientRect(&rect);  // 
	
	// TODO: Add your specialized code here and/or call the base class
	pList   =   new   CListCtrl;   
    pList->Create(WS_CHILD|WS_VISIBLE|LVS_REPORT|LVS_ALIGNTOP|LVS_AUTOARRANGE| LVS_SHOWSELALWAYS,rect, this, IDC_LIST2);   
	pList->SetExtendedStyle(LVS_EX_CHECKBOXES|LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
}
