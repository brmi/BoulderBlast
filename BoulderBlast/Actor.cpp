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
                    
                    //Actor* ap= stud->getActor(--x,y); //this gives me actor at specific location!
                    
                    //StudentWorld *stud= getWorld();
                    
                    vector<Actor*> ptr= stud->getActorContainer();
                    
                    vector<Actor*>::iterator itr;
                    
                    for(itr=ptr.begin(); itr!=ptr.end();)
                    {
                        
                        if((*itr)->getX() ==--x && (*itr)->getY()==y)
                        {
                            if((*itr)->blocksPlayer(*itr, dir))
                               return;
                        }
                        else
                            itr++;
                    }
                    moveTo(x,y);
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
                    vector<Actor*> ptr= stud->getActorContainer();
                    
                    vector<Actor*>::iterator itr;
                    
                    for(itr=ptr.begin(); itr!=ptr.end();)
                    {
                        
                        if((*itr)->getX() ==++x && (*itr)->getY()==y)
                        {
                            if((*itr)->blocksPlayer(*itr, dir))
                                return;
                        }
                        else
                            itr++;
                    }
                     moveTo(x,y);
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
                    vector<Actor*> ptr= stud->getActorContainer();
                    
                    vector<Actor*>::iterator itr;
                    
                    for(itr=ptr.begin(); itr!=ptr.end();)
                    {
                        
                        if((*itr)->getX() ==x && (*itr)->getY()==--y)
                        {
                            if((*itr)->blocksPlayer(*itr, dir))
                                return;
                        }
                        else
                            itr++;
                    }
                     moveTo(x,y);
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
                    vector<Actor*> ptr= stud->getActorContainer();
                    
                    vector<Actor*>::iterator itr;
                    
                    for(itr=ptr.begin(); itr!=ptr.end();)
                    {
                        
                        if((*itr)->getX() ==x && (*itr)->getY()==++y)
                        {
                            if((*itr)->blocksPlayer(*itr, dir))
                                return;
                        }
                        else
                            itr++;
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
    //Actor* ap= stud->getActor(x,y);
    
    vector<Actor*> ptr= stud->getActorContainer();
    
    vector<Actor*>::iterator itr;
    
    for(itr=ptr.begin(); itr!=ptr.end();)
    {
        
        if((*itr)->getX() ==x && (*itr)->getY()==y)
        {
            if((*itr)->bulletWillHarm(*itr))
            {
                setDead();
                return;
            }
        }
        else
            itr++;
    }
    
    
    if(getDirection()==up)
    {
        moveTo(x,++y);
        for(itr=ptr.begin(); itr!=ptr.end();)
        {
            
            if((*itr)->getX() ==x && (*itr)->getY()==y)
            {
                if((*itr)->bulletWillHarm(*itr))
                {
                    setDead();
                    return;
                }
            }
            else
                itr++;
        }
    }
    if(getDirection()==down)
    {
        moveTo(x,--y);
        for(itr=ptr.begin(); itr!=ptr.end();)
        {
            
            if((*itr)->getX() ==x && (*itr)->getY()==y)
            {
                if((*itr)->bulletWillHarm(*itr))
                {
                    setDead();
                    return;
                }
            }
            else
                itr++;
        }

    }
    if(getDirection()==right)
    {
        moveTo(++x, y);
        for(itr=ptr.begin(); itr!=ptr.end();)
        {
            
            if((*itr)->getX() ==x && (*itr)->getY()==y)
            {
                if((*itr)->bulletWillHarm(*itr))
                {
                    setDead();
                    return;
                }
            }
            else
                itr++;
        }

    }
    if(getDirection()==left)
    {
        moveTo(--x, y);
        for(itr=ptr.begin(); itr!=ptr.end();)
        {
            
            if((*itr)->getX() ==x && (*itr)->getY()==y)
            {
                if((*itr)->bulletWillHarm(*itr))
                {
                    setDead();
                    return;
                }
            }
            else
                itr++;
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
    
    vector<Actor*> ptr= stud->getActorContainer();
    
    vector<Actor*>::iterator itr;
    
    for(itr=ptr.begin(); itr!=ptr.end();)
    {
        
        if((*itr)->getX() ==x && (*itr)->getY()==y)
        {
            Boulders* bp= dynamic_cast<Boulders*>(*itr);
            if(bp!=nullptr)
            {
                setDead();
                bp->setDead();
            }
        }
        else
            itr++;
    }
    
    
    
//    if(bp!=nullptr)
//        cout<<"recognized";
   
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
    //Actor* ap= stud->getActor(x,y);
    
    
    //StudentWorld *stud= getWorld();
    
    vector<Actor*> ptr= stud->getActorContainer();
    
    vector<Actor*>::iterator itr;
    
    for(itr=ptr.begin(); itr!=ptr.end();)
    {
        
        if((*itr)->getX() ==x && (*itr)->getY()==y)
        {
            Holes* hp= dynamic_cast<Holes*>(*itr);
            if(hp!=nullptr)
            {
                return false;
            }
        }
        else
            itr++;
    }

    return true;
//    
//    //Holes* hp=dynamic_cast<Holes*>(ap);
//    
//    if(ap==nullptr)
//    {
//        return true;
//    }
//
//    if(ap!=nullptr)
//    {
//        if(hp!=nullptr)
//        {
//            //hp->killHole(hp);
//            return true;
//        }
//    }
//    return false;
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
//////////
//JEWELS//
/////////

Jewels::Jewels(int startX, int startY, StudentWorld* world):Actor(IID_JEWEL, startX, startY, none, world, 0)
{
    setVisible(true);
}

void Jewels::doSomething()
{
    if(isDead())
        return;
    
}

////////
//EXIT//
///////
Exit::Exit(int startX, int startY, StudentWorld* world):Actor(IID_EXIT, startX, startY, none, world, 0)
{
    
}

void Exit::doSomething()
{
    return;
}
