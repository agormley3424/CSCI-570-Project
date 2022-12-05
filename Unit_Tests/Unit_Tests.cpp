#include "pch.h"
#include "CppUnitTest.h"
#include "Solver.h"
#include <iostream>
#include "AlphaTable.h"
#include "AlphaTable.cpp"
#include "BasicSolver.h"
#include "BasicSolver.cpp"
#include "InputConverter.h"
#include "InputConverter.cpp"
#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace UnitTests
{
	TEST_CLASS(UnitTests)
	{
	public:
		AlphaTable AT;
		vector<vector<int>> modelTable = { { 0, 110, 48, 94 },
					   { 110, 0, 118, 48 },
					   { 48, 118, 0, 110 },
					   { 94, 48, 110, 0 } };

		vector<char> letters = { 'A', 'C', 'G', 'T' };

		// Make sure alpha values are correct
		TEST_METHOD(alphaTestCorrectTable)
		{
			for (int i = 0; i < 4; ++i)
			{
				for (int j = 0; j < 4; ++j)
				{
					Assert::AreEqual(AT.getVal(letters[i], letters[j]), modelTable[i][j]);
					//cout << (AT.getVal(i, j)) << ", ";
				}
				//cout << endl;
			}
		}

		Solver* BS = new BasicSolver(&AT, 30);

		// Test alignment solver with single identical characters
		TEST_METHOD(OneCharSameAlignment)
		{
			for (int i = 0; i < 4; ++i)
			{
				string s1;
				string s2;
				s1.push_back(letters[i]);
				s2.push_back(letters[i]);
				Assert::AreEqual(0, BS->solve(s1, s2));
			}
		}

		// Test alignment solver with single different characters
		TEST_METHOD(OneCharDiffAlignment)
		{
			for (int i = 0, j = 3; i < 4 && j > -1; ++i, --j)
			{
				string s1;
				string s2;
				s1.push_back(letters[i]);
				s2.push_back(letters[j]);
				Assert::AreEqual(min(AT.getVal(letters[i], letters[j]), 60) , BS->solve(s1, s2));
			}
		}
		TEST_METHOD(TwoCharSameAlignment)
		{
			for (int i = 0; i < 3; ++i)
			{
				string s1;
				string s2;
				s1.push_back(letters[i]);
				s2.push_back(letters[i]);
				s1.push_back(letters[i + 1]);
				s2.push_back(letters[i + 1]);
				Assert::AreEqual(0, BS->solve(s1, s2));
			}
		}

		InputConverter IS;

		TEST_METHOD(stringGenerator1)
		{
			string s = "ACTG";
			vector<int> v = { 3, 6, 1 };
			string testResult = IS.vectorConvert(s, v);
			string expectedResult = "ACACTGACTACTGACTGGTGACTACTGACTGG";
			Assert::AreEqual(0, testResult.compare(expectedResult));
		}
		TEST_METHOD(stringGenerator2)
		{
			string s = "TACG";
			vector<int> v = { 1, 2, 9 };
			string testResult = IS.vectorConvert(s, v);
			string expectedResult = "TATTATACGCTATTATACGCGACGCGGACGCG";
			Assert::AreEqual(0, testResult.compare(expectedResult));
		}
	};
}
