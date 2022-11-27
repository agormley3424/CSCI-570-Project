#ifndef SOLVER
#define SOLVER

#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

class Solver
{
public:

	virtual int solve(string a, string b);
	Solver(unordered_map<pair<char, char>, int>* alphaTable, int DELTA);
	Solver();
	virtual ~Solver();
	virtual void resetMemos();
	virtual void resetAlpha(unordered_map<pair<char, char>, int>* ALPHATABLE);
	virtual void resetDelta(int DELTA);
	virtual void resetAll(unordered_map<pair<char, char>, int>* ALPHATABLE, int DELTA);

private:
	
	virtual void fillMemos(string& a, string& b);
	virtual int memoize(unsigned int i, unsigned int j, string& a, string& b);
	virtual int alpha(char a, char b);

	unordered_map<pair<unsigned int, unsigned int>, int> memos;
	unordered_map<pair<char, char>, int>* alphaTable;
};

#endif