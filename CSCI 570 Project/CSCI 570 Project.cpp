// CSCI 570 Project.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <unordered_map>
#include "Solver.h"

using namespace std;

int main(int argc, char* argv[])
{

    /* Insert command line procssing code here */

    string s1;
    string s2;
    unordered_map<pair<char, char>, int> ALPHATABLE;
    int DELTA;

    Solver* BS = new Solver(&ALPHATABLE, DELTA);
    Solver* SS = new Solver(&ALPHATABLE, DELTA);

    BS->solve(s1, s2);
    SS->solve(s1, s2);

    /* Insert output processing code here */
}
