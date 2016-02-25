#if !defined(AFX_CALCUNARY1_H__1B66E783_BA2E_4BED_9076_094407CB54EE__INCLUDED_)
#define AFX_CALCUNARY1_H__1B66E783_BA2E_4BED_9076_094407CB54EE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CalcUnary1.h : header file
//

#include "MtxRef.h"
#include "xpMatrix.h"	// Added by ClassView
/////////////////////////////////////////////////////////////////////////////
// CCalcUnary dialog

class CCalcUnary : public CPropertyPage
{
	DECLARE_DYNCREATE(CCalcUnary)

// Construction
public:
	xpMatrix m_mtxResult;
	CList<CMtxRef, CMtxRef> m_mtxList;
	CCalcUnary();
	~CCalcUnary();

// Dialog Data
	//{{AFX_DATA(CCalcUnary)
	enum { IDD = IDD_CALC_UNARY };
	CString	m_selValList1;
	CString	m_det;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CCalcUnary)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CCalcUnary)
	virtual BOOL OnInitDialog();
	afx_msg void OnInverse();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnTranspose();
	afx_msg void OnToolsInitalise();
	afx_msg void OnDeterminant();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	bool getMatrix(xpMatrix& xpMtx);
	void updateListBox();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CALCUNARY1_H__1B66E783_BA2E_4BED_9076_094407CB54EE__INCLUDED_)
