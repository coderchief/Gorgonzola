// CalcUnary1.cpp : implementation file
/**********************************************************************************
        Class:  CalcUnary.cpp
        Author: Tomas Schier
        Description: Handles thre unary calculations Inverse, Adjunct, Transpose,
		             and Determinant. Maybe more stuff later.

   15-01-2004 First draft.
                          Calculation of adjunct and determinant still need to be implemented.

   03-02-2004 Second draft
						  Changes to allow for modeless calulator dialog


***********************************************************************************/

#include "stdafx.h"
#include "MTXCalc.h"
#include "CalcUnary.h"
#include "AllPages.h"
#include "xpException.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCalcUnary property page

IMPLEMENT_DYNCREATE(CCalcUnary, CPropertyPage)

CCalcUnary::CCalcUnary() : CPropertyPage(CCalcUnary::IDD)
{
	//{{AFX_DATA_INIT(CCalcUnary)
	m_selValList1 = _T("");
	m_det = _T("");
	//}}AFX_DATA_INIT
	m_mtxResult = NULL;
}

CCalcUnary::~CCalcUnary()
{
}

void CCalcUnary::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCalcUnary)
	DDX_LBString(pDX, IDC_LIST1, m_selValList1);
	DDX_Text(pDX, IDC_DET_RESULT, m_det);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCalcUnary, CPropertyPage)
	//{{AFX_MSG_MAP(CCalcUnary)
	ON_BN_CLICKED(IDC_INVERSE, OnInverse)
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_TRANSPOSE, OnTranspose)
	ON_COMMAND(ID_TOOLS_INITALISE, OnToolsInitalise)
	ON_BN_CLICKED(IDC_DETERMINANT, OnDeterminant)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCalcUnary message handlers

BOOL CCalcUnary::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	updateListBox();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CCalcUnary::updateListBox()
{
	//get a pointer to the parent window
	CAllPages * parent = (CAllPages*)GetParent();
	//reset all contents
    ((CListBox*)GetDlgItem(IDC_LIST1))->ResetContent();

	parent->updateMtxList();

	POSITION pos = parent->m_mtxList.GetHeadPosition();
	while (pos != NULL)
	{
		CMtxRef ref =  parent->m_mtxList.GetAt(pos);
		CString st = ref.m_Title;
        ((CListBox*)GetDlgItem(IDC_LIST1))->AddString(st);
		parent->m_mtxList.GetNext(pos);
	}
}

void CCalcUnary::OnInverse() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	xpMatrix  mtx;
	CWaitCursor wait; 
	//invert the matrix
	try
	{
        CAllPages * pParent = STATIC_DOWNCAST(CAllPages, GetParent());
 		if (getMatrix(mtx) == TRUE)
		{
	        wait.Restore( );
			m_mtxResult = mtx.getInverse();
		}

	    pParent->m_pMtx->pDoc->m_mtx = &m_mtxResult;
   	    pParent->SetActivePage(0);
	    pParent->m_calcResults.pGridCtrl->Refresh();	
	}
	catch (xpException * e)
	{
		CString errMess;
		e->getErrorMessage(errMess);
		MessageBox(errMess, "Matrix Calculation Error", MB_OK);
		e->Delete();
	}	
}


bool CCalcUnary::getMatrix(xpMatrix &xpMtx)
{
   	CString st1 = m_selValList1;
	bool mtx_1Found = FALSE;
	CMtxRef ref;
	
	CAllPages * parent = (CAllPages*)GetParent();

	POSITION pos = parent->m_mtxList.GetHeadPosition();
	while (pos != NULL)
	{
		ref = (CMtxRef)(parent->m_mtxList.GetAt(pos));
		if (ref.m_Title == st1)
		{
			xpMtx =  *((CMtxRef)(parent->m_mtxList.GetAt(pos))).m_mtxDoc->m_mtx;
			mtx_1Found = TRUE;
			break;
		}
		parent->m_mtxList.GetNext(pos);
	}
    return mtx_1Found;

}

void CCalcUnary::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CPropertyPage::OnShowWindow(bShow, nStatus);
	
	// TODO: Add your message handler code here
	if (bShow == TRUE)
		updateListBox();	
}

void CCalcUnary::OnTranspose() 
{
	// TODO: Add your control notification handler code here
	UpdateData();

	CString st1 = m_selValList1;
	xpMatrix  mtx;
    CWaitCursor wait; 

	try
	{
       if (getMatrix(mtx) == TRUE)
	   {
	      int r = mtx.getRowCount();
		  int c = mtx.getColumnCount();
		  wait.Restore( );
		  m_mtxResult = mtx.getTranspose();
	   }

       CAllPages * pParent = STATIC_DOWNCAST(CAllPages, GetParent());
	   pParent->m_pMtx->pDoc->m_mtx = &m_mtxResult;
	   pParent->updateMtxList();
   	   pParent->SetActivePage(0);
	}
	catch (xpException * e)
	{
		CString errMess;
		e->getErrorMessage(errMess);
		MessageBox(errMess, "Matrix Calculation Error", MB_OK);
		e->Delete();
	}		
}

void CCalcUnary::OnToolsInitalise() 
{
	
}

void CCalcUnary::OnDeterminant() 
{
	// TODO: Add your control notification handler code here
        // TODO: Add your control notification handler code here
        UpdateData();
        xpMatrix  mtx;
        CWaitCursor wait;
		float ret = 0;
        //invert the matrix
        try
        {
           //CAllPages * pParent = STATIC_DOWNCAST(CAllPages, GetParent());
		   char buffer[255];
           if (getMatrix(mtx) == TRUE)
           {
              wait.Restore( );
			  m_det = gcvt(mtx.getDet(),10, buffer);
              //m_det = _gcvt(mtx.getDet());
           }
		   UpdateData(false);	
           //pParent->m_pMtx = &m_mtxResult;
           //pParent->SetActivePage(0);
           //pParent->m_calcResults.pGridCtrl->Refresh();
        }
        catch (xpException * e)
        {
           CString errMess;
           e->getErrorMessage(errMess);
           MessageBox(errMess, "Matrix Calculation Error", MB_OK);
           e->Delete();
        }
	
}
