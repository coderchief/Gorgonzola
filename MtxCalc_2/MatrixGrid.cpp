// MatrixGrid.cpp: implementation of the CMatrixGrid class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "mtxcalc.h"
#include "MatrixGrid.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMatrixGrid::CMatrixGrid()
{
   pDoc = new CMTXCalcDoc;
}

CMatrixGrid::~CMatrixGrid()
{
   delete pDoc;
}

void CMatrixGrid::SetRefreshGrid(bool setGrd, bool setBar)
{
   SetGridRedraw(setGrd, setBar);
}

void CMatrixGrid::OnEditCut()
{
	CGridCtrl::OnEditCut();
}  

void CMatrixGrid::OnEditPaste()
{
	CGridCtrl::OnEditPaste();
}

void CMatrixGrid::OnEditCopy()
{
	CGridCtrl::OnEditCopy();
}


void CMatrixGrid::RefreshMtxGrid(CRect* rect)
{

	    	// Create the Gridctrl object
	    	//pGridCtrl = new CMatrixGrid;
		    //if (!pGridCtrl) return ;
    int gridRows = (pDoc->m_mtx->getRowCount()) + 1;
    int gridCols = (pDoc->m_mtx->getColumnCount()) + 1;

	      	// Create the Gridctrl window
		   // CRect rect;
/*		    GetClientRect(*rect);
		
		    Create(*rect, this, 100);

		    // fill it up with stuff
		    SetEditable(TRUE);
		    EnableDragAndDrop(TRUE);
	//	}
		try {
			SetRowCount(gridRows);
			SetColumnCount(gridCols);
			SetFixedRowCount(1);
			SetFixedColumnCount(1);
		}
		catch (CMemoryException* e)
		{
			e->ReportError();
			e->Delete();
			return ;
		}*/

		// fill rows/cols with text
		for (int row = 0; row < GetRowCount(); row++)
		{
			for (int col = 0; col < GetColumnCount(); col++)
			{ 
				GV_ITEM Item;
				Item.mask = GVIF_TEXT|GVIF_FORMAT;
				Item.row = row;
				Item.col = col;
				if (row < 1) {
					Item.nFormat = DT_LEFT|DT_WORDBREAK;
					Item.strText.Format(_T("Column %d"),col);
				} 
				else if (col < 1) {
					Item.nFormat = DT_RIGHT|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS;
					Item.strText.Format(_T("Row %d"),row);
				} 
				else {
					Item.nFormat = DT_CENTER|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS;
					MTX_TYPE val = pDoc->m_mtx->getValueAt(row-1, col-1);
					Item.strText.Format(_T("%f"),val);
				}
				SetItem(&Item);
			}
		}

		AutoSize();
		SetRowHeight(0, 3*GetRowHeight(0)/2);

}
