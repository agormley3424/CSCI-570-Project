#ifndef ALPHATABLE
#define ALPHATABLE

#include <unordered_map>

using namespace std;

class AlphaTable {
public:
	int getVal (char row, char col);
private:
	unordered_map<char, int> charMap = { {'A', 0},
		{'C', 1},
		{'G', 2},
		{'T', 3} };

	vector<vector<int>> table = { { 0, 110, 48, 94 },
						   { 110, 0, 118, 48 },
						   { 48, 118, 0, 110 },
						   { 94, 48, 110, 0 } };
};

#endif