// SecondSet.cpp : implementation file
//

#include "stdafx.h"
#include "SoapSetting.h"
#include "SecondSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSecondSet dialog


CSecondSet::CSecondSet(CWnd* pParent /*=NULL*/)
	: CDialog(CSecondSet::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSecondSet)
	//}}AFX_DATA_INIT
}


void CSecondSet::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSecondSet)
	DDX_Control(pDX, IDC_EDIT4, m_Jo);
	DDX_Control(pDX, IDC_EDIT3, m_Fin);
	DDX_Control(pDX, IDC_EDIT2, m_Finger);
	DDX_Control(pDX, IDC_EDIT1, m_Job);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSecondSet, CDialog)
	//{{AFX_MSG_MAP(CSecondSet)
	ON_BN_CLICKED(IDC_BUTTON1, OnOK)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSecondSet message handlers

void CSecondSet::OnOK() 
{
	// TODO: Add your control notification handler code here
	CSoapSettingApp *app = (CSoapSettingApp *)AfxGetApp();
	m_Job.GetWindowText(app->strJob);
	m_Finger.GetWindowText(app->strFinger);
	CDialog::OnOK();	
}

BOOL CSecondSet::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CSoapSettingApp *app = (CSoapSettingApp *)AfxGetApp();
	if(strcmp(app->Idd,"1")==0)
	{
		m_Jo.SetWindowText ("JobNum:");
		m_Finger.ShowWindow(FALSE);
		m_Fin.ShowWindow(FALSE);
		m_Job.SetWindowText("All");
	}
	else if(strcmp(app->Idd,"2")==0)	
	{
		m_Jo.SetWindowText ("JobNum:");
		m_Finger.ShowWindow(FALSE);
		m_Fin.ShowWindow(FALSE);
		m_Job.SetWindowText("All");
	}
	else if(strcmp(app->Idd,"3")==0)	
	{
		m_Jo.SetWindowText ("Name:");
		m_Finger.ShowWindow(FALSE);
		m_Fin.ShowWindow(FALSE);
	}
	if(strcmp(app->Idd,"4")==0)
	{
		m_Jo.SetWindowText ("JobNum:");
		m_Finger.ShowWindow(FALSE);
		m_Fin.ShowWindow(FALSE);
	}
	else if(strcmp(app->Idd,"5")==0)	
	{
		m_Jo.SetWindowText ("Name:");
		m_Fin.SetWindowText("Value:");
	}
	
	return FALSE;  // return TRUE unless you set the focus to a control
	
	              // EXCEPTION: OCX Property Pages should return FALSE
}

int CSecondSet::DoModal() 
{
	// TODO: Add your specialized code here and/or call the base class
	CSoapSettingApp *app = (CSoapSettingApp *)AfxGetApp();
	if((app->strCom.IsEmpty()==0)&&(app->strIP.IsEmpty()==0))
	{
	return CDialog::DoModal();
	}
}
