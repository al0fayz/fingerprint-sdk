// IPCOMSet.cpp : implementation file
//

#include "stdafx.h"
#include "SoapSetting.h"
#include "IPCOMSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CIPCOMSet dialog


CIPCOMSet::CIPCOMSet(CWnd* pParent /*=NULL*/)
	: CDialog(CIPCOMSet::IDD, pParent)
{
	//{{AFX_DATA_INIT(CIPCOMSet)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CIPCOMSet::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CIPCOMSet)
	DDX_Control(pDX, IDC_EDIT1, m_Com);
	DDX_Control(pDX, IDC_IPADDRESS1, m_IP);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CIPCOMSet, CDialog)
	//{{AFX_MSG_MAP(CIPCOMSet)
	ON_BN_CLICKED(IDC_BUTTON1, OnOK)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIPCOMSet message handlers

void CIPCOMSet::OnOK() 
{
	// TODO: Add your control notification handler code here
	CSoapSettingApp *app = (CSoapSettingApp *)AfxGetApp();
	m_IP.GetWindowText(app->strIP);
	m_Com.GetWindowText(app->strCom);
	if((app->strIP.Compare("0.0.0.0")<=0)||(app->strCom.IsEmpty()))
	{
		app->strIP="";app->strCom="";}
	CDialog::OnOK();
}

BOOL CIPCOMSet::OnInitDialog() 
{
	CDialog::OnInitDialog();
	CSoapSettingApp *app = (CSoapSettingApp *)AfxGetApp();
	if(app->strIP.IsEmpty())
	m_IP.SetWindowText("0.0.0.0");
	else
	m_IP.SetWindowText(app->strIP);

	if(app->strCom.IsEmpty())
	m_Com.SetWindowText("0");
	else
	m_Com.SetWindowText(app->strCom);
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
