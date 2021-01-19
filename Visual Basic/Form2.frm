VERSION 5.00
Object = "{248DD890-BB45-11CF-9ABC-0080C7E7B78D}#1.0#0"; "MSWINSCK.OCX"
Begin VB.Form Form2 
   Caption         =   "SOAP Test By Fr3"
   ClientHeight    =   5115
   ClientLeft      =   60
   ClientTop       =   450
   ClientWidth     =   7395
   LinkTopic       =   "Form2"
   ScaleHeight     =   5115
   ScaleWidth      =   7395
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton Command2 
      Caption         =   "Clear Data"
      Height          =   495
      Left            =   5400
      TabIndex        =   7
      Top             =   360
      Width           =   1455
   End
   Begin VB.TextBox Text1 
      Height          =   285
      Left            =   1320
      TabIndex        =   3
      Text            =   "192.168.1.201"
      Top             =   120
      Width           =   1695
   End
   Begin VB.CommandButton Command1 
      Caption         =   "Download Data"
      Height          =   495
      Left            =   3480
      TabIndex        =   2
      Top             =   360
      Width           =   1455
   End
   Begin VB.TextBox Buffer 
      Height          =   3735
      Left            =   120
      MultiLine       =   -1  'True
      ScrollBars      =   2  'Vertical
      TabIndex        =   1
      Top             =   1200
      Width           =   7095
   End
   Begin VB.TextBox Text2 
      Height          =   285
      Left            =   1320
      TabIndex        =   0
      Text            =   "0"
      Top             =   480
      Width           =   495
   End
   Begin MSWinsockLib.Winsock Winsock1 
      Left            =   2160
      Top             =   600
      _ExtentX        =   741
      _ExtentY        =   741
      _Version        =   393216
   End
   Begin VB.Label Label1 
      Caption         =   "IP Address"
      Height          =   255
      Left            =   240
      TabIndex        =   6
      Top             =   120
      Width           =   855
   End
   Begin VB.Label Label3 
      Caption         =   "Com Key"
      Height          =   255
      Left            =   240
      TabIndex        =   5
      Top             =   480
      Width           =   855
   End
   Begin VB.Label Label4 
      Caption         =   "Result:"
      Height          =   255
      Left            =   120
      TabIndex        =   4
      Top             =   960
      Width           =   615
   End
End
Attribute VB_Name = "Form2"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Dim Response As String
Dim Keluar As Boolean

Private Sub Command1_Click()
Buffer.Text = ""
Soap_Request = "<GetAttLog><ArgComKey xsi:type=""xsd:integer"">" & Text2.Text & "</ArgComKey><Arg><PIN xsi:type=""xsd:integer"">All</PIN></Arg></GetAttLog>"

Winsock1.LocalPort = 0
If Winsock1.State = sckClosed Then
    Winsock1.Protocol = sckTCPProtocol
    Winsock1.Connect Text1.Text, 80

    Tunggu 0.1
    
    Winsock1.SendData ("POST /iWsService HTTP/1.0" + vbCrLf)
    Winsock1.SendData ("Content-Type: text/xml" + vbCrLf)
    Winsock1.SendData ("Content-Length: " & Len(Soap_Request) & vbCrLf & vbCrLf)
    Winsock1.SendData (Soap_Request + vbCrLf)
    WaitFor ("</GetAttLogResponse>")
    Winsock1.Close
Else
    MsgBox (Str(Winsock1.State))
End If
End Sub

Sub Tunggu(Waktu)
Start = Timer
Do While Timer - Start < Waktu
    DoEvents
Loop
End Sub

Private Sub Command2_Click()
Buffer.Text = ""
Soap_Request = "<ClearData><ArgComKey xsi:type=""xsd:integer"">" & Text2.Text & "</ArgComKey><Arg><Value xsi:type=""xsd:integer"">3</Value></Arg></ClearData>"

Winsock1.LocalPort = 0
If Winsock1.State = sckClosed Then
    Winsock1.Protocol = sckTCPProtocol
    Winsock1.Connect Text1.Text, 80

    Tunggu 0.1
    
    Winsock1.SendData ("POST /iWsService HTTP/1.0" + vbCrLf)
    Winsock1.SendData ("Content-Type: text/xml" + vbCrLf)
    Winsock1.SendData ("Content-Length: " & Len(Soap_Request) & vbCrLf & vbCrLf)
    Winsock1.SendData (Soap_Request + vbCrLf)
    WaitFor ("</ClearDataResponse>")
    Winsock1.Close
Else
    MsgBox (Str(Winsock1.State))
End If
End Sub

Private Sub Winsock1_DataArrival(ByVal bytesTotal As Long)
    Winsock1.GetData Response ' Check for incoming response *IMPORTANT*
    Buffer.Text = Buffer.Text & Response
End Sub

Function Cari(Kata As String) As String
Cari = ""
Buffer.Text = ""
Winsock1.SendData ("cat /mnt/mtdblock/options.cfg" + vbCrLf)
WaitFor ("#")

If InStrRev(Buffer.Text, Kata) <> 0 Then
    Dim Pos1 As Integer
    Dim Buff As String
    Pos1 = InStrRev(Buffer.Text, Kata)
    Buff = Mid(Buffer.Text, Pos1)
    Buff = Mid(Buff, 1, InStr(1, Buff, vbCrLf) - 1)
    Buff = Mid(Buff, InStr(1, Buff, "=") + 1)
    Cari = Buff
End If
End Function

Sub WaitFor(ResponseCode As String)
    Dim Tmr As Long
    Dim Start As Long
    Start = Timer ' Time event so won't get stuck in loop
    While Len(Response) = 0
        Tmr = Timer - Start
        DoEvents ' Let System keep checking for incoming response **IMPORTANT**
        If Tmr > 5 Then ' Time in seconds to wait
            MsgBox "Koneksi Error, Time Out !!!", 64, MsgTitle
            StatusTxt.Caption = "Disconnected"
            StatusTxt.Refresh
            Keluar = True
            Exit Sub
        End If
    Wend
    While InStr(1, Response, ResponseCode) = 0
        Tmr = Timer - Start
        DoEvents
        If Tmr > 5 Then
            MsgBox "Koneksi Error, Data Invalid !!! ", 64, MsgTitle
            StatusTxt.Caption = "Disconnected"
            StatusTxt.Refresh
            Keluar = True
            Exit Sub
        End If
    Wend
Response = "" ' Sent response code to blank **IMPORTANT**
End Sub



