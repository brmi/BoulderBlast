#include "Actor.h"
#include "StudentWorld.h"
#include <iostream>
using namespace std;

// Students:  Add code to this file (if you wish), Actor.h, StudentWorld.h, and StudentWorld.cpp

Actor::Actor(int imageID, int startX, int startY, Direction dir):GraphObject(imageID, startX, startY, none){}

Player::Player(int startX, int startY):Actor(IID_PLAYER, startX, startY, right)
{
    m_hitPoints=20;
    m_roundAmmunition=20;
    setVisible(true);
}

void Player::doSomething()
{
    int x=getX(); //col
    int y=getY(); //row
    
    int key;
    
    cin>>key;
    
    if(key==KEY_PRESS_LEFT)
    {
        if(x>0)
        {
            if(getDirection()!=left)
                setDirection(left);
            moveTo(x--, y);
        }else
        {
            if(getDirection()!=left)
                setDirection(left);
        }
        return;
    }
    
    else if(key==KEY_PRESS_RIGHT)
    {
        if(x<14)
        {
            if(getDirection()!=right)
                setDirection(right);
            moveTo(x++, y);
        }else
        {
            if(getDirection()!=right)
                setDirection(right);
        }
    }
    else if(key==KEY_PRESS_UP)
    {
        if(y>0)
        {
            if(getDirection()!=up)
                setDirection(up);
            moveTo(x, y--);
        }else
        {
            if(getDirection()!=up)
                setDirection(up);
        }
    }
    else if(key==KEY_PRESS_DOWN)
    {
        if(y<14)
        {
            if(getDirection()!=up)
                setDirection(up);
            moveTo(x, y++);
        }else
        {
            if(getDirection()!=up)
                setDirection(up);
        }
    }
}

Wall::Wall(int startX, int startY):Actor(IID_WALL, startX, startY, none)
{
    setVisible(true);
}


