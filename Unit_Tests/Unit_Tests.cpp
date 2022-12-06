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

		TEST_METHOD(input1Value)
		{
			string s1 = "ACTG";
			string s2 = "TACG";
			vector<int> v1 = { 3, 6, 1, 1 };
			vector<int> v2 = { 1, 2, 9, 2 };

			s1 = IS.vectorConvert(s1, v1);
			s2 = IS.vectorConvert(s2, v2);

			int expectedValue = 1296;
			Assert::AreEqual(expectedValue, BS->solve(s1, s2));
		}

		TEST_METHOD(input2Value)
		{
			string s1 = "ACTG";
			string s2 = "TACG";
			vector<int> v1 = { 3, 6, 1, 1 };
			vector<int> v2 = { 1, 2, 0 };

			s1 = IS.vectorConvert(s1, v1);
			s2 = IS.vectorConvert(s2, v2);

			int expectedValue = 1128;
			Assert::AreEqual(expectedValue, BS->solve(s1, s2));
		}

		TEST_METHOD(input3Value)
		{
			string s1 = "AGTC";
			string s2 = "TACG";
			vector<int> v1 = { 0, 0, 0, 0, 0 };
			vector<int> v2 = { 1, 1, 1, 1, 1 };

			s1 = IS.vectorConvert(s1, v1);
			s2 = IS.vectorConvert(s2, v2);

			int expectedValue = 1980;
			Assert::AreEqual(expectedValue, BS->solve(s1, s2));
		}

		TEST_METHOD(input4Value)
		{
			string s1 = "TCGA";
			string s2 = "TCGA";
			vector<int> v1 = { 3, 7, 15, 31, 62};
			vector<int> v2 = { 3, 7, 15, 31, 63 };

			s1 = IS.vectorConvert(s1, v1);
			s2 = IS.vectorConvert(s2, v2);

			int expectedValue = 60;
			Assert::AreEqual(expectedValue, BS->solve(s1, s2));
		}

		TEST_METHOD(input5Value)
		{
			string s1 = "ACGT";
			string s2 = "TACG";
			vector<int> v1 = { 3, 6, 1, 1, 5, 6, 7, 8, 9, 20 };
			vector<int> v2 = { 1, 2, 0, 4, 3, 2, 0, 5, 6, 17 };

			s1 = IS.vectorConvert(s1, v1);
			s2 = IS.vectorConvert(s2, v2);

			int expectedValue = 63996;
			Assert::AreEqual(expectedValue, BS->solve(s1, s2));
		}

		TEST_METHOD(input1Strings)
		{
			string s1 = "ACTG";
			string s2 = "TACG";
			vector<int> v1 = { 3, 6, 1, 1 };
			vector<int> v2 = { 1, 2, 9, 2 };

			s1 = IS.vectorConvert(s1, v1);
			s2 = IS.vectorConvert(s2, v2);

			pair<string, string> testStrings = BS->solveStrings(s1, s2);

			string expectedString1 = "_A_CA_CACT__G__A_C_TAC_TGACTG_GTGA__C_TACTGACTGGACTGACTACTGACTGGTGACTACT_GACTG_G";
			string expectedString2 = "TATTATTA_TACGCTATTATACGCGAC_GCG_GACGCGTA_T_AC__G_CT_ATTA_T_AC__GCGAC_GC_GGAC_GCG";
			Assert::AreEqual(0, testStrings.first.compare(expectedString1));
			Assert::AreEqual(0, testStrings.second.compare(expectedString2));
		}

		TEST_METHOD(input0Strings)
		{
			string s1 = "A";
			string s2 = "C";
			//vector<int> v1 = { 3, 6, 1, 1 };
			//vector<int> v2 = { 1, 2, 9, 2 };

			//s1 = IS.vectorConvert(s1, v1);
			//s2 = IS.vectorConvert(s2, v2);

			pair<string, string> testStrings = BS->solveStrings(s1, s2);

			string expectedString1 = "_C__";
			string expectedString2 = "GCGG";
			Assert::AreEqual(0, testStrings.first.compare(expectedString1));
			Assert::AreEqual(0, testStrings.second.compare(expectedString2));
		}
	};
}
