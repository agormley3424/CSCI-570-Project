#include "BasicSolver.h"
#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>

using namespace std;

/////////////////////////  Public Functions  ///////////////////////////

 //Constructs the solver with an external alpha table and delta value
BasicSolver::BasicSolver(AlphaTable* ATABLE, int DELTA)
{
    //Solver();

	alphaTable = ATABLE;
	delta = DELTA;
}

// Clear the memo table
// Not actually needed with the current scheme
void BasicSolver::resetMemos()
{

	//for (int i = 0; i < memos.size(); ++i)
	//{
 //       memos[i].clear();
	//}
	//	memos.clear();
}

// Update the alpha table
void BasicSolver::resetAlpha(AlphaTable* ATABLE)
{
	alphaTable = ATABLE;
}

// Update the delta value
void BasicSolver::resetDelta(int DELTA)
{
	delta = DELTA;
}

// Clear the memo table and update alpha / delta
// Don't need to delete memos in current scheme
void BasicSolver::resetAll(AlphaTable* ATABLE, int DELTA)
{
    //for (int i = 0; i < memos.size(); ++i)
    //{
    //    memos[i].clear();
    //}
    //memos.clear();

	alphaTable = ATABLE;
	delta = DELTA;
}

 //Returns the minimum alignment cost between strings s1 and s2
int BasicSolver::solve(string& s1, string& s2)
{
    // Create memos table with rows for s1 and columns for s2
    memos = vector<vector<int>>(s1.size(), vector<int>(s2.size(), -1));

    // If trying to solve without a known alpha table, return
    if (alphaTable == nullptr)
    {
        return -1;
    }
    // Else


    int rows = s1.size() - 1;
    int cols = s2.size() - 1;

    //// Initialize base cases (0th column)
    //for (int i = 0; i < s1.size(); ++i) {
    //    memos[i][0] = i * delta;
    //}

    //// Initialize base cases (0th row)
    //for (int i = 0; i < s2.size(); ++i) {
    //    memos[0][i] = i * delta;
    //}


    // Fill in cache array column by column from the 0th row
    for (int i = 0; i <= rows; ++i) {
        for (int j = 0; j <= cols; ++j) {
            memoize(i, j, s1, s2);
        }
    }

    //unordered_map<pair<char, char>, int>& alphaProxy = *alphaTable;

    //--rows;
    //--cols;

    // The numeric cost of the alignment
    int alignmentCost = memoize(rows, cols, s1, s2);

    string s1Alignment;
    string s2Alignment;

    /* I think I need to remind myself how alignments are actually output... */

    // Traverse memo to find output string
    while (rows >= 0 && cols >= 0) {
        int memoVal = memoize(rows, cols, s1, s2);

        // Both characters are matched
        if (memoVal == alphaTable->getVal(s1[rows], s2[cols]) + memoize(rows - 1, cols - 1, s1, s2))
        {
            s1Alignment.push_back(s1[rows]);
            s2Alignment.push_back(s2[cols]);

            --rows;
            --cols;
        }
        // Character from s1 isn't matched
        else if (memoVal == delta + memoize(rows - 1, cols, s1, s2))
        {
            s1Alignment.push_back('_');
            s2Alignment.push_back(s2[cols]);

            --rows;
        }
        // Character from s2 isn't matched
        else if (memoVal == delta + memoize(rows, cols - 1, s1, s2))
        {
            s1Alignment.push_back(s1[rows]);
            s2Alignment.push_back('_');

            --cols;
        }
        // Something has gone wrong
        else
        {
            cout << "BasicSolver Error: Solve() Line 99: Illegal value found during memo backtracing\n";
        }
    }

    return alignmentCost;
}

//Returns the minimum alignment cost strings s1 and s2
pair<string, string> BasicSolver::solveStrings(string& s1, string& s2)
{
    // Create memos table with rows for s1 and columns for s2
    memos = vector<vector<int>>(s1.size(), vector<int>(s2.size(), -1));

    // If trying to solve without a known alpha table, return
    if (alphaTable == nullptr)
    {
        return { "", "" };
    }
    // Else


    int rows = s1.size() - 1;
    int cols = s2.size() - 1;

    //// Initialize base cases (0th column)
    //for (int i = 0; i < s1.size(); ++i) {
    //    memos[i][0] = i * delta;
    //}

    //// Initialize base cases (0th row)
    //for (int i = 0; i < s2.size(); ++i) {
    //    memos[0][i] = i * delta;
    //}


    // Fill in cache array column by column from the 0th row
    for (int i = 0; i <= rows; ++i) {
        for (int j = 0; j <= cols; ++j) {
            memoize(i, j, s1, s2);
        }
    }

    //unordered_map<pair<char, char>, int>& alphaProxy = *alphaTable;

    //--rows;
    //--cols;

    // The numeric cost of the alignment
    int alignmentCost = memoize(rows, cols, s1, s2);

    string s1Alignment;
    string s2Alignment;

    /* I think I need to remind myself how alignments are actually output... */

    // Traverse memo to find output string
    while (rows >= 0 && cols >= 0) {
        int memoVal = memoize(rows, cols, s1, s2);

        // Both characters are matched
        if (memoVal == alphaTable->getVal(s1[rows], s2[cols]) + memoize(rows - 1, cols - 1, s1, s2))
        {
            s1Alignment.push_back(s1[rows]);
            s2Alignment.push_back(s2[cols]);

            --rows;
            --cols;
        }
        // Character from s1 isn't matched
        else if (memoVal == delta + memoize(rows - 1, cols, s1, s2))
        {
            s1Alignment.push_back('_');
            s2Alignment.push_back(s2[cols]);

            --rows;
            //--cols;
        }
        // Character from s2 isn't matched
        else if (memoVal == delta + memoize(rows, cols - 1, s1, s2))
        {
            s1Alignment.push_back(s1[rows]);
            s2Alignment.push_back('_');

            --cols;
            //--rows;
        }
        // Something has gone wrong
        else
        {
            throw "BasicSolver Error: Solve() Line 99: Illegal value found during memo backtracing\n";
        }
    }

    // Travel through s2's remaining values 
    if (rows != -1 || cols != -1)
    {
        // Travel through s2's remaining values
        while (cols >= 0)
        {
            s1Alignment.push_back('_');
            s2Alignment.push_back(s2[cols]);

            --cols;
        }

        // Travel through s1's remaining values
        while (rows >= 0)
        {
            s1Alignment.push_back(s1[rows]);
            s2Alignment.push_back('_');

            --rows;
        }
    }

    return { s1Alignment, s2Alignment };
}

///////////////////////  Private Functions  ///////////////////////////


 //Returns the alignment value between strings s1 and s2, including indices i and j respectively
 //If this alignment hasn't been found yet, it will be recursively calculated
int BasicSolver::memoize(int i, int j, string& s1, string& s2)
{
    // Comparing nothing to the second string (Base case column edges)
    if (i == -1)
    {
        return delta * (j + 1);
    }
    // Comparing nothing to the first string (Base case row edges)
    else if (j == -1)
    {
        return delta * (i + 1);
    }
	// If indices are already cached, return the cached value
    else if (memos[i][j] != -1)
    {
        return memos[i][j];
    }


	// Recursive call to fill memo cell
    // (Have to use two min operators because C++ is dumb)
    memos[i][j] = min(alphaTable->getVal(s1[i], s2[j]) + memoize(i - 1, j - 1, s1, s2),
        delta + memoize(i - 1, j, s1, s2));

    memos[i][j] = min(memos[i][j],
        delta + memoize(i, j - 1, s1, s2));

    return memos[i][j];
}