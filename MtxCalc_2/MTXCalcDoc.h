// MTXCalcDoc.h : interface of the CMTXCalcDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MTXCALCDOC_H__6C8503B3_8155_4B67_88AE_DCA921A905DD__INCLUDED_)
#define AFX_MTXCALCDOC_H__6C8503B3_8155_4B67_88AE_DCA921A905DD__INCLUDED_

// Added by ClassView
#include <map>  
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "afxtempl.h"
#include "xpMatrix.h"
#include "GridCtrl.h"


class CMTXCalcDoc : public CDocument
{
protected: // create from serialization only
	
	DECLARE_DYNCREATE(CMTXCalcDoc)

// Attributes
public:
	CMTXCalcDoc();
	xpMatrix * m_mtx;
// Operations
public:
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMTXCalcDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:

	virtual ~CMTXCalcDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMTXCalcDoc)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void readMtxFromGrid();
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MTXCALCDOC_H__6C8503B3_8155_4B67_88AE_DCA921A905DD__INCLUDED_)
