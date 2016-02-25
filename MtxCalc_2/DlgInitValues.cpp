// DlgInitValues.cpp : implementation file
//

#include "stdafx.h"
#include "mtxcalc.h"
#include "DlgInitValues.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgInitValues dialog


CDlgInitValues::CDlgInitValues(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgInitValues::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgInitValues)
	m_initValue = 0.0;
	//}}AFX_DATA_INIT
}


void CDlgInitValues::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgInitValues)
	DDX_Control(pDX, IDC_CHECK_VALUE, m_btnValue);
	DDX_Control(pDX, IDC_CHECK_UNITY, m_btnUnity);
	DDX_Control(pDX, IDC_CHECK_RANDOM, m_btnRandom);
	DDX_Text(pDX, IDC_ED_INTIAL, m_initValue);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgInitValues, CDialog)
	//{{AFX_MSG_MAP(CDlgInitValues)
	ON_BN_CLICKED(IDC_CHECK_RANDOM, OnCheckRandom)
	ON_BN_CLICKED(IDC_CHECK_UNITY, OnCheckUnity)
	ON_BN_CLICKED(IDC_CHECK_VALUE, OnCheckValue)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgInitValues message handlers

void CDlgInitValues::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(true);
	CDialog::OnOK();
}


BOOL CDlgInitValues::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	SetCheck(IDC_CHECK_VALUE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgInitValues::OnCheckRandom() 
{
	SetCheck(IDC_CHECK_RANDOM);
}

void CDlgInitValues::OnCheckUnity() 
{
	SetCheck(IDC_CHECK_UNITY);
}

void CDlgInitValues::OnCheckValue() 
{
	SetCheck(IDC_CHECK_VALUE);
}

void CDlgInitValues::SetCheck(UINT idBtn)
{
	static UINT buttons []={IDC_CHECK_VALUE,IDC_CHECK_RANDOM,IDC_CHECK_UNITY};
	CButton *pBtn=NULL;
	for(int i=0;i<3;i++)
	{
		pBtn = (CButton*)GetDlgItem(buttons[i]);
		if(!pBtn) continue;

		if(buttons[i]==idBtn)
		{
			pBtn->SetCheck(1);
			m_checkedItem = buttons[i];
		}
		else
			pBtn->SetCheck(0);
	}
}

UINT CDlgInitValues::GetCheck()
{
	return m_checkedItem;
}
