// MatrixGrid.h: interface for the CMatrixGrid class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MATRIXGRID_H__9C82173C_638D_424B_9FD5_31F41827EE05__INCLUDED_)
#define AFX_MATRIXGRID_H__9C82173C_638D_424B_9FD5_31F41827EE05__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GridCtrl.h"
#include "MTXCalcDoc.h"

class CMatrixGrid : public CGridCtrl  
{
public:
	void RefreshMtxGrid(CRect* rect);
	CMTXCalcDoc* pDoc;
	virtual void OnEditCopy();
	virtual void OnEditPaste();
	virtual void OnEditCut();
	void SetRefreshGrid(bool setGrd, bool setBar);
	CMatrixGrid();
	virtual ~CMatrixGrid();

};

#endif // !defined(AFX_MATRIXGRID_H__9C82173C_638D_424B_9FD5_31F41827EE05__INCLUDED_)
