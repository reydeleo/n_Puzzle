/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   testNPuzzle.cpp
 * Author: Liyu Zhang
 *
 * Created on February 5, 2017, 2:20 PM
 */

#include <iostream>
#include <vector>
#include "n_Puzzle.h"
#include "breadthFirst.h"
using namespace std;

/*
 *
 */
int main(int argc, char** argv) {
    
//    // Initialize the puzzle state
//    int a[] = {1,2,3,5,0,6,4,7,8};
//    vector<int> v(a, a+sizeof(a)/sizeof(int));
//    
//    //Creating the puzzle and display
//    //    n_Puzzle myPuzzle(8);
//    n_Puzzle myPuzzle(v);
//    cout << "Initial State: " << endl << endl;
//    myPuzzle.display();
//    
//    //Solving the puzzle
//    string solution = myPuzzle.solve();
//    if(solution=="!")
//        cout << endl << "Solution not found." << endl;
//    else
//        cout << endl << "Solution: " + solution << endl;
    
    int b[] = {1,2,3,5,0,6,4,7,8};
    vector<int> c(b, b+sizeof(b)/sizeof(int));
    n_Puzzle puzzle1(c);
    puzzle1.solveBFS(c);
    
    
    return 0;
}

