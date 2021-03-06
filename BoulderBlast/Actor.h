#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include "StudentWorld.h"
#include "GameWorld.h" //added

class StudentWorld; //added

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

// contains base, Player, and Wall class declarations
// as well as constants required by these classes

class Actor: public GraphObject
{
public:
    Actor(int imageID, int startX, int startY, Direction dir, StudentWorld* world, int startingHitPoints);
    virtual ~Actor(){}
    virtual void doSomething()=0;
    
    StudentWorld* getWorld() const;
    bool isDead() const;
    void setDead();
    
    int getHitPoints() const;
    void decrementHitPoints(int decreaseby);
    void increaseHitPoints(int increaseby);
    
    virtual bool blocksPlayer(Actor* a, Direction dir)=0;
    virtual bool blocksRobots()=0;
    virtual bool bulletWillHarm()=0;
   
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
    virtual ~Player(){}
    virtual void doSomething();
    
    int getAmmo();
    void decrementAmmo();
    void increaseAmmo(int pts);
    void restoreHealth();
    int getHealth() const;
    void decHealth();
    int getPlayerLives(){return m_lives;}
    
    virtual bool blocksPlayer(Actor* a, Direction dir){ return false;}
    virtual bool bulletWillHarm();
    virtual bool blocksRobots(){return true;}

private:
    int m_lives;
    int m_ammo;
    int m_health;
    
};

class Robots: public Actor
{
public:
    Robots(int imageID, int startX, int startY, Direction dir, StudentWorld* world, int startingHitPoints);
    virtual ~Robots(){}
    virtual void doSomething(){};
    void resetTicks();
    void decrTicks();
    int getTicks();
    bool robotWillShoot(Actor *ap);
    bool blocksRobots(){return true;}
    bool robotShoot(int x, int y, GraphObject::Direction dir);
    virtual bool bulletWillHarm(){return false;}
    void RobotMove(int x, int y, Direction dir);
    
private:
    int m_ticks;
};

class SnarlBots: public Robots
{
public:
    SnarlBots(int startX, int startY, Direction dir, StudentWorld* world);
    virtual ~SnarlBots(){}
    virtual void doSomething();
    virtual bool blocksPlayer(Actor* a, Direction dir){ return true;}
    virtual bool bulletWillHarm();
    
};

class KleptoBots: public Robots
{
public:
    KleptoBots(int imageID, int startX, int startY, Direction dir, StudentWorld* world, int hitPoints);
    virtual ~KleptoBots();
    virtual void doSomething();
    virtual bool blocksPlayer(Actor* a, Direction dir){ return true;}
    virtual bool bulletWillHarm();
    

private:
    int m_distanceBeforeTurning;
    int m_kleptoCount;
    std::string typeGoodie;
};

class NormalKleptoBots: public KleptoBots
{
public:
    NormalKleptoBots(int startX, int startY, Direction dir, StudentWorld* world, int hitPoints);
    virtual ~NormalKleptoBots(){}
    virtual void doSomething();
    virtual bool bulletWillHarm();
};

class AngryKleptoBots: public KleptoBots
{
public:
    AngryKleptoBots(int startX, int startY, Direction dir, StudentWorld* world, int hitPoints);
    virtual ~AngryKleptoBots(){}
    virtual bool bulletWillHarm();
    virtual void doSomething();    
};

class Factories: public Actor
{
public:
    Factories(int startX, int startY, StudentWorld* world, bool isNormal);
    virtual ~Factories(){}
    virtual void doSomething();
    virtual bool blocksPlayer(Actor* a, Direction dir){return true;}
    virtual bool blocksRobots(){return true;}
    virtual bool bulletWillHarm(){return true;}
    
private:
    bool m_isNormal;
};

class Bullets: public Actor
{
public:
    Bullets(int startX, int startY, Direction dir, StudentWorld* world);
    virtual ~Bullets(){}
    virtual void doSomething();
    virtual bool blocksPlayer(Actor* a, Direction dir){return true;}
    virtual bool bulletWillHarm(){return false;}
    virtual bool blocksRobots() {return false;}
    
};

class Exit : public Actor
{
public:
    Exit(int startX, int startY, StudentWorld* stud);
    virtual ~Exit(){}
    virtual void doSomething();
    virtual bool blocksPlayer(Actor* a, Direction dir){ return false;}
    virtual bool bulletWillHarm(){return false;}
    virtual bool blocksRobots(){return false;}
};

class Wall: public Actor
{
public:
    Wall(int startX, int startY, StudentWorld* world);
    virtual ~Wall(){}
    virtual void doSomething(){return;}
    virtual bool blocksPlayer(Actor* a, Direction dir){ return true;}
    virtual bool bulletWillHarm(){return true;}
    virtual bool blocksRobots(){return true;}
    
private:
    
};

class Boulders: public Actor
{
public:
    Boulders(int startX, int startY, StudentWorld* world);
    virtual ~Boulders(){}
    virtual void doSomething();
    bool canBePushed(int x, int y);
    void moveBoulder(Direction dir);
    virtual bool blocksPlayer(Actor* a, Direction dir);
    virtual bool bulletWillHarm();
    virtual bool blocksRobots(){return true;}
    
private:
};

class Holes: public Actor
{
public:
    Holes(int startX, int startY, StudentWorld *world);
    virtual ~Holes(){}
    virtual void doSomething();
    virtual bool blocksPlayer(Actor* a, Direction dir){ return true;}
    virtual bool bulletWillHarm(){return false;}
    virtual bool blocksRobots(){return true;}
    
private:
    
};

class Items: public Actor
{
public:
    Items(int imageID, int startX, int startY,Direction dir, StudentWorld *world, int startingHitPoints);
    virtual ~Items(){}
    virtual bool blocksPlayer(Actor* a, Direction dir){ return false;}
    virtual bool bulletWillHarm(){return false;}
    virtual bool blocksRobots(){return false;}
    bool playerCanPickUp();
    void setPlayerCanPickUp(bool yesorno);
private:
    bool m_pickUp;
};

class Jewels: public Items
{
public:
    Jewels(int startX, int startY,StudentWorld *world);
    virtual ~Jewels(){}
    virtual void doSomething();
    
};

class RestoreHealthGoodies: public Items
{
public:
    RestoreHealthGoodies(int startX, int startY, StudentWorld* world);
    virtual ~RestoreHealthGoodies(){}
    virtual void doSomething();
    
};

class ExtraLifeGoodies: public Items
{
public:
    ExtraLifeGoodies(int startX, int startY, StudentWorld *world);
    virtual ~ExtraLifeGoodies(){}
    virtual void doSomething();
    
};

class AmmoGoodies: public Items
{
public:
    AmmoGoodies(int startX, int startY, StudentWorld* world);
    virtual ~AmmoGoodies(){}
    virtual void doSomething();
};
#endif // ACTOR_H_