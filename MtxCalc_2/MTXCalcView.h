// MTXCalcView.h : interface of the CMTXCalcView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MTXCALCVIEW_H__190B72FC_E496_46D1_98AA_7D10F54C2F26__INCLUDED_)
#define AFX_MTXCALCVIEW_H__190B72FC_E496_46D1_98AA_7D10F54C2F26__INCLUDED_

// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//#include "GridCtrl.h"
#include "MatrixGrid.h"

class CMTXCalcView : public CView
{
protected: // create from serialization only
	CMTXCalcView();
	DECLARE_DYNCREATE(CMTXCalcView)

// Attributes
public:
	CMTXCalcDoc* GetDocument();
    CMatrixGrid * pGridCtrl;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMTXCalcView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	virtual void CalcWindowRect(LPRECT lpClientRect, UINT nAdjustType = adjustBorder);
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	//}}AFX_VIRTUAL

// Implementation
public:
	void updateGridFromDoc();
	void updateDocFromGrid();
	int m_mtxColCount;
	int m_mtxRowCount;
	
	virtual ~CMTXCalcView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMTXCalcView)
	afx_msg void OnToggleReadOnly();
	afx_msg void OnToolsAddcol();
	afx_msg void OnToolsAddrow();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
//	void updateDocFromGrid();
	CCellID m_lastCell;
	BOOL getValueFromString(CString st, double * val);

};

#ifndef _DEBUG  // debug version in MTXCalcView.cpp
inline CMTXCalcDoc* CMTXCalcView::GetDocument()
   { return (CMTXCalcDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MTXCALCVIEW_H__190B72FC_E496_46D1_98AA_7D10F54C2F26__INCLUDED_)
