// MTXCalc.h : main header file for the MTXCALC application
//

#if !defined(AFX_MTXCALC_H__6E13D74A_46C6_4330_82D9_4F2B26C94926__INCLUDED_)
#define AFX_MTXCALC_H__6E13D74A_46C6_4330_82D9_4F2B26C94926__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols
#include "AllPages.h"

/////////////////////////////////////////////////////////////////////////////
// CMTXCalcApp:
// See MTXCalc.cpp for the implementation of this class
//

class CMTXCalcApp : public CWinApp
{
public:
	void CalcDone();
	CMTXCalcApp();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMTXCalcApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CMTXCalcApp)
	afx_msg void OnAppAbout();
	afx_msg void OnToolsCalc();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:

protected:
	CAllPages * m_pDlgCalc;
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MTXCALC_H__6E13D74A_46C6_4330_82D9_4F2B26C94926__INCLUDED_)
