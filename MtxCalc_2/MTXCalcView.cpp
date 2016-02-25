// MTXCalcView.cpp : implementation of the CMTXCalcView class
/******************************************************************************
 Filename		:MTXCalcView.cpp
 Author			:Tomas Schier
 Description	:The implementation file for the CView derived CMTXCalcView class.

 Date		Notes

******************************************************************************/

#include "stdafx.h"
#include "MTXCalc.h"

#include "MTXCalcDoc.h"
#include "MTXCalcView.h"
#include "MtxSpecsDlg.h"
#include "GridCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMTXCalcView

IMPLEMENT_DYNCREATE(CMTXCalcView, CView)

BEGIN_MESSAGE_MAP(CMTXCalcView, CView)
	//{{AFX_MSG_MAP(CMTXCalcView)
	ON_COMMAND(ID_TOGGLE_READ_ONLY, OnToggleReadOnly)
	ON_COMMAND(ID_TOOLS_ADDCOL, OnToolsAddcol)
	ON_COMMAND(ID_TOOLS_ADDROW, OnToolsAddrow)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMTXCalcView construction/destruction

CMTXCalcView::CMTXCalcView()
{
	// TODO: add construction code here
	pGridCtrl = NULL;

}

CMTXCalcView::~CMTXCalcView()
{
	if (pGridCtrl)
		delete pGridCtrl;
}

BOOL CMTXCalcView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMTXCalcView drawing

void CMTXCalcView::OnDraw(CDC* pDC)
{
	CMTXCalcDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
    int rc = pGridCtrl->GetRowCount();
	int cc = pGridCtrl->GetColumnCount();
	
}

/////////////////////////////////////////////////////////////////////////////
// CMTXCalcView printing

BOOL CMTXCalcView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMTXCalcView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// TODO: add extra initialization before printing
	if (pGridCtrl)
		pGridCtrl->OnBeginPrinting(pDC, pInfo);
}

void CMTXCalcView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// TODO: add cleanup after printing
	if (pGridCtrl)
		pGridCtrl->OnPrint(pDC, pInfo);
}

/////////////////////////////////////////////////////////////////////////////
// CMTXCalcView diagnostics

#ifdef _DEBUG
void CMTXCalcView::AssertValid() const
{
	CView::AssertValid();
}

void CMTXCalcView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMTXCalcDoc* CMTXCalcView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMTXCalcDoc)));
	return (CMTXCalcDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMTXCalcView message handlers

void CMTXCalcView::OnInitialUpdate() 
{
	
	// TODO: Add your specialized code here and/or call the base class
	CView::OnInitialUpdate();
	CMTXCalcDoc * pDoc = GetDocument();
//	CAllPages * pAllPages;
//	pAllPages = (CAllPages*)GetDlgItem(IDD_CALC_DLG);

	int gridRows = pDoc->m_mtx->getRowCount() + 1;
	int gridCols = pDoc->m_mtx->getColumnCount() + 1;
	
	if (pGridCtrl == NULL)
	{
		// Create the Gridctrl object
		pGridCtrl = new CMatrixGrid;
		if (!pGridCtrl) return;

		// Create the Gridctrl window
		CRect rect;
		GetClientRect(rect);
		
		pGridCtrl->Create(rect, this, 100);

		// fill it up with stuff
		pGridCtrl->SetEditable(TRUE);
		pGridCtrl->EnableDragAndDrop(TRUE);

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
			return;
		}

		// fill rows/cols with text
		for (int row = 0; row < pGridCtrl->GetRowCount(); row++)
			for (int col = 0; col < pGridCtrl->GetColumnCount(); col++)
			{ 
				GV_ITEM Item;
				Item.mask = GVIF_TEXT|GVIF_FORMAT;
				Item.row = row;
				Item.col = col;
				if (row < 1) {
					Item.nFormat = DT_LEFT|DT_WORDBREAK;
					Item.strText.Format(_T("Column %d"),col);
				} else if (col < 1) {
					Item.nFormat = DT_RIGHT|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS;
					Item.strText.Format(_T("Row %d"),row);
				} else {
					Item.nFormat = DT_CENTER|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS;
					MTX_TYPE val = pDoc->m_mtx->getValueAt(row-1, col-1);
					Item.strText.Format(_T("%f"),val);
				}
				pGridCtrl->SetItem(&Item);
		}

		pGridCtrl->AutoSize();
		pGridCtrl->SetRowHeight(0, 3*pGridCtrl->GetRowHeight(0)/2);
	}	
}

void CMTXCalcView::OnPrint(CDC* pDC, CPrintInfo* pInfo) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	if (pGridCtrl)
		pGridCtrl->OnBeginPrinting(pDC, pInfo);
}

BOOL CMTXCalcView::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo) 
{
	// TODO: Add your specialized code here and/or call the base class
    if (pGridCtrl && IsWindow(pGridCtrl->m_hWnd))
        if (pGridCtrl->OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
		{
			return TRUE;
		}
	return CView::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}

void CMTXCalcView::CalcWindowRect(LPRECT lpClientRect, UINT nAdjustType) 
{
	// TODO: Add your specialized code here and/or call the base class	
	CView::CalcWindowRect(lpClientRect, nAdjustType);
}

void CMTXCalcView::OnToggleReadOnly() 
{
	// TODO: Add your command handler code here	
    if (pGridCtrl && IsWindow(pGridCtrl->m_hWnd))
    {
        CCellID cell = pGridCtrl->GetFocusCell();
        if (pGridCtrl->IsValid(cell))
        {
            int nState = pGridCtrl->GetItemState(cell.row, cell.col);
            if (pGridCtrl->IsCellEditable(cell))
                pGridCtrl->SetItemState(cell.row, cell.col, nState | GVIS_READONLY);
            else
                pGridCtrl->SetItemState(cell.row, cell.col, nState & ~GVIS_READONLY);
        }
    }
}

void CMTXCalcView::OnToolsAddcol() 
{
	// TODO: Add your command handler code here
	char  intSt[4];
    int colCnt = pGridCtrl->GetColumnCount();
	_itoa(colCnt, intSt, 10);
	CString st = "Column " + CString(intSt);
	pGridCtrl->InsertColumn(st,DT_CENTER, -1);
	//refresh the grid
	pGridCtrl->Invalidate();
}

void CMTXCalcView::OnToolsAddrow() 
{
	// TODO: Add your command handler code here
	char intSt[4];
    int rowCnt = pGridCtrl->GetRowCount();
	_itoa(rowCnt, intSt, 10);
	CString st = "Row " + CString(intSt);
	pGridCtrl->InsertRow(st, -1);	
	//refresh the grid
	pGridCtrl->Invalidate();
}

BOOL CMTXCalcView::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult) 
{
	// TODO: Add your specialized code here and/or call the base class
	NM_GRIDVIEW * nmgv = (NM_GRIDVIEW*)lParam;

	int msg = nmgv->hdr.code;
    int row = nmgv->iRow;
    int col = nmgv->iColumn;

    //CMTXCalcDoc * pDoc = GetDocument();

	switch (msg)
	{
	    case GVN_ENDLABELEDIT: {							       
								   double val;
								   CString st = pGridCtrl->GetItemText(row, col);
								   if (!getValueFromString(st, &val))
									   MessageBox("Entry must be numeric!", "Data Entry Error", MB_OK);
			                       break;
								};
							   
        case GVN_BEGINLABELEDIT: {
									m_lastCell = pGridCtrl->GetFocusCell();
									break;
								 };
        case GVN_SELCHANGED: break;
        case GVN_DELETEITEM: break;
		//case GVN_PASTE_COMPLETE:{
		//					       updateDocFromGrid();
		//					       break;
		//						}	
	    default: break;
	}
	
//	return CView::OnNotify(wParam, lParam, pResult);
	return true;
}


BOOL CMTXCalcView::getValueFromString(CString st, double * val)
{	
	char * stopSt;
	*val = strtod(st, &stopSt);
	CString st1 = *stopSt;
	if (st1 != "")
		return FALSE;
	else
	   return TRUE;
}

void CMTXCalcView::updateDocFromGrid()
{
    CMTXCalcDoc * pDoc = GetDocument();
	int rows = pGridCtrl->GetRowCount();
	int cols = pGridCtrl->GetColumnCount();
	for (int i = 1; i < rows; i++)
	{
		for (int j = 1; j < cols; j++)
		{
			CString stVal = pGridCtrl->GetItemText(i, j);
			double val;
			if (getValueFromString(stVal, &val) != TRUE)
			   val = 0.0;
			if (i < pDoc->m_mtx->getRowCount() && j < pDoc->m_mtx->getColumnCount())
				pDoc->m_mtx->setValueAt(i-1, j-1, val); 
		}
	}

}

void CMTXCalcView::updateGridFromDoc()
{
}
