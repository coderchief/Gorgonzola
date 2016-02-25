#if !defined(AFX_CALCDLG_H__E8A87941_EF7F_45BC_8916_79A78B4F8B9A__INCLUDED_)
#define AFX_CALCDLG_H__E8A87941_EF7F_45BC_8916_79A78B4F8B9A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CalcDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCalcDlg dialog

class CCalcDlg : public CDialog
{
// Construction
public:
	CCalcDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCalcDlg)
	enum { IDD = IDD_CALC_DLG };
	CTabCtrl	m_tabCtrl;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCalcDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCalcDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CALCDLG_H__E8A87941_EF7F_45BC_8916_79A78B4F8B9A__INCLUDED_)
