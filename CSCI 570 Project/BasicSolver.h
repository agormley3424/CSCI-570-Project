#ifndef BASIC_SOLVER
#define BASIC_SOLVER

#include <string>
#include <vector>
#include <unordered_map>
#include "Solver.h"
#include "AlphaTable.h"

using namespace std;

class BasicSolver
{
public:

	virtual int solve(string& a, string& b);
	BasicSolver(AlphaTable* ATABLE, int DELTA);
	BasicSolver() = delete;
	virtual void resetMemos();
	virtual void resetAlpha(AlphaTable* ATABLE);
	virtual void resetDelta(int DELTA);
	virtual void resetAll(AlphaTable* ATABLE, int DELTA);

private:

	virtual int memoize(unsigned int i, unsigned int j, string& a, string& b);
	//virtual int alpha(unsigned char a, unsigned char b);

	//unordered_map<int, unordered_map<int, int>> memos;
	//unordered_map<pair<unsigned int, unsigned int>, int> memos;
	//unordered_map<pair<char, char>, int>* alphaTable;
	AlphaTable* alphaTable;
	vector<vector<int>> memos;
	int delta;
};

#endif