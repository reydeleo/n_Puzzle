/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   n_Puzzle.h
 * Author: Liyu Zhang
 *
 * Created on February 3, 2017, 3:24 PM
 */

#ifndef n_PUZZLE_H
#define n_PUZZLE_H

//#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include <math.h>
#include <string>
using namespace std;



// variable that defines available actions for the n-Puzzle.
static const string AVAILIBLE_ACTIONS = "RLUD";

// class modeling the n-Puzzle.
class n_Puzzle{
    
private:
    
    // member variables that store the target/initial states
    vector<int> _goalState;
    vector<int> _initState;
    
    // member var that stores the side length of the puzzle.
    int _m;
    // number of attempted actions for the tracing the search
    int _steps;
    
    // randomly generates the initial state
    void randInitState(){
        
        int n = _m * _m - 1;
        for(int i=0; i<=n; i++)
            _initState.push_back(i);
        
        for(int i=0; i<=n; i++){
            int j = rand() % (n+1);
            int k = rand() % (n+1);
            int temp = _initState[j];
            _initState[j] = _initState[k];
            _initState[k] = temp;
        }
        
    }
    
    // computes the distance of two states.
    // returns 0 if the two states are the same.
    int stateDis(vector<int> pState1, vector<int> pState2){
        
        if(pState1.size()!=pState2.size()){
            cout << "Invalid state.\n";
            return -1;
        }
        
        int dis = 0;
        for(int i=0; i<pState1.size(); i++)
            if(pState1[i]!=pState2[i])
                dis++;
        
        return dis;
    }
    
public:
    
    // Constructor 1 of the n-Puzzle class
    // Randomly generates the initial state.
    n_Puzzle(int n=8){
        
        // size checking; the puzzle must be m x m, where n = m*m -1.
        _m = (int) sqrt(n+1.0);
        if(_m*_m<n+1){
            cout << "Invalid size of initial state. An alternate size was used." << endl;
            _m++;
        }
        
        // initializes the target state
        for(int i=0; i<_m*_m-1; i++)
            _goalState.push_back(i+1);
        _goalState.push_back(0);
        
        randInitState();
        
    }
    
    // Constructor 2 of the n-Puzzle class
    // Set the initial state to be a given state.
    n_Puzzle(vector<int> initState){
        
        int n = initState.size()-1;
        bool isValid = true;
        
        // size checking; the puzzle must be m x m, where n = m*m -1.
        _m = (int) sqrt(n+1.0);
        if(_m*_m<(n+1)){
            cout << "Invalid size of initial state. An alternate size was used." << endl;
            _m++;
            isValid = false;
        }
        
        // Checks if the initial state is valid
        // each number between 0 and n (_m*_m1) must appear exactly once.
        for(int i=0; i<=n; i++){
            
            bool found = false;
            for(int j=0; j<=n; j++)
                if(initState[j]==i){
                    found = true;
                    break;
                }
            
            if(!found){
                isValid = false;
                break;
            }
            
        }
        
        if(!isValid){
            cout << "Invalid given initial state. An alternate initial state used.\n";
            randInitState();
        }
        else
            _initState = initState;
        
        // initializes the target state
        for(int i=0; i<_m*_m-1; i++)
            _goalState.push_back(i+1);
        _goalState.push_back(0);
        
    }
    
    
    // Solve the n-Puzzle from curState
    // Assuming preStates stores all states visited before the curState
    string solve(vector<vector<int> > preStates, vector<int> curState){
        //system.pause();
        
        // error checking;
        // "!" indicates no solution is found.
        int d = stateDis(curState, _goalState);
        if (d<0){
            cout << "Invalid state.\n" << endl;
            return "!";
        }
        
        // curState is already the goal state
        if(stateDis(curState,_goalState)==0)
            return "";
        
        // find the location of the blank (0)
        // within the state vector.
        int bLoc = 0;
        for(int i=0; i<curState.size(); i++)
            if(curState[i]==0){
                bLoc = i;
                break;
            }
        
        // main loop to attempt all possible actions.
        for(int i=0; i<AVAILIBLE_ACTIONS.length(); i++){
            
            int toSwap = -1;
            char act = AVAILIBLE_ACTIONS[i];
            bool visited = false;
            
            // Finds the index toSwap of the number to be swapped with the blank
            // toSwap = -1 if the current action cannot be performed.
            switch(act){
                    
                case 'L':
                    if(!(bLoc%_m==0))
                        toSwap = bLoc - 1;
                    break;
                    
                case 'R':
                    if(!(bLoc%_m==_m-1))
                        toSwap = bLoc + 1;
                    break;
                    
                case 'U':
                    if(!(bLoc/_m==0))
                        toSwap = bLoc - _m;
                    break;
                    
                case 'D':
                    if(!(bLoc/_m==_m-1))
                        toSwap = bLoc + _m;
                    break;
                    
                default:
                    cout << "Invalid action.\n";
                    return "!";
                    
            }
            
            if(toSwap!=-1){
                
                // Check if the next state after the action is visited before.
                vector<int> nextState = curState;
                nextState[bLoc] = nextState[toSwap];
                nextState[toSwap] = 0;
                //display(nextState);
                
                for(int i=0; i<preStates.size(); i++)
                    if(stateDis(nextState, preStates[i])==0){
                        visited = true;
                        break;
                    }
                
                if(visited)
                    continue;
                
                // Display the attemted action and the subsequent state
                _steps++;
                cout << endl << "Action #" << _steps << ": " << act <<endl;
                display(nextState);
                vector<vector<int> > nextStates = preStates;
                nextStates.push_back(curState);
                
                // Recursively solve the puzzle from the next state
                string nextActions = solve(nextStates, nextState);
                
                // If a solution is found from the next state
                // append the current action to that solution
                // to form a solution from the current state.
                if(nextActions!="!")
                    return act + nextActions;
                
            }
            
        }
        
        // "!" indicates no found is found from the current state.
        return "!";
        
    }
    
    // Solve the n-puzzle from the initial state
    string solve(){
        vector<vector<int> > preStates;
        _steps = 0;
        return solve(preStates, _initState);
    }
    
    // display the puzzle at the given state pState
    void display(vector<int> pState){
        
        int k = 0;
        for(int i=0; i<_m; i++){
            for(int j=0; j<_m; j++)
                cout << pState[k+j] << "\t";
            k += _m;
            cout << endl;
        }
    }
    
    // Display the initState.
    void display(){
        display(_initState);
    }
    
    string solveBFS(vector<int> curState);
    
};

#endif /* n_PUZZLE_H */
