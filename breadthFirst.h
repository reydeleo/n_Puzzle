//
//  breadthFirst.h
//  n_Puzzle
//
//  Created by reynaldo deleo on 3/16/18.
//  Copyright © 2018 reynaldo deleo. All rights reserved.
//

#ifndef breadthFirst_h
#define breadthFirst_h


string n_Puzzle::solveBFS(vector<int> curState)
{
    _steps = 0;
    string moves = "";
    
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
    
    vector<vector<int>> Q;
    vector<vector<int>> visitedStates;
    visitedStates.push_back(curState);
    Q.push_back(curState);
    
    
    for(int i = 0; i < Q.size(); i++)
    {
        // find the location of the blank (0)
        // within the state vector.
        int bLoc = 0;
        for(int j=0; j<Q[i].size(); j++)
            if(Q[i].at(j) == 0){
                bLoc = j;
                break;
            }
        // main loop to attempt all possible actions.
        for(int k=0; k<AVAILIBLE_ACTIONS.length(); k++)
        {
            
            int toSwap = -1;
            char act = AVAILIBLE_ACTIONS[k];
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
                vector<int> nextState = Q[i];
                nextState[bLoc] = nextState[toSwap];
                nextState[toSwap] = 0;
                
//                display(nextState);
//                cout << endl;
                
                for(int i=0; i<visitedStates.size(); i++)
                    if(stateDis(nextState, visitedStates[i])==0){
                        visited = true;
                        break;
                    }
                
                
                if(visited != true){
                    visitedStates.push_back(nextState);
                    Q.push_back(nextState);
                }
                else{
                    continue;
                }
                _steps++;
                cout << endl << "Action #" << _steps << ": " << act <<endl;
                display(nextState);
                
                if(stateDis(nextState, _goalState) == 0){
                    return moves;
                }
                
            }
            
            
        }
        
    }
    
        return moves;
}
    


#endif /* breadthFirst_h */
