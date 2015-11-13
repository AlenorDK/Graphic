#pragma once
#include <iostream>
template <typename T>
class LegalMatrix
{
	int columns;
	int rows;
	T** matrix;
	
	int max(int a, int b) 
	{
		return a > b ? a : b;
		
	}
	
public:

	LegalMatrix(int rows, int columns)
	{
		this->columns = columns;
		this->rows = rows;
		this->matrix = new T*[rows];
		for (int i = 0; i < rows; i++)
		{
			this->matrix[i] = new T[columns];
		}
	}
	
	LegalMatrix(T** matrix, int rows, int columns)
    	{
        	this->matrix = matrix;
        	this->columns = columns;
        	this->rows = rows;
    	}
    	
	virtual ~LegalMatrix(void)
	{
	}
	
	static LegalMatrix<T> GetIdentityMatrix(int size)
    	{
    		LegalMatrix<T> identityMatrix(size, size);
        	for (int i = 0; i < size; ++i)
        	{
        		for (int j = 0; j < size; j++)
        		{
            			identityMatrix[i][j] = (i == j);
        		}
        	}
        	return identityMatrix;
    	}
	
	int GetLegalMatrixColumns()
	{
		return this->columns;
	}

	int GetLegalMatrixRows()
	{
		return this->rows;
	}

	T GetLegalValue(int row, int column)
	{
		return matrix[row][column];
	}

	void SetLegalValue(T value, int row, int column)
	{
		matrix[row][column] = value;
	}
	
	static void PrintLegalMatrix(LegalMatrix matrixToPrint)
	{
		for (int i = 0; i < matrixToPrint.GetLegalMatrixRows(); i++)
		{
			for (int j = 0; j < matrixToPrint.GetLegalMatrixColumns(); j++)
			{
				std::cout << matrixToPrint.GetLegalValue(i, j);
			}
			std::cout << std::endl;
		}
	}

	//Provides access to specified row.
    	//Notice that matrix[n] construction is lvalue
	//E.g.: LegalMatrix(5, 5)[n] = array;
	//User should make sure matrix[n] length is equal to array length
	T* &operator [](int idx)
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
				T a =
					i < this->GetLegalMatrixRows() &&
					j < this->GetLegalMatrixColumns()
					? (*this)[i][j]
					: 0;
				T b =
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
				T a =
					i < this->GetLegalMatrixRows() &&
					j < this->GetLegalMatrixColumns()
					? (*this)[i][j]
					: 0;
				T b =
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
				T result = 0;
				for (int i = 0; i < inner; i++)
				{
					result += this->GetLegalValue(row, i) * right.GetLegalValue(i, column);
				}
				(*resultMatrix).SetLegalValue(result, row, column);
			}
		}
		return resultMatrix;
	}
	
	//User should check dimmensions before using it.
	LegalMatrix operator= (T** right)
    	{
        	this->matrix = right;
        	return *this;
    	}
};

