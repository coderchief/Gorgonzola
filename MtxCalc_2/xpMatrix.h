/**********************************************************************************
        Class:  xpMatrix
        Author: Tomas Schier
        Description: Header file for xpMatrix class
***********************************************************************************/

//header inclusion defines
#if !defined _xpMatrix_h_INCLUDED
#define _xpMatrix_h_INCLUDED

#pragma warning(disable:4786)

#include <vector>
#include <iterator>
#include <iostream>
#include <list>
#include <deque>
#include "stdafx.h"
#include "xpException.h"

typedef float MTX_TYPE;

typedef std::vector<MTX_TYPE> xpColumn;
typedef std::vector<MTX_TYPE> xpRow;
typedef std::vector<xpRow> xpMtxType;
typedef xpColumn::iterator  iter_c;
typedef xpMtxType::iterator iter_r;
typedef xpMtxType::reverse_iterator rev_iter_r;
typedef std::back_insert_iterator<xpColumn> it_fi;


class xpMatrix : public CObject

{
    DECLARE_SERIAL(xpMatrix)

public:
        xpMatrix();
	//	~xpMatrix();
        xpMatrix(const xpMatrix &xp);
        xpMatrix(const int size);
        xpMatrix(const int row, const int col, MTX_TYPE initVal);
        xpMatrix(const int row, const int col);
        void init(MTX_TYPE initVal);
        void initRandom(int seed);
		void initUnity(int aNum);
        xpRow getRow(int row);
        xpColumn getColumn(int col);

        MTX_TYPE getValueAt(unsigned int r, unsigned int c) const;
        void   setValueAt( unsigned int r, unsigned int c, MTX_TYPE val);
        void   getMtxSize(unsigned int * r,unsigned int * c) const;
        const int getRowCount();
        const int getColumnCount();

        //overloaded operators for easy use of calculator;
        friend const xpMatrix operator*(const xpMatrix& left, const xpMatrix& right);
        friend const xpMatrix operator+(const xpMatrix& left, const xpMatrix& right);
        friend const xpMatrix operator-(const xpMatrix& left, const xpMatrix& right);
        //the assignment operator is required as this class is derived from CObject
        const xpMatrix& operator=(const xpMatrix &left)
                {
                   // check for self assignment
                   if (&left != this)
                   {
                          m_xpMtx = left.m_xpMtx;
                   }
                   return *this;
                };
 
        //the actual matrix
        xpMtxType m_xpMtx;
private:
	    mutable xpException * m_pMtxException;
        void getIteratorFromRef(int ref, iter_r * it);
        //the member containg the data. A vector of a vector
        int m_digits;
        int m_RowCount;
        int m_ColumnCount;
        // some routines used for matrix inversion and other calculations
        MTX_TYPE getSmallestValueInRow(int r);
        MTX_TYPE getLargestValueInRow(int r);
        MTX_TYPE getSmallestValueInColumn(int c);
        MTX_TYPE getLargestValueInColumn(int c);
        xpMatrix buildExpandedMatrix();
        xpMatrix readInverseFromExpanded();
        void roundTo(MTX_TYPE * val);
public:
        void SaveFile(const char * fileName);
        void LoadFile(const char * fileName);
        void Serialize(CArchive& ar);

        double getAdjunct();
        float getDet();
        void insertColumn(int ref, MTX_TYPE val);
        void insertColumn(int ref, xpColumn aCol);
        void insertRow(int ref, MTX_TYPE val);
        void insertRow(int ref, xpRow aRow);
        void insertColumn(int ref);
        void insertRow(int ref);
        void addRow();
        void addColumn();
        void addRow(MTX_TYPE val);
        void addRow(xpRow aRow);
        void addColumn(MTX_TYPE val);
        void addColumn(xpColumn aCol);

        void setSize(int row, int col);

        xpMatrix getInverse();
        xpMatrix getTranspose();
        void printMtx();
        xpRow readRow(int row);
        xpColumn readColumn(int col);
        void setNumberOfDecimals(unsigned int n);
};

inline void sizeTest(xpMatrix * mtx, int row, int col)
{
	if (mtx == NULL)
			exit(1);
	if (mtx->getRowCount() < row)
			exit(1);
	if (mtx->getColumnCount() < col)
			exit(1);
}

inline void sizeTestRow(xpMatrix * mtx, int row)
{
    if (mtx == NULL)
            exit(1);
    if (mtx->getRowCount() < row)
            exit(1);
}

inline void sizeTestColumn(xpMatrix * mtx, int col)
{
        if (mtx == NULL)
                exit(1);
        if (mtx->getColumnCount() < col)
                exit(1);
}

#endif
