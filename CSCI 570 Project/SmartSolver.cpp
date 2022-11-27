#include "SmartSolver.h"
#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>

using namespace std;

/////////////////////////  Public Functions  ///////////////////////////

// Constructs the solver with an external alpha table and delta value
SmartSolver::SmartSolver(unordered_map<pair<char, char>, int>* ALPHATABLE, int DELTA)
{
    alphaTable = ALPHATABLE;
    delta = DELTA;
}

// Clear the memo table
void SmartSolver::resetMemos()
{
    memos.clear();
}

// Update the alpha table
void SmartSolver::resetAlpha(unordered_map<pair<char, char>, int>* ALPHATABLE)
{
    alphaTable = ALPHATABLE;
}

// Update the delta value
void SmartSolver::resetDelta(int DELTA)
{
    delta = DELTA;
}

// Clear the memo table and update alpha / delta
void SmartSolver::resetAll(unordered_map<pair<char, char>, int>* ALPHATABLE, int DELTA)
{
    memos.clear();
    alphaTable = ALPHATABLE;
    delta = DELTA;
}

//// Finds the min cost alignment between substrings s1[0, ... , i] and s2[0, ... , j]
//int leftAlignment(string& s1, string& s2, unsigned int i, unsigned int j)
//
//// Finds the min cost alignment between substrings s1[i, ... , s1.size() - 1] and s2[s2.size() - 1, ... , j]
//int rightAlignment(string& s1, string& s2, unsigned int i, unsigned int j)
//
//// Finds the optimal split point in s2 given a split point of i in s1
//// Returns the index of the optimal point in s2
//int optSplitPoint(string& s1, string& s2, unsigned int i);

//// Finds the min cost alignment between substrings s1[0, ... , i] and s2[0, ... , j]
//// Returns the value of the minimum cost alignment
//int alignment(string& s1, string& s2, unsigned int i, unsigned int j)
//{   
//    unordered_map<pair<char, char>, int>& alphaProxy = *alphaTable;
//    // s1 has one character
//    if (i - s1.size() == 1)
//    {   
//        // s2 has one character
//        if (j - s2.size() == 1)
//        {
//            return min(alphaProxy[{s1[i], s2[j]}], delta);
//        }
//    }
//}


/* I could use reverse iterators to make something super duper fast, but reading it would be a nightmare */



int SmartSolver::solve(string& s1, string& s2)
{
    // Initialize base cases (0th column)
    for (int i = 0; i < s1.size(); ++i) {
        memos[{i, 0}] = i * delta;
    }

    // Initialize base cases (0th row)
    for (int i = 0; i < s2.size(); ++i) {
        memos[{0, i}] = i * delta;
    }
}

// Returns the maximum alignment cost between substrings s1[s1L, ... , s1R] and s2[s2L, ... , s2R]
// I'm setting the arbitrary convention of splitting to the right of the index (so the left will be [0, ... , i] and the right [i + 1, ... , n]
int SmartSolver::alignment(string& s1, string& s2, unsigned int s1L, unsigned int s1R, unsigned int s2L, unsigned int s2R)
{
    // If trying to solve without a known alpha table, return
    if (alphaTable == nullptr)
    {
        return -1;
    }
    // Else

    int s1Size = s1R - s1L + 1;
    int s2Size = s2R - s2L + 1;

    // Base Cases

    // These can probably be simplified by *just* using the memo values, but I wanted to be caerful
    // Can optimize later once this is working correctly

    // Two gaps are being compared
    if (s1Size == 0 && s2Size == 0)
    {
        return 2 * delta;
    }
    // s1's gap is being compared to s2
    else if (s1Size == 0)
    {
        return s2Size * delta;
    }
    // s2's gap is being compared to s1
    else if (s2Size == 0)
    {
        return s1Size * delta;
    }
    // Both s1 and s2 are comparing a single element
    else if (s1Size == 1 && s2Size == 1)
    {
        return memos[{s1L, s2L}];
    }
    // else General element comparison is happening

    unsigned int s1Split = (s1R + s1L) / 2;
    int bests2Split = -1;
    int minAlign = numeric_limits<int>::max();

    // Check every split point on the second string, remember the best one
    for (unsigned int s2Split = s2L; s2Split < s2R; ++s2Split)
    {
        string revString = stringReverse(s2, s2Split + 1, s2R);

        int tempAlignment =
            // Alignment for XL and YL
            alignment(s1, s2, s1L, s1Split, s2L, s2Split) +
            // Alignment for XR and YR
            alignment(s1, s2, s1Split + 1, s1R, 0, revString.size() - 1);

        if (tempAlignment < minAlign)
        {
            minAlign = tempAlignment;
            bests2Split = s2Split;
        }
    }

    string revString = stringReverse(s2, bests2Split + 1, s2R);

    return alignment(s1, s2, s1L, s1Split, s2L, bests2Split) + 
           alignment(s1, s2, s1Split + 1, s1R, 0, revString.size() - 1);
}

/////////////////////////  Private Functions  ///////////////////////////


// Returns the alignment value between strings s1 and s2, including indices i and j respectively
// If this alignment hasn't been found yet, it will be recursively calculated
int SmartSolver::memoize(unsigned int i, unsigned int j, string& s1, string& s2)
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

// Efficiently returns a reversal for a substring of s
string SmartSolver::stringReverse(string& s, unsigned int i, unsigned int j)
{
    string outString;
    for (; i <= j; ++i)
    {
        outString.push_back(s[i]);
    }

    return outString;
}