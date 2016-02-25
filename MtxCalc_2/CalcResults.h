#if !defined(AFX_CALCRESULTS1_H__5940E760_0667_47E9_AEA5_A7C496FABA0E__INCLUDED_)
#define AFX_CALCRESULTS1_H__5940E760_0667_47E9_AEA5_A7C496FABA0E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CalcResults1.h : header file
//

//#include "GridCtrl.h"
#include "MatrixGrid.h"
/////////////////////////////////////////////////////////////////////////////
// CCalcResults dialog

class CCalcResults : public CPropertyPage
{
	DECLARE_DYNCREATE(CCalcResults)

// Construction
public:
	CMatrixGrid * pGridCtrl;
	CCalcResults();
	~CCalcResults();

// Dialog Data
	//{{AFX_DATA(CCalcResults)
	enum { IDD = IDD_CALC_RESULTS };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CCalcResults)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CCalcResults)
	virtual BOOL OnInitDialog();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CALCRESULTS1_H__5940E760_0667_47E9_AEA5_A7C496FABA0E__INCLUDED_)
