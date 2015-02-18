#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "GameConstants.h"
#include "Level.h"
#include "Actor.h"
#include <string>
#include <vector>
#include <stack>
using namespace std;
// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

// contains your StudentWorld class declaration

class StudentWorld : public GameWorld
{
public:
    
    
    StudentWorld(std::string assetDir);
    
    virtual int init();

    virtual int move();

    virtual void cleanUp();

private:
    


    
    int m_playercol;
    int m_playerrow;
    
    int m_wallcol;
    int m_wallrow;
    
    //Coord grid[15][15];
    

    
    
};

#endif // STUDENTWORLD_H_
