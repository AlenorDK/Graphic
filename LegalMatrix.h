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

	int* operator [] (int* _inputArray) 
	{
		return 
			//TODO: implement exeption
	}

	virtual ~LegalMatrix(void)
	{
	}
};

