// MtxSpecsDlg.cpp : implementation file
/******************************************************************************
 Filename		:MtxSpecsDlg.cpp
 Author			:Tomas Schier
 Description	:The implementation file for the CDialog derived CMtxSpecsDlg class.

 Date		Notes
 03-Feb-04	First draft

******************************************************************************/

#include "stdafx.h"
#include "MTXCalc.h"
#include "MtxSpecsDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMtxSpecsDlg dialog


CMtxSpecsDlg::CMtxSpecsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMtxSpecsDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMtxSpecsDlg)
	m_Columns = 1;
	m_Rows = 1;
	//}}AFX_DATA_INIT
}


void CMtxSpecsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMtxSpecsDlg)
	DDX_Text(pDX, IDC_ED_COLUMNS, m_Columns);
	DDV_MinMaxInt(pDX, m_Columns, 1, 2500);
	DDX_Text(pDX, IDC_ED_ROWS, m_Rows);
	DDV_MinMaxInt(pDX, m_Rows, 1, 2500);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMtxSpecsDlg, CDialog)
	//{{AFX_MSG_MAP(CMtxSpecsDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMtxSpecsDlg message handlers


void CMtxSpecsDlg::OnOK() 
{
	// TODO: Add extra validation here


	CDialog::OnOK();
}

//DEL void CMtxSpecsDlg::OnUpdateEdRows() 
//DEL {
//DEL 	// TODO: If this is a RICHEDIT control, the control will not
//DEL 	// send this notification unless you override the CDialog::OnInitDialog()
//DEL 	// function to send the EM_SETEVENTMASK message to the control
//DEL 	// with the ENM_UPDATE flag ORed into the lParam mask.
//DEL 	
//DEL 	// TODO: Add your control notification handler code here
//DEL 	int e = 4;
//DEL 	
//DEL }
