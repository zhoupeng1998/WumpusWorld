// ======================================================================
// FILE:        MyAI.cpp
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

#include "MyAI.hpp"

MyAI::MyAI() : Agent()
{
    // ======================================================================
    // YOUR CODE BEGINS
    // ======================================================================
    xbound = 0x3f3f3f3f;
    ybound = 7;
    withGold = false;
    wumpusAlive = true;
    lastAction = CLIMB;
    currentDirection = RIGHT;
    /*
    actionsTodo.push(FORWARD);
    actionsTodo.push(FORWARD);
    actionsTodo.push(TURN_RIGHT);
    actionsTodo.push(TURN_RIGHT);
    actionsTodo.push(FORWARD);
    actionsTodo.push(FORWARD);
    */
    actionsTodo.push(CLIMB);
    // ======================================================================
    // YOUR CODE ENDS
    // ======================================================================
}

Agent::Action MyAI::getAction
(
 bool stench,
 bool breeze,
 bool glitter,
 bool bump,
 bool scream
 )
{
    // ======================================================================
    // YOUR CODE BEGINS
    // ======================================================================
    
    // get size of world
    if (bump) {
        if (currentDirection == RIGHT) {
            xbound = currentPosition.first;
        } else if (currentDirection == UP) {
            ybound = currentPosition.second;
        } else {
            std::cerr << "*****************WARNING*****************" << std::endl;
            std::cerr << "My program was not designed like this!!!" << std::endl;
            std::cerr << "*****************************************" << std::endl;
        }
    }
    
    // shoot wumpus
    if (isFacingWumpus()) {
        return SHOOT;
    }
    if (scream) {
        wumpusAlive = false;
    }
    // POSSIBLE action queue check here
    if (glitter) {
        withGold = true;
        return GRAB;
    }
    if (withGold) {
        //go back
    }
    if (!breeze && !(wumpusAlive && stench)) {
        markNearbySafe();
    } else {
        if (wumpusAlive && stench) {
            this->stench.insert(currentPosition);
        }
        markNearbyDanger();
    }
    auto avaliableMoves = getValidDirections();
    if (!avaliableMoves.empty()) {
        //move, push in the queue
    } else {
        //get back
    }
    if (!actionsTodo.empty()) {
        auto move = actionsTodo.front();
        actionsTodo.pop();
        return move;
    }
    return CLIMB;
    // ======================================================================
    // YOUR CODE ENDS
    // ======================================================================
}

// ======================================================================
// YOUR CODE BEGINS
// ======================================================================
bool MyAI::coordinateIsOutOfBound (const std::pair<int, int> &coordinate) {
    return (coordinate.first <= 0 || coordinate.second <= 0 ||
            coordinate.first > xbound || coordinate.second > ybound);
}

MyAI::Direction MyAI::getNewDirection(Direction &current, Action &action) {
    if (action == TURN_LEFT) {
        switch (current) {
            case UP: return LEFT;
            case LEFT: return DOWN;
            case DOWN: return RIGHT;
            default: return UP;
        }
    } else if (action == TURN_RIGHT) {
        switch (current) {
            case UP: return RIGHT;
            case RIGHT: return DOWN;
            case DOWN: return LEFT;
            default: return UP;
        }
    }
    return current;
}

std::pair<int, int> MyAI::getNextCoordinate (const std::pair<int, int> &current, Direction direction) {
    if (direction == RIGHT) {
        return std::make_pair(current.first + 1, current.second);
    } else if (direction == LEFT) {
        return std::make_pair(current.first - 1, current.second);
    } else if (direction == UP) {
        return std::make_pair(current.first, current.second + 1);
    } else {
        return std::make_pair(current.first, current.second - 1);
    }
}

bool MyAI::isFacingWumpus() {
    if (!wumpusAlive || wumpusPosition == std::make_pair(0, 0)) {
        return false;
    } else if (currentPosition.first == wumpusPosition.first) {
        return (currentDirection == UP && currentPosition.first - wumpusPosition.first < 0) ||\
        (currentDirection == DOWN && currentPosition.first - wumpusPosition.first > 0) ;
    } else if (currentPosition.second == wumpusPosition.second) {
        return (currentDirection == RIGHT && currentPosition.second - wumpusPosition.second < 0) ||\
        (currentDirection == LEFT && currentPosition.second - wumpusPosition.second > 0) ;
    }
    return false;
}

void MyAI::markNearbySafe() {
    safe.insert(getNextCoordinate(currentPosition, RIGHT));
    safe.insert(getNextCoordinate(currentPosition, LEFT));
    safe.insert(getNextCoordinate(currentPosition, UP));
    safe.insert(getNextCoordinate(currentPosition, DOWN));
}

void MyAI::markNearbyDanger() {
    danger.insert(getNextCoordinate(currentPosition, RIGHT));
    danger.insert(getNextCoordinate(currentPosition, LEFT));
    danger.insert(getNextCoordinate(currentPosition, UP));
    danger.insert(getNextCoordinate(currentPosition, DOWN));
}

std::set<MyAI::Direction> MyAI::getValidDirections() {
    std::set<MyAI::Direction> result;
    auto rightCoord = getNextCoordinate(currentPosition, RIGHT),
        upCoord = getNextCoordinate(currentPosition, UP),
        leftCoord = getNextCoordinate(currentPosition, LEFT),
        downCoord = getNextCoordinate(currentPosition, DOWN);
    if (!coordinateIsOutOfBound(rightCoord) && (safe.find(rightCoord) != safe.end() ||
        danger.find(rightCoord) == danger.end()) && visited.find(rightCoord) == visited.end()) {
        result.insert(RIGHT);
    }
    if (!coordinateIsOutOfBound(upCoord) && (safe.find(upCoord) != safe.end() ||
        danger.find(upCoord) == danger.end()) && visited.find(upCoord) == visited.end()) {
        result.insert(UP);
    }
    if (!coordinateIsOutOfBound(leftCoord) && (safe.find(leftCoord) != safe.end() ||
        danger.find(leftCoord) == danger.end()) && visited.find(leftCoord) == visited.end()) {
        result.insert(LEFT);
    }
    if (!coordinateIsOutOfBound(downCoord) && (safe.find(downCoord) != safe.end() ||
        danger.find(downCoord) == danger.end()) && visited.find(downCoord) == visited.end()) {
        result.insert(DOWN);
    }
    return result;
}
// ======================================================================
// YOUR CODE ENDS
// ======================================================================
