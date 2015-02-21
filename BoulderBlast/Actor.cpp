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
    m_pushedBoulder=false;
}


bool Actor::pushedBoulder()
{
    return m_pushedBoulder;
}

void Actor::setPushedBoulder()
{
    m_pushedBoulder=true;
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


bool Player::bulletWillHarm(Actor* a)
{
    if(getNumLives()>0 && getHitPoints()>2)
    {
        decrementHitPoints(2);
        if(getHitPoints()<0)
            decrementLives();
    }
    return true;
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
                    if(pushedBoulder())
                    moveTo(--x, y);
                    else
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
        if(ap->bulletWillHarm(ap))
        {
            setDead();
            return;
        }
    }
    
    if(getDirection()==up)
    {
        moveTo(x,++y);
        Actor* lp=stud->getActor(x,y);
        if(lp->bulletWillHarm(lp))
        {
            setDead();
            return;
        }
    }
    if(getDirection()==down)
    {
        moveTo(x,--y);
        Actor* lp=stud->getActor(x,y);
        if(lp->bulletWillHarm(lp))
        {
            setDead();
            return;
        }
    }
    if(getDirection()==right)
    {
        moveTo(++x, y);
        Actor* lp=stud->getActor(x,y);
        if(lp->bulletWillHarm(lp))
        {
            setDead();
            return;
        }
    }
    if(getDirection()==left)
    {
        moveTo(--x, y);
        Actor* lp=stud->getActor(x,y);
        if(lp->bulletWillHarm(lp))
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
    
    if(bp!=nullptr)
        cout<<"recognized";
    
    if(ap!=nullptr && bp!=nullptr) //if spot has boulder, kill boulder and hole
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
       a->setPushedBoulder();
       moveBoulder(right);
       return true;
   }else if(dir==left && canBePushed(--x, y))
   {
       a->setPushedBoulder();
       moveBoulder(left);
       return true;
   }else if(dir==up && canBePushed(x, ++y))
   {
       a->setPushedBoulder();
       moveBoulder(up);
       return true;
   }else if(dir==down && canBePushed(x, --y))
   {
       a->setPushedBoulder();
       moveBoulder(down);
       return true;
   }
    
    return false;
}

bool Boulders::bulletWillHarm(Actor* a)
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


