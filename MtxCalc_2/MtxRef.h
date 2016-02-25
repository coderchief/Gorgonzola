// MtxRef2.h: interface for the CMtxRef class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MTXREF2_H__0C48DEDC_BE97_4E22_B971_7A6F96CDCD99__INCLUDED_)
#define AFX_MTXREF2_H__0C48DEDC_BE97_4E22_B971_7A6F96CDCD99__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MtxRef.h"
#include "MtxCalcDoc.h"
#include "MtxCalcView.h"

class CMtxRef
{
public:
	CMTXCalcDoc * m_mtxDoc;
	CMTXCalcView * m_mtxView;
	CString m_Title;
	CMtxRef();
	virtual ~CMtxRef();
};


#endif // !defined(AFX_MTXREF2_H__0C48DEDC_BE97_4E22_B971_7A6F96CDCD99__INCLUDED_)
