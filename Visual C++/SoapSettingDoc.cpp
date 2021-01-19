// SoapSettingDoc.cpp : implementation of the CSoapSettingDoc class
//

#include "stdafx.h"
#include "SoapSetting.h"

#include "SoapSettingDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSoapSettingDoc

IMPLEMENT_DYNCREATE(CSoapSettingDoc, CDocument)

BEGIN_MESSAGE_MAP(CSoapSettingDoc, CDocument)
	//{{AFX_MSG_MAP(CSoapSettingDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSoapSettingDoc construction/destruction

CSoapSettingDoc::CSoapSettingDoc()
{
	// TODO: add one-time construction code here

}

CSoapSettingDoc::~CSoapSettingDoc()
{
}

BOOL CSoapSettingDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CSoapSettingDoc serialization

void CSoapSettingDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CSoapSettingDoc diagnostics

#ifdef _DEBUG
void CSoapSettingDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSoapSettingDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSoapSettingDoc commands
