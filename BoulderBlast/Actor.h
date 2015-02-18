#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

// contains base, Player, and Wall class declarations
// as well as constants required by these classes

class Actor: public GraphObject
{
    public:
        Actor(int imageID, int startX, int startY, Direction dir);
        virtual ~Actor(){};
        virtual void doSomething()=0;
    
    
    
    
};

class Player: public Actor
{
    public:
    Player(int imageID, int startX, int startY, Direction dir);
    virtual ~Player(){};
    virtual void doSomething();
    
    //accessors
    int hitPoints();
    int roundAmmunition();
    
private:
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
//
//class Bullets: public Actor
//{
//public:
//    Bullets(int imageID, int startX, int startY, Direction dir);
//    virtual void doSomething();
//};
//
//class Exit : public Actor
//{
//public:
//    Exit(int imageID, int startX, int startY, Direction dir);
//    virtual void doSomething();
//};

class Wall: public Actor
{
public:
    Wall(int imageID, int startX, int startY, Direction di);
    virtual ~Wall(){}
    virtual void doSomething();
    
    
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
