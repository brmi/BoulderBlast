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
    m_hitPoints-=decreaseby;
}


StudentWorld* Actor::getWorld() const
{
    return m_actorworld;
}

//////////
//PLAYER//
//////////

Player::Player(int startX, int startY, StudentWorld* world):Actor(IID_PLAYER, startX, startY, right, world, 20)
{
  
    m_lives=3;
    m_ammo=20;
    setVisible(true);
}

int Player::getNumLives()
{
    return m_lives;
}

void Player::decrementLives()
{
    if(m_lives>0)
        m_lives--;
    else
        setDead();
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

bool Player::playerCantStep(Actor* ap, int x, int y, Direction dir)
{
    Boulders *bp= dynamic_cast<Boulders*>(ap);
    Wall *wp=dynamic_cast<Wall*>(ap);
    Holes *hp= dynamic_cast<Holes*>(ap);
    if(wp!=nullptr)
        return true;
    if(bp!=nullptr) //after this check to see if boulder can be pushed
    {
        if(dir==right && bp->canBePushed(++x, y, dir))
        {
            bp->moveBoulder(dir);
            return false;
        }else if(dir==left && bp->canBePushed(--x, y, dir))
        {
            bp->moveBoulder(dir);
            return false;
        }
        else if(dir==up && bp->canBePushed(x, ++y, dir))
        {
            bp->moveBoulder(dir);
            return false;
        }else if(dir==down && bp->canBePushed(x, --y, dir))
        {
            bp->moveBoulder(dir);
            return false;
        }
        return true;
    }
    
    if(hp!=nullptr)
        return true;
    return false;
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
                    
                    Actor* ap= stud->getActor(--x,y);
                    if(ap!=nullptr)
                    {
                        if(playerCantStep(ap, x, y, dir))
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
                        if(playerCantStep(ap, x, y, dir))
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
                        if(playerCantStep(ap, x, y, dir))
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
                        if(playerCantStep(ap, x, y, dir))
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
                ;
                break;
            case KEY_PRESS_SPACE:
                decrementAmmo();
                if(getDirection()==up)
                    getWorld()->makeBullet(x, ++y, dir);
                if(getDirection()==down)
                    getWorld()->makeBullet(x,--y, dir);
                if(getDirection()==right)
                    getWorld()->makeBullet(++x, y, dir);
                if(getDirection()==left)
                    getWorld()->makeBullet(--x, y, dir);
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

bool Bullets::willDamage(Actor* ap)
{
    Player* pp=dynamic_cast<Player*>(ap);
    Wall* wp=dynamic_cast<Wall*>(ap);
    Boulders* bp=dynamic_cast<Boulders*>(ap);
    if(pp!=nullptr)
    {
        if(pp->getNumLives()>0 && pp->getHitPoints()>2)
        {
            decrementHitPoints(2);
        }else
            pp->decrementLives();
        setDead();
        return true;
            
    }
    if(wp!=nullptr)
    {
        setDead();
        return true;
    }
    if(bp!=nullptr)
    {
        //do this
        if(bp->getHitPoints()>2)
        {
            bp->decrementHitPoints(2);
        }else
            bp->setDead();
        setDead();
        return true;
    }
    return false;
}

void Bullets::doSomething()
{
    
    if(isDead())
        return;
    
    int x=getX();
    int y=getY();
  
    StudentWorld *stud= getWorld();
    Actor* ap= stud->getActor(x,y);
    
    if(ap!=nullptr)
    {
        if(willDamage(ap)==true)
            return;
    }
    
    if(getDirection()==up)
    {
        moveTo(x,++y);
        Actor* lp=stud->getActor(x,y);
        if(willDamage(lp)==true)
            return;
    }
    if(getDirection()==down)
    {
        moveTo(x,--y);
        Actor* lp=stud->getActor(x,y);
        if(willDamage(lp)==true)
            return;
    }
    if(getDirection()==right)
    {
        moveTo(++x, y);
        Actor* lp=stud->getActor(x,y);
        if(willDamage(lp)==true)
            return;
    }
    if(getDirection()==left)
    {
        moveTo(--x, y);
        Actor* lp=stud->getActor(x,y);
        if(willDamage(lp)==true)
            return;
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
    if(isDead())
        return;
    
}


////////////
//BOULDER//
//////////

Boulders::Boulders(int startX, int startY, StudentWorld* world): Actor(IID_BOULDER, startX, startY, none, world, 10)
{
    setVisible(true);
}

bool Boulders::canBePushed(int x, int y, Direction dir)
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
            moveBoulder(dir);
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
    
    StudentWorld *stud= getWorld();
    
        if(dir==right)
        {
            Actor* ap= stud->getActor(++x,y);
            Holes* hp=dynamic_cast<Holes*>(ap);
            if(ap!=nullptr && hp!=nullptr) //if spot has hole, kill boulder
                setDead();
            moveTo(x, y);
            return;
        }
        if(dir==left)
        {
            Actor* ap= stud->getActor(--x,y);
            Holes* hp=dynamic_cast<Holes*>(ap);
            if(ap!=nullptr && hp!=nullptr) //if spot has hole, kill boulder
                setDead();
            moveTo(x, y);
            return;
        }
        if(dir==up)
        {
            Actor* ap= stud->getActor(x,++y);
            Holes* hp=dynamic_cast<Holes*>(ap);
            if(ap!=nullptr && hp!=nullptr) //if spot has hole, kill boulder
                setDead();
            moveTo(x, y);
            return;
        }
        if(dir==down)
        {
            Actor* ap= stud->getActor(x,--y);
            Holes* hp=dynamic_cast<Holes*>(ap);
            if(ap!=nullptr && hp!=nullptr) //if spot has hole, kill boulder
                setDead();
            moveTo(x, y);
            return;
        }
}


