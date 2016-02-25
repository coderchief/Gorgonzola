// MTXCalcDoc.cpp : implementation of the CMTXCalcDoc class
/******************************************************************************
 Filename		:MTXCalcDoc.cpp
 Author			:Tomas Schier
 Description	:The implementation file for the CDocument derived CMTXCalcDoc class.
				 This is where the class xpMatrix is used.

 Date		Notes
 03-Feb-04	First draft

******************************************************************************/

#include "stdafx.h"
#include "xpMatrix.h"

#include "MTXCalc.h"

#include "MTXCalcDoc.h"
#include "MTXCalcView.h"
#include "MTXSpecsDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMTXCalcDoc

IMPLEMENT_DYNCREATE(CMTXCalcDoc, CDocument)

BEGIN_MESSAGE_MAP(CMTXCalcDoc, CDocument)
	//{{AFX_MSG_MAP(CMTXCalcDoc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMTXCalcDoc construction/destruction

CMTXCalcDoc::CMTXCalcDoc()
{
	// TODO: add one-time construction code here
//	pGridCtrl = NULL;
	m_mtx = NULL;

}

CMTXCalcDoc::~CMTXCalcDoc()
{
//	if (pGridCtrl)
//		delete pGridCtrl;
	if (m_mtx)
		delete m_mtx;
}

BOOL CMTXCalcDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)
	CMtxSpecsDlg mtxSpecsDlg;
	if (mtxSpecsDlg.DoModal() != IDOK)
		return FALSE;
	
	m_mtx = new xpMatrix(mtxSpecsDlg.m_Rows, mtxSpecsDlg.m_Columns);
	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CMTXCalcDoc serialization

void CMTXCalcDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		readMtxFromGrid();
		ar << m_mtx;
	}
	else
	{
	   ar >> m_mtx;
	}
}

/////////////////////////////////////////////////////////////////////////////
// CMTXCalcDoc diagnostics

#ifdef _DEBUG
void CMTXCalcDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMTXCalcDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMTXCalcDoc commands



void CMTXCalcDoc::readMtxFromGrid()
{
	CMTXCalcView * pView;
	POSITION pos = GetFirstViewPosition();
	while (pos != NULL)
	{
		pView = (CMTXCalcView*)GetNextView(pos);
		CGridCtrl * pGridCtrl = pView->pGridCtrl;
		int cc = pGridCtrl->GetColumnCount();
		int rc = pGridCtrl->GetRowCount();
		m_mtx = new xpMatrix(rc-1, cc-1);

		for (int i = 0; i < rc-1; i++)
		{
			for (int j = 0; j < cc-1; j++)
			{
				CString st = pGridCtrl->GetItemText(i+1, j+1);
				char * stopSt;
				MTX_TYPE val = strtod(st, &stopSt);
				m_mtx->setValueAt(i, j, val);
			}
		}
	}

}

