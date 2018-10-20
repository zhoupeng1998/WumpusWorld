// ======================================================================
// FILE:        MyAI.hpp
//
// AUTHOR:      Abdullah Younis
//
// DESCRIPTION: This file contains your agent class, which you will
//              implement. You are responsible for implementing the
//              'getAction' function and any helper methods you feel you
//              need.
//
// NOTES:       - If you are having trouble understanding how the shell
//                works, look at the other parts of the code, as well as
//                the documentation.
//
//              - You are only allowed to make changes to this portion of
//                the code. Any changes to other portions of the code will
//                be lost when the tournament runs your code.
// ======================================================================

#ifndef MYAI_LOCK
#define MYAI_LOCK

#include "Agent.hpp"
#include <set>
#include <stack>
#include <queue>
#include <iostream>

class MyAI : public Agent
{
public:
    MyAI ( void );
    
    Action getAction
    (
     bool stench,
     bool breeze,
     bool glitter,
     bool bump,
     bool scream
     );
    
    // ======================================================================
    // YOUR CODE BEGINS
    // ======================================================================
    enum Direction {
        UP,
        DOWN,
        LEFT,
        RIGHT
    };
    int xbound;
    int ybound;
    Direction currentDirection;
    Action lastAction;
    bool withGold;
    bool wumpusAlive;
    std::pair<int, int> wumpusPosition;
    std::pair<int, int> currentPosition;
    
    std::stack<std::pair<int, int>> path;
    std::set<std::pair<int, int>> visited;
    std::set<std::pair<int, int>> safe;
    std::set<std::pair<int, int>> danger;
    std::set<std::pair<int, int>> stench;
    std::queue<Action> actionsTodo;
    
    bool coordinateIsOutOfBound (const std::pair<int, int>& coordinate);
    Direction getNewDirection (Direction& current, Action& action);
    std::pair<int, int> getNextCoordinate (const std::pair<int, int>& current, Direction direction);
    bool isFacingWumpus ();
    
    void markNearbySafe ();
    void markNearbyDanger ();
    std::set<Direction> getValidDirections ();
    void adjustDirectionAndMove (Direction direction);
    void moveBack ();
    Direction getDirectionToTargetPosition(std::pair<int, int>& target);
    
    
    // ======================================================================
    // YOUR CODE ENDS
    // ======================================================================
};

class BackupCoordinateException {};

#endif
