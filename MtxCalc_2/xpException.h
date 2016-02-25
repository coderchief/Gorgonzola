// xpException.h: interface for the xpException class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_XPEXCEPTION_H__39948DAD_CA61_4EFF_95C8_4F1AF31D0D0C__INCLUDED_)
#define AFX_XPEXCEPTION_H__39948DAD_CA61_4EFF_95C8_4F1AF31D0D0C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "stdafx.h"



class xpException : public CException  
{
   DECLARE_DYNAMIC(xpException);

public:
	xpException(CString errMess);
	xpException();
	virtual ~xpException();

	void setErrorMessage(CString errMess);
	void getErrorMessage(CString& errMess);
private:
	CString m_errMessage;
};

#endif // !defined(AFX_XPEXCEPTION_H__39948DAD_CA61_4EFF_95C8_4F1AF31D0D0C__INCLUDED_)
