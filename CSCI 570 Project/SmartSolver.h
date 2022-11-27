#ifndef SMART_SOLVER
#define SMART_SOLVER

#include <string>
#include <vector>
#include <unordered_map>
#include "Solver.h"

using namespace std;

class SmartSolver : public Solver
{
public:

	virtual int solve(string& a, string& b);
	virtual int alignment(string& s1, string& s2, unsigned int s1L, unsigned int s1R, unsigned int s2L, unsigned int s2R);
	SmartSolver(unordered_map<pair<char, char>, int>* ALPHATABLE, int DELTA);
	SmartSolver() = delete;
	virtual ~SmartSolver();
	virtual void resetMemos();
	virtual void resetAlpha(unordered_map<pair<char, char>, int>* ALPHATABLE);
	virtual void resetDelta(int DELTA);
	virtual void resetAll(unordered_map<pair<char, char>, int>* ALPHATABLE, int DELTA);

private:

	virtual void fillMemos(string& a, string& b);
	virtual int memoize(unsigned int i, unsigned int j, string& a, string& b);
	virtual int alpha(unsigned char a, unsigned char b);
	virtual string stringReverse(string& s, unsigned int i, unsigned int j);

	unordered_map<pair<unsigned int, unsigned int>, int> memos;
	unordered_map<pair<char, char>, int>* alphaTable;
	int delta;
};

#endif