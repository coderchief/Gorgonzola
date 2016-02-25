; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CCalcUnary
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "mtxcalc.h"
LastPage=0

ClassCount=13
Class1=CAllPages
Class2=CCalcBinary
Class3=CCalcDlg
Class4=CCalcResults
Class5=CCalcUnary
Class6=CChildFrame
Class7=CMainFrame
Class8=CMTXCalcApp
Class9=CAboutDlg
Class10=CMTXCalcDoc
Class11=CMTXCalcView
Class12=CMtxSpecsDlg

ResourceCount=9
Resource1=IDD_CALC_BINARY
Resource2=IDR_MTXCALTYPE (English (U.S.))
Resource3=IDD_MTX_SPECS
Resource4=IDD_CALC_UNARY
Resource5=IDD_CALC_RESULTS
Resource6=IDD_ABOUTBOX (English (U.S.))
Resource7=IDR_MAINFRAME (English (U.S.))
Resource8=IDD_CALC_DLG
Class13=CDlgInitValues
Resource9=IDD_DIALOG_INITIAL

[CLS:CAllPages]
Type=0
BaseClass=CPropertySheet
HeaderFile=AllPages.h
ImplementationFile=AllPages.cpp
LastObject=CAllPages

[CLS:CCalcBinary]
Type=0
BaseClass=CPropertyPage
HeaderFile=CalcBinary.h
ImplementationFile=CalcBinary.cpp
Filter=D
VirtualFilter=idWC
LastObject=IDC_SUBTRACT

[CLS:CCalcDlg]
Type=0
BaseClass=CDialog
HeaderFile=CalcDlg.h
ImplementationFile=CalcDlg.cpp

[CLS:CCalcResults]
Type=0
BaseClass=CPropertyPage
HeaderFile=CalcResults.h
ImplementationFile=CalcResults.cpp
LastObject=CCalcResults
Filter=D
VirtualFilter=idWC

[CLS:CCalcUnary]
Type=0
BaseClass=CPropertyPage
HeaderFile=CalcUnary.h
ImplementationFile=CalcUnary.cpp
Filter=D
VirtualFilter=idWC
LastObject=IDC_DET_RESULT

[CLS:CChildFrame]
Type=0
BaseClass=CMDIChildWnd
HeaderFile=ChildFrm.h
ImplementationFile=ChildFrm.cpp
LastObject=CChildFrame
Filter=M
VirtualFilter=mfWC

[CLS:CMainFrame]
Type=0
BaseClass=CMDIFrameWnd
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
VirtualFilter=fWC
LastObject=ID_EDIT_CUT

[CLS:CMTXCalcApp]
Type=0
BaseClass=CWinApp
HeaderFile=MTXCalc.h
ImplementationFile=MTXCalc.cpp
LastObject=ID_FILE_NEW
Filter=N
VirtualFilter=AC

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=MTXCalc.cpp
ImplementationFile=MTXCalc.cpp
LastObject=CAboutDlg

[CLS:CMTXCalcDoc]
Type=0
BaseClass=CDocument
HeaderFile=MTXCalcDoc.h
ImplementationFile=MTXCalcDoc.cpp
LastObject=CMTXCalcDoc

[CLS:CMTXCalcView]
Type=0
BaseClass=CView
HeaderFile=MTXCalcView.h
ImplementationFile=MTXCalcView.cpp
LastObject=CMTXCalcView

[CLS:CMtxSpecsDlg]
Type=0
BaseClass=CDialog
HeaderFile=MtxSpecsDlg.h
ImplementationFile=MtxSpecsDlg.cpp
Filter=D
VirtualFilter=dWC
LastObject=CMtxSpecsDlg

[DLG:IDD_CALC_BINARY]
Type=1
Class=CCalcBinary
ControlCount=5
Control1=IDC_ADD,button,1342242816
Control2=IDC_SUBTRACT,button,1342242816
Control3=IDC_LIST1,listbox,1352728835
Control4=IDC_LIST2,listbox,1352728835
Control5=IDC_MULTIPLY,button,1342242816

[DLG:IDD_CALC_DLG]
Type=1
Class=CCalcDlg
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_CALC_TAB,SysTabControl32,1342177280

[DLG:IDD_CALC_RESULTS]
Type=1
Class=CCalcResults
ControlCount=0

[DLG:IDD_CALC_UNARY]
Type=1
Class=CCalcUnary
ControlCount=7
Control1=IDC_DETERMINANT,button,1342242816
Control2=IDC_ADJUNCT,button,1342242816
Control3=IDC_LIST1,listbox,1352728835
Control4=IDC_DET_RESULT,edit,1350633600
Control5=IDC_ADJ_RESULT,edit,1350633600
Control6=IDC_INVERSE,button,1342242816
Control7=IDC_TRANSPOSE,button,1342242816

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg

[DLG:IDD_MTX_SPECS]
Type=1
Class=CMtxSpecsDlg
ControlCount=6
Control1=IDC_ED_ROWS,edit,1350643842
Control2=IDC_ED_COLUMNS,edit,1350643842
Control3=IDOK,button,1342242817
Control4=IDCANCEL,button,1342242816
Control5=IDC_ROW_LBL,static,1342308352
Control6=IDC_COL_LBL,static,1342308352

[TB:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_FILE_PRINT
Command8=ID_APP_ABOUT
CommandCount=8

[MNU:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_PRINT_SETUP
Command4=ID_FILE_MRU_FILE1
Command5=ID_APP_EXIT
Command6=ID_VIEW_TOOLBAR
Command7=ID_VIEW_STATUS_BAR
Command8=ID_APP_ABOUT
CommandCount=8

[MNU:IDR_MTXCALTYPE (English (U.S.))]
Type=1
Class=CChildFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_CLOSE
Command4=ID_FILE_SAVE
Command5=ID_FILE_SAVE_AS
Command6=ID_FILE_PRINT
Command7=ID_FILE_PRINT_PREVIEW
Command8=ID_FILE_PRINT_SETUP
Command9=ID_FILE_MRU_FILE1
Command10=ID_APP_EXIT
Command11=ID_EDIT_UNDO
Command12=ID_EDIT_CUT
Command13=ID_EDIT_COPY
Command14=ID_EDIT_PASTE
Command15=ID_TOGGLE_READ_ONLY
Command16=ID_VIEW_TOOLBAR
Command17=ID_VIEW_STATUS_BAR
Command18=ID_WINDOW_NEW
Command19=ID_WINDOW_CASCADE
Command20=ID_WINDOW_TILE_HORZ
Command21=ID_WINDOW_ARRANGE
Command22=ID_APP_ABOUT
Command23=ID_TOOLS_ADDROW
Command24=ID_TOOLS_ADDCOL
Command25=ID_TOOLS_CALC
Command26=ID_TOOLS_INITALISE
CommandCount=26

[ACL:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE
CommandCount=14

[DLG:IDD_ABOUTBOX (English (U.S.))]
Type=1
Class=?
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_DIALOG_INITIAL]
Type=1
Class=CDlgInitValues
ControlCount=8
Control1=IDC_ED_INTIAL,edit,1350631552
Control2=IDOK,button,1342242817
Control3=IDCANCEL,button,1342242816
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC_MTXINIT,button,1342177287
Control6=IDC_CHECK_RANDOM,button,1342308361
Control7=IDC_CHECK_UNITY,button,1342308361
Control8=IDC_CHECK_VALUE,button,1342308361

[CLS:CDlgInitValues]
Type=0
HeaderFile=DlgInitValues.h
ImplementationFile=DlgInitValues.cpp
BaseClass=CDialog
Filter=D
LastObject=CDlgInitValues
VirtualFilter=dWC

