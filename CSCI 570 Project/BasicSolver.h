#ifndef BASIC_SOLVER
#define BASIC_SOLVER

#include <string>
#include <vector>
#include <unordered_map>
#include "Solver.h"

using namespace std;

class BasicSolver : public Solver
{
public:

	virtual int solve(string& a, string& b);
	BasicSolver(unordered_map<pair<char, char>, int>* ALPHATABLE, int DELTA);
	BasicSolver() = delete;
	virtual ~BasicSolver();
	virtual void resetMemos();
	virtual void resetAlpha(unordered_map<pair<char, char>, int>* ALPHATABLE);
	virtual void resetDelta(int DELTA);
	virtual void resetAll(unordered_map<pair<char, char>, int>* ALPHATABLE, int DELTA);

private:

	virtual void fillMemos(string& a, string& b);
	virtual int memoize(unsigned int i, unsigned int j, string& a, string& b);
	virtual int alpha(unsigned char a, unsigned char b);

	unordered_map<pair<unsigned int, unsigned int>, int> memos;
	unordered_map<pair<char, char>, int>* alphaTable;
	int delta;
};

#endif