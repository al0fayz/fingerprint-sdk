// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "SoapSetting.h"
#include "MainFrm.h"
#include "MyList.h"
#include "IPCOMSet.h"
#include "SecondSet.h"
#include "MGrid.h"
#include "UserInfo.h"
#include "Date.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_COMMAND(ID_FILE_Set, OnFILESet)
	ON_COMMAND(ID_EDIT_GetAttlog, OnEDITGetAttlog)
	ON_COMMAND(ID_EDIT_GetUserInfo, OnEDITGetUserInfo)
	ON_COMMAND(ID_EDIT_GetUserTemplate, OnEDITGetUserTemplate)
	ON_COMMAND(ID_EDIT_GetDate, OnEDITGetDate)
	ON_COMMAND(ID_EDIT_GetAllUserInfo, OnEDITGetAllUserInfo)
	ON_COMMAND(ID_EDIT_GetOption, OnEDITGetOption)
	ON_COMMAND(ID_EDIT_SetDate, OnEDITSetDate)
	ON_COMMAND(ID_EDIT_SetOption, OnEDITSetOption)
	ON_COMMAND(ID_EDIT_Restart, OnEDITRestart)
	ON_COMMAND(ID_EDIT_RefreshDB, OnEDITRefreshDB)
	ON_COMMAND(ID_EDIT_SetUserInfo, OnEDITSetUserInfo)
	ON_COMMAND(ID_EDIT_SetUserTemplate, OnEDITSetUserTemplate)
	ON_COMMAND(ID_EDIT_DeleteUser, OnEDITDeleteUser)
	ON_COMMAND(ID_EDIT_DeleteTemplate, OnEDITDeleteTemplate)
	ON_COMMAND(ID_EDIT_ClearUserPassword, OnEDITClearUserPassword)
	ON_COMMAND(ID_ClearAllAttlog, OnClearAllAttlog)
	ON_COMMAND(ID_ClearAllTemplate, OnClearAllTemplate)
	ON_COMMAND(ID_ClearAllUserInfo, OnClearAllUserInfo)
	ON_COMMAND(ID_EDIT_TestTemplate, OnEDITTestTemplate)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	CoInitialize(NULL);
	CSoapSettingApp *app = (CSoapSettingApp *)AfxGetApp();
}

CMainFrame::~CMainFrame()
{
	CoUninitialize();
	ss.~vector<FingerTemplate>();
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
  	cs.style&=~FWS_ADDTOTITLE;
	cs.style&=~WS_MAXIMIZEBOX;
	m_strTitle = _T("SoapSetting"); 
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers


BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) 
{
	// TODO: Add your specialized code here and/or call the base class
	CRect cr;
	GetClientRect(&cr);
	CSize paneSize(cr.Width()*2/3, cr.Height() );
	m_Splitter.CreateStatic(this,1,2);
	m_Splitter.CreateView(0,1,RUNTIME_CLASS(CMyList),paneSize,pContext);
	m_Splitter.CreateView(0,0,RUNTIME_CLASS(CMGrid),paneSize,pContext);
	CenterWindow( GetDesktopWindow() );

	return TRUE;
	
	//return CFrameWnd::OnCreateClient(lpcs, pContext);
}

void CMainFrame::OnFILESet() 
{
	// TODO: Add your command handler code here
       CIPCOMSet dlg;
       dlg.DoModal();
	
}

void CMainFrame::OnEDITGetAttlog() 
{
	// TODO: Add your command handler code here
	CSoapSettingApp *app = (CSoapSettingApp *)AfxGetApp();
	if((app->strCom.IsEmpty()!=0)||(app->strIP.IsEmpty()!=0))
	{AfxMessageBox("Please input IP and ComKey.");}
	else
	{
	app->Idd="1";
    CSecondSet dlg;
    dlg.DoModal();
	if(app->strJob.IsEmpty())
	{}
	else
	{
	char SoapUrl[255+1];
	_bstr_t pp,mJob;
	CMyList *pView=(CMyList *)this->m_Splitter.GetPane(0,1);
	pView->DisplayMsg("Creatting Message: GetAttLog.......");
	CMGrid *bView=(CMGrid *)this->m_Splitter.GetPane(0,0);

	ISoapSerializerPtr Serializer=NULL;
    ISoapReaderPtr Reader=NULL;
    ISoapConnectorPtr Connector=NULL;
    Connector.CreateInstance(__uuidof(HttpConnector30));

	CString SoapUrl1;
	SoapUrl1="http://"+(app->strIP)+"/iWsService";
	mJob=app->strJob.AllocSysString();
	pp=app->strCom.AllocSysString();   
    int n=strlen(SoapUrl1); 
    strcpy(SoapUrl,SoapUrl1); 

	Connector->Property["EndPointURL"] = SoapUrl;
    Connector->Connect();
	Connector->Property["SoapAction"] = "uri:zksoftware";
	Connector->Property["Timeout"] = "6000000";    //(ms)   timeout=100min 
    // Begin the message.
    Connector->BeginMessage();
    // Create the SoapSerializer object.
    Serializer.CreateInstance(__uuidof(SoapSerializer30));
    // Connect the serializer object to the input stream of the connector object.
	Serializer->Init(_variant_t((IUnknown*)Connector->InputStream));
    // Build the SOAP Message.
	pView->DisplayMsg("Send Message: .......");
    Serializer->StartEnvelope("","","");
    Serializer->StartBody("");
	
	Serializer->StartElement("GetAttLog","http://www.zksoftware/Service/message/","","");

	Serializer->StartElement("ArgComKey","http://www.zksoftware/Service/message/","","");
	Serializer->WriteString(pp);
	Serializer->EndElement();

	Serializer->StartElement("Arg","","","");
	Serializer->StartElement("PIN","","","");
	Serializer->WriteString(mJob);
	Serializer->EndElement();
	
	Serializer->EndElement();

    Serializer->EndElement();
    Serializer->EndBody();
    Serializer->EndEnvelope();
	try{
		Connector->EndMessage();}
	catch (...)
	{
/*	CString ss;
	long ds=::GetLastError();
	ss.Format("%d",ds);*/
	pView->DisplayMsg("Send Message abnormity.");
	pView->DisplayMsg("connection false.");
	pView->DisplayMsg("");
	return;
	}

	if(Connector->OutputStream!=NULL)
	{
	pView->DisplayMsg("Recieve Message: ..........");
    Reader.CreateInstance(__uuidof(SoapReader30));
    // Connect the reader to the output stream of the connector object.
    Reader->Load(_variant_t((IUnknown*)Connector->OutputStream), "");

	MSXML2::IXMLDOMDocumentPtr pDoc; 
    HRESULT hr = pDoc.CreateInstance(__uuidof(MSXML2::DOMDocument30));
	MSXML2::IXMLDOMElementPtr  childNode;

	CListCtrl *vView=(CListCtrl*)bView->GetDlgItem(IDC_LIST2);
	vView->DeleteAllItems();
	while (vView->DeleteColumn(0));
	vView->InsertColumn(0,   "ID",   LVCFMT_LEFT,   100);   
	vView->InsertColumn(1,   "DateTime",   LVCFMT_LEFT,   164);   
	vView->InsertColumn(2,   "Verified",   LVCFMT_LEFT,   100);   
	vView->InsertColumn(3,   "Status",   LVCFMT_LEFT,   70);   
	vView->InsertColumn(4,   "WorkCord",   LVCFMT_LEFT,   70);   
    pDoc->loadXML(Reader->Dom->xml);
    childNode = (MSXML2::IXMLDOMElementPtr)(pDoc->selectSingleNode("//Row"));
    int sid=0;
    CString inf;
    while(childNode!=NULL)
	{
	  MSXML2::DOMNodeType nodeType;
      childNode->get_nodeType(&nodeType);
	  //Node Name
      BSTR var;
      //Node Value
      VARIANT varVal;
      childNode->get_nodeName(&var);
	  childNode->get_nodeTypedValue(&varVal);

	  MSXML2::IXMLDOMNodeListPtr childlist=NULL;
	  MSXML2::IXMLDOMNodePtr pnodeitem;
	  childNode->get_childNodes(&childlist);
	  long cCount ;
      childlist->get_length(&cCount);
	  CString info[5];
	  for(int m = 0 ; m < cCount ; m++)
      {           
		    childlist->get_item(m,&pnodeitem);                                           //char info[256]; sprintf(info,"%s=%s",(char*)(_bstr_t)pnodeitem->nodeName,(char*)(_bstr_t)pnodeitem->nodeTypedValue);//pView->DisplayMsg(info);
            info[m]=(LPCTSTR)((_bstr_t)pnodeitem->nodeTypedValue);
			//pView->DisplayMsg((LPCSTR)info[m]);
      }
	  vView->InsertItem(sid,info[0]);
	  vView->SetItemText(sid,1,info[1]);
	  vView->SetItemText(sid,2,info[2]);
	  vView->SetItemText(sid,3,info[3]);
	  vView->SetItemText(sid,4,info[4]);
	  childNode=childNode->nextSibling;
	  ++sid;
	}	
	inf.Format("Record Number:%d",sid);
	pView->DisplayMsg(inf);
	pView->DisplayMsg("");
	}
	app->strJob="";
	}	
	}
}

void CMainFrame::OnEDITGetUserInfo() 
{
	// TODO: Add your command handler code here
	CSoapSettingApp *app = (CSoapSettingApp *)AfxGetApp();
	if((app->strCom.IsEmpty()!=0)||(app->strIP.IsEmpty()!=0))
	{AfxMessageBox("Please input IP and ComKey.");}
	else
	{
	app->Idd="1";
    CSecondSet dlg;
    dlg.DoModal();
	if(app->strJob.IsEmpty())
	{}
	else
	{
	char SoapUrl[255+1];
	_bstr_t pp,mJob;

	ISoapSerializerPtr Serializer=NULL;
    ISoapReaderPtr Reader=NULL;
    ISoapConnectorPtr Connector=NULL;
	CMyList *pView=(CMyList *)this->m_Splitter.GetPane(0,1);
	pView->DisplayMsg("Creatting Message: GetUserInfo...........");
	CMGrid *bView=(CMGrid *)this->m_Splitter.GetPane(0,0);
    Connector.CreateInstance(__uuidof(HttpConnector30));

	CString SoapUrl1;
	SoapUrl1="http://"+(app->strIP)+"/iWsService";
	mJob=app->strJob.AllocSysString();
	pp=app->strCom.AllocSysString();   
    int n=strlen(SoapUrl1); 
    strcpy(SoapUrl,SoapUrl1); 

	Connector->Property["EndPointURL"] = SoapUrl;
    Connector->Connect();
	Connector->Property["SoapAction"] = "uri:zksoftware";
	Connector->Property["Timeout"] = "6000000";    //(ms)   timeout=100min 
    // Begin the message.
    Connector->BeginMessage();
    // Create the SoapSerializer object.
    Serializer.CreateInstance(__uuidof(SoapSerializer30));
    // Connect the serializer object to the input stream of the connector object.
	Serializer->Init(_variant_t((IUnknown*)Connector->InputStream));
    // Build the SOAP Message.
	pView->DisplayMsg("Send Message: .......");
    Serializer->StartEnvelope("","","");
    Serializer->StartBody("");
	
	Serializer->StartElement("GetUserInfo","http://www.zksoftware/Service/message/","","");

	Serializer->StartElement("ArgComKey","http://www.zksoftware/Service/message/","","");
	Serializer->WriteString(pp);
	Serializer->EndElement();

	Serializer->StartElement("Arg","","","");
	Serializer->StartElement("PIN","","","");
	Serializer->WriteString(mJob);
	Serializer->EndElement();
	
	Serializer->StartElement("FingerID","","","");
	Serializer->WriteString("All");
	Serializer->EndElement();
	
	Serializer->EndElement();

    Serializer->EndElement();
    Serializer->EndBody();
    Serializer->EndEnvelope();

	try{
		Connector->EndMessage(); }
	catch (...)
	{
	pView->DisplayMsg("Send Message abnormity.");
	pView->DisplayMsg("connection false.");
	pView->DisplayMsg("");
	return;
	}

	if(Connector->OutputStream!=NULL)
	{
	pView->DisplayMsg("Recieve Message: ..........");
    Reader.CreateInstance(__uuidof(SoapReader30));
    // Connect the reader to the output stream of the connector object.
    Reader->Load(_variant_t((IUnknown*)Connector->OutputStream), "");

	MSXML2::IXMLDOMDocumentPtr pDoc; 
    HRESULT hr = pDoc.CreateInstance(__uuidof(MSXML2::DOMDocument30));
	MSXML2::IXMLDOMElementPtr  childNode;

    pDoc->loadXML(Reader->Dom->xml);
    childNode = (MSXML2::IXMLDOMElementPtr)(pDoc->selectSingleNode("//Row"));
    int sid=0;
    CString inf;
 	CListCtrl *vView=(CListCtrl*)bView->GetDlgItem(IDC_LIST2);
	vView->DeleteAllItems();
	while (vView->DeleteColumn(0));
	vView->InsertColumn(0,   "UerID",   LVCFMT_LEFT,   80);   
	vView->InsertColumn(1,   "Name",   LVCFMT_LEFT,   81);   
	vView->InsertColumn(2,   "Password",   LVCFMT_LEFT,   60);   
	vView->InsertColumn(3,   "Group",   LVCFMT_LEFT,   45);   
	vView->InsertColumn(4,   "Privilege",   LVCFMT_LEFT,   68);   
	vView->InsertColumn(5,   "Card",   LVCFMT_LEFT,   80);   
 	vView->InsertColumn(6,   "TZ1",   LVCFMT_LEFT,   30);   
	vView->InsertColumn(7,   "TZ2",   LVCFMT_LEFT,   30);   
	vView->InsertColumn(8,   "TZ3",   LVCFMT_LEFT,   30);   
   while(childNode!=NULL)
	{
	  MSXML2::DOMNodeType nodeType;
      childNode->get_nodeType(&nodeType);
	  //Node Name
      BSTR var;
      //Node Value
      VARIANT varVal;
      childNode->get_nodeName(&var);
	  childNode->get_nodeTypedValue(&varVal);

	  MSXML2::IXMLDOMNodeListPtr childlist=NULL;
	  MSXML2::IXMLDOMNodePtr pnodeitem;
	  childNode->get_childNodes(&childlist);
	  long cCount ;
      childlist->get_length(&cCount);
      CString info[10];
	  for(int m = 0 ; m < cCount ; m++)
      {           
            childlist->get_item(m,&pnodeitem);
			info[m]=(LPCTSTR)((_bstr_t)pnodeitem->nodeTypedValue);
			//pView->DisplayMsg((LPCSTR)info[m]);			
      }  
	  vView->InsertItem(sid,info[6]);
	  vView->SetItemText(sid,1,info[1]);
	  vView->SetItemText(sid,2,info[2]);
	  vView->SetItemText(sid,3,info[3]);
	  vView->SetItemText(sid,4,info[4]);
	  vView->SetItemText(sid,5,info[5]); 
	  vView->SetItemText(sid,6,info[7]); 
	  vView->SetItemText(sid,7,info[8]); 
	  vView->SetItemText(sid,8,info[9]); 
	  childNode=childNode->nextSibling;
	  ++sid;
	}	
	inf.Format("Record Number:%d",sid);
	pView->DisplayMsg(inf);
	  pView->DisplayMsg("");
	}
	app->strJob="";
	}
	}
}

void CMainFrame::OnEDITGetDate() 
{
	// TODO: Add your command handler code here
	CSoapSettingApp *app = (CSoapSettingApp *)AfxGetApp();
	if((app->strCom.IsEmpty()!=0)||(app->strIP.IsEmpty()!=0))
	{AfxMessageBox("Please input IP and ComKey.");}
	else
	{
	char SoapUrl[255+1];
	_bstr_t pp,mJob;
	app->Idd="5";

	ISoapSerializerPtr Serializer=NULL;
    ISoapReaderPtr Reader=NULL;
    ISoapConnectorPtr Connector=NULL;
	CMyList *pView=(CMyList *)this->m_Splitter.GetPane(0,1);
	pView->DisplayMsg("Creatting Message: GetDate...........");
	CMGrid *bView=(CMGrid *)this->m_Splitter.GetPane(0,0);
    Connector.CreateInstance(__uuidof(HttpConnector30));

	CString SoapUrl1;
	SoapUrl1="http://"+(app->strIP)+"/iWsService";
	mJob=app->strJob.AllocSysString();
	pp=app->strCom.AllocSysString();   
    int n=strlen(SoapUrl1); 
    strcpy(SoapUrl,SoapUrl1); 

	Connector->Property["EndPointURL"] = SoapUrl;
    Connector->Connect();
	Connector->Property["SoapAction"] = "uri:zksoftware";
	Connector->Property["Timeout"] = "6000000";    //(ms)   timeout=100min 
    // Begin the message.
    Connector->BeginMessage();
    // Create the SoapSerializer object.
    Serializer.CreateInstance(__uuidof(SoapSerializer30));
    // Connect the serializer object to the input stream of the connector object.
	Serializer->Init(_variant_t((IUnknown*)Connector->InputStream));
    // Build the SOAP Message.
	pView->DisplayMsg("Send Message: .......");
    Serializer->StartEnvelope("","","");
    Serializer->StartBody("");
	
	Serializer->StartElement("GetDate","http://www.zksoftware/Service/message/","","");

	Serializer->StartElement("ArgComKey","http://www.zksoftware/Service/message/","","");
	Serializer->WriteString(pp);
	Serializer->EndElement();

    Serializer->EndElement();
    Serializer->EndBody();
    Serializer->EndEnvelope();

	try{
		Connector->EndMessage(); }
	catch (...)
	{
	pView->DisplayMsg("Send Message abnormity.");
	pView->DisplayMsg("connection false.");
	pView->DisplayMsg("");
	return;
	}

	if(Connector->OutputStream!=NULL)
	{
	pView->DisplayMsg("Recieve Message: ..........");
    Reader.CreateInstance(__uuidof(SoapReader30));
    // Connect the reader to the output stream of the connector object.
    Reader->Load(_variant_t((IUnknown*)Connector->OutputStream), "");

	MSXML2::IXMLDOMDocumentPtr pDoc; 
    HRESULT hr = pDoc.CreateInstance(__uuidof(MSXML2::DOMDocument30));
	MSXML2::IXMLDOMElementPtr  childNode;

    pDoc->loadXML(Reader->Dom->xml);
    childNode = (MSXML2::IXMLDOMElementPtr)(pDoc->selectSingleNode("//Row"));
 	CListCtrl *vView=(CListCtrl*)bView->GetDlgItem(IDC_LIST2);
	vView->DeleteAllItems();
	while (vView->DeleteColumn(0));
	vView->InsertColumn(0,   "Date",   LVCFMT_LEFT,   252);   
	vView->InsertColumn(1,   "Time",   LVCFMT_LEFT,   252);   
    int sid=0;
    while(childNode!=NULL)
	{
	  MSXML2::DOMNodeType nodeType;
      childNode->get_nodeType(&nodeType);
	  //Node Name
      BSTR var;
      //Node Value
      VARIANT varVal;
      childNode->get_nodeName(&var);
	  childNode->get_nodeTypedValue(&varVal);

	  MSXML2::IXMLDOMNodeListPtr childlist=NULL;
	  MSXML2::IXMLDOMNodePtr pnodeitem;
	  childNode->get_childNodes(&childlist);
	  long cCount ;
      childlist->get_length(&cCount);
      CString info[2];
	  for(int m = 0 ; m < cCount ; m++)
      {           
            childlist->get_item(m,&pnodeitem);
			info[m]=(LPCTSTR)((_bstr_t)pnodeitem->nodeTypedValue);		
      }
	  vView->InsertItem(sid,info[0]);
	  vView->SetItemText(sid,1,info[1]);
	  ++sid;
	  childNode=childNode->nextSibling;
	}	
	pView->DisplayMsg("");
	}
	}	
}

void CMainFrame::OnEDITGetUserTemplate() 
{
	// TODO: Add your command handler code here
	CSoapSettingApp *app = (CSoapSettingApp *)AfxGetApp();
	if((app->strCom.IsEmpty()!=0)||(app->strIP.IsEmpty()!=0))
	{AfxMessageBox("Please input IP and ComKey.");}
	else
	{
	app->Idd="2";
    CSecondSet dlg;
    dlg.DoModal();
	if(app->strJob.IsEmpty())
	{}
	else
	{
	char SoapUrl[255+1];
	_bstr_t pp,mJob;

	ISoapSerializerPtr Serializer=NULL;
    ISoapReaderPtr Reader=NULL;
    ISoapConnectorPtr Connector=NULL;
	CMyList *pView=(CMyList *)this->m_Splitter.GetPane(0,1);
	pView->DisplayMsg("Creatting Message: GetUserTemplate...........");
	CMGrid *bView=(CMGrid *)this->m_Splitter.GetPane(0,0);
    Connector.CreateInstance(__uuidof(HttpConnector30));

	CString SoapUrl1;
	SoapUrl1="http://"+(app->strIP)+"/iWsService";
	mJob=app->strJob.AllocSysString();
	pp=app->strCom.AllocSysString();   
    int n=strlen(SoapUrl1); 
    strcpy(SoapUrl,SoapUrl1); 

	Connector->Property["EndPointURL"] = SoapUrl;
    Connector->Connect();
	Connector->Property["SoapAction"] = "uri:zksoftware";
	Connector->Property["Timeout"] = "6000000";    //(ms)   timeout=100min 
    // Begin the message.
    Connector->BeginMessage();
    // Create the SoapSerializer object.
    Serializer.CreateInstance(__uuidof(SoapSerializer30));
    // Connect the serializer object to the input stream of the connector object.
	Serializer->Init(_variant_t((IUnknown*)Connector->InputStream));
    // Build the SOAP Message.
	pView->DisplayMsg("Send Message: .......");
    Serializer->StartEnvelope("","","");
    Serializer->StartBody("");
	
	Serializer->StartElement("GetUserTemplate","http://www.zksoftware/Service/message/","","");

	Serializer->StartElement("ArgComKey","http://www.zksoftware/Service/message/","","");
	Serializer->WriteString(pp);
	Serializer->EndElement();

	Serializer->StartElement("Arg","","","");
	Serializer->StartElement("PIN","","","");
	Serializer->WriteString(mJob);
	Serializer->EndElement();
	
	Serializer->StartElement("FingerID","","","");
	Serializer->WriteString("All");
	Serializer->EndElement();
	
	Serializer->EndElement();

    Serializer->EndElement();
    Serializer->EndBody();
    Serializer->EndEnvelope();

	try{
		Connector->EndMessage(); }
	catch (...)
	{
	pView->DisplayMsg("Send Message abnormity.");
	pView->DisplayMsg("connection false.");
		pView->DisplayMsg("");
		return;
	}

	if(Connector->OutputStream!=NULL)
	{
	pView->DisplayMsg("Recieve Message: ..........");
    Reader.CreateInstance(__uuidof(SoapReader30));
    // Connect the reader to the output stream of the connector object.
    Reader->Load(_variant_t((IUnknown*)Connector->OutputStream), "");

	MSXML2::IXMLDOMDocumentPtr pDoc; 
    HRESULT hr = pDoc.CreateInstance(__uuidof(MSXML2::DOMDocument30));
	MSXML2::IXMLDOMElementPtr  childNode;

    pDoc->loadXML(Reader->Dom->xml);
    childNode = (MSXML2::IXMLDOMElementPtr)(pDoc->selectSingleNode("//Row"));
 	CListCtrl *vView=(CListCtrl*)bView->GetDlgItem(IDC_LIST2);
	vView->DeleteAllItems();
	while (vView->DeleteColumn(0));
	vView->InsertColumn(0,   "UserID",   LVCFMT_LEFT,   80);   
	vView->InsertColumn(1,   "FingerID",   LVCFMT_LEFT,   60);   
	vView->InsertColumn(2,   "Size",   LVCFMT_LEFT,   50);   
	vView->InsertColumn(3,   "Valid",   LVCFMT_LEFT,   50);   
	vView->InsertColumn(4,   "Template",   LVCFMT_LEFT,   264);   
    int sid=0;
	ss.clear();
	CString inf;
    while(childNode!=NULL)
	{
	  MSXML2::DOMNodeType nodeType;
      childNode->get_nodeType(&nodeType);
	  //Node Name
      BSTR var;
      //Node Value
      VARIANT varVal;
      childNode->get_nodeName(&var);
	  childNode->get_nodeTypedValue(&varVal);

	  MSXML2::IXMLDOMNodeListPtr childlist=NULL;
	  MSXML2::IXMLDOMNodePtr pnodeitem;
	  childNode->get_childNodes(&childlist);
	  long cCount;
      childlist->get_length(&cCount);
      CString info[5];
	  for(int m = 0 ; m < cCount ; m++)
      {           
            childlist->get_item(m,&pnodeitem);
			info[m]=(LPCTSTR)((_bstr_t)pnodeitem->nodeTypedValue);	
			if(!strcmp((char*)(_bstr_t)pnodeitem->nodeName,"PIN"))
				sa.Id=info[m];
			else
			if(!strcmp((char*)(_bstr_t)pnodeitem->nodeName,"Size"))
				sa.Size=info[m];
			else
			if(!strcmp((char*)(_bstr_t)pnodeitem->nodeName,"Template"))
				sa.Template=info[m];
			else
			if(!strcmp((char*)(_bstr_t)pnodeitem->nodeName,"FingerID"))
				sa.Fid=info[m];
			else
			if(!strcmp((char*)(_bstr_t)pnodeitem->nodeName,"Valid"))
				sa.Valid=info[m];
			//pView->DisplayMsg((LPCSTR)info[m]);
      }
	  ss.push_back(sa);
	  vView->InsertItem(sid,info[0]);
	  vView->SetItemText(sid,1,info[1]);
	  vView->SetItemText(sid,2,info[2]);
	  vView->SetItemText(sid,3,info[3]);
	  vView->SetItemText(sid,4,info[4]);
	  childNode=childNode->nextSibling;
	  ++sid;
	}
	inf.Format("Record Number:%d",sid);
	pView->DisplayMsg(inf);
	pView->DisplayMsg("");
	}
	app->strJob="";
	}	
	}
}

void CMainFrame::OnEDITGetAllUserInfo() 
{
	// TODO: Add your command handler code here
	CSoapSettingApp *app = (CSoapSettingApp *)AfxGetApp();
	if((app->strCom.IsEmpty()!=0)||(app->strIP.IsEmpty()!=0))
	{AfxMessageBox("Please input IP and ComKey.");}
	else
	{
	char SoapUrl[255+1];
	_bstr_t pp,mJob;
	app->Idd="5";

	ISoapSerializerPtr Serializer=NULL;
    ISoapReaderPtr Reader=NULL;
    ISoapConnectorPtr Connector=NULL;
	CMyList *pView=(CMyList *)this->m_Splitter.GetPane(0,1);
	pView->DisplayMsg("Creatting Message: GetAllUserInfo...........");
	CMGrid *bView=(CMGrid *)this->m_Splitter.GetPane(0,0);
    Connector.CreateInstance(__uuidof(HttpConnector30));

	CString SoapUrl1;
	SoapUrl1="http://"+(app->strIP)+"/iWsService";
	mJob=app->strJob.AllocSysString();
	pp=app->strCom.AllocSysString();   
    int n=strlen(SoapUrl1); 
    strcpy(SoapUrl,SoapUrl1); 

	Connector->Property["EndPointURL"] = SoapUrl;
    Connector->Connect();
	Connector->Property["SoapAction"] = "uri:zksoftware";
	Connector->Property["Timeout"] = "6000000";    //(ms)   timeout=100min 
   // Begin the message.
    Connector->BeginMessage();
    // Create the SoapSerializer object.
    Serializer.CreateInstance(__uuidof(SoapSerializer30));
    // Connect the serializer object to the input stream of the connector object.
	Serializer->Init(_variant_t((IUnknown*)Connector->InputStream));
    // Build the SOAP Message.
	pView->DisplayMsg("Send Message: .......");
    Serializer->StartEnvelope("","","");
    Serializer->StartBody("");
	
	Serializer->StartElement("GetAllUserInfo","http://www.zksoftware/Service/message/","","");

	Serializer->StartElement("ArgComKey","http://www.zksoftware/Service/message/","","");
	Serializer->WriteString(pp);
	Serializer->EndElement();

    Serializer->EndElement();
    Serializer->EndBody();
    Serializer->EndEnvelope();

	try{
		Connector->EndMessage(); }
	catch (...)
	{
	pView->DisplayMsg("Send Message abnormity.");
	pView->DisplayMsg("connection false.");
	pView->DisplayMsg("");
	return;
	}

	if(Connector->OutputStream!=NULL)
	{
	pView->DisplayMsg("Recieve Message: ..........");
    Reader.CreateInstance(__uuidof(SoapReader30));
    // Connect the reader to the output stream of the connector object.
    Reader->Load(_variant_t((IUnknown*)Connector->OutputStream), "");

	MSXML2::IXMLDOMDocumentPtr pDoc; 
    HRESULT hr = pDoc.CreateInstance(__uuidof(MSXML2::DOMDocument30));
	MSXML2::IXMLDOMElementPtr  childNode;

    pDoc->loadXML(Reader->Dom->xml);
    childNode = (MSXML2::IXMLDOMElementPtr)(pDoc->selectSingleNode("//Row"));
 	CListCtrl *vView=(CListCtrl*)bView->GetDlgItem(IDC_LIST2);
	vView->DeleteAllItems();
	while (vView->DeleteColumn(0));
	vView->InsertColumn(0,   "UerID",   LVCFMT_LEFT,   80);   
	vView->InsertColumn(1,   "Name",   LVCFMT_LEFT,   81);   
	vView->InsertColumn(2,   "PassWord",   LVCFMT_LEFT,   60);   
	vView->InsertColumn(3,   "Group",   LVCFMT_LEFT,   45);   
	vView->InsertColumn(4,   "Privilege",   LVCFMT_LEFT,   68);   
	vView->InsertColumn(5,   "Card",   LVCFMT_LEFT,   80);   
 	vView->InsertColumn(6,   "TZ1",   LVCFMT_LEFT,   30);   
	vView->InsertColumn(7,   "TZ2",   LVCFMT_LEFT,   30);   
	vView->InsertColumn(8,   "TZ3",   LVCFMT_LEFT,   30);   
    int sid=0;
    CString inf;
    while(childNode!=NULL)
	{
	  MSXML2::DOMNodeType nodeType;
      childNode->get_nodeType(&nodeType);
	  //Node Name
      BSTR var;
      //Node Value
      VARIANT varVal;
      childNode->get_nodeName(&var);
	  childNode->get_nodeTypedValue(&varVal);

	  MSXML2::IXMLDOMNodeListPtr childlist=NULL;
	  MSXML2::IXMLDOMNodePtr pnodeitem;
	  childNode->get_childNodes(&childlist);
	  long cCount ;
      childlist->get_length(&cCount);
      CString info[10];
	  for(int m = 0 ; m < cCount ; m++)
      {           
            childlist->get_item(m,&pnodeitem);
			info[m]=(LPCTSTR)((_bstr_t)pnodeitem->nodeTypedValue);						
      }
	  vView->InsertItem(sid,info[6]);
	  vView->SetItemText(sid,1,info[1]);
	  vView->SetItemText(sid,2,info[2]);
	  vView->SetItemText(sid,3,info[3]);
	  vView->SetItemText(sid,4,info[4]);
	  vView->SetItemText(sid,5,info[5]); 
	  vView->SetItemText(sid,6,info[7]); 
	  vView->SetItemText(sid,7,info[8]); 
	  vView->SetItemText(sid,8,info[9]); 
	  childNode=childNode->nextSibling;
	  ++sid;
	}	
	inf.Format("Record Number:%d",sid);
	pView->DisplayMsg(inf);
	pView->DisplayMsg("");
	}
	}	
}

void CMainFrame::OnEDITGetOption() 
{
	// TODO: Add your command handler code here
	CSoapSettingApp *app = (CSoapSettingApp *)AfxGetApp();
	if((app->strCom.IsEmpty()!=0)||(app->strIP.IsEmpty()!=0))
	{AfxMessageBox("Please input IP and ComKey.");}
	else
	{
	app->Idd="3";
    CSecondSet dlg;
    dlg.DoModal();
	if(app->strJob.IsEmpty())
	{}
	else
	{
	char SoapUrl[255+1];
	_bstr_t pp,mJob;

	ISoapSerializerPtr Serializer=NULL;
    ISoapReaderPtr Reader=NULL;
    ISoapConnectorPtr Connector=NULL;
	CMyList *pView=(CMyList *)this->m_Splitter.GetPane(0,1);
	pView->DisplayMsg("Creatting Message: GetOption...........");
	CMGrid *bView=(CMGrid *)this->m_Splitter.GetPane(0,0);
    Connector.CreateInstance(__uuidof(HttpConnector30));

	CString SoapUrl1;
	SoapUrl1="http://"+(app->strIP)+"/iWsService";
	mJob=app->strJob.AllocSysString();
	pp=app->strCom.AllocSysString();   
    int n=strlen(SoapUrl1); 
    strcpy(SoapUrl,SoapUrl1); 

	Connector->Property["EndPointURL"] = SoapUrl;
    Connector->Connect();
	Connector->Property["SoapAction"] = "uri:zksoftware";
	Connector->Property["Timeout"] = "6000000";    //(ms)   timeout=100min 
    // Begin the message.
    Connector->BeginMessage();
    // Create the SoapSerializer object.
    Serializer.CreateInstance(__uuidof(SoapSerializer30));
    // Connect the serializer object to the input stream of the connector object.
	Serializer->Init(_variant_t((IUnknown*)Connector->InputStream));
    // Build the SOAP Message.
	pView->DisplayMsg("Send Message: .......");
    Serializer->StartEnvelope("","","");
    Serializer->StartBody("");
	
	Serializer->StartElement("GetOption","http://www.zksoftware/Service/message/","","");

	Serializer->StartElement("ArgComKey","http://www.zksoftware/Service/message/","","");
	Serializer->WriteString(pp);
	Serializer->EndElement();

	Serializer->StartElement("Arg","","","");
	Serializer->StartElement("Name","","","");
	Serializer->WriteString(mJob);
	Serializer->EndElement();
	Serializer->EndElement();

    Serializer->EndElement();
    Serializer->EndBody();
    Serializer->EndEnvelope();

	try{
		Connector->EndMessage(); }
	catch (...)
	{
	pView->DisplayMsg("Send Message abnormity.");
	pView->DisplayMsg("connection false.");
	pView->DisplayMsg("");
	return;
	}

	if(Connector->OutputStream!=NULL)
	{
	pView->DisplayMsg("Recieve Message: ..........");
    Reader.CreateInstance(__uuidof(SoapReader30));
    // Connect the reader to the output stream of the connector object.
    Reader->Load(_variant_t((IUnknown*)Connector->OutputStream), "");

	MSXML2::IXMLDOMDocumentPtr pDoc; 
    HRESULT hr = pDoc.CreateInstance(__uuidof(MSXML2::DOMDocument30));
	MSXML2::IXMLDOMElementPtr  childNode;

    pDoc->loadXML(Reader->Dom->xml);
    childNode = (MSXML2::IXMLDOMElementPtr)(pDoc->selectSingleNode("//Row"));
 	CListCtrl *vView=(CListCtrl*)bView->GetDlgItem(IDC_LIST2);
	vView->DeleteAllItems();
	while (vView->DeleteColumn(0));
	vView->InsertColumn(0,   "Name",   LVCFMT_LEFT,   252);   
	vView->InsertColumn(1,   "Value",   LVCFMT_LEFT,   252);   
    int sid=0;
    while(childNode!=NULL)
	{
	  MSXML2::DOMNodeType nodeType;
      childNode->get_nodeType(&nodeType);
	  //Node Name
      BSTR var;
      //Node Value
      VARIANT varVal;
      childNode->get_nodeName(&var);
	  childNode->get_nodeTypedValue(&varVal);

	  MSXML2::IXMLDOMNodeListPtr childlist=NULL;
	  MSXML2::IXMLDOMNodePtr pnodeitem;
	  childNode->get_childNodes(&childlist);
	  long cCount ;
      childlist->get_length(&cCount);
      CString info[256];
	  for(int m = 0 ; m < cCount ; m++)
      {           
            childlist->get_item(m,&pnodeitem);
			info[m]=(LPCTSTR)((_bstr_t)pnodeitem->nodeTypedValue);		
      }
	  vView->InsertItem(sid,app->strJob);
	  vView->SetItemText(sid,1,info[0]);
	  childNode=childNode->nextSibling;
	  ++sid;
	}	
	pView->DisplayMsg("");
	}
	app->strJob="";
	}	
	}
}

void CMainFrame::OnEDITSetDate() 
{
	// TODO: Add your command handler code here
	CSoapSettingApp *app = (CSoapSettingApp *)AfxGetApp();
	if((app->strCom.IsEmpty()!=0)||(app->strIP.IsEmpty()!=0))
	{AfxMessageBox("Please input IP and ComKey.");}
	else
	{
    CDate dlg;
    dlg.DoModal();
	if((app->strDate.IsEmpty())||(app->strTime.IsEmpty()))
	{}
	else
	{
	char SoapUrl[255+1];
	_bstr_t pp,mDate,mTime,mJob;

	ISoapSerializerPtr Serializer=NULL;
    ISoapReaderPtr Reader=NULL;
    ISoapConnectorPtr Connector=NULL;
	CMyList *pView=(CMyList *)this->m_Splitter.GetPane(0,1);
	pView->DisplayMsg("Creatting Message: SetDate...........");
    Connector.CreateInstance(__uuidof(HttpConnector30));

	CString SoapUrl1;
	SoapUrl1="http://"+(app->strIP)+"/iWsService";
	mJob=app->strJob.AllocSysString();
	pp=app->strCom.AllocSysString();   
	mDate=app->strDate.AllocSysString();   
	mTime=app->strTime.AllocSysString();   
    int n=strlen(SoapUrl1); 
    strcpy(SoapUrl,SoapUrl1); 

	Connector->Property["EndPointURL"] = SoapUrl;
    Connector->Connect();
	Connector->Property["SoapAction"] = "uri:zksoftware";
	Connector->Property["Timeout"] = "6000000";    //(ms)   timeout=100min 
    // Begin the message.
    Connector->BeginMessage();
    // Create the SoapSerializer object.
    Serializer.CreateInstance(__uuidof(SoapSerializer30));
    // Connect the serializer object to the input stream of the connector object.
	Serializer->Init(_variant_t((IUnknown*)Connector->InputStream));
    // Build the SOAP Message.
	pView->DisplayMsg("Send Message: .......");
    Serializer->StartEnvelope("","","");
    Serializer->StartBody("");
	
	Serializer->StartElement("SetDate","http://www.zksoftware/Service/message/","","");

	Serializer->StartElement("ArgComKey","http://www.zksoftware/Service/message/","","");
	Serializer->WriteString(pp);
	Serializer->EndElement();

	Serializer->StartElement("Arg","","","");
	Serializer->StartElement("Date","","","");
	Serializer->WriteString(mDate);
	Serializer->EndElement();
	Serializer->StartElement("Time","","","");
	Serializer->WriteString(mTime);
	Serializer->EndElement();
	Serializer->EndElement();

    Serializer->EndElement();
    Serializer->EndBody();
    Serializer->EndEnvelope();

	try{
		Connector->EndMessage(); }
	catch (...)
	{
	pView->DisplayMsg("Send Message abnormity.");
	pView->DisplayMsg("connection false.");
	pView->DisplayMsg("");
	return;
	}

	if(Connector->OutputStream!=NULL)
	{
	pView->DisplayMsg("Recieve Message: ..........");
    Reader.CreateInstance(__uuidof(SoapReader30));
    // Connect the reader to the output stream of the connector object.
    Reader->Load(_variant_t((IUnknown*)Connector->OutputStream), "");

	MSXML2::IXMLDOMDocumentPtr pDoc; 
    HRESULT hr = pDoc.CreateInstance(__uuidof(MSXML2::DOMDocument30));
	MSXML2::IXMLDOMElementPtr  childNode;

    pDoc->loadXML(Reader->Dom->xml);
    childNode = (MSXML2::IXMLDOMElementPtr)(pDoc->selectSingleNode("//Row"));
    int sid=0;
    while(childNode!=NULL)
	{
	  MSXML2::DOMNodeType nodeType;
      childNode->get_nodeType(&nodeType);
	  //Node Name
      BSTR var;
      //Node Value
      VARIANT varVal;
      childNode->get_nodeName(&var);
	  childNode->get_nodeTypedValue(&varVal);
	  ++sid;

	  MSXML2::IXMLDOMNodeListPtr childlist=NULL;
	  MSXML2::IXMLDOMNodePtr pnodeitem;
	  childNode->get_childNodes(&childlist);
	  long cCount ;
      childlist->get_length(&cCount);
      char info[256];
	  for(int m = 0 ; m < cCount ; m++)
      {           
            childlist->get_item(m,&pnodeitem);
			sprintf(info,"%s=%s",(char*)(_bstr_t)pnodeitem->nodeName,(char*)(_bstr_t)pnodeitem->nodeTypedValue);
			pView->DisplayMsg((LPCSTR)info);
		
      }
	  childNode=childNode->nextSibling;
	}	
	pView->DisplayMsg("");
	}
	app->strDate="";
	app->strTime="";
	}	
	}
}

void CMainFrame::OnEDITSetOption() 
{
	// TODO: Add your command handler code here
	CSoapSettingApp *app = (CSoapSettingApp *)AfxGetApp();
	if((app->strCom.IsEmpty()!=0)||(app->strIP.IsEmpty()!=0))
	{AfxMessageBox("Please input IP and ComKey.");}
	else
	{
	app->Idd="5";
    CSecondSet dlg;
    dlg.DoModal();
	if((app->strJob.IsEmpty())||(app->strFinger.IsEmpty()))
	{}
	else
	{
	char SoapUrl[255+1];
	_bstr_t pp,mDate,mTime;

	ISoapSerializerPtr Serializer=NULL;
    ISoapReaderPtr Reader=NULL;
    ISoapConnectorPtr Connector=NULL;
	CMyList *pView=(CMyList *)this->m_Splitter.GetPane(0,1);
	pView->DisplayMsg("Creatting Message: SetOption...........");
    Connector.CreateInstance(__uuidof(HttpConnector30));

	CString SoapUrl1;
	SoapUrl1="http://"+(app->strIP)+"/iWsService";
	pp=app->strCom.AllocSysString();   
	mDate=app->strJob.AllocSysString();   
	mTime=app->strFinger.AllocSysString();   
    int n=strlen(SoapUrl1); 
    strcpy(SoapUrl,SoapUrl1); 

	Connector->Property["EndPointURL"] = SoapUrl;
    Connector->Connect();
	Connector->Property["SoapAction"] = "uri:zksoftware";
	Connector->Property["Timeout"] = "6000000";    //(ms)   timeout=100min 
    // Begin the message.
    Connector->BeginMessage();
    // Create the SoapSerializer object.
    Serializer.CreateInstance(__uuidof(SoapSerializer30));
    // Connect the serializer object to the input stream of the connector object.
	Serializer->Init(_variant_t((IUnknown*)Connector->InputStream));
    // Build the SOAP Message.
	pView->DisplayMsg("Send Message: .......");
    Serializer->StartEnvelope("","","");
    Serializer->StartBody("");
	
	Serializer->StartElement("SetOption","http://www.zksoftware/Service/message/","","");

	Serializer->StartElement("ArgComKey","http://www.zksoftware/Service/message/","","");
	Serializer->WriteString(pp);
	Serializer->EndElement();

	Serializer->StartElement("Arg","","","");
	Serializer->StartElement("Name","","","");
	Serializer->WriteString(mDate);
	Serializer->EndElement();
	Serializer->StartElement("Value","","","");
	Serializer->WriteString(mTime);
	Serializer->EndElement();
	Serializer->EndElement();

    Serializer->EndElement();
    Serializer->EndBody();
    Serializer->EndEnvelope();

	try{
		Connector->EndMessage(); }
	catch (...)
	{
	pView->DisplayMsg("Send Message abnormity.");
	pView->DisplayMsg("connection false.");
	pView->DisplayMsg("");
	return;
	}

	if(Connector->OutputStream!=NULL)
	{
	pView->DisplayMsg("Recieve Message: ..........");
    Reader.CreateInstance(__uuidof(SoapReader30));
    // Connect the reader to the output stream of the connector object.
    Reader->Load(_variant_t((IUnknown*)Connector->OutputStream), "");

	MSXML2::IXMLDOMDocumentPtr pDoc; 
    HRESULT hr = pDoc.CreateInstance(__uuidof(MSXML2::DOMDocument30));
	MSXML2::IXMLDOMElementPtr  childNode;

    pDoc->loadXML(Reader->Dom->xml);
    childNode = (MSXML2::IXMLDOMElementPtr)(pDoc->selectSingleNode("//Row"));
    int sid=0;
    while(childNode!=NULL)
	{
	  MSXML2::DOMNodeType nodeType;
      childNode->get_nodeType(&nodeType);
	  //Node Name
      BSTR var;
      //Node Value
      VARIANT varVal;
      childNode->get_nodeName(&var);
	  childNode->get_nodeTypedValue(&varVal);
	  ++sid;

	  MSXML2::IXMLDOMNodeListPtr childlist=NULL;
	  MSXML2::IXMLDOMNodePtr pnodeitem;
	  childNode->get_childNodes(&childlist);
	  long cCount ;
      childlist->get_length(&cCount);
      char info[256];
	  for(int m = 0 ; m < cCount ; m++)
      {           
            childlist->get_item(m,&pnodeitem);
			sprintf(info,"%s=%s",(char*)(_bstr_t)pnodeitem->nodeName,(char*)(_bstr_t)pnodeitem->nodeTypedValue);
			pView->DisplayMsg((LPCSTR)info);
		
      }
	  childNode=childNode->nextSibling;
	}	
	pView->DisplayMsg("");
	}
	app->strFinger="";
	app->strJob="";
	}	
	}
}


void CMainFrame::OnEDITRestart() 
{
	// TODO: Add your command handler code here
	CSoapSettingApp *app = (CSoapSettingApp *)AfxGetApp();
	if((app->strCom.IsEmpty()!=0)||(app->strIP.IsEmpty()!=0))
	{AfxMessageBox("Please input IP and ComKey.");}
	else
	{
	char SoapUrl[255+1];
	_bstr_t pp;

	ISoapSerializerPtr Serializer=NULL;
    ISoapReaderPtr Reader=NULL;
    ISoapConnectorPtr Connector=NULL;
	CMyList *pView=(CMyList *)this->m_Splitter.GetPane(0,1);
	pView->DisplayMsg("Creatting Message: Restart...........");
    Connector.CreateInstance(__uuidof(HttpConnector30));

	CString SoapUrl1;
	SoapUrl1="http://"+(app->strIP)+"/iWsService";
	pp=app->strCom.AllocSysString();   
    int n=strlen(SoapUrl1); 
    strcpy(SoapUrl,SoapUrl1); 

	Connector->Property["EndPointURL"] = SoapUrl;
    Connector->Connect();
	Connector->Property["SoapAction"] = "uri:zksoftware";
	Connector->Property["Timeout"] = "6000000";    //(ms)   timeout=100min 
    // Begin the message.
    Connector->BeginMessage();
    // Create the SoapSerializer object.
    Serializer.CreateInstance(__uuidof(SoapSerializer30));
    // Connect the serializer object to the input stream of the connector object.
	Serializer->Init(_variant_t((IUnknown*)Connector->InputStream));
    // Build the SOAP Message.
	pView->DisplayMsg("Send Message: .......");
    Serializer->StartEnvelope("","","");
    Serializer->StartBody("");
	
	Serializer->StartElement("Restart","http://www.zksoftware/Service/message/","","");

	Serializer->StartElement("ArgComKey","http://www.zksoftware/Service/message/","","");
	Serializer->WriteString(pp);
	Serializer->EndElement();

    Serializer->EndElement();
    Serializer->EndBody();
    Serializer->EndEnvelope();

	try{
		Connector->EndMessage(); }
	catch (...)
	{
	pView->DisplayMsg("Send Message abnormity.");
	pView->DisplayMsg("connection false.");
	pView->DisplayMsg("");
	return;
	}

	if(Connector->OutputStream!=NULL)
	{
	pView->DisplayMsg("Recieve Message: ..........");
    Reader.CreateInstance(__uuidof(SoapReader30));
    // Connect the reader to the output stream of the connector object.
    Reader->Load(_variant_t((IUnknown*)Connector->OutputStream), "");

	MSXML2::IXMLDOMDocumentPtr pDoc; 
    HRESULT hr = pDoc.CreateInstance(__uuidof(MSXML2::DOMDocument30));
	MSXML2::IXMLDOMElementPtr  childNode;

    pDoc->loadXML(Reader->Dom->xml);
    childNode = (MSXML2::IXMLDOMElementPtr)(pDoc->selectSingleNode("//Row"));
    int sid=0;
    while(childNode!=NULL)
	{
	  MSXML2::DOMNodeType nodeType;
      childNode->get_nodeType(&nodeType);
	  //Node Name
      BSTR var;
      //Node Value
      VARIANT varVal;
      childNode->get_nodeName(&var);
	  childNode->get_nodeTypedValue(&varVal);
	  ++sid;

	  MSXML2::IXMLDOMNodeListPtr childlist=NULL;
	  MSXML2::IXMLDOMNodePtr pnodeitem;
	  childNode->get_childNodes(&childlist);
	  long cCount ;
      childlist->get_length(&cCount);
      char info[256];
	  for(int m = 0 ; m < cCount ; m++)
      {           
            childlist->get_item(m,&pnodeitem);
			sprintf(info,"%s=%s",(char*)(_bstr_t)pnodeitem->nodeName,(char*)(_bstr_t)pnodeitem->nodeTypedValue);
			pView->DisplayMsg((LPCSTR)info);
		
      }
	  childNode=childNode->nextSibling;
	}	
	pView->DisplayMsg("");
	}
	}	
}



void CMainFrame::OnEDITRefreshDB() 
{
	// TODO: Add your command handler code here
	CSoapSettingApp *app = (CSoapSettingApp *)AfxGetApp();
	if((app->strCom.IsEmpty()!=0)||(app->strIP.IsEmpty()!=0))
	{AfxMessageBox("Please input IP and ComKey.");}
	else
	{
	char SoapUrl[255+1];
	_bstr_t pp;

	ISoapSerializerPtr Serializer=NULL;
    ISoapReaderPtr Reader=NULL;
    ISoapConnectorPtr Connector=NULL;
	CMyList *pView=(CMyList *)this->m_Splitter.GetPane(0,1);
	pView->DisplayMsg("Creatting Message: RefreshDB...........");
    Connector.CreateInstance(__uuidof(HttpConnector30));

	CString SoapUrl1;
	SoapUrl1="http://"+(app->strIP)+"/iWsService";
	pp=app->strCom.AllocSysString();   
    int n=strlen(SoapUrl1); 
    strcpy(SoapUrl,SoapUrl1); 

	Connector->Property["EndPointURL"] = SoapUrl;
    Connector->Connect();
	Connector->Property["SoapAction"] = "uri:zksoftware";
	Connector->Property["Timeout"] = "6000000";    //(ms)   timeout=100min 
    // Begin the message.
    Connector->BeginMessage();
    // Create the SoapSerializer object.
    Serializer.CreateInstance(__uuidof(SoapSerializer30));
    // Connect the serializer object to the input stream of the connector object.
	Serializer->Init(_variant_t((IUnknown*)Connector->InputStream));
    // Build the SOAP Message.
	pView->DisplayMsg("Send Message: .......");
    Serializer->StartEnvelope("","","");
    Serializer->StartBody("");
	
	Serializer->StartElement("RefreshDB","http://www.zksoftware/Service/message/","","");

	Serializer->StartElement("ArgComKey","http://www.zksoftware/Service/message/","","");
	Serializer->WriteString(pp);
	Serializer->EndElement();

    Serializer->EndElement();
    Serializer->EndBody();
    Serializer->EndEnvelope();

	try{
		Connector->EndMessage(); }
	catch (...)
	{
	pView->DisplayMsg("Send Message abnormity.");
	pView->DisplayMsg("connection false.");
	pView->DisplayMsg("");
	return;
	}

	if(Connector->OutputStream!=NULL)
	{
	pView->DisplayMsg("Recieve Message: ..........");
    Reader.CreateInstance(__uuidof(SoapReader30));
    // Connect the reader to the output stream of the connector object.
    Reader->Load(_variant_t((IUnknown*)Connector->OutputStream), "");

	MSXML2::IXMLDOMDocumentPtr pDoc; 
    HRESULT hr = pDoc.CreateInstance(__uuidof(MSXML2::DOMDocument30));
	MSXML2::IXMLDOMElementPtr  childNode;

    pDoc->loadXML(Reader->Dom->xml);
    childNode = (MSXML2::IXMLDOMElementPtr)(pDoc->selectSingleNode("//Row"));
    int sid=0;
    while(childNode!=NULL)
	{
	  MSXML2::DOMNodeType nodeType;
      childNode->get_nodeType(&nodeType);
	  //Node Name
      BSTR var;
      //Node Value
      VARIANT varVal;
      childNode->get_nodeName(&var);
	  childNode->get_nodeTypedValue(&varVal);
	  ++sid;

	  MSXML2::IXMLDOMNodeListPtr childlist=NULL;
	  MSXML2::IXMLDOMNodePtr pnodeitem;
	  childNode->get_childNodes(&childlist);
	  long cCount ;
      childlist->get_length(&cCount);
      char info[256];
	  for(int m = 0 ; m < cCount ; m++)
      {           
            childlist->get_item(m,&pnodeitem);
			sprintf(info,"%s=%s",(char*)(_bstr_t)pnodeitem->nodeName,(char*)(_bstr_t)pnodeitem->nodeTypedValue);
			pView->DisplayMsg((LPCSTR)info);
		
      }
	  childNode=childNode->nextSibling;
	}	
	pView->DisplayMsg("");
	}
	}	
}


void CMainFrame::OnEDITSetUserInfo() 
{
	// TODO: Add your command handler code here
	CSoapSettingApp *app = (CSoapSettingApp *)AfxGetApp();
	if((app->strCom.IsEmpty()!=0)||(app->strIP.IsEmpty()!=0))
	{AfxMessageBox("Please input IP and ComKey.");}
	else
	{
    CUserInfo dlg;
    dlg.DoModal();
	if((app->strID.IsEmpty()))
	{return;}
	else
	{
	char SoapUrl[255+1];
	_bstr_t pp,mName,mJob,mID,mPass,mPrivilege,mGroup,mTZ1,mTZ2,mTZ3;//,mCard;

	ISoapSerializerPtr Serializer=NULL;
    ISoapReaderPtr Reader=NULL;
    ISoapConnectorPtr Connector=NULL;
	CMyList *pView=(CMyList *)this->m_Splitter.GetPane(0,1);
	pView->DisplayMsg("Creatting Message: SetUserInfo...........");
    Connector.CreateInstance(__uuidof(HttpConnector30));
	CString SoapUrl1;
	SoapUrl1="http://"+(app->strIP)+"/iWsService";
	mJob=app->strJob.AllocSysString();
	pp=app->strCom.AllocSysString();   
	mID=app->strID.AllocSysString();   
	mName=app->strName.AllocSysString();   
	mPass=app->strPass.AllocSysString();   
	mPrivilege=app->strPrivilege.AllocSysString();   
	//mCard=app->strCard.AllocSysString();   
	mGroup=app->strGroup.AllocSysString();   
	mTZ1=app->strTZ1.AllocSysString();   
	mTZ2=app->strTZ2.AllocSysString();   
	mTZ3=app->strTZ3.AllocSysString();   
    int n=strlen(SoapUrl1); 
    strcpy(SoapUrl,SoapUrl1); 

	Connector->Property["EndPointURL"] = SoapUrl;
    Connector->Connect();
	Connector->Property["SoapAction"] = "uri:zksoftware";
	Connector->Property["Timeout"] = "6000000";    //(ms)   timeout=100min 
    // Begin the message.
    Connector->BeginMessage();
    // Create the SoapSerializer object.
    Serializer.CreateInstance(__uuidof(SoapSerializer30));
    // Connect the serializer object to the input stream of the connector object.
	Serializer->Init(_variant_t((IUnknown*)Connector->InputStream));
    // Build the SOAP Message.
	pView->DisplayMsg("Send Message: .......");
    Serializer->StartEnvelope("","","");
    Serializer->StartBody("");
	
	Serializer->StartElement("SetUserInfo","http://www.zksoftware/Service/message/","","");

	Serializer->StartElement("ArgComKey","http://www.zksoftware/Service/message/","","");
	Serializer->WriteString(pp);
	Serializer->EndElement();

	Serializer->StartElement("Arg","","","");
	Serializer->StartElement("PIN","","","");
	Serializer->WriteString(mID);
	Serializer->EndElement();
	Serializer->StartElement("Name","","","");
	Serializer->WriteString(mName);
	Serializer->EndElement();
	Serializer->StartElement("Password","","","");
	Serializer->WriteString(mPass);
	Serializer->EndElement();
	Serializer->StartElement("Privilege","","","");
	Serializer->WriteString(mPrivilege);
	Serializer->EndElement();
	/*Serializer->StartElement("Card","","","");
	Serializer->WriteString(mCard);
	Serializer->EndElement();*/
	Serializer->StartElement("Group","","","");
	Serializer->WriteString(mGroup);
	Serializer->EndElement();
	Serializer->StartElement("TZ1","","","");
	Serializer->WriteString(mTZ1);
	Serializer->EndElement();
	Serializer->StartElement("TZ2","","","");
	Serializer->WriteString(mTZ2);
	Serializer->EndElement();
	Serializer->StartElement("TZ3","","","");
	Serializer->WriteString(mTZ3);
	Serializer->EndElement();
	Serializer->EndElement();

    Serializer->EndElement();
    Serializer->EndBody();
    Serializer->EndEnvelope();

	try{
		Connector->EndMessage(); }
	catch (...)
	{
	pView->DisplayMsg("Send Message abnormity.");
	pView->DisplayMsg("connection false.");
	pView->DisplayMsg("");
	return;
	}

	if(Connector->OutputStream!=NULL)
	{
	pView->DisplayMsg("Recieve Message: ..........");
    Reader.CreateInstance(__uuidof(SoapReader30));
    // Connect the reader to the output stream of the connector object.
    Reader->Load(_variant_t((IUnknown*)Connector->OutputStream), "");

	MSXML2::IXMLDOMDocumentPtr pDoc; 
    HRESULT hr = pDoc.CreateInstance(__uuidof(MSXML2::DOMDocument30));
	MSXML2::IXMLDOMElementPtr  childNode;

    pDoc->loadXML(Reader->Dom->xml);
    childNode = (MSXML2::IXMLDOMElementPtr)(pDoc->selectSingleNode("//Row"));
    int sid=0;
    while(childNode!=NULL)
	{
	  MSXML2::DOMNodeType nodeType;
      childNode->get_nodeType(&nodeType);
	  //Node Name
      BSTR var;
      //Node Value
      VARIANT varVal;
      childNode->get_nodeName(&var);
	  childNode->get_nodeTypedValue(&varVal);
	  ++sid;

	  MSXML2::IXMLDOMNodeListPtr childlist=NULL;
	  MSXML2::IXMLDOMNodePtr pnodeitem;
	  childNode->get_childNodes(&childlist);
	  long cCount ;
      childlist->get_length(&cCount);
      char info[256];
	  for(int m = 0 ; m < cCount ; m++)
      {           
            childlist->get_item(m,&pnodeitem);
			sprintf(info,"%s=%s",(char*)(_bstr_t)pnodeitem->nodeName,(char*)(_bstr_t)pnodeitem->nodeTypedValue);
			pView->DisplayMsg((LPCSTR)info);
		
      }
	  childNode=childNode->nextSibling;
	}	
	pView->DisplayMsg("");
	}
	app->strID="";
	app->strPass="";
	app->strName="";
	app->strPrivilege="";
	app->strCard="";
	}	
	}
}

void CMainFrame::OnEDITSetUserTemplate() 
{
	// TODO: Add your command handler code here
	CSoapSettingApp *app = (CSoapSettingApp *)AfxGetApp();
	if((app->strCom.IsEmpty()!=0)||(app->strIP.IsEmpty()!=0))
	{AfxMessageBox("Please input IP and ComKey.");}
	else
	{
	CString dd,dd1;
	dd="1";
	dd1="2";
	CMGrid *bView=(CMGrid *)this->m_Splitter.GetPane(0,0);
	CListCtrl *vView=(CListCtrl*)bView->GetDlgItem(IDC_LIST2);
    for(int i=0; i<vView->GetItemCount(); i++)
    {
    if( vView->GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED || vView->GetCheck(i))
    {
	sa=ss.at(i);
	char SoapUrl[255+1];
	_bstr_t pp,mFid,mJob,mID,mSize,mTemplate,mValid;
	ISoapSerializerPtr Serializer=NULL;
    ISoapReaderPtr Reader=NULL;
    ISoapConnectorPtr Connector=NULL;
	CMyList *pView=(CMyList *)this->m_Splitter.GetPane(0,1);
	pView->DisplayMsg("Creatting Message: SetUserTemplate...........");
    Connector.CreateInstance(__uuidof(HttpConnector30));
	CString SoapUrl1;
	SoapUrl1="http://"+(app->strIP)+"/iWsService";
	mJob=app->strJob.AllocSysString();
	pp=app->strCom.AllocSysString();   
	mID=sa.Id.AllocSysString();   
	mFid=sa.Fid.AllocSysString();   
	mSize=sa.Size.AllocSysString();   
	mTemplate=sa.Template.AllocSysString();   
	mValid=dd.AllocSysString();   
	//mValid=sa.Valid.AllocSysString();   
    int n=strlen(SoapUrl1); 
    strcpy(SoapUrl,SoapUrl1); 

	Connector->Property["EndPointURL"] = SoapUrl;
    Connector->Connect();
	Connector->Property["SoapAction"] = "uri:zksoftware";
	Connector->Property["Timeout"] = "6000000";    //(ms)   timeout=100min 
    // Begin the message.
    Connector->BeginMessage();
    // Create the SoapSerializer object.
    Serializer.CreateInstance(__uuidof(SoapSerializer30));
    // Connect the serializer object to the input stream of the connector object.
	Serializer->Init(_variant_t((IUnknown*)Connector->InputStream));
    // Build the SOAP Message.
	pView->DisplayMsg("Send Message: .......");
    Serializer->StartEnvelope("","","");
    Serializer->StartBody("");
	
	Serializer->StartElement("SetUserTemplate","http://www.zksoftware/Service/message/","","");

	Serializer->StartElement("ArgComKey","http://www.zksoftware/Service/message/","","");
	Serializer->WriteString(pp);
	Serializer->EndElement();

	Serializer->StartElement("Arg","","","");
	Serializer->StartElement("PIN","","","");
	Serializer->WriteString(mID);
	Serializer->EndElement();
	Serializer->StartElement("FingerID","","","");
	Serializer->WriteString(mFid);
	Serializer->EndElement();
	Serializer->StartElement("Size","","","");
	Serializer->WriteString(mSize);
	Serializer->EndElement();
	Serializer->StartElement("Template","","","");
	Serializer->WriteString(mTemplate);
	Serializer->EndElement();
	Serializer->StartElement("Valid","","","");
	Serializer->WriteString(mValid);
	Serializer->EndElement();
	Serializer->EndElement();

    Serializer->EndElement();
    Serializer->EndBody();
    Serializer->EndEnvelope();

	try{
		Connector->EndMessage(); }
	catch (...)
	{
	pView->DisplayMsg("Send Message abnormity.");
	pView->DisplayMsg("connection false.");
	pView->DisplayMsg("");
	return;
	}

	if(Connector->OutputStream!=NULL)
	{
	pView->DisplayMsg("Recieve Message: ..........");
    Reader.CreateInstance(__uuidof(SoapReader30));
    // Connect the reader to the output stream of the connector object.
    Reader->Load(_variant_t((IUnknown*)Connector->OutputStream), "");

	MSXML2::IXMLDOMDocumentPtr pDoc; 
    HRESULT hr = pDoc.CreateInstance(__uuidof(MSXML2::DOMDocument30));
	MSXML2::IXMLDOMElementPtr  childNode;

    pDoc->loadXML(Reader->Dom->xml);
    childNode = (MSXML2::IXMLDOMElementPtr)(pDoc->selectSingleNode("//Row"));
    int sid=0;
    while(childNode!=NULL)
	{
	  MSXML2::DOMNodeType nodeType;
      childNode->get_nodeType(&nodeType);
	  //Node Name
      BSTR var;
      //Node Value
      VARIANT varVal;
      childNode->get_nodeName(&var);
	  childNode->get_nodeTypedValue(&varVal);
	  ++sid;

	  MSXML2::IXMLDOMNodeListPtr childlist=NULL;
	  MSXML2::IXMLDOMNodePtr pnodeitem;
	  childNode->get_childNodes(&childlist);
	  long cCount ;
      childlist->get_length(&cCount);
      char info[256];
	  for(int m = 0 ; m < cCount ; m++)
      {           
            childlist->get_item(m,&pnodeitem);
			sprintf(info,"%s=%s",(char*)(_bstr_t)pnodeitem->nodeName,(char*)(_bstr_t)pnodeitem->nodeTypedValue);
			pView->DisplayMsg((LPCSTR)info);
		
      }
	  childNode=childNode->nextSibling;
	}	
	pView->DisplayMsg("");
	}
	}	
    }
    }
}

void CMainFrame::OnEDITDeleteUser() 
{
	// TODO: Add your command handler code here
	CSoapSettingApp *app = (CSoapSettingApp *)AfxGetApp();
	if((app->strCom.IsEmpty()!=0)||(app->strIP.IsEmpty()!=0))
	{AfxMessageBox("Please input IP and ComKey.");}
	else
	{
	app->Idd="4";
    CSecondSet dlg;
    dlg.DoModal();
	if(app->strJob.IsEmpty())
	{}
	else
	{
	char SoapUrl[255+1];
	_bstr_t pp,mJob;

	ISoapSerializerPtr Serializer=NULL;
    ISoapReaderPtr Reader=NULL;
    ISoapConnectorPtr Connector=NULL;
 	CMyList *pView=(CMyList *)this->m_Splitter.GetPane(0,1);
	pView->DisplayMsg("Creatting Message: DeleteUser...........");
    Connector.CreateInstance(__uuidof(HttpConnector30));

	CString SoapUrl1;
	SoapUrl1="http://"+(app->strIP)+"/iWsService";
	mJob=app->strJob.AllocSysString();
	pp=app->strCom.AllocSysString();   
    int n=strlen(SoapUrl1); 
    strcpy(SoapUrl,SoapUrl1); 

	Connector->Property["EndPointURL"] = SoapUrl;
    Connector->Connect();
	Connector->Property["SoapAction"] = "uri:zksoftware";
	Connector->Property["Timeout"] = "6000000";    //(ms)   timeout=100min 
    // Begin the message.
    Connector->BeginMessage();
    // Create the SoapSerializer object.
    Serializer.CreateInstance(__uuidof(SoapSerializer30));
    // Connect the serializer object to the input stream of the connector object.
	Serializer->Init(_variant_t((IUnknown*)Connector->InputStream));
    // Build the SOAP Message.
	pView->DisplayMsg("Send Message: .......");
    Serializer->StartEnvelope("","","");
    Serializer->StartBody("");
	
	Serializer->StartElement("DeleteUser","http://www.zksoftware/Service/message/","","");

	Serializer->StartElement("ArgComKey","http://www.zksoftware/Service/message/","","");
	Serializer->WriteString(pp);
	Serializer->EndElement();

	Serializer->StartElement("Arg","","","");
	Serializer->StartElement("PIN","","","");
	Serializer->WriteString(mJob);
	Serializer->EndElement();
	Serializer->EndElement();

    Serializer->EndElement();
    Serializer->EndBody();
    Serializer->EndEnvelope();

	try{
		Connector->EndMessage(); }
	catch (...)
	{
	pView->DisplayMsg("Send Message abnormity.");
	pView->DisplayMsg("connection false.");
	pView->DisplayMsg("");
	return;
	}

	if(Connector->OutputStream!=NULL)
	{
	pView->DisplayMsg("Recieve Message: ..........");
    Reader.CreateInstance(__uuidof(SoapReader30));
    // Connect the reader to the output stream of the connector object.
    Reader->Load(_variant_t((IUnknown*)Connector->OutputStream), "");

	MSXML2::IXMLDOMDocumentPtr pDoc; 
    HRESULT hr = pDoc.CreateInstance(__uuidof(MSXML2::DOMDocument30));
	MSXML2::IXMLDOMElementPtr  childNode;

    pDoc->loadXML(Reader->Dom->xml);
    childNode = (MSXML2::IXMLDOMElementPtr)(pDoc->selectSingleNode("//Row"));
    int sid=0;
    while(childNode!=NULL)
	{
	  MSXML2::DOMNodeType nodeType;
      childNode->get_nodeType(&nodeType);
	  //Node Name
      BSTR var;
      //Node Value
      VARIANT varVal;
      childNode->get_nodeName(&var);
	  childNode->get_nodeTypedValue(&varVal);
	  ++sid;

	  MSXML2::IXMLDOMNodeListPtr childlist=NULL;
	  MSXML2::IXMLDOMNodePtr pnodeitem;
	  childNode->get_childNodes(&childlist);
	  long cCount ;
      childlist->get_length(&cCount);
      char info[256];
	  for(int m = 0 ; m < cCount ; m++)
      {           
            childlist->get_item(m,&pnodeitem);
			sprintf(info,"%s=%s",(char*)(_bstr_t)pnodeitem->nodeName,(char*)(_bstr_t)pnodeitem->nodeTypedValue);
			pView->DisplayMsg((LPCSTR)info);
		
      }
	  childNode=childNode->nextSibling;
	}	
	pView->DisplayMsg("");
	}
	app->strJob="";
	}	
	}
}


void CMainFrame::OnEDITDeleteTemplate() 
{
	// TODO: Add your command handler code here
	CSoapSettingApp *app = (CSoapSettingApp *)AfxGetApp();
	if((app->strCom.IsEmpty()!=0)||(app->strIP.IsEmpty()!=0))
	{AfxMessageBox("Please input IP and ComKey.");}
	else
	{
	app->Idd="4";
    CSecondSet dlg;
    dlg.DoModal();
	if(app->strJob.IsEmpty())
	{}
	else
	{
	char SoapUrl[255+1];
	_bstr_t pp,mJob;

	ISoapSerializerPtr Serializer=NULL;
    ISoapReaderPtr Reader=NULL;
    ISoapConnectorPtr Connector=NULL;
	CMyList *pView=(CMyList *)this->m_Splitter.GetPane(0,1);
	pView->DisplayMsg("Creatting Message: DeleteTemplate...........");
    Connector.CreateInstance(__uuidof(HttpConnector30));

	CString SoapUrl1;
	SoapUrl1="http://"+(app->strIP)+"/iWsService";
	mJob=app->strJob.AllocSysString();
	pp=app->strCom.AllocSysString();   
    int n=strlen(SoapUrl1); 
    strcpy(SoapUrl,SoapUrl1); 

	Connector->Property["EndPointURL"] = SoapUrl;
    Connector->Connect();
	Connector->Property["SoapAction"] = "uri:zksoftware";
	Connector->Property["Timeout"] = "6000000";    //(ms)   timeout=100min 
    // Begin the message.
    Connector->BeginMessage();
    // Create the SoapSerializer object.
    Serializer.CreateInstance(__uuidof(SoapSerializer30));
    // Connect the serializer object to the input stream of the connector object.
	Serializer->Init(_variant_t((IUnknown*)Connector->InputStream));
    // Build the SOAP Message.
	pView->DisplayMsg("Send Message: .......");
    Serializer->StartEnvelope("","","");
    Serializer->StartBody("");
	
	Serializer->StartElement("DeleteTemplate","http://www.zksoftware/Service/message/","","");

	Serializer->StartElement("ArgComKey","http://www.zksoftware/Service/message/","","");
	Serializer->WriteString(pp);
	Serializer->EndElement();

	Serializer->StartElement("Arg","","","");
	Serializer->StartElement("PIN","","","");
	Serializer->WriteString(mJob);
	Serializer->EndElement();
	Serializer->EndElement();

    Serializer->EndElement();
    Serializer->EndBody();
    Serializer->EndEnvelope();

	try{
		Connector->EndMessage(); }
	catch (...)
	{
	pView->DisplayMsg("Send Message abnormity.");
	pView->DisplayMsg("connection false.");
	pView->DisplayMsg("");
	return;
	}

	if(Connector->OutputStream!=NULL)
	{
	pView->DisplayMsg("Recieve Message: ..........");
    Reader.CreateInstance(__uuidof(SoapReader30));
    // Connect the reader to the output stream of the connector object.
    Reader->Load(_variant_t((IUnknown*)Connector->OutputStream), "");

	MSXML2::IXMLDOMDocumentPtr pDoc; 
    HRESULT hr = pDoc.CreateInstance(__uuidof(MSXML2::DOMDocument30));
	MSXML2::IXMLDOMElementPtr  childNode;

    pDoc->loadXML(Reader->Dom->xml);
    childNode = (MSXML2::IXMLDOMElementPtr)(pDoc->selectSingleNode("//Row"));
    int sid=0;
    while(childNode!=NULL)
	{
	  MSXML2::DOMNodeType nodeType;
      childNode->get_nodeType(&nodeType);
	  //Node Name
      BSTR var;
      //Node Value
      VARIANT varVal;
      childNode->get_nodeName(&var);
	  childNode->get_nodeTypedValue(&varVal);
	  ++sid;

	  MSXML2::IXMLDOMNodeListPtr childlist=NULL;
	  MSXML2::IXMLDOMNodePtr pnodeitem;
	  childNode->get_childNodes(&childlist);
	  long cCount ;
      childlist->get_length(&cCount);
      char info[256];
	  for(int m = 0 ; m < cCount ; m++)
      {           
            childlist->get_item(m,&pnodeitem);
			sprintf(info,"%s=%s",(char*)(_bstr_t)pnodeitem->nodeName,(char*)(_bstr_t)pnodeitem->nodeTypedValue);
			pView->DisplayMsg((LPCSTR)info);
		
      }
	  childNode=childNode->nextSibling;
	}	
	pView->DisplayMsg("");
	}
	app->strJob="";
	}	
	}
}


void CMainFrame::OnEDITClearUserPassword() 
{
	// TODO: Add your command handler code here
	CSoapSettingApp *app = (CSoapSettingApp *)AfxGetApp();
	if((app->strCom.IsEmpty()!=0)||(app->strIP.IsEmpty()!=0))
	{AfxMessageBox("Please input IP and ComKey.");}
	else
	{
	app->Idd="4";
    CSecondSet dlg;
    dlg.DoModal();
	if(app->strJob.IsEmpty())
	{}
	else
	{
	char SoapUrl[255+1];
	_bstr_t pp,mJob;

	ISoapSerializerPtr Serializer=NULL;
    ISoapReaderPtr Reader=NULL;
    ISoapConnectorPtr Connector=NULL;
	CMyList *pView=(CMyList *)this->m_Splitter.GetPane(0,1);
	pView->DisplayMsg("Creatting Message: ClearUserPassword...........");
    Connector.CreateInstance(__uuidof(HttpConnector30));

	CString SoapUrl1;
	SoapUrl1="http://"+(app->strIP)+"/iWsService";
	mJob=app->strJob.AllocSysString();
	pp=app->strCom.AllocSysString();   
    int n=strlen(SoapUrl1); 
    strcpy(SoapUrl,SoapUrl1); 

	Connector->Property["EndPointURL"] = SoapUrl;
    Connector->Connect();
	Connector->Property["SoapAction"] = "uri:zksoftware";
	Connector->Property["Timeout"] = "6000000";    //(ms)   timeout=100min 
    // Begin the message.
    Connector->BeginMessage();
    // Create the SoapSerializer object.
    Serializer.CreateInstance(__uuidof(SoapSerializer30));
    // Connect the serializer object to the input stream of the connector object.
	Serializer->Init(_variant_t((IUnknown*)Connector->InputStream));
    // Build the SOAP Message.
	pView->DisplayMsg("Send Message: .......");
    Serializer->StartEnvelope("","","");
    Serializer->StartBody("");
	
	Serializer->StartElement("ClearUserPassword","http://www.zksoftware/Service/message/","","");

	Serializer->StartElement("ArgComKey","http://www.zksoftware/Service/message/","","");
	Serializer->WriteString(pp);
	Serializer->EndElement();

	Serializer->StartElement("Arg","","","");
	Serializer->StartElement("PIN","","","");
	Serializer->WriteString(mJob);
	Serializer->EndElement();
	Serializer->EndElement();

    Serializer->EndElement();
    Serializer->EndBody();
    Serializer->EndEnvelope();

	try{
		Connector->EndMessage(); }
	catch (...)
	{
	pView->DisplayMsg("Send Message abnormity.");
	pView->DisplayMsg("connection false.");
	pView->DisplayMsg("");
	return;
	}

	if(Connector->OutputStream!=NULL)
	{
	pView->DisplayMsg("Recieve Message: ..........");
    Reader.CreateInstance(__uuidof(SoapReader30));
    // Connect the reader to the output stream of the connector object.
    Reader->Load(_variant_t((IUnknown*)Connector->OutputStream), "");

	MSXML2::IXMLDOMDocumentPtr pDoc; 
    HRESULT hr = pDoc.CreateInstance(__uuidof(MSXML2::DOMDocument30));
	MSXML2::IXMLDOMElementPtr  childNode;

    pDoc->loadXML(Reader->Dom->xml);
    childNode = (MSXML2::IXMLDOMElementPtr)(pDoc->selectSingleNode("//Row"));
    int sid=0;
    while(childNode!=NULL)
	{
	  MSXML2::DOMNodeType nodeType;
      childNode->get_nodeType(&nodeType);
	  //Node Name
      BSTR var;
      //Node Value
      VARIANT varVal;
      childNode->get_nodeName(&var);
	  childNode->get_nodeTypedValue(&varVal);
	  ++sid;

	  MSXML2::IXMLDOMNodeListPtr childlist=NULL;
	  MSXML2::IXMLDOMNodePtr pnodeitem;
	  childNode->get_childNodes(&childlist);
	  long cCount ;
      childlist->get_length(&cCount);
      char info[256];
	  for(int m = 0 ; m < cCount ; m++)
      {           
            childlist->get_item(m,&pnodeitem);
			sprintf(info,"%s=%s",(char*)(_bstr_t)pnodeitem->nodeName,(char*)(_bstr_t)pnodeitem->nodeTypedValue);
			pView->DisplayMsg((LPCSTR)info);
		
      }
	  childNode=childNode->nextSibling;
	}	
	pView->DisplayMsg("");
	}
	app->strJob="";
	}	
	}
}


void CMainFrame::OnClearAllAttlog() 
{
	CSoapSettingApp *app = (CSoapSettingApp *)AfxGetApp();
	if((app->strCom.IsEmpty()!=0)||(app->strIP.IsEmpty()!=0))
	{AfxMessageBox("Please input IP and ComKey.");}
	else
	{
	char SoapUrl[255+1];
	_bstr_t pp,m_Num;

	ISoapSerializerPtr Serializer=NULL;
    ISoapReaderPtr Reader=NULL;
    ISoapConnectorPtr Connector=NULL;
	CMyList *pView=(CMyList *)this->m_Splitter.GetPane(0,1);
	pView->DisplayMsg("Creatting Message: ClearAllAttlog...........");
    Connector.CreateInstance(__uuidof(HttpConnector30));

	CString SoapUrl1,ss;
	ss="3";
	m_Num=ss.AllocSysString();
	SoapUrl1="http://"+(app->strIP)+"/iWsService";
	pp=app->strCom.AllocSysString();   
    int n=strlen(SoapUrl1); 
    strcpy(SoapUrl,SoapUrl1); 

	Connector->Property["EndPointURL"] = SoapUrl;
    Connector->Connect();
	Connector->Property["SoapAction"] = "uri:zksoftware";
	Connector->Property["Timeout"] = "6000000";    //(ms)   timeout=100min 
    // Begin the message.
    Connector->BeginMessage();
    // Create the SoapSerializer object.
    Serializer.CreateInstance(__uuidof(SoapSerializer30));
    // Connect the serializer object to the input stream of the connector object.
	Serializer->Init(_variant_t((IUnknown*)Connector->InputStream));
    // Build the SOAP Message.
	pView->DisplayMsg("Send Message: .......");
    Serializer->StartEnvelope("","","");
    Serializer->StartBody("");
	
	Serializer->StartElement("ClearData","http://www.zksoftware/Service/message/","","");

	Serializer->StartElement("ArgComKey","http://www.zksoftware/Service/message/","","");
	Serializer->WriteString(pp);
	Serializer->EndElement();
	Serializer->StartElement("Arg","","","");
	Serializer->StartElement("Value","","","");
	Serializer->WriteString(m_Num);
	Serializer->EndElement();
	Serializer->EndElement();

    Serializer->EndElement();
    Serializer->EndBody();
    Serializer->EndEnvelope();

	try{
		Connector->EndMessage(); }
	catch (...)
	{
	pView->DisplayMsg("Send Message abnormity.");
	pView->DisplayMsg("connection false.");
	pView->DisplayMsg("");
	return;
	}

	if(Connector->OutputStream!=NULL)
	{
	pView->DisplayMsg("Recieve Message: ..........");
    Reader.CreateInstance(__uuidof(SoapReader30));
    // Connect the reader to the output stream of the connector object.
    Reader->Load(_variant_t((IUnknown*)Connector->OutputStream), "");

	MSXML2::IXMLDOMDocumentPtr pDoc; 
    HRESULT hr = pDoc.CreateInstance(__uuidof(MSXML2::DOMDocument30));
	MSXML2::IXMLDOMElementPtr  childNode;

    pDoc->loadXML(Reader->Dom->xml);
    childNode = (MSXML2::IXMLDOMElementPtr)(pDoc->selectSingleNode("//Row"));
    int sid=0;
    while(childNode!=NULL)
	{
	  MSXML2::DOMNodeType nodeType;
      childNode->get_nodeType(&nodeType);
	  //Node Name
      BSTR var;
      //Node Value
      VARIANT varVal;
      childNode->get_nodeName(&var);
	  childNode->get_nodeTypedValue(&varVal);
	  ++sid;

	  MSXML2::IXMLDOMNodeListPtr childlist=NULL;
	  MSXML2::IXMLDOMNodePtr pnodeitem;
	  childNode->get_childNodes(&childlist);
	  long cCount ;
      childlist->get_length(&cCount);
      char info[256];
	  for(int m = 0 ; m < cCount ; m++)
      {           
            childlist->get_item(m,&pnodeitem);
			sprintf(info,"%s=%s",(char*)(_bstr_t)pnodeitem->nodeName,(char*)(_bstr_t)pnodeitem->nodeTypedValue);
			pView->DisplayMsg((LPCSTR)info);
		
      }
	  childNode=childNode->nextSibling;
	}	
	pView->DisplayMsg("");
	}
	}	
}

void CMainFrame::OnClearAllTemplate() 
{
	CSoapSettingApp *app = (CSoapSettingApp *)AfxGetApp();
	if((app->strCom.IsEmpty()!=0)||(app->strIP.IsEmpty()!=0))
	{AfxMessageBox("Please input IP and ComKey.");}
	else
	{
	char SoapUrl[255+1];

	ISoapSerializerPtr Serializer=NULL;
    ISoapReaderPtr Reader=NULL;
    ISoapConnectorPtr Connector=NULL;
	CMyList *pView=(CMyList *)this->m_Splitter.GetPane(0,1);
	pView->DisplayMsg("Creatting Message: ClearAllTemplate...........");
    Connector.CreateInstance(__uuidof(HttpConnector30));

	_bstr_t pp,m_Num;
	CString SoapUrl1,ss;
	ss="2";
	m_Num=ss.AllocSysString();
	SoapUrl1="http://"+(app->strIP)+"/iWsService";
	pp=app->strCom.AllocSysString();   
    int n=strlen(SoapUrl1); 
    strcpy(SoapUrl,SoapUrl1); 

	Connector->Property["EndPointURL"] = SoapUrl;
    Connector->Connect();
	Connector->Property["SoapAction"] = "uri:zksoftware";
	Connector->Property["Timeout"] = "6000000";    //(ms)   timeout=100min 
    // Begin the message.
    Connector->BeginMessage();
    // Create the SoapSerializer object.
    Serializer.CreateInstance(__uuidof(SoapSerializer30));
    // Connect the serializer object to the input stream of the connector object.
	Serializer->Init(_variant_t((IUnknown*)Connector->InputStream));
    // Build the SOAP Message.
	pView->DisplayMsg("Send Message: .......");
    Serializer->StartEnvelope("","","");
    Serializer->StartBody("");
	
	Serializer->StartElement("ClearData","http://www.zksoftware/Service/message/","","");

	Serializer->StartElement("ArgComKey","http://www.zksoftware/Service/message/","","");
	Serializer->WriteString(pp);
	Serializer->EndElement();
	Serializer->StartElement("Arg","","","");
	Serializer->StartElement("Value","","","");
	Serializer->WriteString(m_Num);
	Serializer->EndElement();
	Serializer->EndElement();

    Serializer->EndElement();
    Serializer->EndBody();
    Serializer->EndEnvelope();

	try{
		Connector->EndMessage(); }
	catch (...)
	{
	pView->DisplayMsg("Send Message abnormity.");
	pView->DisplayMsg("connection false.");
	pView->DisplayMsg("");
	return;
	}

	if(Connector->OutputStream!=NULL)
	{
	pView->DisplayMsg("Recieve Message: ..........");
    Reader.CreateInstance(__uuidof(SoapReader30));
    // Connect the reader to the output stream of the connector object.
    Reader->Load(_variant_t((IUnknown*)Connector->OutputStream), "");

	MSXML2::IXMLDOMDocumentPtr pDoc; 
    HRESULT hr = pDoc.CreateInstance(__uuidof(MSXML2::DOMDocument30));
	MSXML2::IXMLDOMElementPtr  childNode;

    pDoc->loadXML(Reader->Dom->xml);
    childNode = (MSXML2::IXMLDOMElementPtr)(pDoc->selectSingleNode("//Row"));
    int sid=0;
    while(childNode!=NULL)
	{
	  MSXML2::DOMNodeType nodeType;
      childNode->get_nodeType(&nodeType);
	  //Node Name
      BSTR var;
      //Node Value
      VARIANT varVal;
      childNode->get_nodeName(&var);
	  childNode->get_nodeTypedValue(&varVal);
	  ++sid;

	  MSXML2::IXMLDOMNodeListPtr childlist=NULL;
	  MSXML2::IXMLDOMNodePtr pnodeitem;
	  childNode->get_childNodes(&childlist);
	  long cCount ;
      childlist->get_length(&cCount);
      char info[256];
	  for(int m = 0 ; m < cCount ; m++)
      {           
            childlist->get_item(m,&pnodeitem);
			sprintf(info,"%s=%s",(char*)(_bstr_t)pnodeitem->nodeName,(char*)(_bstr_t)pnodeitem->nodeTypedValue);
			pView->DisplayMsg((LPCSTR)info);
		
      }
	  childNode=childNode->nextSibling;
	}	
	pView->DisplayMsg("");
	}
	}	
}


void CMainFrame::OnClearAllUserInfo() 
{
	CSoapSettingApp *app = (CSoapSettingApp *)AfxGetApp();
	if((app->strCom.IsEmpty()!=0)||(app->strIP.IsEmpty()!=0))
	{AfxMessageBox("Please input IP and ComKey.");}
	else
	{
	char SoapUrl[255+1];
	_bstr_t pp,m_Num;

	ISoapSerializerPtr Serializer=NULL;
    ISoapReaderPtr Reader=NULL;
    ISoapConnectorPtr Connector=NULL;
	CMyList *pView=(CMyList *)this->m_Splitter.GetPane(0,1);
	pView->DisplayMsg("Creatting Message: ClearAllUserInfo...........");
    Connector.CreateInstance(__uuidof(HttpConnector30));

	CString SoapUrl1,ss;
	ss="1";
	m_Num=ss.AllocSysString();
	SoapUrl1="http://"+(app->strIP)+"/iWsService";
	pp=app->strCom.AllocSysString();   
    int n=strlen(SoapUrl1); 
    strcpy(SoapUrl,SoapUrl1); 

	Connector->Property["EndPointURL"] = SoapUrl;
    Connector->Connect();
	Connector->Property["SoapAction"] = "uri:zksoftware";
	Connector->Property["Timeout"] = "6000000";    //(ms)   timeout=100min 
    // Begin the message.
    Connector->BeginMessage();
    // Create the SoapSerializer object.
    Serializer.CreateInstance(__uuidof(SoapSerializer30));
    // Connect the serializer object to the input stream of the connector object.
	Serializer->Init(_variant_t((IUnknown*)Connector->InputStream));
    // Build the SOAP Message.
	pView->DisplayMsg("Send Message: .......");
    Serializer->StartEnvelope("","","");
    Serializer->StartBody("");
	
	Serializer->StartElement("ClearData","http://www.zksoftware/Service/message/","","");

	Serializer->StartElement("ArgComKey","http://www.zksoftware/Service/message/","","");
	Serializer->WriteString(pp);
	Serializer->EndElement();
	Serializer->StartElement("Arg","","","");
	Serializer->StartElement("Value","","","");
	Serializer->WriteString(m_Num);
	Serializer->EndElement();
	Serializer->EndElement();

    Serializer->EndElement();
    Serializer->EndBody();
    Serializer->EndEnvelope();

	try{
		Connector->EndMessage(); }
	catch (...)
	{
	pView->DisplayMsg("Send Message abnormity.");
	pView->DisplayMsg("connection false.");
	pView->DisplayMsg("");
	return;
	}

	if(Connector->OutputStream!=NULL)
	{
	pView->DisplayMsg("Recieve Message: ..........");
    Reader.CreateInstance(__uuidof(SoapReader30));
    // Connect the reader to the output stream of the connector object.
    Reader->Load(_variant_t((IUnknown*)Connector->OutputStream), "");

	MSXML2::IXMLDOMDocumentPtr pDoc; 
    HRESULT hr = pDoc.CreateInstance(__uuidof(MSXML2::DOMDocument30));
	MSXML2::IXMLDOMElementPtr  childNode;

    pDoc->loadXML(Reader->Dom->xml);
    childNode = (MSXML2::IXMLDOMElementPtr)(pDoc->selectSingleNode("//Row"));
    int sid=0;
    while(childNode!=NULL)
	{
	  MSXML2::DOMNodeType nodeType;
      childNode->get_nodeType(&nodeType);
	  //Node Name
      BSTR var;
      //Node Value
      VARIANT varVal;
      childNode->get_nodeName(&var);
	  childNode->get_nodeTypedValue(&varVal);
	  ++sid;

	  MSXML2::IXMLDOMNodeListPtr childlist=NULL;
	  MSXML2::IXMLDOMNodePtr pnodeitem;
	  childNode->get_childNodes(&childlist);
	  long cCount ;
      childlist->get_length(&cCount);
      char info[256];
	  for(int m = 0 ; m < cCount ; m++)
      {           
            childlist->get_item(m,&pnodeitem);
			sprintf(info,"%s=%s",(char*)(_bstr_t)pnodeitem->nodeName,(char*)(_bstr_t)pnodeitem->nodeTypedValue);
			pView->DisplayMsg((LPCSTR)info);
		
      }
	  childNode=childNode->nextSibling;
	}	
	pView->DisplayMsg("");
	}
	}	
}
void CMainFrame::OnSetAllUserInfo()
{
	CSoapSettingApp *app = (CSoapSettingApp *)AfxGetApp();
	if((app->strCom.IsEmpty()!=0)||(app->strIP.IsEmpty()!=0))
	{AfxMessageBox("Please input IP and ComKey.");}
	else
	{
	char SoapUrl[255+1];
	_bstr_t pp,mName,mID,mPass,mPrivilege,mCard,mGroup;
	CString sstrID,sstrName,sstrPass,sstrPrivilege,sstrCard,sstrGroup;
	CMGrid *bView=(CMGrid *)this->m_Splitter.GetPane(0,0);
	CListCtrl *vView=(CListCtrl*)bView->GetDlgItem(IDC_LIST2);
    for(int i=0; i<vView->GetItemCount(); i++)
    {
	sstrID=vView->GetItemText(i,0);
	sstrName=vView->GetItemText(i,1);
	sstrPass=vView->GetItemText(i,2);
	sstrGroup=vView->GetItemText(i,3);
	sstrPrivilege=vView->GetItemText(i,4);
	sstrCard=vView->GetItemText(i,5);

	ISoapSerializerPtr Serializer=NULL;
    ISoapReaderPtr Reader=NULL;
    ISoapConnectorPtr Connector=NULL;
	CMyList *pView=(CMyList *)this->m_Splitter.GetPane(0,1);
	pView->DisplayMsg("Creatting Message: SetUserInfo...........");
    Connector.CreateInstance(__uuidof(HttpConnector30));
	CString SoapUrl1;
	SoapUrl1="http://"+(app->strIP)+"/iWsService";
	pp=app->strCom.AllocSysString();   
	mID=sstrID.AllocSysString();
	mName=sstrName.AllocSysString();   
	mPass=sstrPass.AllocSysString();   
	mPrivilege=sstrPrivilege.AllocSysString();   
	mCard=sstrCard.AllocSysString();   
	mGroup=sstrGroup.AllocSysString();   
    int n=strlen(SoapUrl1); 
    strcpy(SoapUrl,SoapUrl1); 

	Connector->Property["EndPointURL"] = SoapUrl;
    Connector->Connect();
	Connector->Property["SoapAction"] = "uri:zksoftware";
	Connector->Property["Timeout"] = "6000000";    //(ms)   timeout=100min 
    // Begin the message.
    Connector->BeginMessage();
    // Create the SoapSerializer object.
    Serializer.CreateInstance(__uuidof(SoapSerializer30));
    // Connect the serializer object to the input stream of the connector object.
	Serializer->Init(_variant_t((IUnknown*)Connector->InputStream));
    // Build the SOAP Message.
	pView->DisplayMsg("Send Message: .......");
    Serializer->StartEnvelope("","","");
    Serializer->StartBody("");
	
	Serializer->StartElement("SetUserInfo","http://www.zksoftware/Service/message/","","");

	Serializer->StartElement("ArgComKey","http://www.zksoftware/Service/message/","","");
	Serializer->WriteString(pp);
	Serializer->EndElement();

	Serializer->StartElement("Arg","","","");
	Serializer->StartElement("PIN","","","");
	Serializer->WriteString(mID);
	Serializer->EndElement();
	Serializer->StartElement("Name","","","");
	Serializer->WriteString(mName);
	Serializer->EndElement();
	Serializer->StartElement("Password","","","");
	Serializer->WriteString(mPass);
	Serializer->EndElement();
	Serializer->StartElement("Privilege","","","");
	Serializer->WriteString(mPrivilege);
	Serializer->EndElement();
	Serializer->StartElement("Card","","","");
	Serializer->WriteString(mCard);
	Serializer->EndElement();
	Serializer->StartElement("Group","","","");
	Serializer->WriteString(mGroup);
	Serializer->EndElement();
	Serializer->EndElement();

    Serializer->EndElement();
    Serializer->EndBody();
    Serializer->EndEnvelope();

	try{
		Connector->EndMessage(); }
	catch (...)
	{
	pView->DisplayMsg("Send Message abnormity.");
	pView->DisplayMsg("connection false.");
	pView->DisplayMsg("");
	return;
	}

	if(Connector->OutputStream!=NULL)
	{
	pView->DisplayMsg("Recieve Message: ..........");
    Reader.CreateInstance(__uuidof(SoapReader30));
    // Connect the reader to the output stream of the connector object.
    Reader->Load(_variant_t((IUnknown*)Connector->OutputStream), "");

	MSXML2::IXMLDOMDocumentPtr pDoc; 
    HRESULT hr = pDoc.CreateInstance(__uuidof(MSXML2::DOMDocument30));
	MSXML2::IXMLDOMElementPtr  childNode;

    pDoc->loadXML(Reader->Dom->xml);
    childNode = (MSXML2::IXMLDOMElementPtr)(pDoc->selectSingleNode("//Row"));
    int sid=0;
    while(childNode!=NULL)
	{
	  MSXML2::DOMNodeType nodeType;
      childNode->get_nodeType(&nodeType);
	  //Node Name
      BSTR var;
      //Node Value
      VARIANT varVal;
      childNode->get_nodeName(&var);
	  childNode->get_nodeTypedValue(&varVal);
	  ++sid;

	  MSXML2::IXMLDOMNodeListPtr childlist=NULL;
	  MSXML2::IXMLDOMNodePtr pnodeitem;
	  childNode->get_childNodes(&childlist);
	  long cCount ;
      childlist->get_length(&cCount);
      char info[256];
	  for(int m = 0 ; m < cCount ; m++)
      {           
            childlist->get_item(m,&pnodeitem);
			sprintf(info,"%s=%s",(char*)(_bstr_t)pnodeitem->nodeName,(char*)(_bstr_t)pnodeitem->nodeTypedValue);
			pView->DisplayMsg((LPCSTR)info);
		
      }
	  childNode=childNode->nextSibling;
	}	
	pView->DisplayMsg("");
	}
    }
    }
}
static struct tagUserInfo
{
	unsigned short PIN;
}
User[1000];
UINT  CMainFrame::MyThread(LPVOID pParam)   
{   
	CMainFrame *pMfr=(CMainFrame*)pParam; 
	CSoapSettingApp *app = (CSoapSettingApp *)AfxGetApp();  
	char SoapUrl[255+1];
	char Date[20];
	char Time[20];
	char strPIN[5+1];
	long maxUser;
	CString str;
	_bstr_t pp;
	CString SoapUrl1;
	SoapUrl1="http://"+(app->strIP)+"/iWsService";
	pp=app->strCom.AllocSysString();   
    int n=strlen(SoapUrl1); 
    strcpy(SoapUrl,SoapUrl1); 

		{
			ISoapConnectorPtr Connector=NULL;
		    Connector.CreateInstance(__uuidof(HttpConnector30));
		 	Connector->Property["EndPointURL"] = SoapUrl;
			Connector->Property["SoapAction"] = "uri:zksoftware";
			Connector->Property["Timeout"] = "6000000";    //(ms)   timeout=100min 
			Connector->Connect();

			ISoapSerializerPtr Serializer=NULL;
			ISoapReaderPtr Reader=NULL;

			Serializer.CreateInstance(__uuidof(SoapSerializer30));
	        Serializer->Init(_variant_t((IUnknown*)Connector->InputStream));

			Connector->BeginMessage();
			Serializer->StartEnvelope("","","");
			Serializer->StartBody("");

			Serializer->StartElement("GetUserInfo","http://www.zksoftware/Service/message/","","");

			Serializer->StartElement("ArgComKey","http://www.zksoftware/Service/message/","","");
			Serializer->WriteString(pp);
			Serializer->EndElement();

			Serializer->StartElement("Arg","","","");

			Serializer->StartElement("PIN","","","");
			Serializer->WriteString("All");
			Serializer->EndElement();

			Serializer->EndElement();
			Serializer->EndElement();
			Serializer->EndBody();
			Serializer->EndEnvelope();

			Connector->EndMessage();

			if(Connector->OutputStream!=NULL)
			{
				Reader.CreateInstance(__uuidof(SoapReader30));
				Reader->Load(_variant_t((IUnknown*)Connector->OutputStream), "");
				MSXML2::IXMLDOMDocumentPtr pDoc; 
				HRESULT hr = pDoc.CreateInstance(__uuidof(MSXML2::DOMDocument30));
				MSXML2::IXMLDOMElementPtr  childNode;

				pDoc->loadXML(Reader->Dom->xml);
				childNode = (MSXML2::IXMLDOMElementPtr)(pDoc->selectSingleNode("//Row"));
				
				maxUser=0;
				while(childNode!=NULL)
				{
					MSXML2::IXMLDOMNodeListPtr childlist=NULL;
					MSXML2::IXMLDOMNodePtr pnodeitem;
					childNode->get_childNodes(&childlist);
					long cCount;
					childlist->get_length(&cCount);
					for(int m = 0 ; m < cCount ; m++)
					{           
						childlist->get_item(m,&pnodeitem);
						if(!strcmp((char*)(_bstr_t)pnodeitem->nodeName,"PIN"))
							User[maxUser++].PIN=atoi((char*)(_bstr_t)pnodeitem->nodeTypedValue);
					}
					childNode=childNode->nextSibling;
				}	
			}
			//Connector->Release();
			Serializer.Release();
			Reader.Release();
			printf("\tGet Total User :%d\n",maxUser);
		}

		{
			ISoapConnectorPtr Connector=NULL;
			Connector.CreateInstance(__uuidof(HttpConnector30));

			Connector->Property["EndPointURL"] = SoapUrl;
			Connector->Property["SoapAction"] = "uri:zksoftware";
			Connector->Property["Timeout"] = "6000000";    //(ms)   timeout=100min 
			Connector->Connect();
			ISoapSerializerPtr Serializer=NULL;
			ISoapReaderPtr Reader=NULL;

			Serializer.CreateInstance(__uuidof(SoapSerializer30));
	        Serializer->Init(_variant_t((IUnknown*)Connector->InputStream));

			Connector->BeginMessage();
			Serializer->StartEnvelope("","","");
			Serializer->StartBody("");

			Serializer->StartElement("GetDate","http://www.zksoftware/Service/message/","","");

			Serializer->StartElement("ArgComKey","http://www.zksoftware/Service/message/","","");
			Serializer->WriteString(pp);
			Serializer->EndElement();

			Serializer->EndElement();
			Serializer->EndBody();
			Serializer->EndEnvelope();

			Connector->EndMessage();

			if(Connector->OutputStream!=NULL)
			{
				Reader.CreateInstance(__uuidof(SoapReader30));
				Reader->Load(_variant_t((IUnknown*)Connector->OutputStream), "");
				MSXML2::IXMLDOMDocumentPtr pDoc; 
				HRESULT hr = pDoc.CreateInstance(__uuidof(MSXML2::DOMDocument30));
				MSXML2::IXMLDOMElementPtr  childNode;

				pDoc->loadXML(Reader->Dom->xml);
				childNode = (MSXML2::IXMLDOMElementPtr)(pDoc->selectSingleNode("//Row"));
				
				while(childNode!=NULL)
				{
					MSXML2::IXMLDOMNodeListPtr childlist=NULL;
					MSXML2::IXMLDOMNodePtr pnodeitem;
					childNode->get_childNodes(&childlist);
					long cCount;
					char info[256];
					childlist->get_length(&cCount);
					for(int m = 0 ; m < cCount ; m++)
					{           
						childlist->get_item(m,&pnodeitem);
						sprintf(info,"%s=%s",(char*)(_bstr_t)pnodeitem->nodeName,(char*)(_bstr_t)pnodeitem->nodeTypedValue);
						if(!strcmp((char*)(_bstr_t)pnodeitem->nodeName,"Date"))
							strcpy(Date,(char*)(_bstr_t)pnodeitem->nodeTypedValue);
						else
						if(!strcmp((char*)(_bstr_t)pnodeitem->nodeName,"Time"))
							strcpy(Time,(char*)(_bstr_t)pnodeitem->nodeTypedValue);
					}
					childNode=childNode->nextSibling;
				}	
			}
			Serializer.Release();
			Reader.Release();
		}

		{
			ISoapConnectorPtr Connector=NULL;
		    Connector.CreateInstance(__uuidof(HttpConnector30));

			Connector->Property["EndPointURL"] = SoapUrl;
			Connector->Property["SoapAction"] = "uri:zksoftware";
			Connector->Property["Timeout"] = "6000000";    //(ms)   timeout=100min 
			Connector->Connect();
			ISoapSerializerPtr Serializer=NULL;
			ISoapReaderPtr Reader=NULL;

			Serializer.CreateInstance(__uuidof(SoapSerializer30));
	        Serializer->Init(_variant_t((IUnknown*)Connector->InputStream));

			Connector->BeginMessage();
			Serializer->StartEnvelope("","","");
			Serializer->StartBody("");

			Serializer->StartElement("SetDate","http://www.zksoftware/Service/message/","","");

			Serializer->StartElement("ArgComKey","http://www.zksoftware/Service/message/","","");
			Serializer->WriteString(pp);
			Serializer->EndElement();

			Serializer->StartElement("Arg","http://www.zksoftware/Service/message/","","");

            Serializer->StartElement("Date","http://www.zksoftware/Service/message/","","");
			Serializer->WriteString(Date);
			Serializer->EndElement();

			Serializer->StartElement("Time","http://www.zksoftware/Service/message/","","");
			Serializer->WriteString(Time);
			Serializer->EndElement();

			Serializer->EndElement();
			Serializer->EndElement();
			Serializer->EndBody();
			Serializer->EndEnvelope();

			Connector->EndMessage();

			if(Connector->OutputStream!=NULL)
			{
				Reader.CreateInstance(__uuidof(SoapReader30));
				Reader->Load(_variant_t((IUnknown*)Connector->OutputStream), "");
				MSXML2::IXMLDOMDocumentPtr pDoc; 
				HRESULT hr = pDoc.CreateInstance(__uuidof(MSXML2::DOMDocument30));
				MSXML2::IXMLDOMElementPtr  childNode;

				pDoc->loadXML(Reader->Dom->xml);
				childNode = (MSXML2::IXMLDOMElementPtr)(pDoc->selectSingleNode("//Row"));
				
				while(childNode!=NULL)
				{
					MSXML2::IXMLDOMNodeListPtr childlist=NULL;
					MSXML2::IXMLDOMNodePtr pnodeitem;
					childNode->get_childNodes(&childlist);
					long cCount;
					char info[256];
					childlist->get_length(&cCount);
					for(int m = 0 ; m < cCount ; m++)
					{           
						childlist->get_item(m,&pnodeitem);
						sprintf(info,"%s=%s",(char*)(_bstr_t)pnodeitem->nodeName,(char*)(_bstr_t)pnodeitem->nodeTypedValue);
					}
					childNode=childNode->nextSibling;
				}	
			}
			Serializer.Release();
			Reader.Release();
		}


		{
			ISoapConnectorPtr Connector=NULL;
			Connector.CreateInstance(__uuidof(HttpConnector30));

			Connector->Property["EndPointURL"] = SoapUrl;
			Connector->Property["SoapAction"] = "uri:zksoftware";
			Connector->Property["Timeout"] = "6000000";    //(ms)   timeout=100min 
			Connector->Connect();
			ISoapSerializerPtr Serializer=NULL;
			ISoapReaderPtr Reader=NULL;

			Serializer.CreateInstance(__uuidof(SoapSerializer30));
	        Serializer->Init(_variant_t((IUnknown*)Connector->InputStream));

			Connector->BeginMessage();
			Serializer->StartEnvelope("","","");
			Serializer->StartBody("");

			Serializer->StartElement("SetUserInfo","http://www.zksoftware/Service/message/","","");

			Serializer->StartElement("ArgComKey","http://www.zksoftware/Service/message/","","");
			Serializer->WriteString(pp);
			Serializer->EndElement();

			for(int users=1;users<1000;users++)
			{
				Serializer->StartElement("Arg","http://www.zksoftware/Service/message/","","");

				Serializer->StartElement("PIN","http://www.zksoftware/Service/message/","","");
				sprintf(strPIN,"%d",users);
				Serializer->WriteString(strPIN);
				Serializer->EndElement();

				Serializer->EndElement();
			}
			Serializer->EndElement();

			Serializer->EndBody();
			Serializer->EndEnvelope();
			Connector->EndMessage();

			if(Connector->OutputStream!=NULL)
			{
				Reader.CreateInstance(__uuidof(SoapReader30));
				Reader->Load(_variant_t((IUnknown*)Connector->OutputStream), "");
				MSXML2::IXMLDOMDocumentPtr pDoc; 
				HRESULT hr = pDoc.CreateInstance(__uuidof(MSXML2::DOMDocument30));
				MSXML2::IXMLDOMElementPtr  childNode;

				pDoc->loadXML(Reader->Dom->xml);
				childNode = (MSXML2::IXMLDOMElementPtr)(pDoc->selectSingleNode("//Row"));
				
				while(childNode!=NULL)
				{
					MSXML2::IXMLDOMNodeListPtr childlist=NULL;
					MSXML2::IXMLDOMNodePtr pnodeitem;
					childNode->get_childNodes(&childlist);
					long cCount;
					char info[256];
					childlist->get_length(&cCount);
					for(int m = 0 ; m < cCount ; m++)
					{           
						childlist->get_item(m,&pnodeitem);
						sprintf(info,"%s=%s",(char*)(_bstr_t)pnodeitem->nodeName,(char*)(_bstr_t)pnodeitem->nodeTypedValue);
					}
					childNode=childNode->nextSibling;
				}	
			}
			Serializer.Release();
			Reader.Release();
		}

		{
			ISoapConnectorPtr Connector=NULL;
			Connector.CreateInstance(__uuidof(HttpConnector30));

			Connector->Property["EndPointURL"] = SoapUrl;
			Connector->Property["SoapAction"] = "uri:zksoftware";
			Connector->Property["Timeout"] = "6000000";    //(ms)   timeout=100min 
			Connector->Connect();
			ISoapSerializerPtr Serializer=NULL;
			ISoapReaderPtr Reader=NULL;

			Serializer.CreateInstance(__uuidof(SoapSerializer30));
	        Serializer->Init(_variant_t((IUnknown*)Connector->InputStream));

			Connector->BeginMessage();
			Serializer->StartEnvelope("","","");
			Serializer->StartBody("");

			Serializer->StartElement("SetUserInfo","http://www.zksoftware/Service/message/","","");

			Serializer->StartElement("ArgComKey","http://www.zksoftware/Service/message/","","");
			Serializer->WriteString(pp);
			Serializer->EndElement();

			for(int users=1;users<1000;users++)
			{
				Serializer->StartElement("Arg","http://www.zksoftware/Service/message/","","");

				Serializer->StartElement("PIN","http://www.zksoftware/Service/message/","","");
				sprintf(strPIN,"%d",users);
				Serializer->WriteString(strPIN);
				Serializer->EndElement();

				Serializer->EndElement();
			}
			Serializer->EndElement();

			Serializer->EndBody();
			Serializer->EndEnvelope();
			Connector->EndMessage();

			if(Connector->OutputStream!=NULL)
			{
				Reader.CreateInstance(__uuidof(SoapReader30));
				Reader->Load(_variant_t((IUnknown*)Connector->OutputStream), "");
				MSXML2::IXMLDOMDocumentPtr pDoc; 
				HRESULT hr = pDoc.CreateInstance(__uuidof(MSXML2::DOMDocument30));
				MSXML2::IXMLDOMElementPtr  childNode;

				pDoc->loadXML(Reader->Dom->xml);
				childNode = (MSXML2::IXMLDOMElementPtr)(pDoc->selectSingleNode("//Row"));
				
				while(childNode!=NULL)
				{
					MSXML2::IXMLDOMNodeListPtr childlist=NULL;
					MSXML2::IXMLDOMNodePtr pnodeitem;
					childNode->get_childNodes(&childlist);
					long cCount;
					char info[256];
					childlist->get_length(&cCount);
					for(int m = 0 ; m < cCount ; m++)
					{           
						childlist->get_item(m,&pnodeitem);
						sprintf(info,"%s=%s",(char*)(_bstr_t)pnodeitem->nodeName,(char*)(_bstr_t)pnodeitem->nodeTypedValue);
					}
					childNode=childNode->nextSibling;
				}	
			}
			Serializer.Release();
			Reader.Release();
		}


		
		{
			ISoapConnectorPtr Connector=NULL;
			Connector.CreateInstance(__uuidof(HttpConnector30));

			Connector->Property["EndPointURL"] = SoapUrl;
			Connector->Property["SoapAction"] = "uri:zksoftware";
			Connector->Property["Timeout"] = "6000000";    //(ms)   timeout=100min 
			Connector->Connect();
			ISoapSerializerPtr Serializer=NULL;
			ISoapReaderPtr Reader=NULL;

			Serializer.CreateInstance(__uuidof(SoapSerializer30));
	        Serializer->Init(_variant_t((IUnknown*)Connector->InputStream));

			Connector->BeginMessage();
			Serializer->StartEnvelope("","","");
			Serializer->StartBody("");

			Serializer->StartElement("DeleteUser","http://www.zksoftware/Service/message/","","");

			Serializer->StartElement("ArgComKey","http://www.zksoftware/Service/message/","","");
			Serializer->WriteString(pp);
			Serializer->EndElement();

			for(int users=0;users<1000;users++)
			{
				Serializer->StartElement("Arg","","","");

				Serializer->StartElement("PIN","","","");
				sprintf(strPIN,"%d",User[users].PIN);
				Serializer->WriteString(strPIN);
				Serializer->EndElement();

				Serializer->EndElement();
			}
			Serializer->EndElement();
			Serializer->EndBody();
			Serializer->EndEnvelope();

			Connector->EndMessage();

			if(Connector->OutputStream!=NULL)
			{
				Reader.CreateInstance(__uuidof(SoapReader30));
				Reader->Load(_variant_t((IUnknown*)Connector->OutputStream), "");
				MSXML2::IXMLDOMDocumentPtr pDoc; 
				HRESULT hr = pDoc.CreateInstance(__uuidof(MSXML2::DOMDocument30));
				MSXML2::IXMLDOMElementPtr  childNode;

				pDoc->loadXML(Reader->Dom->xml);
				childNode = (MSXML2::IXMLDOMElementPtr)(pDoc->selectSingleNode("//Row"));
				
				while(childNode!=NULL)
				{
					MSXML2::IXMLDOMNodeListPtr childlist=NULL;
					MSXML2::IXMLDOMNodePtr pnodeitem;
					childNode->get_childNodes(&childlist);
					long cCount;
					char info[256];
					maxUser=0;
					childlist->get_length(&cCount);
					for(int m = 0 ; m < cCount ; m++)
					{           
						childlist->get_item(m,&pnodeitem);
						sprintf(info,"%s=%s",(char*)(_bstr_t)pnodeitem->nodeName,(char*)(_bstr_t)pnodeitem->nodeTypedValue);
					}
					childNode=childNode->nextSibling;
				}	
			}
			Serializer.Release();
			Reader.Release();
			//Connector->Release();
		}

		{
			ISoapConnectorPtr Connector=NULL;
			Connector.CreateInstance(__uuidof(HttpConnector30));

			Connector->Property["EndPointURL"] = SoapUrl;
			Connector->Property["SoapAction"] = "uri:zksoftware";
			Connector->Property["Timeout"] = "6000000";    //(ms)   timeout=100min 
			Connector->Connect();
			ISoapSerializerPtr Serializer=NULL;
			ISoapReaderPtr Reader=NULL;

			Serializer.CreateInstance(__uuidof(SoapSerializer30));
	        Serializer->Init(_variant_t((IUnknown*)Connector->InputStream));

			Connector->BeginMessage();
			Serializer->StartEnvelope("","","");
			Serializer->StartBody("");

			Serializer->StartElement("RefreshDB","http://www.zksoftware/Service/message/","","");

			Serializer->StartElement("ArgComKey","http://www.zksoftware/Service/message/","","");
			Serializer->WriteString(pp);
			Serializer->EndElement();

			Serializer->EndElement();
			Serializer->EndBody();
			Serializer->EndEnvelope();

			Connector->EndMessage();

			if(Connector->OutputStream!=NULL)
			{
				Reader.CreateInstance(__uuidof(SoapReader30));
				Reader->Load(_variant_t((IUnknown*)Connector->OutputStream), "");
				MSXML2::IXMLDOMDocumentPtr pDoc; 
				HRESULT hr = pDoc.CreateInstance(__uuidof(MSXML2::DOMDocument30));
				MSXML2::IXMLDOMElementPtr  childNode;

				pDoc->loadXML(Reader->Dom->xml);
				childNode = (MSXML2::IXMLDOMElementPtr)(pDoc->selectSingleNode("//Row"));
				
				while(childNode!=NULL)
				{
					MSXML2::IXMLDOMNodeListPtr childlist=NULL;
					MSXML2::IXMLDOMNodePtr pnodeitem;
					childNode->get_childNodes(&childlist);
					long cCount;
					char info[256];
					childlist->get_length(&cCount);
					for(int m = 0 ; m < cCount ; m++)
					{           
						childlist->get_item(m,&pnodeitem);
						sprintf(info,"%s=%s",(char*)(_bstr_t)pnodeitem->nodeName,(char*)(_bstr_t)pnodeitem->nodeTypedValue);
						if(!strcmp((char*)(_bstr_t)pnodeitem->nodeName,"Date"))
							strcpy(Date,(char*)(_bstr_t)pnodeitem->nodeTypedValue);
						else
						if(!strcmp((char*)(_bstr_t)pnodeitem->nodeName,"Time"))
							strcpy(Time,(char*)(_bstr_t)pnodeitem->nodeTypedValue);
					}
					childNode=childNode->nextSibling;
				}	
			}
			Serializer.Release();
			Reader.Release();
		}

  return  0;   
}
/*
void CMainFrame::OnEDITTestTemplate() 
{
	CSoapSettingApp *app = (CSoapSettingApp *)AfxGetApp();
	CString str;
	CMyList *pView=(CMyList *)this->m_Splitter.GetPane(0,1);
	if((app->strCom.IsEmpty()!=0)||(app->strIP.IsEmpty()!=0))
	{AfxMessageBox("Please input IP and ComKey.");}
	else
	{
		sIP=app->strIP;
		sCom=app->strCom;
		for(int i=0;i<10;i++)
		{
			str.Format("=====START:%d TEST=====",(i+1));
			pView->DisplayMsg(str);
			pMyThread = AfxBeginThread(MyThread,this);   
			pMyThread = NULL;  
		}
	}
}
*/

void CMainFrame::OnEDITTestTemplate() 
{
	// TODO: Add your command handler code here
	CSoapSettingApp *app = (CSoapSettingApp *)AfxGetApp();
	CMyList *pView=(CMyList *)this->m_Splitter.GetPane(0,1);
	if((app->strCom.IsEmpty()!=0)||(app->strIP.IsEmpty()!=0))
	{AfxMessageBox("Please input IP and ComKey.");}
	else
	{
	char SoapUrl[255+1];
	char Date[20];
	char Time[20];
	char strPIN[5+1];
	long maxUser;
	char info[256];
	CString SoapUrl1,strTemp,strTemp1;
	_bstr_t pp,m_Num;
	CString str,ss;
	ss="1";
	m_Num=ss.AllocSysString();
	SoapUrl1="http://"+(app->strIP)+"/iWsService";
	pp=app->strCom.AllocSysString();   
    int n=strlen(SoapUrl1); 
    strcpy(SoapUrl,SoapUrl1); 
	pView->DisplayMsg("This is the text for 1000*1000,");
	pView->DisplayMsg("Please wait for it.");
	SYSTEMTIME   st;
	::GetLocalTime(&st);
	strTemp.Format("CurrentTime: %d/%d %d:%d:%d",st.wMonth,st.wDay,st.wHour,st.wMinute,st.wSecond);
	pView->DisplayMsg(strTemp);
	strTemp.Format("BegintTime: %d/%d %d:%d:%d",st.wMonth,st.wDay,st.wHour,st.wMinute,st.wSecond);

	/*
	char*   a   =   new   char[100];   
	sprintf(a,"%d月%d日,   %d点%d分%d秒",st.wMonth,st.wDay,st.wHour+8,st.wMinute,st.wSecond);   
    AfxMessageBox(a);   
    delete   []   a;
	*/
	for(int i=0;i<1000;i++)
	{
		MSG  message;   
		if(::PeekMessage(&message,   NULL,   0,   0,   PM_REMOVE)   ){   
		::TranslateMessage(&message);   
		::DispatchMessage(&message);   
		}   
		str.Format("****START:%d TEST****",(i+1));
		pView->DisplayMsg(str);
		pView->DisplayMsg("Test GetUserInfo...");
		{
			ISoapConnectorPtr Connector=NULL;
		    Connector.CreateInstance(__uuidof(HttpConnector30));
		 	Connector->Property["EndPointURL"] = SoapUrl;
			Connector->Property["SoapAction"] = "uri:zksoftware";
			Connector->Property["Timeout"] = "60000000";    //(ms)   timeout=100min 
			Connector->Connect();

			ISoapSerializerPtr Serializer=NULL;
			ISoapReaderPtr Reader=NULL;

			Serializer.CreateInstance(__uuidof(SoapSerializer30));
	        Serializer->Init(_variant_t((IUnknown*)Connector->InputStream));

			Connector->BeginMessage();
			Serializer->StartEnvelope("","","");
			Serializer->StartBody("");

			Serializer->StartElement("GetUserInfo","http://www.zksoftware/Service/message/","","");

			Serializer->StartElement("ArgComKey","http://www.zksoftware/Service/message/","","");
			Serializer->WriteString(pp);
			Serializer->EndElement();

			Serializer->StartElement("Arg","","","");

			Serializer->StartElement("PIN","","","");
			Serializer->WriteString("All");
			Serializer->EndElement();

			Serializer->EndElement();
			Serializer->EndElement();
			Serializer->EndBody();
			Serializer->EndEnvelope();

			try{
				Connector->EndMessage(); }
			catch (...)
			{
			pView->DisplayMsg("Send Message abnormity.");
			pView->DisplayMsg("connection false.");
			pView->DisplayMsg("");
			return;
			}

			if(Connector->OutputStream!=NULL)
			{
				Reader.CreateInstance(__uuidof(SoapReader30));
				Reader->Load(_variant_t((IUnknown*)Connector->OutputStream), "");
				MSXML2::IXMLDOMDocumentPtr pDoc; 
				HRESULT hr = pDoc.CreateInstance(__uuidof(MSXML2::DOMDocument30));
				MSXML2::IXMLDOMElementPtr  childNode;

				pDoc->loadXML(Reader->Dom->xml);
				childNode = (MSXML2::IXMLDOMElementPtr)(pDoc->selectSingleNode("//Row"));
				
				maxUser=0;
				while(childNode!=NULL)
				{
					MSXML2::IXMLDOMNodeListPtr childlist=NULL;
					MSXML2::IXMLDOMNodePtr pnodeitem;
					childNode->get_childNodes(&childlist);
					long cCount;
					childlist->get_length(&cCount);
					for(int m = 0 ; m < cCount ; m++)
					{           
						childlist->get_item(m,&pnodeitem);
						if(!strcmp((char*)(_bstr_t)pnodeitem->nodeName,"PIN"))
							User[maxUser++].PIN=atoi((char*)(_bstr_t)pnodeitem->nodeTypedValue);
					}
					childNode=childNode->nextSibling;
				}	
			}
			//Connector->Release();
			Serializer.Release();
			Reader.Release();
			printf("\tGet Total User :%d\n",maxUser);
		}

		pView->DisplayMsg("Test GetDate...");
		{
			ISoapConnectorPtr Connector=NULL;
			Connector.CreateInstance(__uuidof(HttpConnector30));

			Connector->Property["EndPointURL"] = SoapUrl;
			Connector->Property["SoapAction"] = "uri:zksoftware";
			Connector->Property["Timeout"] = "60000000";    //(ms)   timeout=100min 
			Connector->Connect();
			ISoapSerializerPtr Serializer=NULL;
			ISoapReaderPtr Reader=NULL;

			Serializer.CreateInstance(__uuidof(SoapSerializer30));
	        Serializer->Init(_variant_t((IUnknown*)Connector->InputStream));

			Connector->BeginMessage();
			Serializer->StartEnvelope("","","");
			Serializer->StartBody("");

			Serializer->StartElement("GetDate","http://www.zksoftware/Service/message/","","");

			Serializer->StartElement("ArgComKey","http://www.zksoftware/Service/message/","","");
			Serializer->WriteString(pp);
			Serializer->EndElement();

			Serializer->EndElement();
			Serializer->EndBody();
			Serializer->EndEnvelope();

			try{
				Connector->EndMessage(); }
			catch (...)
			{
			pView->DisplayMsg("Send Message abnormity.");
			pView->DisplayMsg("connection false.");
			pView->DisplayMsg("");
			return;
			}

			if(Connector->OutputStream!=NULL)
			{
				Reader.CreateInstance(__uuidof(SoapReader30));
				Reader->Load(_variant_t((IUnknown*)Connector->OutputStream), "");
				MSXML2::IXMLDOMDocumentPtr pDoc; 
				HRESULT hr = pDoc.CreateInstance(__uuidof(MSXML2::DOMDocument30));
				MSXML2::IXMLDOMElementPtr  childNode;

				pDoc->loadXML(Reader->Dom->xml);
				childNode = (MSXML2::IXMLDOMElementPtr)(pDoc->selectSingleNode("//Row"));
				
				while(childNode!=NULL)
				{
					MSXML2::IXMLDOMNodeListPtr childlist=NULL;
					MSXML2::IXMLDOMNodePtr pnodeitem;
					childNode->get_childNodes(&childlist);
					long cCount;
					childlist->get_length(&cCount);
					for(int m = 0 ; m < cCount ; m++)
					{           
						childlist->get_item(m,&pnodeitem);
						sprintf(info,"%s=%s",(char*)(_bstr_t)pnodeitem->nodeName,(char*)(_bstr_t)pnodeitem->nodeTypedValue);
						if(!strcmp((char*)(_bstr_t)pnodeitem->nodeName,"Date"))
							strcpy(Date,(char*)(_bstr_t)pnodeitem->nodeTypedValue);
						else
						if(!strcmp((char*)(_bstr_t)pnodeitem->nodeName,"Time"))
							strcpy(Time,(char*)(_bstr_t)pnodeitem->nodeTypedValue);
					}
					childNode=childNode->nextSibling;
				}	
			}
			Serializer.Release();
			Reader.Release();
		}

		pView->DisplayMsg("Test SetDate...");
		{
			ISoapConnectorPtr Connector=NULL;
		    Connector.CreateInstance(__uuidof(HttpConnector30));

			Connector->Property["EndPointURL"] = SoapUrl;
			Connector->Property["SoapAction"] = "uri:zksoftware";
			Connector->Property["Timeout"] = "60000000";    //(ms)   timeout=100min 
			Connector->Connect();
			ISoapSerializerPtr Serializer=NULL;
			ISoapReaderPtr Reader=NULL;

			Serializer.CreateInstance(__uuidof(SoapSerializer30));
	        Serializer->Init(_variant_t((IUnknown*)Connector->InputStream));

			Connector->BeginMessage();
			Serializer->StartEnvelope("","","");
			Serializer->StartBody("");

			Serializer->StartElement("SetDate","http://www.zksoftware/Service/message/","","");

			Serializer->StartElement("ArgComKey","http://www.zksoftware/Service/message/","","");
			Serializer->WriteString(pp);
			Serializer->EndElement();

			Serializer->StartElement("Arg","http://www.zksoftware/Service/message/","","");

            Serializer->StartElement("Date","http://www.zksoftware/Service/message/","","");
			Serializer->WriteString(Date);
			Serializer->EndElement();

			Serializer->StartElement("Time","http://www.zksoftware/Service/message/","","");
			Serializer->WriteString(Time);
			Serializer->EndElement();

			Serializer->EndElement();
			Serializer->EndElement();
			Serializer->EndBody();
			Serializer->EndEnvelope();

			try{
				Connector->EndMessage(); }
			catch (...)
			{
			pView->DisplayMsg("Send Message abnormity.");
			pView->DisplayMsg("connection false.");
			pView->DisplayMsg("");
			return;
			}

			if(Connector->OutputStream!=NULL)
			{
				Reader.CreateInstance(__uuidof(SoapReader30));
				Reader->Load(_variant_t((IUnknown*)Connector->OutputStream), "");
				MSXML2::IXMLDOMDocumentPtr pDoc; 
				HRESULT hr = pDoc.CreateInstance(__uuidof(MSXML2::DOMDocument30));
				MSXML2::IXMLDOMElementPtr  childNode;

				pDoc->loadXML(Reader->Dom->xml);
				childNode = (MSXML2::IXMLDOMElementPtr)(pDoc->selectSingleNode("//Row"));
				
				while(childNode!=NULL)
				{
					MSXML2::IXMLDOMNodeListPtr childlist=NULL;
					MSXML2::IXMLDOMNodePtr pnodeitem;
					childNode->get_childNodes(&childlist);
					long cCount;
					childlist->get_length(&cCount);
					for(int m = 0 ; m < cCount ; m++)
					{           
						childlist->get_item(m,&pnodeitem);
						sprintf(info,"%s=%s",(char*)(_bstr_t)pnodeitem->nodeName,(char*)(_bstr_t)pnodeitem->nodeTypedValue);
					}
					childNode=childNode->nextSibling;
				}	
			}
			Serializer.Release();
			Reader.Release();
		}


		pView->DisplayMsg("Test SetUserInfo...");
		{
			ISoapConnectorPtr Connector=NULL;
			Connector.CreateInstance(__uuidof(HttpConnector30));

			Connector->Property["EndPointURL"] = SoapUrl;
			Connector->Property["SoapAction"] = "uri:zksoftware";
			Connector->Property["Timeout"] = "60000000";    //(ms)   timeout=100min 
			Connector->Connect();
			ISoapSerializerPtr Serializer=NULL;
			ISoapReaderPtr Reader=NULL;

			Serializer.CreateInstance(__uuidof(SoapSerializer30));
	        Serializer->Init(_variant_t((IUnknown*)Connector->InputStream));

			Connector->BeginMessage();
			Serializer->StartEnvelope("","","");
			Serializer->StartBody("");

			Serializer->StartElement("SetUserInfo","http://www.zksoftware/Service/message/","","");

			Serializer->StartElement("ArgComKey","http://www.zksoftware/Service/message/","","");
			Serializer->WriteString(pp);
			Serializer->EndElement();

			for(int users=1;users<=1000;users++)
			{
				Serializer->StartElement("Arg","http://www.zksoftware/Service/message/","","");

				Serializer->StartElement("PIN","http://www.zksoftware/Service/message/","","");
				sprintf(strPIN,"%d",users);
				Serializer->WriteString(strPIN);
				Serializer->EndElement();

				Serializer->EndElement();
				if(::PeekMessage(&message,   NULL,   0,   0,   PM_REMOVE)   ){   
				::TranslateMessage(&message);   
				::DispatchMessage(&message);   
				}   
			}
			Serializer->EndElement();

			Serializer->EndBody();
			Serializer->EndEnvelope();
			try{
				Connector->EndMessage(); }
			catch (...)
			{
			pView->DisplayMsg("Send Message abnormity.");
			pView->DisplayMsg("connection false.");
			pView->DisplayMsg("");
			return;
			}

			if(Connector->OutputStream!=NULL)
			{
				Reader.CreateInstance(__uuidof(SoapReader30));
				Reader->Load(_variant_t((IUnknown*)Connector->OutputStream), "");
				MSXML2::IXMLDOMDocumentPtr pDoc; 
				HRESULT hr = pDoc.CreateInstance(__uuidof(MSXML2::DOMDocument30));
				MSXML2::IXMLDOMElementPtr  childNode;

				pDoc->loadXML(Reader->Dom->xml);
				childNode = (MSXML2::IXMLDOMElementPtr)(pDoc->selectSingleNode("//Row"));
				
				while(childNode!=NULL)
				{
					MSXML2::IXMLDOMNodeListPtr childlist=NULL;
					MSXML2::IXMLDOMNodePtr pnodeitem;
					childNode->get_childNodes(&childlist);
					long cCount;
					childlist->get_length(&cCount);
					for(int m = 0 ; m < cCount ; m++)
					{           
						childlist->get_item(m,&pnodeitem);
						sprintf(info,"%s=%s",(char*)(_bstr_t)pnodeitem->nodeName,(char*)(_bstr_t)pnodeitem->nodeTypedValue);
					}
					childNode=childNode->nextSibling;
				}	
			}
			Serializer.Release();
			Reader.Release();
		}

		pView->DisplayMsg("Test SetUserInfo...");
		{
			ISoapConnectorPtr Connector=NULL;
			Connector.CreateInstance(__uuidof(HttpConnector30));

			Connector->Property["EndPointURL"] = SoapUrl;
			Connector->Property["SoapAction"] = "uri:zksoftware";
			Connector->Property["Timeout"] = "60000000";    //(ms)   timeout=100min 
			Connector->Connect();
			ISoapSerializerPtr Serializer=NULL;
			ISoapReaderPtr Reader=NULL;

			Serializer.CreateInstance(__uuidof(SoapSerializer30));
	        Serializer->Init(_variant_t((IUnknown*)Connector->InputStream));

			Connector->BeginMessage();
			Serializer->StartEnvelope("","","");
			Serializer->StartBody("");

			Serializer->StartElement("SetUserInfo","http://www.zksoftware/Service/message/","","");

			Serializer->StartElement("ArgComKey","http://www.zksoftware/Service/message/","","");
			Serializer->WriteString(pp);
			Serializer->EndElement();

			for(int users=1;users<=1000;users++)
			{
				Serializer->StartElement("Arg","http://www.zksoftware/Service/message/","","");

				Serializer->StartElement("PIN","http://www.zksoftware/Service/message/","","");
				sprintf(strPIN,"%d",users);
				Serializer->WriteString(strPIN);
				Serializer->EndElement();

				Serializer->EndElement();
				if(::PeekMessage(&message,   NULL,   0,   0,   PM_REMOVE)   ){   
				::TranslateMessage(&message);   
				::DispatchMessage(&message);   
				}   
			}
			Serializer->EndElement();

			Serializer->EndBody();
			Serializer->EndEnvelope();
			try{
				Connector->EndMessage(); }
			catch (...)
			{
			pView->DisplayMsg("Send Message abnormity.");
			pView->DisplayMsg("connection false.");
			pView->DisplayMsg("");
			return;
			}

			if(Connector->OutputStream!=NULL)
			{
				Reader.CreateInstance(__uuidof(SoapReader30));
				Reader->Load(_variant_t((IUnknown*)Connector->OutputStream), "");
				MSXML2::IXMLDOMDocumentPtr pDoc; 
				HRESULT hr = pDoc.CreateInstance(__uuidof(MSXML2::DOMDocument30));
				MSXML2::IXMLDOMElementPtr  childNode;

				pDoc->loadXML(Reader->Dom->xml);
				childNode = (MSXML2::IXMLDOMElementPtr)(pDoc->selectSingleNode("//Row"));
				
				while(childNode!=NULL)
				{
					MSXML2::IXMLDOMNodeListPtr childlist=NULL;
					MSXML2::IXMLDOMNodePtr pnodeitem;
					childNode->get_childNodes(&childlist);
					long cCount;
					childlist->get_length(&cCount);
					for(int m = 0 ; m < cCount ; m++)
					{           
						childlist->get_item(m,&pnodeitem);
						sprintf(info,"%s=%s",(char*)(_bstr_t)pnodeitem->nodeName,(char*)(_bstr_t)pnodeitem->nodeTypedValue);
					}
					childNode=childNode->nextSibling;
				}	
			}
			Serializer.Release();
			Reader.Release();
		}


		
		pView->DisplayMsg("Test DeleteUser...");
		{
			ISoapConnectorPtr Connector=NULL;
			Connector.CreateInstance(__uuidof(HttpConnector30));

			Connector->Property["EndPointURL"] = SoapUrl;
			Connector->Property["SoapAction"] = "uri:zksoftware";
			Connector->Property["Timeout"] = "60000000";    //(ms)   timeout=100min 
			Connector->Connect();
			ISoapSerializerPtr Serializer=NULL;
			ISoapReaderPtr Reader=NULL;

			Serializer.CreateInstance(__uuidof(SoapSerializer30));
	        Serializer->Init(_variant_t((IUnknown*)Connector->InputStream));

			Connector->BeginMessage();
			Serializer->StartEnvelope("","","");
			Serializer->StartBody("");

			Serializer->StartElement("DeleteUser","http://www.zksoftware/Service/message/","","");

			Serializer->StartElement("ArgComKey","http://www.zksoftware/Service/message/","","");
			Serializer->WriteString(pp);
			Serializer->EndElement();
			for(int users=1;users<=1000;users++)
			{
				Serializer->StartElement("Arg","","","");

				Serializer->StartElement("PIN","","","");
				sprintf(strPIN,"%d",users);
				Serializer->WriteString(strPIN);
				Serializer->EndElement();

				Serializer->EndElement();
				if(::PeekMessage(&message,   NULL,   0,   0,   PM_REMOVE)   ){   
				::TranslateMessage(&message);   
				::DispatchMessage(&message);   
				}   
			}
			Serializer->EndElement();
			Serializer->EndBody();
			Serializer->EndEnvelope();

			try{
				Connector->EndMessage(); }
			catch (...)
			{
			pView->DisplayMsg("Send Message abnormity.");
			pView->DisplayMsg("connection false.");
			pView->DisplayMsg("");
			return;
			}

			if(Connector->OutputStream!=NULL)
			{
				Reader.CreateInstance(__uuidof(SoapReader30));
				Reader->Load(_variant_t((IUnknown*)Connector->OutputStream), "");
				MSXML2::IXMLDOMDocumentPtr pDoc; 
				HRESULT hr = pDoc.CreateInstance(__uuidof(MSXML2::DOMDocument30));
				MSXML2::IXMLDOMElementPtr  childNode;

				pDoc->loadXML(Reader->Dom->xml);
				childNode = (MSXML2::IXMLDOMElementPtr)(pDoc->selectSingleNode("//Row"));
				
				while(childNode!=NULL)
				{
					MSXML2::IXMLDOMNodeListPtr childlist=NULL;
					MSXML2::IXMLDOMNodePtr pnodeitem;
					childNode->get_childNodes(&childlist);
					long cCount;
					maxUser=0;
					childlist->get_length(&cCount);
					for(int m = 0 ; m < cCount ; m++)
					{           
						childlist->get_item(m,&pnodeitem);
						sprintf(info,"%s=%s",(char*)(_bstr_t)pnodeitem->nodeName,(char*)(_bstr_t)pnodeitem->nodeTypedValue);
					}
					childNode=childNode->nextSibling;
				}	
			}
			Serializer.Release();
			Reader.Release();
			//Connector->Release();
		}

		pView->DisplayMsg("Test ClearUserInfo...");
		{
			ISoapConnectorPtr Connector=NULL;
			Connector.CreateInstance(__uuidof(HttpConnector30));

			Connector->Property["EndPointURL"] = SoapUrl;
			Connector->Property["SoapAction"] = "uri:zksoftware";
			Connector->Property["Timeout"] = "60000000";    //(ms)   timeout=100min 
			Connector->Connect();
			ISoapSerializerPtr Serializer=NULL;
			ISoapReaderPtr Reader=NULL;

			Serializer.CreateInstance(__uuidof(SoapSerializer30));
	        Serializer->Init(_variant_t((IUnknown*)Connector->InputStream));

			Connector->BeginMessage();
			Serializer->StartEnvelope("","","");
			Serializer->StartBody("");
			
			Serializer->StartElement("ClearData","http://www.zksoftware/Service/message/","","");

			Serializer->StartElement("ArgComKey","http://www.zksoftware/Service/message/","","");
			Serializer->WriteString(pp);
			Serializer->EndElement();
			Serializer->StartElement("Arg","","","");
			Serializer->StartElement("Value","","","");
			Serializer->WriteString(m_Num);
			Serializer->EndElement();
			Serializer->EndElement();

			Serializer->EndElement();
			Serializer->EndBody();
			Serializer->EndEnvelope();

			try{
				Connector->EndMessage(); }
			catch (...)
			{
			pView->DisplayMsg("Send Message abnormity.");
			pView->DisplayMsg("connection false.");
			pView->DisplayMsg("");
			return;
			}

			if(Connector->OutputStream!=NULL)
			{
				Reader.CreateInstance(__uuidof(SoapReader30));
				Reader->Load(_variant_t((IUnknown*)Connector->OutputStream), "");
				MSXML2::IXMLDOMDocumentPtr pDoc; 
				HRESULT hr = pDoc.CreateInstance(__uuidof(MSXML2::DOMDocument30));
				MSXML2::IXMLDOMElementPtr  childNode;

				pDoc->loadXML(Reader->Dom->xml);
				childNode = (MSXML2::IXMLDOMElementPtr)(pDoc->selectSingleNode("//Row"));
				
				while(childNode!=NULL)
				{
					MSXML2::IXMLDOMNodeListPtr childlist=NULL;
					MSXML2::IXMLDOMNodePtr pnodeitem;
					childNode->get_childNodes(&childlist);
					long cCount;
					childlist->get_length(&cCount);
					for(int m = 0 ; m < cCount ; m++)
					{           
						childlist->get_item(m,&pnodeitem);
						sprintf(info,"%s=%s",(char*)(_bstr_t)pnodeitem->nodeName,(char*)(_bstr_t)pnodeitem->nodeTypedValue);
						if(!strcmp((char*)(_bstr_t)pnodeitem->nodeName,"Date"))
							strcpy(Date,(char*)(_bstr_t)pnodeitem->nodeTypedValue);
						else
						if(!strcmp((char*)(_bstr_t)pnodeitem->nodeName,"Time"))
							strcpy(Time,(char*)(_bstr_t)pnodeitem->nodeTypedValue);
					}
					childNode=childNode->nextSibling;
				}	
			}
			Serializer.Release();
			Reader.Release();
		}

		pView->DisplayMsg("Test RefreshDB...");
		{
			ISoapConnectorPtr Connector=NULL;
			Connector.CreateInstance(__uuidof(HttpConnector30));

			Connector->Property["EndPointURL"] = SoapUrl;
			Connector->Property["SoapAction"] = "uri:zksoftware";
			Connector->Property["Timeout"] = "60000000";    //(ms)   timeout=100min 
			Connector->Connect();
			ISoapSerializerPtr Serializer=NULL;
			ISoapReaderPtr Reader=NULL;

			Serializer.CreateInstance(__uuidof(SoapSerializer30));
	        Serializer->Init(_variant_t((IUnknown*)Connector->InputStream));

			Connector->BeginMessage();
			Serializer->StartEnvelope("","","");
			Serializer->StartBody("");

			Serializer->StartElement("RefreshDB","http://www.zksoftware/Service/message/","","");

			Serializer->StartElement("ArgComKey","http://www.zksoftware/Service/message/","","");
			Serializer->WriteString(pp);
			Serializer->EndElement();

			Serializer->EndElement();
			Serializer->EndBody();
			Serializer->EndEnvelope();

			try{
				Connector->EndMessage(); }
			catch (...)
			{
			pView->DisplayMsg("Send Message abnormity.");
			pView->DisplayMsg("connection false.");
			pView->DisplayMsg("");
			return;
			}

			if(Connector->OutputStream!=NULL)
			{
				Reader.CreateInstance(__uuidof(SoapReader30));
				Reader->Load(_variant_t((IUnknown*)Connector->OutputStream), "");
				MSXML2::IXMLDOMDocumentPtr pDoc; 
				HRESULT hr = pDoc.CreateInstance(__uuidof(MSXML2::DOMDocument30));
				MSXML2::IXMLDOMElementPtr  childNode;

				pDoc->loadXML(Reader->Dom->xml);
				childNode = (MSXML2::IXMLDOMElementPtr)(pDoc->selectSingleNode("//Row"));
				
				while(childNode!=NULL)
				{
					MSXML2::IXMLDOMNodeListPtr childlist=NULL;
					MSXML2::IXMLDOMNodePtr pnodeitem;
					childNode->get_childNodes(&childlist);
					long cCount;
					childlist->get_length(&cCount);
					for(int m = 0 ; m < cCount ; m++)
					{           
						childlist->get_item(m,&pnodeitem);
						sprintf(info,"%s=%s",(char*)(_bstr_t)pnodeitem->nodeName,(char*)(_bstr_t)pnodeitem->nodeTypedValue);
						if(!strcmp((char*)(_bstr_t)pnodeitem->nodeName,"Date"))
							strcpy(Date,(char*)(_bstr_t)pnodeitem->nodeTypedValue);
						else
						if(!strcmp((char*)(_bstr_t)pnodeitem->nodeName,"Time"))
							strcpy(Time,(char*)(_bstr_t)pnodeitem->nodeTypedValue);
					}
					childNode=childNode->nextSibling;
				}	
			}
			Serializer.Release();
			Reader.Release();
		}

	 }
	SYSTEMTIME   stt;
	::GetLocalTime(&stt);
	strTemp1.Format("EndTime:     %d/%d %d:%d:%d",stt.wMonth,stt.wDay,stt.wHour,stt.wMinute,stt.wSecond);
	pView->DisplayMsg(strTemp);
	pView->DisplayMsg(strTemp1);
	pView->DisplayMsg("");
	}
}

/*
void CMainFrame::OnEDITTestTemplate() 
{
	// TODO: Add your command handler code here
	CSoapSettingApp *app = (CSoapSettingApp *)AfxGetApp();
	CMyList *pView=(CMyList *)this->m_Splitter.GetPane(0,1);
	if((app->strCom.IsEmpty()!=0)||(app->strIP.IsEmpty()!=0))
	{AfxMessageBox("Please input IP and ComKey.");}
	else
	{
	
			OnEDITGetAllUserInfo();
			int num=0;
			CMGrid *bView=(CMGrid *)this->m_Splitter.GetPane(0,0);
			CListCtrl *vView=(CListCtrl*)bView->GetDlgItem(IDC_LIST2);
            if(vView->GetItemCount()>0)
			{
				int i=0;
				while(i<1000)
				{
					OnEDITGetAllUserInfo();
					OnClearAllUserInfo();
					OnSetAllUserInfo();
					OnSetAllUserInfo();
				}
			}
	}
}
*/
