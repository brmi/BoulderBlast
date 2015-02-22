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
    Actor(int imageID, int startX, int startY, Direction dir, StudentWorld* world, int startingHitPoints);
    virtual ~Actor()
    {
        //getGraphObjects().erase(this);
    }
    virtual void doSomething()=0;
    
    StudentWorld* getWorld() const;
    bool isDead();
    void setDead();
    
    int getHitPoints();
    void decrementHitPoints(int decreaseby);
    
    
    //Actor* getspecificActor(int x, int y);
    
    virtual bool blocksPlayer(Actor* a, Direction dir)=0;
    virtual bool bulletWillHarm(Actor* a)=0;



    
    
private:
    StudentWorld* m_actorworld;
    bool m_isDead;
    int m_hitPoints;
    int m_ammo;

    
    
};


class Player: public Actor
{
public:
    Player(int startX, int startY, StudentWorld* world);
    virtual ~Player()
    {
        //getGraphObjects().erase(this);
    }
    virtual void doSomething();
    
    void decrementLives();
    int getNumLives();
    
    int getAmmo();
    void decrementAmmo();
    
    virtual bool blocksPlayer(Actor* a, Direction dir){ return false;}
    virtual bool bulletWillHarm(Actor* a);
    

    
private:
    int m_lives;
    int m_ammo;
    
    
    
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
    virtual bool blocksPlayer(Actor* a, Direction dir){return true;}
    virtual bool bulletWillHarm(Actor* a){return false;}
    
};

class Exit : public Actor
{
public:
    Exit(int startX, int startY, StudentWorld* stud);
    virtual ~Exit(){}
    virtual void doSomething();
    virtual bool blocksPlayer(Actor* a, Direction dir){ return false;}
    virtual bool bulletWillHarm(Actor* a){return false;}
};

class Wall: public Actor
{
public:
    Wall(int startX, int startY, StudentWorld* world);
    virtual ~Wall(){}
    virtual void doSomething(){return;}
    virtual bool blocksPlayer(Actor* a, Direction dir){ return true;}
    virtual bool bulletWillHarm(Actor* a){return true;}
    
    
private:
    
};

class Boulders: public Actor
{
public:
    Boulders(int startX, int startY, StudentWorld* world);
    virtual ~Boulders(){};
    virtual void doSomething();
    bool canBePushed(int x, int y);
    void moveBoulder(Direction dir);
    virtual bool blocksPlayer(Actor* a, Direction dir);
    virtual bool bulletWillHarm(Actor* a);
   
    
    
    
private:
    
  
};

class Holes: public Actor
{
public:
    Holes(int startX, int startY, StudentWorld *world);
    virtual ~Holes(){}
    virtual void doSomething();
    virtual bool blocksPlayer(Actor* a, Direction dir){ return true;}
    virtual bool bulletWillHarm(Actor* a){return false;}
    
    
    
private:

};


class Jewels: public Actor
{
public:
    Jewels(int startX, int startY, StudentWorld *world);
    virtual ~Jewels(){}
    virtual void doSomething();
    virtual bool blocksPlayer(Actor* a, Direction dir){ return false;}
    virtual bool bulletWillHarm(Actor* a){return false;}
};

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