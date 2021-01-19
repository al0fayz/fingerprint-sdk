// Date.cpp : implementation file
//

#include "stdafx.h"
#include "soapsetting.h"
#include "Date.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDate dialog


CDate::CDate(CWnd* pParent /*=NULL*/)
	: CDialog(CDate::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDate)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDate::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDate)
	DDX_Control(pDX, IDC_DATETIMEPICKER1, m_Date);
	DDX_Control(pDX, IDC_DATETIMEPICKER2, m_Time);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDate, CDialog)
	//{{AFX_MSG_MAP(CDate)
	ON_BN_CLICKED(IDC_BUTTON1, OnOK)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDate message handlers

void CDate::OnOK() 
{
	// TODO: Add your control notification handler code here
	CSoapSettingApp *app = (CSoapSettingApp *)AfxGetApp();
	m_Date.GetWindowText(app->strDate);
	m_Time.GetWindowText(app->strTime);
	CDialog::OnOK();	
}

int CDate::DoModal() 
{
	// TODO: Add your specialized code here and/or call the base class
	CSoapSettingApp *app = (CSoapSettingApp *)AfxGetApp();
	if((app->strCom.IsEmpty()==0)&&(app->strIP.IsEmpty()==0))
	{
	return CDialog::DoModal();
	}
}
