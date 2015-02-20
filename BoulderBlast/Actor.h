#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include "StudentWorld.h"



// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

// contains base, Player, and Wall class declarations
// as well as constants required by these classes

class Actor: public GraphObject
{
public:
    Actor(int imageID, int startX, int startY, Direction dir, StudentWorld* world);
    virtual ~Actor()
    {
        //getGraphObjects().erase(this);
    }
    virtual void doSomething()=0;
    
    StudentWorld* getWorld() const;
    bool isDead();
    void setDead();
    
    //accessor
    
    
    
private:
    StudentWorld* m_actorworld;
    bool m_isDead;
    
};

//class ThingsThatShoot: public Actor
//{
//public:
//    ThingsThatShoot(int imageID, int startX, int startY, Direction dir, StudentWorld* world);
//    virtual ~ThingsThatShoot()
//    {
//    }
//
//    
//};

class Player: public Actor
{
public:
    Player(int startX, int startY, StudentWorld* world);
    virtual ~Player()
    {
        //getGraphObjects().erase(this);
    }
    virtual void doSomething();
    
    //mutator
    int numLives();
    int hitPoints(bool gotShot);
    bool gotHit(bool gotHit);
    
    //accessors
    
    int roundAmmunition();
    
    
    
private:
    
    bool m_gotHit;
    int m_hitPoints;
    int m_roundAmmunition;
    
    
};

//class SnarlBots: public Actor
//{
//public:
//    SnarlBots(int imageID, int startX, int startY, Direction dir);
//    virtual void doSomething();
//
//};
//
//class KleptoBots: public Actor
//{
//public:
//    KleptoBots(int imageID, int startX, int startY, Direction dir);
//    virtual void doSomething();
//};
//
//class AngryKleptoBots: public KleptoBots
//{
//public:
//    AngryKleptoBots(int imageID, int startX, int startY, Direction dir);
//    virtual void doSomething();
//};
//
//class Factories: public Actor
//{
//public:
//    Factories(int imageID, int startX, int startY, Direction dir);
//    virtual void doSomething();
//};



class Bullets: public Actor
{
public:
    Bullets(int startX, int startY, Direction dir, StudentWorld* world);
    virtual ~Bullets(){}
    virtual void doSomething();
    bool willDamage(Actor* ap);
    
};

//class Exit : public Actor
//{
//public:
//    Exit(int imageID, int startX, int startY, Direction dir);
//    virtual void doSomething();
//};

class Wall: public Actor
{
public:
    Wall(int startX, int startY, StudentWorld* world);
    virtual ~Wall(){}
    virtual void doSomething(){return;}
    
    
private:
    
};

//class Boulders: public Actor
//{
//public:
//    Boulders(int imageID, int startX, int startY, Direction dir);
//    virtual void doSomething();
//};
//
//class Holes: public Actor
//{
//public:
//    Holes(int imageID, int startX, int startY, Direction dir);
//    virtual void doSomething();
//};
//
//class Jewels: public Actor
//{
//public:
//    Jewels(int imageID, int startX, int startY, Direction dir);
//    virtual void doSomething();
//};
//
//class RestoreHealthGoodies: public Actor
//{
//public:
//    RestoreHealthGoodies(int imageID, int startX, int startY, Direction dir);
//    virtual void doSomething();
//};
//
//class ExtraLifeGoodies: public Actor
//{
//public:
//    ExtraLifeGoodies(int imageID, int startX, int startY, Direction dir);
//    virtual void doSomething();
//};
//
//class AmmoGoodies: public Actor
//{
//public:
//    AmmoGoodies(int imageID, int startX, int startY, Direction dir);
//    virtual void doSomething();
//};
#endif // ACTOR_H_