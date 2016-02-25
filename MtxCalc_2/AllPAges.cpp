// AllPages.cpp : implementation file
/**********************************************************************************
        Class:  CAllPages
        Author: Tomas Schier
        Description: The implementation of the CPropertySheet derived class that holds
		             the individual property pages CCalcBinary, CCalcResults, CCalcUnary.


   15-01-2004 First draft.
                          Calculation of adjunct and determinant still need to be implemented.

   03-02-2004 Second draft
						  Changes to allow for modeless calculator dialog

***********************************************************************************/

#include "stdafx.h"
#include "MTXCalc.h"
#include "AllPages.h"
#include "MtxRef.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAllPages

IMPLEMENT_DYNAMIC(CAllPages, CPropertySheet)

CAllPages::CAllPages(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
	//m_pMtx = NULL;
	m_pMtx = new CMatrixGrid;
	m_SelectedPage = iSelectPage;
}

CAllPages::CAllPages(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
	ASSERT(pParentWnd != NULL);
	//m_pMtx = NULL;
	m_pMtx = new CMatrixGrid;
	m_pParent = (CMainFrame*)pParentWnd;
	m_SelectedPage = iSelectPage;
	
	AddControlPages();
}

CAllPages::~CAllPages()
{
	if (m_pMtx != NULL)
		delete m_pMtx;
}


BEGIN_MESSAGE_MAP(CAllPages, CPropertySheet)
	//{{AFX_MSG_MAP(CAllPages)
	ON_WM_CLOSE()
	ON_WM_SHOWWINDOW()
	ON_WM_SETFOCUS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAllPages message handlers

void CAllPages::AddControlPages()
{
   AddPage(&m_calcResults);
   AddPage(&m_calcUnary);
   AddPage(&m_calcBinary);
}


void CAllPages::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	CPropertySheet::ShowWindow(SW_HIDE);
	m_pMtx = NULL;
	m_mtxList.RemoveAll();
}



BOOL CAllPages::OnInitDialog() 
{
	BOOL bResult = CPropertySheet::OnInitDialog();
	updateMtxList();
	// TODO: Add your specialized code here
	return bResult;
}

void CAllPages::updateMtxList()
{
	m_mtxList.RemoveAll();

	POSITION pos = AfxGetApp()->GetFirstDocTemplatePosition();
	while (pos != NULL)
	{
		CDocTemplate * pDocTempl = AfxGetApp()->GetNextDocTemplate(pos);
		POSITION pos_doc= pDocTempl->GetFirstDocPosition();
		while (pos_doc != NULL)
		{
			CMTXCalcDoc * pDoc = (CMTXCalcDoc*)pDocTempl->GetNextDoc(pos_doc);
			CString st = pDoc->GetTitle();
			CMtxRef ref;
			ref.m_mtxDoc = pDoc;
			ref.m_Title = st;
			m_mtxList.AddHead(ref);
		}
	}

}


void CAllPages::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CPropertySheet::OnShowWindow(bShow, nStatus);	
	// TODO: Add your message handler code here
	// TODO: Add your message handler code here
 //   CAllPages * pSheet = STATIC_DOWNCAST(CAllPages, GetParent());
    //if (pSheet->m_pMtx == NULL)
	//   return ;

   // int gridRows = (m_pMtx->pDoc->m_mtx->getRowCount()) + 1;
  //  int gridCols = (m_pMtx->pDoc->m_mtx->getColumnCount()) + 1;
	updateMtxList();
/*	if (bShow == TRUE)
	{
	   //if (m_pMtx == NULL)
	  // {
	    	// Create the Gridctrl object
	    //	pGridCtrl = new CMatrixGrid;
		 //   if (!pGridCtrl) return ;

	      	// Create the Gridctrl window
		    CRect rect;
		    pSheet->GetClientRect(rect);
		
		    m_pMtx->Create(rect, this, 100);

		    // fill it up with stuff
		    m_pMtx->SetEditable(TRUE);
		    m_pMtx->EnableDragAndDrop(TRUE);
		}
		try {
			m_pMtx->SetRowCount(1);
			m_pMtx->SetColumnCount(1);
			m_pMtx->SetFixedRowCount(1);
			m_pMtx->SetFixedColumnCount(1);
		}
		catch (CMemoryException* e)
		{
			e->ReportError();
			e->Delete();
			return ;
		}
//	}

	updateMtxList();*/	
}

void CAllPages::OnSetFocus(CWnd* pOldWnd) 
{
	CPropertySheet::OnSetFocus(pOldWnd);	
	// TODO: Add your message handler code here
	
}

BOOL CAllPages::getMtxFromString(xpMatrix *mtx, CString st)
{
	CMtxRef * pMtxRef;
	POSITION pos = m_mtxList.GetHeadPosition();
	while (pos != NULL)
	{
		pMtxRef = &m_mtxList.GetAt(pos);
		if (pMtxRef->m_Title == st)
		{
			mtx = pMtxRef->m_mtxDoc->m_mtx;
			return TRUE;
		}
		m_mtxList.GetNext(pos);
	}
	return FALSE;

}
