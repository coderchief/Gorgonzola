#if !defined(AFX_ALLPAGES_H__9CCB418F_D1F0_4B8D_B456_6B1035BADC91__INCLUDED_)
#define AFX_ALLPAGES_H__9CCB418F_D1F0_4B8D_B456_6B1035BADC91__INCLUDED_

#include "CalcResults.h"	// Added by ClassView
#include "CalcUnary.h"	// Added by ClassView
#include "CalcBinary.h"	// Added by ClassView
#include "xpMatrix.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AllPAges.h : header file
//
#include "MainFrm.h"


/////////////////////////////////////////////////////////////////////////////
// CAllPages

class CAllPages : public CPropertySheet
{
	DECLARE_DYNAMIC(CAllPages)

// Construction
public:
	CAllPages(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CAllPages(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
    CList<CMtxRef, CMtxRef> m_mtxList;
// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAllPages)
	public:
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL

// Implementation
public:
	BOOL getMtxFromString(xpMatrix * mtx, CString st);
	void updateMtxList();
	CMatrixGrid * m_pMtx;
	CCalcBinary m_calcBinary;
	CCalcUnary m_calcUnary;
	CCalcResults m_calcResults;
	virtual ~CAllPages();

	// Generated message map functions
protected:
	int m_SelectedPage;
	//{{AFX_MSG(CAllPages)
	afx_msg void OnClose();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	CMainFrame * m_pParent;
private:
	void AddControlPages();
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ALLPAGES_H__9CCB418F_D1F0_4B8D_B456_6B1035BADC91__INCLUDED_)
