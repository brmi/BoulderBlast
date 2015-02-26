#include "Actor.h"
#include "StudentWorld.h"
using namespace std;
#include <iostream>

// Students:  Add code to this file (if you wish), Actor.h, StudentWorld.h, and StudentWorld.cpp

Actor::Actor(int imageID, int startX, int startY, Direction dir, StudentWorld* world, int startingHitPoints):GraphObject(imageID, startX, startY, dir)
{
    m_hitPoints=startingHitPoints;
    m_actorworld=world;
    m_isDead=false;
    
}

bool Actor::isDead()
{
    return m_isDead;
}

void Actor::setDead()
{
    m_isDead=true;
}

int Actor::getHitPoints()
{
    return m_hitPoints;
}


void Actor::decrementHitPoints(int decreaseby)
{
    m_hitPoints=m_hitPoints-decreaseby;
}

void Actor::increaseHitPoints(int increaseby)
{
    m_hitPoints+=increaseby;
}

StudentWorld* Actor::getWorld() const
{
    return m_actorworld;
}
//////////
//ROBOTS//
/////////
Robots::Robots(int imageID, int startX, int startY, Direction dir, StudentWorld* world, int startingHitPoints):Actor(imageID, startX, startY, dir, world, startingHitPoints)
{
    m_ticks = (28 - world->GameWorld::getLevel()) / 4;
    
    if (m_ticks < 3)
        m_ticks = 3;
//    m_ticks=1;
}

void Robots::decrTicks()
{
    m_ticks-=1;
}

int Robots::getTicks()
{
    return m_ticks;
}

void Robots::resetTicks()
{
    StudentWorld* stud=getWorld();
    m_ticks = (28 - stud->GameWorld::getLevel()) / 4;
    
    if (m_ticks < 3)
        m_ticks = 3;
}

bool Robots::robotWillShoot(Actor* ap)
{
    if(ap==nullptr)
        return false;
    Player* pp=dynamic_cast<Player*>(ap);
    if(pp!=nullptr)
        return true;
    return false;
}

//////////////
//SNARLBOTS//
////////////

SnarlBots::SnarlBots(int startX, int startY, Direction dir, StudentWorld* world):Robots(IID_SNARLBOT, startX, startY, dir, world, 10 )
{
    setVisible(true);
}

bool SnarlBots:: bulletWillHarm()
{
    StudentWorld* stud=getWorld();
    stud->playSound(SOUND_ROBOT_DIE);
    stud->increaseScore(100);
    decrementHitPoints(2);
    if(getHitPoints()<=0)
        setDead();
    return true;
}

void SnarlBots::doSomething()
{
    decrTicks();
if(getTicks()<=0)
    {
    if(isDead())
        return;
    decrTicks();
  
    int x=getX();
    int y=getY();

    
    StudentWorld *stud= getWorld();
    

    GraphObject::Direction dir= getDirection();
    
    if(dir==right)
        {
            for(int i= x+1; i<=14; i++)
            {
                Actor* ap= stud->getActor(i, y);
                Player* pp= dynamic_cast<Player*>(ap);
                Boulders* bp=dynamic_cast<Boulders*>(ap);
                if(ap!=nullptr && pp!=nullptr)
                {
                    stud->playSound(SOUND_ENEMY_FIRE);
                    stud->makeBullet(++x, y, right);
                    resetTicks();
                    return;
                }
                else if(ap!=nullptr && bp!=nullptr)
                    break;
            }
            
            Actor* rp=stud->getActor(x+1, y);
            if(rp!=nullptr && rp->blocksRobots()==false)
            {
                moveTo(++x,y);
                resetTicks();
                return;
            }
            else if(rp!=nullptr && rp->blocksRobots()) //if it's a wall or boulder or something
            {
                setDirection(left);
                resetTicks();
                return;
            }else if(rp==nullptr)
                moveTo(++x, y);
        }
    
    if(dir==left)
        {
            
            for(int i= x-1; i>=0; i--)
            {
                Actor* qp= stud->getActor(i, y);
                Player* pp= dynamic_cast<Player*>(qp);
                Boulders* bp=dynamic_cast<Boulders*>(qp);
                if(qp!=nullptr && pp!=nullptr)
                {
                    stud->playSound(SOUND_ENEMY_FIRE);
                    stud->makeBullet(--x, y, left);
                    resetTicks();
                    return;
                }else if(qp!=nullptr && bp!=nullptr)
                    break;
            }
            Actor* qp=stud->getActor(x-1, y);
            if(qp!=nullptr && qp->blocksRobots()==false)
            {
                moveTo(--x,y);
                resetTicks();
                return;
            }else if(qp!=nullptr && qp->blocksRobots()) //if it's a wall or boulder or something
            {
                setDirection(right);
                resetTicks();
                return;
            }else if(qp==nullptr)
                moveTo(--x, y);
        }
    
        if(dir==up)
        {
            
            for(int i= y+1; i<=14; i++)
            {
                Actor* zp= stud->getActor(x, i);
                Player* pp= dynamic_cast<Player*>(zp);
                Boulders* bp= dynamic_cast<Boulders*>(zp);
                if(zp!= nullptr && pp!=nullptr)
                {
                    stud->playSound(SOUND_ENEMY_FIRE);
                    stud->makeBullet(x, ++y, up);
                    resetTicks();
                    return;
                }
                else if(zp!=nullptr && bp!=nullptr)
                    break;
            }
            Actor* zp= stud->getActor(x, y+1);
            if(zp!=nullptr && zp->blocksRobots()==false) //if nothing is blocking
            {
                moveTo(x,++y);
                resetTicks();
                return;
            }else if(zp!=nullptr && zp->blocksRobots()) //if it's a wall or boulder or something
            {
                setDirection(down);
                resetTicks();
                return;
            }else if(zp==nullptr)
                moveTo(x, ++y);
        }
            
        if(dir==down)
        {
            for(int i= y-1; i>=0; i--)
            {
                Actor* fp= stud->getActor(x, i);
                Player* pp= dynamic_cast<Player*>(fp);
                Boulders* bp=dynamic_cast<Boulders*>(fp);
                 if(fp!=nullptr && pp!=nullptr)
                 {
                     stud->playSound(SOUND_ENEMY_FIRE);
                     stud->makeBullet(x, --y, down);
                     resetTicks();
                     return;
                 }else if(fp!=nullptr && bp!=nullptr)
                     break;
            }
            Actor* fp= stud->getActor(x, y-1);
            if(fp!=nullptr && fp->blocksRobots()==false)
            {
                moveTo(x, --y);
                resetTicks();
                return;
            }else if(fp!=nullptr && fp->blocksRobots())
            {
                setDirection(up);
                resetTicks();
                return;
            }else if(fp==nullptr)
                moveTo(x,--y);
        }
        resetTicks();
    }else
        return;
    
}



//////////
//PLAYER//
//////////

Player::Player(int startX, int startY, StudentWorld* world):Actor(IID_PLAYER, startX, startY, right, world, 20)
{
    m_health=100;
    m_lives=3;
    m_ammo=20;
    setVisible(true);
}

int Player::getAmmo()
{
    return m_ammo;
}

void Player::decrementAmmo()
{
    if(m_ammo>0)
        m_ammo--;
    else
        m_ammo=0;
}

void Player::increaseAmmo(int pts)
{
    m_ammo+=pts;
}

void Player::restoreHealth()
{
    m_health=100;
}

int Player::getHealth() const
{
    return m_health;
}

bool Player::bulletWillHarm()
{
    StudentWorld* stud= getWorld();
    if(stud->getLives() >0)
    {
        decHealth();
        decrementHitPoints(2);
        if(getHitPoints()<0)
            stud->decLives();
        if(getHealth()<=0)
            setDead();
    }
    return true;
}
void Player:: decHealth()
{
    m_health=m_health-10;
}

void Player::doSomething()
{
    int x=getX();
    int y=getY();
    Direction dir=getDirection();
    
    int ch;
    
    StudentWorld *stud= getWorld();
    
    
    if(getWorld()->getKey(ch))
    {
        switch(ch)
        {
            case KEY_PRESS_LEFT:
                if(x>0)
                {
                    if(getDirection()!=left)
                        setDirection(left);
                    dir=left;
                    
                    Actor* ap= stud->getActor(--x,y); //this gives me actor at specific location!
                    if(ap!=nullptr)
                    {
                        if(ap->blocksPlayer(ap, dir))
                            return;
                    }
                    moveTo(x, y);
                }else
                {
                    if(getDirection()!=left)
                        setDirection(left);
                }
                break;
            case KEY_PRESS_RIGHT:
                if(x<14)
                {
                    if(getDirection()!=right)
                        setDirection(right);
                    
                    dir=right;
                    Actor* ap= stud->getActor(++x,y);
                    if(ap!=nullptr)
                    {
                        if(ap->blocksPlayer(ap, dir))
                            return;
                    }
                    moveTo(x, y);
                }else
                {
                    if(getDirection()!=right)
                        setDirection(right);
                }
                break;
            case KEY_PRESS_UP:
                if(y>0)
                {
                    if(getDirection()!=up)
                        setDirection(up);
                    
                    dir=up;
                    Actor* ap= stud->getActor(x,++y);
                    if(ap!=nullptr)
                    {
                        if(ap->blocksPlayer(ap, dir))
                            return;
                    }
                    moveTo(x, y);
                }else
                {
                    if(getDirection()!=up)
                        setDirection(up);
                }
                break;
            case KEY_PRESS_DOWN:
                if(y<14)
                {
                    if(getDirection()!=down)
                        setDirection(down);
                    dir=down;
                    Actor* ap= stud->getActor(x,--y);
                    if(ap!=nullptr)
                    {
                        if(ap->blocksPlayer(ap, dir))
                            return;
                    }
                    moveTo(x, y);
                }else
                {
                    if(getDirection()!=down)
                        setDirection(down);
                }
                break;
            case KEY_PRESS_ESCAPE:
                stud->decLives();
                setDead();
                break;
            case KEY_PRESS_SPACE:
                decrementAmmo();
                if(getDirection()==up)
                {
                    stud->playSound(SOUND_PLAYER_FIRE);
                    getWorld()->makeBullet(x, ++y, dir);
                }
                if(getDirection()==down)
                {
                    stud->playSound(SOUND_PLAYER_FIRE);
                    getWorld()->makeBullet(x,--y, dir);
                }
                if(getDirection()==right)
                {
                    stud->playSound(SOUND_PLAYER_FIRE);
                    getWorld()->makeBullet(++x, y, dir);
                }
                if(getDirection()==left)
                {
                    stud->playSound(SOUND_PLAYER_FIRE);
                    getWorld()->makeBullet(--x, y, dir);
                }
                break;
        }
    }
}

////////
//WALL//
////////

Wall::Wall(int startX, int startY, StudentWorld* world):Actor(IID_WALL, startX, startY, none, world, 1)
{
    setVisible(true);
}

////////////
//BULLETS//
//////////

Bullets::Bullets(int startX, int startY, Direction dir, StudentWorld* world):Actor(IID_BULLET, startX, startY, dir, world, 1)
{
    setVisible(true);
}

void Bullets::doSomething()
{
    if(isDead())
        return;
    
    int x=getX();
    int y=getY();
    
    StudentWorld *stud= getWorld();
    
    if(getDirection()==up)
    {
        moveTo(x,++y);
        Actor* lp=stud->getActor(x,y);
        if(lp!=nullptr && lp->bulletWillHarm())
        {
            setDead();
            return;
        }
    }
    if(getDirection()==down)
    {
        moveTo(x,--y);
        Actor* lp=stud->getActor(x,y);
        if(lp!=nullptr && lp->bulletWillHarm())
        {
            setDead();
            return;
        }
    }
    if(getDirection()==right)
    {
        moveTo(++x, y);
        Actor* lp=stud->getActor(x,y);
        if(lp!=nullptr && lp->bulletWillHarm())
        {
            setDead();
            return;
        }
    }
    if(getDirection()==left)
    {
        moveTo(--x, y);
        Actor* lp=stud->getActor(x,y);
        if(lp!=nullptr && lp->bulletWillHarm())
        {
            setDead();
            return;
        }
    }
}

/////////
//HOLES//
////////

Holes::Holes(int x, int y, StudentWorld* world):Actor(IID_HOLE, x, y, none, world, 0)
{
    setVisible(true);
}

void Holes::doSomething()
{
    int x=getX();
    int y= getY();
    
    if(isDead())
        return;
    
    StudentWorld *stud= getWorld();
    
    Actor* ap= stud->getActor(x,y);
    
    Boulders* bp=dynamic_cast<Boulders*>(ap);
    if(ap!= nullptr && bp!=nullptr)
    {
        setDead();
        bp->setDead();
    }
}


////////////
//BOULDER//
//////////

Boulders::Boulders(int startX, int startY, StudentWorld* world): Actor(IID_BOULDER, startX, startY, none, world, 10)
{
    setVisible(true);
}

bool Boulders::blocksPlayer(Actor *a, Direction dir)
{
    int x=getX();
    int y=getY();
    
    if(dir==right && canBePushed(++x, y))
    {
        moveBoulder(right);
        return false;
    }else if(dir==left && canBePushed(--x, y))
    {
        moveBoulder(left);
        return false;
    }else if(dir==up && canBePushed(x, ++y))
    {
        moveBoulder(up);
        return false;
    }else if(dir==down && canBePushed(x, --y))
    {
        moveBoulder(down);
        return false;
    }
    return true;
}

bool Boulders::bulletWillHarm()
{
    if(getHitPoints()>2)
        decrementHitPoints(2);
    else
        setDead();
    return true;
}

bool Boulders::canBePushed(int x, int y)
{
    
    //can only move if there is a space or a hole
    StudentWorld *stud= getWorld();
    Actor* ap= stud->getActor(x,y);
    Holes* hp=dynamic_cast<Holes*>(ap);
    
    if(ap==nullptr)
    {
        return true;
    }
    
    if(ap!=nullptr)
    {
        if(hp!=nullptr)
        {
            //hp->killHole(hp);
            return true;
        }
    }
    return false;
}

void Boulders::doSomething()
{
    
}

void Boulders::moveBoulder(Direction dir)
{
    int x= getX();
    int y= getY();
    
    
    if(dir==right)
    {
        
        moveTo(++x, y);
        return;
    }
    if(dir==left)
    {
        
        moveTo(--x, y);
        return;
    }
    if(dir==up)
    {
        moveTo(x, ++y);
        return;
    }
    if(dir==down)
    {
        moveTo(x, --y);
        return;
    }
}

/////////
//ITEMS//
////////
Items::Items(int imageID, int startX, int startY,Direction dir, StudentWorld *world, int startingHitPoints):Actor(imageID, startX, startY, dir, world, startingHitPoints)
{
    
}

//////////
//JEWELS//
/////////

Jewels::Jewels(int startX, int startY,StudentWorld *world):Items(IID_JEWEL, startX, startY, none, world, 0)
{
    setVisible(true);
}

void Jewels::doSomething()
{
    int x=getX();
    int y=getY();
    
    if(isDead())
        return;
    
    StudentWorld* stud=getWorld();
    Actor* ap=stud->getActor(x, y);
    Player* hp=dynamic_cast<Player*>(ap);
    
    if(ap!=nullptr)
        if(hp!=nullptr)
        {
            stud->decNumJewels();
            stud->increaseScore(50);
            setDead();
            stud->playSound(SOUND_GOT_GOODIE);
        }
}

///////////////////////
//EXTRA LIFE GOODIES//
/////////////////////

ExtraLifeGoodies::ExtraLifeGoodies(int startX, int startY,StudentWorld *world):Items(IID_EXTRA_LIFE, startX, startY, none, world, 0)
{
    setVisible(true);
}

void ExtraLifeGoodies::doSomething()
{
    int x=getX();
    int y=getY();
    
    if(isDead())
        return;
    
    StudentWorld* stud=getWorld();
    Actor* ap=stud->getActor(x, y);
    Player* hp=dynamic_cast<Player*>(ap);
    
    if(ap!=nullptr)
        if(hp!=nullptr)
        {
            stud->increaseScore(1000);
            setDead();
            stud->playSound(SOUND_GOT_GOODIE);
            stud->incLives();
        }
}
///////////////////////////
//RESTORE HEALTH GOODIES//
/////////////////////////


RestoreHealthGoodies::RestoreHealthGoodies(int startX, int startY,StudentWorld *world):Items(IID_RESTORE_HEALTH, startX, startY, none, world, 0)
{
    setVisible(true);
}

void RestoreHealthGoodies::doSomething()
{
    int x=getX();
    int y=getY();
    
    if(isDead())
        return;
    
    StudentWorld* stud=getWorld();
    Actor* ap=stud->getActor(x, y);
    Player* hp=dynamic_cast<Player*>(ap);
    
    if(ap!=nullptr)
        if(hp!=nullptr)
        {
            stud->increaseScore(500);
            hp->restoreHealth();
            setDead();
            stud->playSound(SOUND_GOT_GOODIE);
            while(getHitPoints()!=20)
                increaseHitPoints(1);
        }
}

////////////////
//AMMO GOODIES//
///////////////
AmmoGoodies::AmmoGoodies(int startX, int startY, StudentWorld* world): Items(IID_AMMO, startX, startY, none, world, 0)
{
    setVisible(true);
}

void AmmoGoodies::doSomething()
{
    int x=getX();
    int y=getY();
    
    if(isDead())
        return;
    
    StudentWorld* stud=getWorld();
    Actor* ap=stud->getActor(x, y);
    Player* hp=dynamic_cast<Player*>(ap);
    
    if(ap!=nullptr)
        if(hp!=nullptr)
        {
            stud->increaseScore(100);
            setDead();
            stud->playSound(SOUND_GOT_GOODIE);
            hp->increaseAmmo(20);
            
        }
}

////////
//EXIT//
///////
Exit::Exit(int startX, int startY, StudentWorld* world):Actor(IID_EXIT, startX, startY, none, world, 0)
{
    
}

void Exit::doSomething()
{
    int x=getX();
    int y=getY();
    
    StudentWorld* stud=getWorld();
    Actor* ap=stud->getActor(x,y);
    Player* hp=dynamic_cast<Player*>(ap);
    
    if(stud->numJewels()==0)
        setVisible(true);
    if(ap!=nullptr)
    {
        if(stud->numJewels()==0 && hp!=nullptr)
        {
            stud->playSound(SOUND_FINISHED_LEVEL);
            stud->increaseScore(2000);
            stud->setPlayerCompletedLevel();
            //do bonus point stuff
        }
    }
}