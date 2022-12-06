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

	virtual int solve(string& a, string& b)= 0;
	virtual pair<string, string> solveStrings(string& a, string& b) = 0;
	//Solver(AlphaTable* ATABLE, int DELTA) {}= 0;
	Solver() {};
	virtual ~Solver() {};
	virtual void resetMemos()= 0;
	virtual void resetAlpha(AlphaTable* ATABLE)= 0;
	virtual void resetDelta(int DELTA)= 0;
	virtual void resetAll(AlphaTable* ATABLE, int DELTA)= 0;

protected:
	
	virtual int memoize(int i, int j, string& a, string& b)= 0;
	//virtual int alpha(char a, char b)= 0;
	AlphaTable* alphaTable;

	vector<vector<int>> memos;
	//unordered_map<pair<unsigned int, unsigned int>, int> memos= 0;
	//unordered_map<pair<char, char>, int>* alphaTable= 0;
};

#endif