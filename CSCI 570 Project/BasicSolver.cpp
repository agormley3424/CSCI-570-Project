#include "BasicSolver.h"
#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>

using namespace std;

/////////////////////////  Public Functions  ///////////////////////////

// Constructs the solver with an external alpha table and delta value
BasicSolver::BasicSolver(unordered_map<pair<char, char>, int>* ALPHATABLE, int DELTA)
{
	alphaTable = ALPHATABLE;
	delta = DELTA;
}

// Clear the memo table
void BasicSolver::resetMemos()
{
		memos.clear();
}

// Update the alpha table
void BasicSolver::resetAlpha(unordered_map<pair<char, char>, int>* ALPHATABLE)
{
	alphaTable = ALPHATABLE;
}

// Update the delta value
void BasicSolver::resetDelta(int DELTA)
{
	delta = DELTA;
}

// Clear the memo table and update alpha / delta
void BasicSolver::resetAll(unordered_map<pair<char, char>, int>* ALPHATABLE, int DELTA)
{
	memos.clear();
	alphaTable = ALPHATABLE;
	delta = DELTA;
}

// Returns the maximum alignment cost between strings s1 and s2
int BasicSolver::solve(string& s1, string& s2)
{
    // If trying to solve without a known alpha table, return
    if (alphaTable == nullptr)
    {
        return -1;
    }
    // Else


    unsigned int rows = s1.size();
    unsigned int cols = s2.size();

    // Initialize base cases (0th column)
    for (int i = 0; i < s1.size(); ++i) {
        memos[{i, 0}] = i * delta;
    }

    // Initialize base cases (0th row)
    for (int i = 0; i < s2.size(); ++i) {
        memos[{0, i}] = i * delta;
    }


    // Fill in cache array column by column from the 1st column
    for (int i = 1; i < cols; ++i) {
        for (int j = 1; j < rows; ++j) {
            memoize(i, j, s1, s2);
        }
    }

    unordered_map<pair<char, char>, int>& alphaProxy = *alphaTable;

    --rows;
    --cols;

    // The numeric cost of the alignment
    int alignmentCost = memoize(rows, cols, s1, s2);

    string s1Alignment;
    string s2Alignment;

    /* I think I need to remind myself how alignments are actually output... */

    // Traverse memo to find output string
    while (rows >= 0 && cols >= 0) {
        int memoVal = memoize(rows, cols, s1, s2);

        // Both characters are matched
        if (memoVal == alphaProxy[{s1[rows], s2[cols]}] + memoize(rows - 1, cols - 1, s1, s2))
        {
            s1Alignment.push_back(s1[rows]);
            s2Alignment.push_back(s2[cols]);
        }
        // Character from s1 isn't matched
        else if (memoVal == delta + memoize(rows - 1, cols, s1, s2))
        {
            s1Alignment.push_back('_');
            s2Alignment.push_back(s2[cols]);
        }
        // Character from s2 isn't matched
        else if (memoVal == delta + memoize(rows, cols - 1, s1, s2))
        {
            s1Alignment.push_back(s1[rows]);
            s2Alignment.push_back('_');
        }
        // Something has gone wrong
        else
        {
            cout << "BasicSolver Error: Solve() Line 99: Illegal value found during memo backtracing\n";
        }
    }

    

    return alignmentCost;
}

/////////////////////////  Private Functions  ///////////////////////////


// Returns the alignment value between strings s1 and s2, including indices i and j respectively
// If this alignment hasn't been found yet, it will be recursively calculated
int BasicSolver::memoize(unsigned int i, unsigned int j, string& s1, string& s2)
{
	// If indices are already cached, return the cached value
	if (memos.find({ i, j }) != memos.end()) {
		return memos.find({ i, j })->second;
	}

	// Create reference for alphaTable, easier notation
	unordered_map<pair<char, char>, int>& alphaProxy = *alphaTable;

	// Recursive call to fill memo cell
	memos[{i, j}] = min(alphaProxy[{s1[i], s2[j]}] + memoize(i - 1, j - 1, s1, s2),
		delta + memoize(i - 1, j, s1, s2),
		delta + memoize(i, j - 1, s1, s2));

    return memos[{i, j}];
}