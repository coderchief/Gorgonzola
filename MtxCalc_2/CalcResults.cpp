// CalcResults1.cpp : implementation file
/**********************************************************************************
        Class:  CalcResults
        Author: Tomas Schier
        Description: The tab that contains the GridCtrl to display the result of
		             actions triggered by the other two tabs.

   15-01-2004 First draft.

   03-02-2004 Second draft
						  Changes to allow for modeless calulator dialog

***********************************************************************************/

#include "stdafx.h"
#include "MTXCalc.h"
#include "CalcResults.h"
#include "AllPages.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCalcResults property page

IMPLEMENT_DYNCREATE(CCalcResults, CPropertyPage)

CCalcResults::CCalcResults() : CPropertyPage(CCalcResults::IDD)
{
	//{{AFX_DATA_INIT(CCalcResults)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	pGridCtrl = NULL;
}

CCalcResults::~CCalcResults()
{
	if (pGridCtrl != NULL)
		delete pGridCtrl;
}

void CCalcResults::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCalcResults)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCalcResults, CPropertyPage)
	//{{AFX_MSG_MAP(CCalcResults)
	ON_WM_SHOWWINDOW()
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCalcResults message handlers

BOOL CCalcResults::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CCalcResults::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CPropertyPage::OnShowWindow(bShow, nStatus);
	
	// TODO: Add your message handler code here
    CAllPages * pSheet = STATIC_DOWNCAST(CAllPages, GetParent());
    if (pSheet->m_pMtx->pDoc->m_mtx == NULL)
	   return ;

    int gridRows = (pSheet->m_pMtx->pDoc->m_mtx->getRowCount()) + 1;
    int gridCols = (pSheet->m_pMtx->pDoc->m_mtx->getColumnCount()) + 1;

	if (bShow == TRUE)
	{
	   if (pGridCtrl == NULL)
	   {
	    	// Create the Gridctrl object
	    	pGridCtrl = new CMatrixGrid;
		    if (!pGridCtrl) return ;

	      	// Create the Gridctrl window
		    CRect rect;
		    GetClientRect(rect);
		
		    pGridCtrl->Create(rect, this, 100);

		    // fill it up with stuff
		    pGridCtrl->SetEditable(TRUE);
		    pGridCtrl->EnableDragAndDrop(TRUE);
		}
		try {
			pGridCtrl->SetRowCount(gridRows);
			pGridCtrl->SetColumnCount(gridCols);
			pGridCtrl->SetFixedRowCount(1);
			pGridCtrl->SetFixedColumnCount(1);
		}
		catch (CMemoryException* e)
		{
			e->ReportError();
			e->Delete();
			return ;
		}

		// fill rows/cols with text
		for (int row = 0; row < pSheet->m_pMtx->GetRowCount(); row++)
		{
			for (int col = 0; col < pSheet->m_pMtx->GetColumnCount(); col++)
			{ 
				GV_ITEM Item;
				Item.mask = GVIF_TEXT|GVIF_FORMAT;
				Item.row = row;
				Item.col = col;
				if (row < 1)
				{
					Item.nFormat = DT_LEFT|DT_WORDBREAK;
					Item.strText.Format(_T("Column %d"),col);
				} 
				else if (col < 1)
				{
					Item.nFormat = DT_RIGHT|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS;
					Item.strText.Format(_T("Row %d"),row);
				} 
				else 
				{
					Item.nFormat = DT_CENTER|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS;
					MTX_TYPE val = pSheet->m_pMtx->pDoc->m_mtx->getValueAt(row-1, col-1);
					Item.strText.Format(_T("%f"),val);
				}
				pGridCtrl->SetItem(&Item);
			}
		}

		pGridCtrl->AutoSize();
		pGridCtrl->SetRowHeight(0, 3*pGridCtrl->GetRowHeight(0)/2);
	}	
}


void CCalcResults::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	CPropertyPage::OnClose();
}
