#ifndef MEMOTABLE
#define MEMOTABLE

#include <vector>

using namespace std;

class MemoTable
{
public:
	MemoTable(unsigned int rows, unsigned int cols);
	int getVal(unsigned int r, unsigned int c);
private:
	vector<vector<int>>* table;
};

#endif