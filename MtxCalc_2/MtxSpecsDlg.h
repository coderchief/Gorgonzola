#if !defined(AFX_MTXSPECSDLG_H__837F2041_1584_4DE8_A0BD_9982EE59075E__INCLUDED_)
#define AFX_MTXSPECSDLG_H__837F2041_1584_4DE8_A0BD_9982EE59075E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MtxSpecsDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMtxSpecsDlg dialog

class CMtxSpecsDlg : public CDialog
{
// Construction
public:
	CMtxSpecsDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMtxSpecsDlg)
	enum { IDD = IDD_MTX_SPECS };
	int		m_Columns;
	int		m_Rows;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMtxSpecsDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMtxSpecsDlg)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MTXSPECSDLG_H__837F2041_1584_4DE8_A0BD_9982EE59075E__INCLUDED_)
