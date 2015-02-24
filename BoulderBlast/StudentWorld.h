#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "GameConstants.h"
#include "GraphObject.h"
#include <string>
#include <vector>


class Actor;
class Player;
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
    
    Actor* getActor(int x, int y);
    
    bool playerDied();
    
    void setPlayerCompletedLevel();
    
    bool playerCompletedLevel();
    
    void removeDeadGameObjects();
    
    void setDisplayText();
    
    std::string format(int score, int level, int lives, int health, int ammo, unsigned int bonus);
    
    void makeBullet(int x, int y, GraphObject::Direction dir);
    
    int numJewels();
    void decNumJewels();
    
    //accessor
    std::vector<Actor*>* getActorContainer();
    Player* getPlayer();
    
    
    
private:
    
    std::vector<Actor*> m_container;         //container for my objects
    Player* m_playerContainer;   //holds where player is
    int m_numJewels;
    bool m_playerCompletedLvl;
    
    
};

#endif // STUDENTWORLD_H_