/**********************************************************************************
        Class:  xpMatrix
        Author: Tomas Schier
        Description: This class can be used for general matrix algebra, such as
                                 additions, multiplications, inverse matrix calculation, transpose
                                 adjunct, determinants and more.
                                 The operators * , +,  and - are overloaded to simplify usage.
                                 
                                 This file will compile with Visual C++ (v6). The original version
                                 designed for standard C++. However, to accommodate the Doc/View
                                 architecture of MFC the class needed to be derived from COject.
                                 Tags could be introduced to account for compiler specific handling.

   15-01-2004 First draft.
                          Calculation of adjunct and determinant still need to be implemented.


***********************************************************************************/
#pragma warning(disable:4786)
#include <iostream>
#include <iterator>
#include <iomanip>
#include <math.h>
#include <fstream>
#include "xpMatrix.h"
#include "stdafx.h"

IMPLEMENT_SERIAL(xpMatrix, CObject, 1)

xpMatrix::xpMatrix()
{
   m_digits = 0;
   m_RowCount = 0;
   m_ColumnCount = 0;
}


// Copy constructor is required as the assignmnet operator "=" is overloaded.
// This in turn was required because this class is derived from CObject
xpMatrix::xpMatrix(const xpMatrix &xp)
{
    m_digits = xp.m_digits;
    m_RowCount = xp.m_RowCount;
    m_ColumnCount = xp.m_ColumnCount;
    m_xpMtx = xp.m_xpMtx;
}

//constructor for a quadratic matrix
xpMatrix::xpMatrix(const int size)
{
    m_digits = 0;
    m_RowCount = size;
    m_ColumnCount = size;

    for (int i=0; i <size; i++)
    {
        //build a row
        xpRow tmp(size, 0);
        //now add the row
        m_xpMtx.push_back(tmp);
    }
}


//constructor for a non-quadratic matrix, with initilisation
xpMatrix::xpMatrix(const int row, const int col, const MTX_TYPE initVal)
{
    m_digits = 0;
    m_RowCount = row;
    m_ColumnCount = col;

    for (int i=0; i <row; i++)
    {
        //build a row
        xpRow tmp(col, initVal);;
        //now add the row
        m_xpMtx.push_back(tmp);
    }
}

//constructor for a non-quadratic matrix, no initilisation
xpMatrix::xpMatrix(const int row, const int col)
{
    m_digits = 0;
    m_RowCount = row;
    m_ColumnCount = col;

    for (int i=0; i <row; i++)
    {
        //build a column
        xpRow tmp(col, 0);
        //now add the column
        m_xpMtx.push_back(tmp);
    }
}

//set all values in the matrix to initVal
void xpMatrix::init(MTX_TYPE initVal)
{
    for (iter_r it1 = m_xpMtx.begin(); it1 != m_xpMtx.end(); it1++)
    {
        for (iter_c it2 = (*it1).begin(); it2 != (*it1).end(); it2++)
        {
            *it2 = initVal;
        }
    }
}

//set all values in the matrix to a  random value
void xpMatrix::initRandom(int seed)
{
	srand(seed);
	for (iter_r it_r = m_xpMtx.begin(); it_r != m_xpMtx.end(); it_r++)
	{
		for (iter_c it_c = (*it_r).begin(); it_c != (*it_r).end(); it_c++)
		{
			
		    int tt = RAND_MAX*RAND_MAX*2;
			*it_c = (MTX_TYPE)rand()/tt;
		}		
	}
}

MTX_TYPE xpMatrix::getValueAt(unsigned int r, unsigned int c) const
{
	if ((r >= m_xpMtx.size()) || (c >= m_xpMtx.front().size()))
	{
		m_pMtxException = new xpException("Error in: getValueAt()!");
		throw(m_pMtxException);
	}
    return m_xpMtx.at(r).at(c);
}


void  xpMatrix::setValueAt(unsigned int r, unsigned int c, MTX_TYPE val)
{
        if ((r >= m_xpMtx.size()) || (c >= m_xpMtx[0].size()))
		{
			m_pMtxException = new xpException("Error in: setValueAt()!");
			throw(m_pMtxException);
		}
        m_xpMtx.at(r).at(c) = val;
}


const int xpMatrix::getRowCount()
{
        return m_xpMtx.size();
}

const int xpMatrix::getColumnCount()
{
    if (getRowCount() > 0)
        return m_xpMtx.at(0).size();
    else
        return 0;
}

void  xpMatrix::getMtxSize( unsigned int * r, unsigned int * c) const
{
        *r = m_xpMtx.size();
        *c = m_xpMtx.at(0).size();
}

MTX_TYPE xpMatrix::getSmallestValueInRow(int r)
{
        xpRow  tmp;
        MTX_TYPE ret;
    iter_c it=tmp.begin();
        ret = (*it);
        do
        {
                if ((*it) < ret)
                   ret = (*it);
                it++;
        }
        while (it != tmp.end());
        return ret;
}


MTX_TYPE xpMatrix::getLargestValueInRow(int r)
{
        xpRow  tmp;
        MTX_TYPE ret;
    iter_c it=tmp.begin();
        ret = (*it);
        do
        {
                if ((*it) > ret)
                   ret = (*it);
                it++;
        }
        while (it != tmp.end());
        return ret;

}

MTX_TYPE xpMatrix::getSmallestValueInColumn(int c)
{
        xpColumn tmp = getColumn(c);
        iter_c it = tmp.begin();
        MTX_TYPE ret = (*it);
        do
        {
            if ((*it) < ret)
               ret = (*it);
            it++;
        }
        while (it != tmp.end());
        return ret;
}

MTX_TYPE xpMatrix::getLargestValueInColumn(int c)
{
        xpColumn tmp = getColumn(c);
        iter_c it = tmp.begin();
        MTX_TYPE ret = (*it);
        do
        {
            if ((*it) > ret)
               ret = (*it);
            it++;
        }
        while (it != tmp.end());
        return ret;
}

/****************************************************************************
      This will bring the matrix into a format used to calculate the inverse
      The format will be changed so that the member m_xpMtx consists of a vector
      of rows as opposed to a vector of columns.
          The makes the inversion algorithm much more efficient.
****************************************************************************/

xpMatrix xpMatrix::buildExpandedMatrix()
{
        //ensure the matrix is quadratic
        if (m_xpMtx.size() != m_xpMtx.at(0).size())
		{
			m_pMtxException = new xpException("Can't build expanded matrix!");
			throw(m_pMtxException);
		}

        xpMatrix expandedMtx = xpMatrix(*this);

        int cnt = 0;
        int rowCount = expandedMtx.getRowCount();
        iter_r it;
        for (it = expandedMtx.m_xpMtx.begin(); it != expandedMtx.m_xpMtx.end(); it++)
        {
                for (int k = 0; k < rowCount; k++)
                {
                        if (k==cnt)
                           (*it).push_back(1);
                    else
                           (*it).push_back(0);
                }
                cnt++;
        }
        int rr = expandedMtx.getColumnCount();
        return expandedMtx;
}

xpMatrix xpMatrix::readInverseFromExpanded()
{
        int col = getColumnCount();
        div_t halfWayPoint;
        xpMatrix invMtx;

        // the iterator
        iter_r it;
        iter_c it_c;

        xpColumn aCol;
    halfWayPoint = div(col, 2);
    if (halfWayPoint.rem != 0)
	{
		m_pMtxException = new xpException("Internal calculation error!");
		throw(m_pMtxException);
	}
    int startPoint = halfWayPoint.quot;
    xpMatrix ret;
        for (it = m_xpMtx.begin(); it < m_xpMtx.end(); it++)
        {
        //      it_c = (*it).begin() + startPoint;
                xpRow aRow;
                for (it_c = (*it).begin() + startPoint; it_c != (*it).end(); it_c++)
                        aRow.push_back(*it_c);
                ret.m_xpMtx.push_back(aRow);
        }
        return ret;
}


/*************Calculate the inverse of the matrix******************************
* This is an implementation of the Gauss elimination algoritm. This involves the
* following steps.
* 1) Expand the matrix to
*
*       a       b       c       d       |       1       0       0       0
*       e       f       g       h       |       0       1       0       0
*       i       j       k       l       |       0       0       1       0
*       m       n       o       p       |       0       0       0       1
*
*               left                            right
*
*  2) Row by row the left side is to be changed to the unity matrix, which will
*         tranform the right side, which is inititally the unity matrix (as above),
*     to read the inverse matrix.
*
/******************************************************************************/

xpMatrix xpMatrix::getInverse()
   {
	unsigned int xp_r = 0;
	unsigned int xp_c = 0;

	iter_r it;
	iter_r itTmpRow;
	iter_r it_1;
	xpMatrix invMtx;

    getMtxSize(&xp_r, &xp_c);
    if (xp_r != xp_c)
	{
		m_pMtxException = new xpException("Only quadratic matrices can be inverted!");
		throw(m_pMtxException);
	}

    invMtx = this->buildExpandedMatrix();
	int col = invMtx.getColumnCount();
	/* after the expanded matrix has been build the rows
	   need to be treated as columns */
	int dg = 0;

/*************************************************************************** 
* The first step will change the expaned matrix to 
*
*	1	b	c	d	|	1	0	0	0
*	0	1	g	h	|	a	1	0	0
*	0	0	1	l	|	p	y	1	0
*	0	0	0	1	| 	k	u	v	1
*
*****************************************************************************/
        for (it = invMtx.m_xpMtx.begin(); it != invMtx.m_xpMtx.end(); it++)
		{
			/* Divide all elements by the value of the diagonal */
			MTX_TYPE diagonal = (*it).at(dg);
			if (diagonal == 0)
			{
				m_pMtxException = new xpException("No inverse exists!");
				throw(m_pMtxException);
			}
			/* store the current row here */
			itTmpRow = it;
			
			double tmp;
			for (iter_c it_c = (*it).begin(); it_c != (*it).end(); it_c++)
			{
				tmp = (*it_c) / diagonal;
				(*it_c) = tmp;

			}
		   /* For all remaining rows, ie rows below the current one */
	       /* get  the multiplier, which is used to modify all other*/
		   /* values in this row                                    */
		   for (it_1 = it + 1; it_1 != invMtx.m_xpMtx.end(); it_1++)
		   {			   
			   if ((*it_1).at(dg) == 0)
			   {
				   continue;
			   }
			   double ti,ty,tu, newVal;
               double multiplier = 1/(*it_1).at(dg);
			   for (int i = dg; i < col; i++)
			   {
				   ti = (*it).at(i);
				   ty = (*it_1).at(i);
				   tu = (*itTmpRow).at(i);
				   
				   newVal = tu - ty * multiplier;
				   (*it_1).at(i) = newVal;				  
			   }
		   }
		   dg++;
		}
	
    div_t halfWayPoint = div(col, 2);
	if (halfWayPoint.rem != 0)
	{
		m_pMtxException = new xpException("Matrix Inversion: Internal calculation error!");
		throw(m_pMtxException);
	}
    int startPoint = halfWayPoint.quot;
	
	// need to reset the starting point 

	dg = startPoint - 1;
/*************************************************************************** 
* At this point the matrix will be  in the format
*
*	1	b	c	d	|	1	0	0	0
*	0	1	g	h	|	a	1	0	0
*	0	0	1	l	|	p	y	1	0
*	0	0	0	1	| 	k	u	v	1
*
*****************************************************************************/

	for (rev_iter_r it_2 = invMtx.m_xpMtx.rbegin(); it_2 != invMtx.m_xpMtx.rend(); it_2++)
	{
		
		xpColumn itTmpRow = *it_2;
		

	   /* For all remaining rows, ie rows below the current one */
	   /* get  the multiplier, which is used to modify all other*/
	   /* values in this row                                    */
	   for (rev_iter_r it_3 = it_2 + 1; it_3 != invMtx.m_xpMtx.rend(); it_3++)
	   {			   
		   if ((*it_3).at(dg) == 0)
		   {
			   continue;
		   }
           double multiplier = 1/(*it_3).at(dg) * (-1);
		   double ti,ty,tu,newVal;
		   for (int i = 0; i < col; i++)
		   {
			   ti = (*it_2).at(i);
			   ty = (*it_3).at(i);
			   tu = itTmpRow.at(i);
			   
			   newVal = ty * multiplier + tu;
			   (*it_3).at(i) = newVal;				  
		   }
           MTX_TYPE diagonal = (*it_3).at(dg-1);
		   double tmp;
		   for (iter_c it_c = (*it_3).begin(); it_c != (*it_3).end(); it_c++)
		   {
		      tmp = (*it_c) / diagonal;
		      (*it_c) = tmp;
		   }
	   }
	   dg--;
	}
	return invMtx.readInverseFromExpanded();
}


xpMatrix xpMatrix::getTranspose()
{
    int row = getRowCount();
	int col = getColumnCount();
	int source_row = 0;
	int source_col = 0;
	int target_row = 0;
	int target_col = 0;
	xpMatrix ret(col,row, 0);
    for (iter_r it = m_xpMtx.begin(); it != m_xpMtx.end(); it++)
    {      
	   source_col = 0;
	   target_col = source_row;
	   for (iter_c itc = (*it).begin(); itc != (*it).end(); itc++)
	   {
           target_row = source_col;
		   MTX_TYPE val = getValueAt(source_row, source_col);
		   ret.setValueAt(target_row, target_col, val);
		   source_col++;	
	   }
	   source_row++;
    }
    return ret;
}


xpRow xpMatrix::getColumn(int row)
{
    iter_r it;
    xpRow ret;
	if (row > getRowCount())
		return ret;

    for (it = m_xpMtx.begin(); it != m_xpMtx.end(); it++)
    {
        ret.push_back((*it).at(row));
    }
    return ret;
}


xpColumn xpMatrix::getRow(int col)
{
	xpColumn ret;
	if (col > getColumnCount())
        return ret;
    return m_xpMtx.at(col);
}




//overloaded operators
const xpMatrix operator*(const xpMatrix& left, const xpMatrix& right)
{
    unsigned int xp1_r = 0;
    unsigned int xp1_c = 0;
    unsigned int xp2_r = 0;
    unsigned int xp2_c = 0;


    left.getMtxSize(&xp1_r, &xp1_c);
    right.getMtxSize(&xp2_r,& xp2_c);
    if (xp1_c != xp2_r)
	{
		xpException * ex = new xpException("Matrix size mismatch during multiplication!");
		throw(ex);
	}
    else
    {
        xpMatrix ret = xpMatrix(xp1_r, xp2_c);

        for (int i=0; i <xp2_c; i++)
        {
            for (int j=0; j < xp1_r; j++)
            {
                MTX_TYPE theVal = 0;
                for (int k=0; k < xp2_r; k++)
                {
                    theVal = theVal + left.getValueAt(j, k) * right.getValueAt(k, i);
                }
                ret.setValueAt(j, i, theVal);

            }
        }
        return ret;
    }
 
}

const xpMatrix operator+(const xpMatrix& left, const xpMatrix& right)
{
    unsigned int xp1_r = 0;
    unsigned int xp1_c = 0;
    unsigned int xp2_r = 0;
    unsigned int xp2_c = 0;


    left.getMtxSize(&xp1_r, &xp1_c);
    right.getMtxSize(&xp2_r,& xp2_c);
    if (xp1_c != xp2_c || xp1_r != xp2_r)
	{
		xpException * ex = new xpException("Matrices must be the same size!");
		throw(ex);
	}
    else
    {
        xpMatrix ret = xpMatrix(xp1_r, xp1_c);

        for (int i=0; i< xp1_r; i++)
        {
            for (int j=0; j<xp1_c; j++)
            {
                MTX_TYPE theVal = left.getValueAt(i, j) + right.getValueAt(i, j);
                ret.setValueAt(i, j, theVal);
            }
        }
        return ret;
    }
}


const xpMatrix operator-(const xpMatrix& left, const xpMatrix& right)
{
    unsigned int xp1_r = 0;
    unsigned int xp1_c = 0;
    unsigned int xp2_r = 0;
    unsigned int xp2_c = 0;

    left.getMtxSize(&xp1_r, &xp1_c);
    right.getMtxSize(&xp2_r,& xp2_c);
    if (xp1_c != xp2_c || xp1_r != xp2_r)
	{
		xpException * ex = new xpException("Matrices must be the same size!");
		throw(ex);
	}
    else
    {
        xpMatrix ret = xpMatrix(xp1_r, xp1_c);
        for (int i=0; i< xp1_r; i++)
        {
            for (int j=0; j<xp1_c; j++)
            {
				MTX_TYPE theVal = left.getValueAt(i, j) - right.getValueAt(i, j);
                ret.setValueAt(i, j, theVal);
            }
        }
        return ret;
    }
}


void xpMatrix::printMtx()
{
   unsigned int row = 0;
   unsigned int col = 0;
   for (iter_r it1 = m_xpMtx.begin(); it1 != m_xpMtx.end(); it1++)
   {
       for (iter_c it2 = (*it1).begin(); it2 != (*it1).end(); it2++)
       {
          MTX_TYPE val = (*it2);
          roundTo(&val);
          std::cout << val << "\t";
       }
       std::cout << "\n";
   }
}


xpRow xpMatrix::readRow(int row)
{
    sizeTest(this, row, 0);
    return m_xpMtx.at(row);
}


xpColumn xpMatrix::readColumn(int col)
{
    sizeTest(this, 0, col);
    xpColumn ret;
    for (iter_r it=m_xpMtx.begin(); it != m_xpMtx.end(); it++)
    {
        ret.push_back((*it).at(col));
    }
    return ret;
}

void xpMatrix::roundTo(MTX_TYPE * val)
{
    /* This will ensure that values that should read 0 but do not due
         * to rounding errors. The testValue will determine the minimum that
         * must be exceeded for any value to be considered >0.
         * This functions acts like a gate for values in the matrix            */
    if (m_digits == 0)
        return;
    double testValue = 1/pow(static_cast<double>(10), m_digits);
    double tt = abs((*val));
    double ty = *val;
    if (ty < 0)
        ty = ty * (-1);
    if (ty < testValue)
        (*val) = 0;
}

void xpMatrix::setNumberOfDecimals(unsigned int n)
{
    m_digits = n;
}

void xpMatrix::Serialize(CArchive& ar)
{
    if (ar.IsStoring())
    {
        int rc = getRowCount();
        int cc = getColumnCount();
        ar << rc << cc;
        for (iter_r itr = m_xpMtx.begin(); itr != m_xpMtx.end(); itr++)
        {
            for (iter_c itc = (*itr).begin(); itc != (*itr).end(); itc++)
            {
                ar << *itc;
            }
        }
    }
    else
    {
        int rc ;
        int cc ;
        ar >> rc;
        ar >> cc;
        setSize(rc, cc);
        for (int i = 0; i < rc; i++)
        {
            for (int j =0; j < cc; j++)
            {
                MTX_TYPE val;
                ar >> val;
                setValueAt(i, j, val);
            }
        }
    }
}

void xpMatrix::addColumn()
{
   for (iter_r it = m_xpMtx.begin(); it != m_xpMtx.end(); it++)
   {
       (*it).push_back(0);
   }
   m_ColumnCount++;
}

void xpMatrix::addColumn(MTX_TYPE val)
{
   for (iter_r it = m_xpMtx.begin(); it != m_xpMtx.end(); it++)
   {
       (*it).push_back(val);
   }
   m_ColumnCount++;
}


void xpMatrix::addColumn(xpColumn aCol)
{
    /* Ensure that the number of rows equals the number of elements
         * in the column. This implies that at least one column exists    */
    sizeTest(this, aCol.size(), 1);
    iter_r it;
    int cnt = 0;
    MTX_TYPE val;
    for (it = m_xpMtx.begin(); it != m_xpMtx.end(); it++)
    {
       val = aCol.at(cnt);
       (*it).push_back(val);
       cnt++;
    }
    m_ColumnCount++;
}


void xpMatrix::addRow()
{
    xpRow row;
    for (int i=0; i < getColumnCount(); i++)
        row.push_back(0);
    m_xpMtx.push_back(row);
    m_RowCount++;
}

void xpMatrix::addRow(MTX_TYPE val)
{
    xpRow row;
    for (int i=0; i < getColumnCount(); i++)
        row.push_back(val);
    m_xpMtx.push_back(row);
    m_RowCount++;
}

void xpMatrix::addRow(xpRow aRow)
{
 
    /* Ensure that the number of rows equals the number of elements
     * in the column. This implies that at least one column exists    */
    sizeTest(this, 1, aRow.size());

    if (m_xpMtx.begin() == m_xpMtx.end() && m_xpMtx.at(0).size() != aRow.size())
	{
		m_pMtxException = new xpException("Error in addRow()!");
		throw(m_pMtxException);
	}
    m_xpMtx.push_back(aRow);
    m_RowCount++;
}

void xpMatrix::insertRow(int ref)
{
	int c = getColumnCount();
	if (c==0)
	{
			addRow();
			return;
	}

	xpRow aRow(c, 0);
	//iter_r it = NULL;
	iter_r it_1 = m_xpMtx.begin();
	for (int i = 1; i <= ref; i++)
	   it_1++;

	m_xpMtx.insert(it_1, aRow);
	m_RowCount++;
}



void xpMatrix::insertRow(int ref, xpRow aRow)
{
    int c = getColumnCount();
    if (c==0)
    {
            addRow();
            return;
    }
    //iter_r it = NULL;
    iter_r it_1 = m_xpMtx.begin();
    for (int i = 1; i <= ref; i++)
       it_1++;

    m_xpMtx.insert(it_1, aRow);
    m_RowCount++;
}

void xpMatrix::insertRow(int ref, MTX_TYPE val)
{
    int c = getColumnCount();
    if (c==0)
    {
            addRow();
            return;
    }

    xpRow aRow(c, val);
  //  iter_r it = NULL;
    iter_r it_1 = m_xpMtx.begin();
    for (int i = 1; i <= ref; i++)
       it_1++;

    m_xpMtx.insert(it_1, aRow);
    m_RowCount++;
}

void xpMatrix::insertColumn(int ref)
{
   sizeTestColumn(this, ref);
   for (iter_r it = m_xpMtx.begin(); it != m_xpMtx.end(); it++)
   {
      iter_c it_1 = (*it).begin();
      for (int i = 1; i <= ref; i++)
         it_1++;

      (*it).insert(it_1, 0);
   }
   m_ColumnCount++;
}

void xpMatrix::insertColumn(int ref, xpColumn aCol)
{
   sizeTest(this, m_xpMtx.size(), ref);
   int cnt = 0;
   for (iter_r it = m_xpMtx.begin(); it != m_xpMtx.end(); it++)
   {
 
      iter_c it_1 = (*it).begin();
      for (int i = 1; i <= ref; i++)
         it_1++;

      (*it).insert(it_1, aCol.at(cnt));
      cnt++;
   }
   m_ColumnCount++;
}

void xpMatrix::insertColumn(int ref, MTX_TYPE val)
{
  sizeTestColumn(this, ref);
   for (iter_r it = m_xpMtx.begin(); it != m_xpMtx.end(); it++)
   {
      iter_c it_1 = (*it).begin();
      for (int i = 1; i <= ref; i++)
         it_1++;

      (*it).insert(it_1, val);
   }
   m_ColumnCount++;
}

void xpMatrix::getIteratorFromRef(int ref, iter_r * it)
{
   *it = m_xpMtx.begin();
   for (int i = 1; i <= ref; i++)
       it++;
}

float xpMatrix::getDet()
{
	unsigned int xp_r = 0;
	unsigned int xp_c = 0;

	iter_r it;
	iter_r itTmpRow;
	iter_r it_1;
	xpMatrix invMtx;

    getMtxSize(&xp_r, &xp_c);
    if (xp_r != xp_c)
	{
		m_pMtxException = new xpException("Only quadratic matrices have determinants!");
		throw(m_pMtxException);
	}
	int currRow = 0;
	MTX_TYPE dg = 0;
	xpRow aRow;
	for (int u = 0; u < xp_r; u++)
	{

	   for (int i = u+1; i < xp_r; i++)
	   {
	
		   dg = m_xpMtx.at(i).at(u)/m_xpMtx.at(u).at(u);
		   for (int j = 0; j < xp_c; j++)
		   {
		      
			  MTX_TYPE aNum;
			  MTX_TYPE v1,v2;
			  v1 = m_xpMtx.at(i).at(j);
			  v2 = m_xpMtx.at(u).at(j);
			  aNum =  v1 - v2*dg;
			  m_xpMtx.at(i).at(j) = aNum;
		   }
	   }
    }
	MTX_TYPE ret = 1;
	for (int i = 0; i < xp_r; i++)
	{
		MTX_TYPE aVal = m_xpMtx.at(i).at(i);
		ret = aVal*ret;
	}
	return ret;
}

double xpMatrix::getAdjunct()
{
   return 0;
}

void xpMatrix::setSize(int row, int col)
{
    int rr = getRowCount();
    int cc = getColumnCount();
    if (rr <= row && rr > 0)
        return;
    if (cc <= col && cc >0)
        return;

    for (int i= rr; i <row; i++)
    {               //build a column
        xpRow tmp(col, 0);
        //now add the column
        m_xpMtx.push_back(tmp);
    }
}

void xpMatrix::LoadFile(const char * fileName)
{
  std::ifstream in(fileName);
  const int bufsize = 255;
  char buffer[bufsize];

  while (in.getline(buffer, bufsize))
  {
     char* cp = buffer;
     while(*cp != ',')
      cp++;
         std::cout << cp << std::endl;
  }
}

void xpMatrix::SaveFile(const char * fileName)
{
    std::ofstream out(fileName);

    for (iter_r it = m_xpMtx.begin(); it != m_xpMtx.end(); it++)
    {
        for (iter_c it_c = (*it).begin(); it_c != (*it).end(); it_c++)
        {
            out << (*it_c) << ",";
        }
        out << std::endl;
    }
}

void xpMatrix::initUnity(int aNum)
{
        if (aNum == 0)
            aNum = 1;
        int row, col;
        row = 0;
        col = 0;
        for (iter_r it_r = m_xpMtx.begin(); it_r != m_xpMtx.end(); it_r++)
        {
                row++;
                for (iter_c it_c = (*it_r).begin(); it_c != (*it_r).end(); it_c++)
                {
                        col++;
                        if (row == col)
                                *it_c = (MTX_TYPE)aNum;
                    else
                                *it_c = 0.00;
                }
                col = 0;
        }
}

