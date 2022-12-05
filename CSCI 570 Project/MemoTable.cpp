#include "MemoTable.h"

int getVal(unsigned int r, unsigned int c)
{
	return table[r][c];
}

MemoTable::MemoTable(unsigned int rows, unsigned int cols)
{
	table = new vector<vector<int>>(rows, vector<int>(cols, -1));
}

MemoTable::~MemoTable()
{
	for (int i = 0; i < table->size(); ++i)
	{
		delete &table[i];
	}

	delete table;
}