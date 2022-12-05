#include "AlphaTable.h"

// Return the correct alpha value for given two characters
int AlphaTable::getVal(char row, char col)
{
	return table[charMap[row]][charMap[col]];
}