#include "Actor.h"
#include "StudentWorld.h"
using namespace std;
#include <iostream>

// Students:  Add code to this file (if you wish), Actor.h, StudentWorld.h, and StudentWorld.cpp

Actor::Actor(int imageID, int startX, int startY, Direction dir, StudentWorld* world):GraphObject(imageID, startX, startY, dir)
{
    m_actorworld=world;
    m_isDead=false;
}

////////////////////
//THINGSTHATSHOOT//
//////////////////



//ThingsThatShoot::ThingsThatShoot(int imageID, int startX, int startY, Direction dir, StudentWorld* world):Actor(imageID, startX, startY, dir, world)
//{
//    
//}

bool Actor::isDead()
{
    return m_isDead;
}

void Actor::setDead()
{
    m_isDead=true;
}

StudentWorld* Actor::getWorld() const
{
    return m_actorworld;
}


Player::Player(int startX, int startY, StudentWorld* world):Actor(IID_PLAYER, startX, startY, right, world)
{
  
    m_hitPoints=20;
    m_roundAmmunition=20;
    setVisible(true);
}


int Player::hitPoints(bool gotShot)
{
    if(gotShot==true)
       return (m_hitPoints-2);
    return m_hitPoints;
}

bool Player::gotHit(bool gotHit)
{
    return m_gotHit;
}


void Player::doSomething()
{
    int x=getX();
    int y=getY();
    Direction dir=this->getDirection ();

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
                    Actor* ap= stud->getActor(--x,y);
                    if(ap!=nullptr)
                    {
                        Wall *wp=dynamic_cast<Wall*>(ap);
                        if(wp!=nullptr)
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
                    Actor* ap= stud->getActor(++x,y);
                    if(ap!=nullptr)
                    {
                        Wall *wp=dynamic_cast<Wall*>(ap);
                        if(wp!=nullptr)
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
                    Actor* ap= stud->getActor(x,++y);
                    if(ap!=nullptr)
                    {
                        Wall *wp=dynamic_cast<Wall*>(ap);
                        if(wp!=nullptr)
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
                    Actor* ap= stud->getActor(x,--y);
                    if(ap!=nullptr)
                    {
                        Wall *wp=dynamic_cast<Wall*>(ap);
                        if(wp!=nullptr)
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

Wall::Wall(int startX, int startY, StudentWorld* world):Actor(IID_WALL, startX, startY, none, world)
{
    setVisible(true);
}

////////////
//BULLETS//
//////////

Bullets::Bullets(int startX, int startY, Direction dir, StudentWorld* world):Actor(IID_BULLET, startX, startY, dir, world)
{
    setVisible(true);
}

bool Bullets::willDamage(Actor* ap)
{
    Player* pp=dynamic_cast<Player*>(ap);
    Wall* wp=dynamic_cast<Wall*>(ap);
    if(pp!=nullptr)
    {
        pp->hitPoints(true);
        pp->gotHit(true);
        
        setDead();
        return true;
    }
    if(wp!=nullptr)
    {
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


