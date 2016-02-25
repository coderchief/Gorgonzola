// CalcBinary1.cpp : implementation file
/**********************************************************************************
        Class:  CalcBinary
        Author: Tomas Schier
        Description: Handles the binary calculations such as Multiplication, Addition, 
		             and Subtraction. 

   15-01-2004 First draft.
                          Calculation of adjunct and determinant still need to be implemented.

   03-02-2004 Second draft
						  Changes to allow for modeless calulator dialog

***********************************************************************************/
#include "stdafx.h"
#include "MTXCalc.h"
#include "CalcBinary.h"
#include "MtxCalcDoc.h"
#include "MainFrm.h"
#include "MtxRef.h"
#include "xpMatrix.h"
#include "AllPages.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCalcBinary property page

IMPLEMENT_DYNCREATE(CCalcBinary, CPropertyPage)

CCalcBinary::CCalcBinary() : CPropertyPage(CCalcBinary::IDD)
{
	//{{AFX_DATA_INIT(CCalcBinary)
	m_selValList1 = _T("");
	m_selValList2 = _T("");
	//}}AFX_DATA_INIT
	m_mtxResult = NULL;
}

CCalcBinary::~CCalcBinary()
{
}

void CCalcBinary::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCalcBinary)
	DDX_LBString(pDX, IDC_LIST1, m_selValList1);
	DDX_LBString(pDX, IDC_LIST2, m_selValList2);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCalcBinary, CPropertyPage)
	//{{AFX_MSG_MAP(CCalcBinary)
	ON_BN_CLICKED(IDC_MULTIPLY, OnMultiply)
	ON_WM_CLOSE()
	ON_WM_CANCELMODE()
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_ADD, OnAdd)
	ON_BN_CLICKED(IDC_SUBTRACT, OnSubtract)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCalcBinary message handlers

int CCalcBinary::DoModal() 
{
	// TODO: Add your specialized code here and/or call the base class
	return CPropertyPage::DoModal();
}

BOOL CCalcBinary::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();	
	// TODO: Add extra initialization here
	updateListBox();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CCalcBinary::updateListBox()
{
	//get a pointer to the parent window
	CAllPages * parent = (CAllPages*)GetParent();
	//reset all contents
    ((CListBox*)GetDlgItem(IDC_LIST1))->ResetContent();
	((CListBox*)GetDlgItem(IDC_LIST2))->ResetContent();
	parent->updateMtxList();

	POSITION pos = parent->m_mtxList.GetHeadPosition();
	while (pos != NULL)
	{
		CMtxRef ref =  parent->m_mtxList.GetAt(pos);
		CString st = ref.m_Title;
        ((CListBox*)GetDlgItem(IDC_LIST1))->AddString(st);
		((CListBox*)GetDlgItem(IDC_LIST2))->AddString(st);
		parent->m_mtxList.GetNext(pos);
	}
}

void CCalcBinary::OnMultiply() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	CWaitCursor wait; 

	//pointer to parent window
	CAllPages * parent = (CAllPages*)GetParent();
	xpMatrix  mtx_1;
	xpMatrix  mtx_2;
    try 
	{
		//now multiply
		wait.Restore();
		CAllPages * pParent = STATIC_DOWNCAST(CAllPages, GetParent());
		if (getMatrices(mtx_1, mtx_2) == TRUE)
    		m_mtxResult = mtx_1 * mtx_2;

		
		pParent->m_pMtx->pDoc->m_mtx = &m_mtxResult;
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

bool CCalcBinary::getMatrices(xpMatrix&  xpMtx_1,xpMatrix & xpMtx_2)
{	
   	CString st1 = m_selValList1;
	CString st2 = m_selValList2;
	bool mtx_1Found = FALSE;
	bool mtx_2Found = FALSE;
	CMtxRef ref;
	
	CAllPages * parent = (CAllPages*)GetParent();

	POSITION pos = parent->m_mtxList.GetHeadPosition();
	while (pos != NULL)
	{
		ref = (CMtxRef)(parent->m_mtxList.GetAt(pos));
		if (ref.m_Title == st1)
		{
			xpMtx_1 =  *((CMtxRef)(parent->m_mtxList.GetAt(pos))).m_mtxDoc->m_mtx;
			mtx_1Found = TRUE;
			break;
		}
		parent->m_mtxList.GetNext(pos);
	}

	pos = parent->m_mtxList.GetHeadPosition();
	while (pos != NULL)
	{
		ref = (CMtxRef)(parent->m_mtxList.GetAt(pos));
		if (ref.m_Title == st2)
		{
			xpMtx_2 =  *((CMtxRef)(parent->m_mtxList.GetAt(pos))).m_mtxDoc->m_mtx;
			mtx_2Found = TRUE;
			break;
		}
		parent->m_mtxList.GetNext(pos);
	}
	return (mtx_1Found && mtx_2Found);
}

void CCalcBinary::OnClose() 
{
	// TODO: Add your message handler code here and/or call default	
	CPropertyPage::OnClose();

}

void CCalcBinary::OnCancelMode() 
{
	CPropertyPage::OnCancelMode();
	
	// TODO: Add your message handler code here
	
}


BOOL CCalcBinary::OnSetActive() 
{
	// TODO: Add your specialized code here and/or call the base class
	updateListBox();
	return CPropertyPage::OnSetActive();
}

void CCalcBinary::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CPropertyPage::OnShowWindow(bShow, nStatus);
	
	// TODO: Add your message handler code here
	if (bShow == TRUE)
		updateListBox();
	
}

void CCalcBinary::OnAdd() 
{
	// TODO: Add your control notification handler code here
	// TODO: Add your control notification handler code here
	UpdateData();

	//pointer to parent window
	CAllPages * parent = (CAllPages*)GetParent();
	xpMatrix  mtx_1;
	xpMatrix  mtx_2;
	CWaitCursor wait; 

    try 
	{
		//now multiply
		wait.Restore();
		CAllPages * pParent = STATIC_DOWNCAST(CAllPages, GetParent());
		if (getMatrices(mtx_1, mtx_2) == TRUE)
    		m_mtxResult = mtx_1 + mtx_2;

		
		pParent->m_pMtx->pDoc->m_mtx = &m_mtxResult;
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

void CCalcBinary::OnSubtract() 
{
	// TODO: Add your control notification handler code here
	// TODO: Add your control notification handler code here
	UpdateData();

	//pointer to parent window
	CAllPages * parent = (CAllPages*)GetParent();
	xpMatrix  mtx_1;
	xpMatrix  mtx_2;
	CWaitCursor wait; 
    try 
	{
		//now multiply
		wait.Restore();
		CAllPages * pParent = STATIC_DOWNCAST(CAllPages, GetParent());
		if (getMatrices(mtx_1, mtx_2) == TRUE)
    		m_mtxResult = mtx_1 - mtx_2;

		
		pParent->m_pMtx->pDoc->m_mtx = &m_mtxResult;
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
