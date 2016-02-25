// xpException.cpp: implementation of the xpException class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "mtxcalc.h"
#include "xpException.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNAMIC(xpException,CException);

xpException::xpException(CString errMess) :
   m_errMessage(errMess)
{

}

xpException::xpException()
{
   m_errMessage = "";
}


xpException::~xpException()
{

}

void xpException::setErrorMessage(CString errMess)
{
	m_errMessage = errMess;
}

void xpException::getErrorMessage(CString& errMess)
{
	errMess = m_errMessage; 
}
