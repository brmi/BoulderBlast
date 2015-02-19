#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "GameConstants.h"
#include "Level.h"
#include "Actor.h"
#include <string>
#include <vector>
using namespace std;


// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

// contains your StudentWorld class declaration

class StudentWorld : public GameWorld
{
public:
    
    
    StudentWorld(std::string assetDir);
    ~StudentWorld();
    
    virtual int init();

    virtual int move();

    virtual void cleanUp();

private:
    
    vector<Actor*> m_container;         //container for my objects
    Player* m_playerContainer;   //holds where player is
 
    
};

#endif // STUDENTWORLD_H_
