// UserInfo.cpp : implementation file
//

#include "stdafx.h"
#include "soapsetting.h"
#include "UserInfo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUserInfo dialog


CUserInfo::CUserInfo(CWnd* pParent /*=NULL*/)
	: CDialog(CUserInfo::IDD, pParent)
{
	//{{AFX_DATA_INIT(CUserInfo)
	m_Groupi = 0;
	m_TZ1i = 0;
	m_TZ2i = 0;
	m_TZ3i = 0;
	//}}AFX_DATA_INIT
}


void CUserInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CUserInfo)
	DDX_Control(pDX, IDC_EDIT8, m_TZ3);
	DDX_Control(pDX, IDC_EDIT7, m_TZ2);
	DDX_Control(pDX, IDC_EDIT6, m_TZ1);
	DDX_Control(pDX, IDC_EDIT4, m_Group);
	DDX_Control(pDX, IDC_COMBO1, m_Privilege);
	DDX_Control(pDX, IDC_EDIT2, m_Card);
	DDX_Control(pDX, IDC_EDIT3, m_Name);
	DDX_Control(pDX, IDC_EDIT5, m_Pass);
	DDX_Control(pDX, IDC_EDIT1, m_ID);
	DDX_Text(pDX, IDC_EDIT4, m_Groupi);
	DDV_MinMaxInt(pDX, m_Groupi, 1, 5);
	DDX_Text(pDX, IDC_EDIT6, m_TZ1i);
	DDV_MinMaxInt(pDX, m_TZ1i, 0, 50);
	DDX_Text(pDX, IDC_EDIT7, m_TZ2i);
	DDV_MinMaxInt(pDX, m_TZ2i, 0, 50);
	DDX_Text(pDX, IDC_EDIT8, m_TZ3i);
	DDV_MinMaxInt(pDX, m_TZ3i, 0, 50);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CUserInfo, CDialog)
	//{{AFX_MSG_MAP(CUserInfo)
	ON_BN_CLICKED(IDC_BUTTON2, OnOk)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUserInfo message handlers

void CUserInfo::OnOk() 
{
	// TODO: Add your control notification handler code here
	CString ss,ss1,ss2;
	m_ID.GetWindowText(ss);
	if((ss.IsEmpty())||(strcmp(ss,"")==0))
	{
		AfxMessageBox("Please input UserID.");
		return;
	}
	int ff,ff1,ff2;
	ff=m_ID.GetWindowTextLength();
	if(ff>9)
	{
		AfxMessageBox("UserID overstep 9 digit, Please input it over again.");
		m_ID.SetWindowText("");
		return;
	}
	ff=m_Name.GetWindowTextLength();
	if(ff>7)
	{
		AfxMessageBox("Name overstep 7 digit, Please input it over again.");
		m_Name.SetWindowText("");
		return;
	}
	ff=m_Pass.GetWindowTextLength();
	if(ff>4)
	{
		AfxMessageBox("Password overstep 4 digit, Please input it over again.");
		m_Pass.SetWindowText("");
		return;
	}
	m_TZ1.GetWindowText(ss);
	ff=atoi(ss);
	m_TZ2.GetWindowText(ss1);
	ff1=atoi(ss1);
	m_TZ3.GetWindowText(ss2);
	ff2=atoi(ss2);
	if((ff==0)&&((ff1>0)||(ff2>0)))
	{
		AfxMessageBox("Please input TZ1 first,then input others.");
		return;
	}
	if((ff>0)&&((ff1==0)&&(ff2>0)))
	{
		AfxMessageBox("Please input TZ2 first,then input others.");
		return;
	}
	/*
	ff=m_Card.GetWindowTextLength();
	if(ff>10)
	{
		AfxMessageBox("CardNumber overstep 10 digit, Please input it over again.");
		m_Card.SetWindowText("");
		return;
	}
	*/

	CSoapSettingApp *app = (CSoapSettingApp *)AfxGetApp();
	//m_Card.GetWindowText(app->strCard);
	m_ID.GetWindowText(app->strID);
	m_Pass.GetWindowText(app->strPass);
	m_Name.GetWindowText(app->strName);
	m_Group.GetWindowText(app->strGroup);
	m_TZ1.GetWindowText(app->strTZ1);
	m_TZ2.GetWindowText(app->strTZ2);
	m_TZ3.GetWindowText(app->strTZ3);
	int nIndex = m_Privilege.GetCurSel();
	if(nIndex==1)
	{app->strPrivilege="14";}
	else
	{app->strPrivilege="0";}
	CDialog::OnOK();	
}

BOOL CUserInfo::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_Privilege.InsertString(0,"User");
	m_Privilege.InsertString(1,"Administrator");
	m_Privilege.SetCurSel(0);
	m_Group.SetWindowText("1");
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

int CUserInfo::DoModal() 
{
	// TODO: Add your specialized code here and/or call the base class
	CSoapSettingApp *app = (CSoapSettingApp *)AfxGetApp();
	if((app->strCom.IsEmpty()==0)&&(app->strIP.IsEmpty()==0))
	{
	return CDialog::DoModal();
	}
}
