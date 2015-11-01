#pragma once
#include <iostream>

class LegalMatrix
{
	int columns;
	int rows;
	int** matrix;
	
	void to_identity()
    {
        for (int i = 0; i < this->rows; ++i)
        {
            this->matrix[i][i] = 1;
        }
    }
	
	int max(int a, int b) 
	{
		return a > b ? a : b;
	}
	
public:

	LegalMatrix(int rows, int columns)
	{
		this->columns = columns;
		this->rows = rows;
		this->matrix = new int*[rows];
		for (int i = 0; i < rows; i++)
		{
			this->matrix[i] = new int[columns];
		}
	}
    	
	virtual ~LegalMatrix(void)
	{
	}
	
	int GetLegalMatrixColumns()
	{
		return this->columns;
	}

	int GetLegalMatrixRows()
	{
		return this->rows;
	}

	int GetLegalValue(int row, int column)
	{
		return matrix[row][column];
	}

	void SetLegalValue(int value, int row, int column)
	{
		matrix[row][column] = value;
	}
	
	static void PrintLegalMatrix(LegalMatrix matrixToPrint)
	{
		for (int i = 0; i < matrixToPrint.GetLegalMatrixRows(); i++)
		{
			for (int j = 0; j < matrixToPrint.GetLegalMatrixColumns(); j++)
			{
				printf("%i ", matrixToPrint.GetLegalValue(i, j));
			}
			printf("%c", '\n');
		}
	}

	//Provides access to specified row.
    	//Notice that matrix[n] construction is lvalue
	//E.g.: LegalMatrix(5, 5)[n] = array;
	//User should make sure matrix[n] length is equal to array length
	int* &operator [](int idx)
	{
	   return this->matrix[idx];
	}
	
	LegalMatrix operator+(LegalMatrix right)
	{
		LegalMatrix ret_legal_matrix(
			max(this->GetLegalMatrixRows(), right.GetLegalMatrixRows()),
			max(this->GetLegalMatrixColumns(), right.GetLegalMatrixColumns())
			);
		for (int i = 0; i < ret_legal_matrix.GetLegalMatrixRows(); ++i)
		{
			for (int j = 0; j < ret_legal_matrix.GetLegalMatrixColumns(); ++j)
			{
				//If somebody tries to add matrix of different dimmensions
				//the little one is considered as filled up with zeroes.
				int a =
					i < this->GetLegalMatrixRows() &&
					j < this->GetLegalMatrixColumns()
					? (*this)[i][j]
					: 0;
				int b =
					i < right.GetLegalMatrixRows() &&
					j < right.GetLegalMatrixColumns()
					? right[i][j]
					: 0;

				ret_legal_matrix[i][j] = a + b;
			}
		}
		return ret_legal_matrix;
	}

	LegalMatrix operator- (LegalMatrix right)
	{
		LegalMatrix ret_legal_matrix(
			max(this->GetLegalMatrixRows(), right.GetLegalMatrixRows()),
			max(this->GetLegalMatrixColumns(), right.GetLegalMatrixColumns()));
		for (int i = 0; i < ret_legal_matrix.GetLegalMatrixRows(); ++i)
		{
			for (int j = 0; j < ret_legal_matrix.GetLegalMatrixColumns(); ++j)
			{
				//If somebody tries to add matrix of different dimmensions
				//the little one is considered as filled up with zeroes.
				int a =
					i < this->GetLegalMatrixRows() &&
					j < this->GetLegalMatrixColumns()
					? (*this)[i][j]
					: 0;
				int b =
					i < right.GetLegalMatrixRows() &&
					j < right.GetLegalMatrixColumns()
					? right[i][j]
					: 0;

				ret_legal_matrix[i][j] = a - b;
			}
		}
		return ret_legal_matrix;
	}
	
	LegalMatrix* operator * (LegalMatrix right)
	{
		LegalMatrix *resultMatrix = new LegalMatrix(this->GetLegalMatrixRows(), right.GetLegalMatrixColumns());
		int resultLegalMatrixRows = resultMatrix->GetLegalMatrixRows();
		int resultLegalMatrixColumns = resultMatrix->GetLegalMatrixColumns();
		int inner = this->GetLegalMatrixColumns();
		for (int row = 0; row < resultLegalMatrixRows; row++)
		{
			for (int column = 0; column < resultLegalMatrixColumns; column++)
			{
				int result = 0;
				for (int i = 0; i < inner; i++)
				{
					result += this->GetLegalValue(row, i) * right.GetLegalValue(i, column);
				}
				(*resultMatrix).SetLegalValue(result, row, column);
			}
		}
		return resultMatrix;
	}
	
    //UNCHECKED!
    //Use for square matrices only
    LegalMatrix operator^ (unsigned int power)
    {
        //If *this is not square, do nothing and return this.
        if (this->GetLegalMatrixColumns() != this->GetLegalMatrixRows())
        {
            return *this;
        }
        
        LegalMatrix ret_legal_matrix(
            this->GetLegalMatrixColumns(),
            this->GetLegalMatrixRows());
        
        ret_legal_matrix.to_identity();

        for (int i = 0; i < power; ++i)
        {
            ret_legal_matrix = *(ret_legal_matrix * *this);
        }

        return ret_legal_matrix;
    }
};

