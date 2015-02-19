#include "Actor.h"
#include "StudentWorld.h"



// Students:  Add code to this file (if you wish), Actor.h, StudentWorld.h, and StudentWorld.cpp

Actor::Actor(int imageID, int startX, int startY, Direction dir, GameWorld* world):GraphObject(imageID, startX, startY, none)
{
    m_actorworld=world;
    m_step=false;
}

GameWorld* Actor::world() const
{
    return m_actorworld;
}

Player::Player(int startX, int startY, GameWorld* world):Actor(IID_PLAYER, startX, startY, right, world)
{
    m_lives=3;
    m_hitPoints=20;
    m_roundAmmunition=20;
    setVisible(true);
}

void Player::doSomething()
{
    int x=getX();
    int y=getY();
    
    int ch;
    
    if(world()->getKey(ch))
    {
        switch(ch)
        {
            case KEY_PRESS_LEFT:
                if(x>0)
                {
                    if(getDirection()!=left)
                        setDirection(left);
                    moveTo(--x, y);
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
                    moveTo(++x, y);
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
                    moveTo(x, ++y);
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
                    moveTo(x, --y);
                }else
                {
                    if(getDirection()!=down)
                        setDirection(down);
                }
                break;
            case KEY_PRESS_ESCAPE:
                m_lives--;
            break;
            case KEY_PRESS_SPACE:
                m_roundAmmunition--;
                break;
                
        }
    }
    

}

Wall::Wall(int startX, int startY, GameWorld* world):Actor(IID_WALL, startX, startY, none, world)
{
    setVisible(true);
}


