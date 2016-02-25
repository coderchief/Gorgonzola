// CalcDlg.cpp : implementation file
/******************************************************************************
 Filename		:CalcDlg.cpp
 Author			:Tomas Schier
 Description	:

 Date		Notes
 03-Feb-04	First draft

******************************************************************************/

#include "stdafx.h"
#include "MTXCalc.h"
#include "CalcDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCalcDlg dialog


CCalcDlg::CCalcDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCalcDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCalcDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CCalcDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCalcDlg)
	DDX_Control(pDX, IDC_CALC_TAB, m_tabCtrl);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCalcDlg, CDialog)
	//{{AFX_MSG_MAP(CCalcDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCalcDlg message handlers
