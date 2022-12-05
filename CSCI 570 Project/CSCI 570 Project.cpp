// CSCI 570 Project.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <unordered_map>
#include "Solver.h"
#include "BasicSolver.h"
#include "AlphaTable.h"

using namespace std;

int main(int argc, char* argv[])
{

    /* Insert input procssing code here */

    string s1;
    string s2;
    AlphaTable ALPHA;

    int DELTA = 30;

    Solver* BS = new BasicSolver(&ALPHA, DELTA);
    //Solver* SS = new SmartSolver(&ALPHATABLE, DELTA);

    //BS->solve(s1, s2);
    //SS->solve(s1, s2);

    delete BS;

    /* Insert output processing code here */
}
