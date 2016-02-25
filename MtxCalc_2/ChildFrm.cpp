// ChildFrm.cpp : implementation of the CChildFrame class
//

#include "stdafx.h"
#include "MTXCalc.h"

#include "ChildFrm.h"
#include "DlgInitValues.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChildFrame

IMPLEMENT_DYNCREATE(CChildFrame, CMDIChildWnd)

BEGIN_MESSAGE_MAP(CChildFrame, CMDIChildWnd)
	//{{AFX_MSG_MAP(CChildFrame)
	ON_COMMAND(ID_TOOLS_INITALISE, OnToolsInitalise)
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_COMMAND(ID_EDIT_CUT, OnEditCut)
	ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChildFrame construction/destruction

CChildFrame::CChildFrame()
{
	// TODO: add member initialization code here
	
}

CChildFrame::~CChildFrame()
{
}

BOOL CChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	if( !CMDIChildWnd::PreCreateWindow(cs) )
		return FALSE;

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CChildFrame diagnostics

#ifdef _DEBUG
void CChildFrame::AssertValid() const
{
	CMDIChildWnd::AssertValid();
}

void CChildFrame::Dump(CDumpContext& dc) const
{
	CMDIChildWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CChildFrame message handlers

void CChildFrame::OnToolsInitalise() 
{
	CDlgInitValues initDlg;
	if (initDlg.DoModal() != IDOK)
		return;
	CMTXCalcView* pView = (CMTXCalcView*)GetActiveView();
	CMTXCalcDoc * pDoc = (CMTXCalcDoc*)pView->GetDocument();
	UINT aType = initDlg.GetCheck();
	switch (aType) {

	case IDC_CHECK_VALUE: pDoc->m_mtx->init((MTX_TYPE)initDlg.m_initValue);
		break;
	case IDC_CHECK_RANDOM: pDoc->m_mtx->initRandom((int)initDlg.m_initValue);
		break;
	case IDC_CHECK_UNITY: pDoc->m_mtx->initUnity(initDlg.m_initValue);
		break;
	default: pDoc->m_mtx->init((int)initDlg.m_initValue);
	}
	updateGridFromDoc();
	pView->pGridCtrl->Refresh();	
}

void CChildFrame::updateGridFromDoc()
{
	CMTXCalcView* pView = (CMTXCalcView*)GetActiveView();    
	CMTXCalcDoc * pDoc = (CMTXCalcDoc*)pView->GetDocument();
	int rows = pView->pGridCtrl->GetRowCount();
	int cols = pView->pGridCtrl->GetColumnCount();
	int currRow, currCol;
	currRow = 1;
	currCol = 1;
	//ensure the number of rows is equal, resize if required
	//ensure the number of columns is equal, resize if required
	// use iterator to step througgh document and fill grid
	MTX_TYPE aVal;

	for (iter_r itr = pDoc->m_mtx->m_xpMtx.begin(); itr != pDoc->m_mtx->m_xpMtx.end(); itr++)
	{
		for (iter_c itc = (*itr).begin(); itc != (*itr).end(); itc++)
		{
		//	aVal = *itc;

			char  buffer[50];
			char * buf;
			//int sign, decimal;
		//	buf = _fcvt((double)*itc,10,&decimal,&sign);
			//if (
			int k = sizeof(buf);
			gcvt((double)*itc,10,buffer);
			pView->pGridCtrl->SetItemText(currRow, currCol, buffer);
			//pView->pGridCtrl->SetItemText(currRow, currCol, buf);
			currCol++;
		}
		currCol = 1;
		currRow++;
	}
	

}

void CChildFrame::OnEditCopy() 
{
	// TODO: Add your command handler code here
	CMTXCalcView* pView = (CMTXCalcView*)GetActiveView();
    ((CMainFrame*)AfxGetApp()->m_pMainWnd)->pDoc = pView->GetDocument();
	pView->pGridCtrl->OnEditCopy();	
}

void CChildFrame::OnEditCut() 
{
	// TODO: Add your command handler code here
	CMTXCalcView* pView = (CMTXCalcView*)GetActiveView();    
	pView->pGridCtrl->OnEditCut();   
}

void CChildFrame::OnEditPaste() 
{
	// TODO: Add your command handler code here
	CMTXCalcView* pView = (CMTXCalcView*)GetActiveView();    
	pView->pGridCtrl->OnEditPaste();
	pView->updateDocFromGrid();
}
