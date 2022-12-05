#include "InputConverter.h"
#include <string>
#include <vector>


string InputConverter::vectorConvert(string& s, vector<int>& v)
{
	string newString = s;


	for (int i = 0; i < v.size(); ++i)
	{
		int index = v[i] + 1;

		// Append to end of string
		if (index == s.size())
		{
			newString.append(s);
		}
		// Insert somewhere in the string
		else if (index < s.size())
		{
			newString.insert(index, s);
		}
		// Index is greater than it should be
		else
		{
			throw "InputConverter Error: vectorConvert line 26: Impossible index specified\n";
		}

		s = newString;
	}

	return newString;
}