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
};

