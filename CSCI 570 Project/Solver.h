#ifndef SOLVER
#define SOLVER

#include <string>
#include <vector>
#include <unordered_map>
#include "AlphaTable.h"

using namespace std;

class Solver
{
public:

	virtual int solve(string a, string b);
	Solver(AlphaTable* ATABLE, int DELTA);
	Solver();
	virtual ~Solver();
	virtual void resetMemos();
	virtual void resetAlpha(AlphaTable* ATABLE);
	virtual void resetDelta(int DELTA);
	virtual void resetAll(AlphaTable* ATABLE, int DELTA);

private:
	
	virtual void fillMemos(string& a, string& b);
	virtual int memoize(unsigned int i, unsigned int j, string& a, string& b);
	//virtual int alpha(char a, char b);
	AlphaTable* alphaTable;

	vector<vector<int>> memos;
	//unordered_map<pair<unsigned int, unsigned int>, int> memos;
	//unordered_map<pair<char, char>, int>* alphaTable;
};

#endif