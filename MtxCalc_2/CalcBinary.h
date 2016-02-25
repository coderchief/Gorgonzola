#if !defined(AFX_CALCBINARY1_H__10B8CFE5_65F2_48AA_9B75_ADBF7244A18E__INCLUDED_)
#define AFX_CALCBINARY1_H__10B8CFE5_65F2_48AA_9B75_ADBF7244A18E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CalcBinary1.h : header file
//
#include "GridCtrl.h"
#include "MtxRef.h"
#include "xpMatrix.h"
#include "AllPages.h"

/////////////////////////////////////////////////////////////////////////////
// CCalcBinary dialog

class CCalcBinary : public CPropertyPage
{
	DECLARE_DYNCREATE(CCalcBinary)

// Construction
public:
	xpMatrix m_mtxResult;
	
	CCalcBinary();
	~CCalcBinary();

// Dialog Data
	//{{AFX_DATA(CCalcBinary)
	enum { IDD = IDD_CALC_BINARY };
	CString	m_selValList1;
	CString	m_selValList2;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CCalcBinary)
	public:
	virtual int DoModal();
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CCalcBinary)
	virtual BOOL OnInitDialog();
	afx_msg void OnMultiply();
	afx_msg void OnClose();
	afx_msg void OnCancelMode();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnAdd();
	afx_msg void OnSubtract();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	bool getMatrices(xpMatrix&  mtx_1, xpMatrix&  mtx_2);
	void updateListBox();
//	CAllPages * getParent();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CALCBINARY1_H__10B8CFE5_65F2_48AA_9B75_ADBF7244A18E__INCLUDED_)
