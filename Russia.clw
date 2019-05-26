; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CRussiaDlg
LastTemplate=CStatic
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "Russia.h"

ClassCount=5
Class1=CRussiaApp
Class2=CRussiaDlg

ResourceCount=4
Resource1=IDR_MAINFRAME
Class3=CBrick
Class4=CColorButton
Class5=CColorStatic
Resource2=IDD_DIALOGBAR (English (U.S.))
Resource3=IDD_RUSSIA_DIALOG
Resource4=IDD_ABOUTBOX

[CLS:CRussiaApp]
Type=0
HeaderFile=Russia.h
ImplementationFile=Russia.cpp
Filter=W
LastObject=CRussiaApp

[CLS:CRussiaDlg]
Type=0
HeaderFile=RussiaDlg.h
ImplementationFile=RussiaDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=IDC_GAME_PAUSE



[DLG:IDD_RUSSIA_DIALOG]
Type=1
Class=CRussiaDlg
ControlCount=16
Control1=IDC_GAME_PAUSE,button,1342242827
Control2=IDC_STATIC_NEXT,static,1342312961
Control3=IDC_STATIC_CONTAIN,button,1342177287
Control4=IDC_STATIC_VIEW,button,1342177287
Control5=IDC_GAME_START,button,1342242827
Control6=IDC_STATIC_LEVEL,static,1342312961
Control7=IDC_SLIDER_LEVEL,msctls_trackbar32,1342242849
Control8=IDC_STATIC_TIME,static,1342312961
Control9=IDC_STATIC_TIMEBOX,static,1342308609
Control10=IDC_STATIC_SCORE,static,1342312961
Control11=IDC_STATIC_SCOREBOX,static,1342308353
Control12=IDC_STATIC_LINE,static,1342312961
Control13=IDC_STATIC_LINEBOX,static,1342308353
Control14=IDC_SETTOP,button,1342242827
Control15=IDC_GAME_NET,button,1342242827
Control16=IDC_GAME_SOUND,button,1342242827

[CLS:CBrick]
Type=0
HeaderFile=Brick.h
ImplementationFile=Brick.cpp
BaseClass=CButton
Filter=W
VirtualFilter=BWC
LastObject=CBrick

[CLS:CColorButton]
Type=0
HeaderFile=ColorButton.h
ImplementationFile=ColorButton.cpp
BaseClass=CButton
Filter=W
VirtualFilter=BWC

[CLS:CColorStatic]
Type=0
HeaderFile=ColorStatic.h
ImplementationFile=ColorStatic.cpp
BaseClass=CStatic
Filter=W
VirtualFilter=WC

[DLG:IDD_ABOUTBOX]
Type=1
Class=?
ControlCount=5
Control1=IDC_STATIC,static,1342308480
Control2=IDC_STATIC,static,1342308352
Control3=IDOK,button,1342373889
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342177294

[DLG:IDD_DIALOGBAR (English (U.S.))]
Type=1
Class=?
ControlCount=1
Control1=IDC_STATIC,static,1342308352

