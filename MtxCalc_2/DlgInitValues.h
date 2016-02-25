#if !defined(AFX_DLGINITVALUES_H__6E825408_23E8_493C_8871_7525BDD75F09__INCLUDED_)
#define AFX_DLGINITVALUES_H__6E825408_23E8_493C_8871_7525BDD75F09__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgInitValues.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgInitValues dialog

class CDlgInitValues : public CDialog
{
// Construction
public:
	
	UINT GetCheck();
	void SetCheck(UINT idBtn);
	CDlgInitValues(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgInitValues)
	enum { IDD = IDD_DIALOG_INITIAL };
	CButton	m_btnValue;
	CButton	m_btnUnity;
	CButton	m_btnRandom;
	double	m_initValue;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgInitValues)
	public:
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgInitValues)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnCheckRandom();
	afx_msg void OnCheckUnity();
	afx_msg void OnCheckValue();
	//}}AFX_MSG
private:
	UINT m_checkedItem;
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGINITVALUES_H__6E825408_23E8_493C_8871_7525BDD75F09__INCLUDED_)
