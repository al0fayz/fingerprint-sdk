// MyList.cpp : implementation file
//

#include "stdafx.h"
#include "soapsetting.h"
#include "MyList.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyList

IMPLEMENT_DYNCREATE(CMyList, CFormView)

CMyList::CMyList()
	: CFormView(CMyList::IDD)
{
	//{{AFX_DATA_INIT(CMyList)
	//}}AFX_DATA_INIT
}

CMyList::~CMyList()
{
}

void CMyList::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMyList)
	DDX_Control(pDX, IDC_LIST1, m_List);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMyList, CFormView)
	//{{AFX_MSG_MAP(CMyList)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyList diagnostics

#ifdef _DEBUG
void CMyList::AssertValid() const
{
	CFormView::AssertValid();
}

void CMyList::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyList message handlers
void CMyList::DisplayMsg( LPCSTR lpFormat, ... )
{

	char tchMsg[1024];
	va_list vl;
	va_start( vl, lpFormat );
    vsprintf( tchMsg, lpFormat, vl );
	va_end(vl);
	CString ff;
	int n = m_List.GetCount();

	if ( n >= 1000 )
		m_List.DeleteString(0); 

	m_List.InsertString( m_List.GetCount(), tchMsg );
	m_List.SetCurSel( m_List.GetCount() - 1 );
	
}

void CMyList::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();
	
	// TODO: Add your specialized code here and/or call the base class
	CRect   rect;   
	GetClientRect(&rect);  // 
	
	// TODO: Add your specialized code here and/or call the base class
	m_List.DestroyWindow ();
    m_List.Create(WS_CHILD|WS_VISIBLE|LVS_AUTOARRANGE|LVS_REPORT|LVS_ALIGNTOP,rect, this, IDC_LIST1);   	
}
