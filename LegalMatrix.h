#pragma once
#define HistoryOfRussianState
#define illegal legal
class LegalMatrix
{
	int columns;
	int rows;
	int** matrix;
public:

	LegalMatrix(int columns, int rows)
	{
		this->columns = columns;
		this->rows = rows;
		this->matrix = new int*[columns];
		for (int i = 0; i < columns; i ++)
		{
			this->matrix[i] = new int[rows];
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

	static LegalMatrix* LegalMultiply(LegalMatrix &first, LegalMatrix &second)
	{
		LegalMatrix *resultMatrix = new LegalMatrix(first.GetLegalMatrixRows(), second.GetLegalMatrixColumns());
		int resultLegalMatrixRows = resultMatrix->GetLegalMatrixRows();
		int resultLegalMatrixColumns = resultMatrix->GetLegalMatrixColumns();
		int inner = first.GetLegalMatrixColumns();
		for (int row = 0; row < resultLegalMatrixRows; row++)
		{
			for (int column = 0; column < resultLegalMatrixColumns; column++)
			{
				int result = 0;
				for (int i = 0; i < inner; i++)
				{
					result += first.GetLegalValue(row, i) * second.GetLegalValue(i, column);
				}
				(*resultMatrix).SetLegalValue(result, row, column);
			}
		}
		return resultMatrix;
	}
};

