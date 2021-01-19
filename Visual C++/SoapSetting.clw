; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CUserInfo
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "soapsetting.h"
LastPage=0

ClassCount=12
Class1=CIPCOMSet
Class2=CMainFrame
Class3=CSecondSet
Class4=CSoapSettingApp
Class5=CAboutDlg
Class6=CSoapSettingDoc
Class7=CSoapSettingView

ResourceCount=8
Resource1=IDD_IPCom
Resource2=IDD_UserInfo
Resource3=IDD_MYLIST_FORM
Resource4=IDD_Second
Resource5=IDD_ABOUTBOX
Class8=CMyList
Class9=CGyView
Resource6=IDD_MGRID_FORM
Resource7=IDR_MAINFRAME
Class10=CMGrid
Class11=CUserInfo
Class12=CDate
Resource8=IDD_DateTime

[CLS:CIPCOMSet]
Type=0
BaseClass=CDialog
HeaderFile=IPCOMSet.h
ImplementationFile=IPCOMSet.cpp
Filter=D
VirtualFilter=dWC
LastObject=CIPCOMSet

[CLS:CMainFrame]
Type=0
BaseClass=CFrameWnd
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
VirtualFilter=fWC
LastObject=CMainFrame

[CLS:CSecondSet]
Type=0
BaseClass=CDialog
HeaderFile=SecondSet.h
ImplementationFile=SecondSet.cpp
LastObject=CSecondSet
Filter=D
VirtualFilter=dWC

[CLS:CSoapSettingApp]
Type=0
BaseClass=CWinApp
HeaderFile=SoapSetting.h
ImplementationFile=SoapSetting.cpp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=SoapSetting.cpp
ImplementationFile=SoapSetting.cpp
LastObject=CAboutDlg

[CLS:CSoapSettingDoc]
Type=0
BaseClass=CDocument
HeaderFile=SoapSettingDoc.h
ImplementationFile=SoapSettingDoc.cpp

[CLS:CSoapSettingView]
Type=0
BaseClass=CView
HeaderFile=SoapSettingView.h
ImplementationFile=SoapSettingView.cpp

[DLG:IDD_IPCom]
Type=1
Class=CIPCOMSet
ControlCount=5
Control1=IDC_IPADDRESS1,SysIPAddress32,1342242816
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDC_EDIT1,edit,1350631552
Control5=IDC_BUTTON1,button,1342242816

[DLG:IDD_Second]
Type=1
Class=CSecondSet
ControlCount=5
Control1=IDC_EDIT1,edit,1350631552
Control2=IDC_EDIT2,edit,1350631552
Control3=IDC_BUTTON1,button,1342242816
Control4=IDC_EDIT3,edit,1342244992
Control5=IDC_EDIT4,edit,1342244992

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_Set
Command2=ID_EDIT_RefreshDB
Command3=ID_EDIT_Restart
Command4=ID_APP_EXIT
Command5=ID_EDIT_GetAttlog
Command6=ID_EDIT_GetUserInfo
Command7=ID_EDIT_SetUserInfo
Command8=ID_EDIT_GetAllUserInfo
Command9=ID_EDIT_DeleteUser
Command10=ID_EDIT_ClearUserPassword
Command11=ID_EDIT_GetUserTemplate
Command12=ID_EDIT_SetUserTemplate
Command13=ID_EDIT_DeleteTemplate
Command14=ID_EDIT_GetOption
Command15=ID_EDIT_SetOption
Command16=ID_EDIT_GetDate
Command17=ID_EDIT_SetDate
Command18=ID_ClearAllUserInfo
Command19=ID_ClearAllTemplate
Command20=ID_ClearAllAttlog
Command21=ID_EDIT_TestTemplate
Command22=ID_APP_ABOUT
CommandCount=22

[ACL:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_UNDO
Command5=ID_EDIT_CUT
Command6=ID_EDIT_COPY
Command7=ID_EDIT_PASTE
Command8=ID_EDIT_UNDO
Command9=ID_EDIT_CUT
Command10=ID_EDIT_COPY
Command11=ID_EDIT_PASTE
Command12=ID_NEXT_PANE
Command13=ID_PREV_PANE
CommandCount=13

[DLG:IDD_MYLIST_FORM]
Type=1
Class=CMyList
ControlCount=1
Control1=IDC_LIST1,listbox,1352728835

[CLS:CMyList]
Type=0
HeaderFile=MyList.h
ImplementationFile=MyList.cpp
BaseClass=CFormView
Filter=D
VirtualFilter=VWC
LastObject=CMyList

[CLS:CGyView]
Type=0
HeaderFile=GyView.h
ImplementationFile=GyView.cpp
BaseClass=CListView
Filter=C
VirtualFilter=VWC
LastObject=CGyView

[DLG:IDD_MGRID_FORM]
Type=1
Class=CMGrid
ControlCount=0

[CLS:CMGrid]
Type=0
HeaderFile=MGrid.h
ImplementationFile=MGrid.cpp
BaseClass=CFormView
Filter=D
VirtualFilter=VWC
LastObject=CMGrid

[DLG:IDD_UserInfo]
Type=1
Class=CUserInfo
ControlCount=19
Control1=IDC_EDIT1,edit,1350639744
Control2=IDC_STATIC,static,1342308352
Control3=IDC_EDIT5,edit,1350639776
Control4=IDC_STATIC,static,1342308352
Control5=IDC_EDIT2,edit,1082204288
Control6=IDC_STATIC,static,1073872896
Control7=IDC_EDIT3,edit,1350631552
Control8=IDC_STATIC,static,1342308352
Control9=IDC_STATIC,static,1342308352
Control10=IDC_BUTTON2,button,1342242816
Control11=IDC_COMBO1,combobox,1344340227
Control12=IDC_STATIC,static,1342308352
Control13=IDC_EDIT4,edit,1350639744
Control14=IDC_STATIC,static,1342308352
Control15=IDC_EDIT6,edit,1350639744
Control16=IDC_STATIC,static,1342308352
Control17=IDC_EDIT7,edit,1350639744
Control18=IDC_STATIC,static,1342308352
Control19=IDC_EDIT8,edit,1350639744

[DLG:IDD_DateTime]
Type=1
Class=CDate
ControlCount=5
Control1=IDC_STATIC,static,1342308352
Control2=IDC_DATETIMEPICKER1,SysDateTimePick32,1342242848
Control3=IDC_BUTTON1,button,1342242816
Control4=IDC_STATIC,static,1342308352
Control5=IDC_DATETIMEPICKER2,SysDateTimePick32,1342242857

[CLS:CUserInfo]
Type=0
HeaderFile=UserInfo.h
ImplementationFile=UserInfo.cpp
BaseClass=CDialog
Filter=D
LastObject=CUserInfo
VirtualFilter=dWC

[CLS:CDate]
Type=0
HeaderFile=Date.h
ImplementationFile=Date.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CDate

