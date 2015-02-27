
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

bool Robots::robotShoot(int x, int y, GraphObject::Direction dir)
{
    StudentWorld* stud=getWorld();
    
    if(dir==right)
    {
        for(int i= x+1; i<=14; i++)
        {
            Actor* ap= stud->getActor(i, y);
            Player* pp= dynamic_cast<Player*>(ap);
            Boulders* bp=dynamic_cast<Boulders*>(ap);
            KleptoBots* kp=dynamic_cast<KleptoBots*>(ap);
            Wall* wp=dynamic_cast<Wall*>(ap);
            if(ap!=nullptr && pp!=nullptr)
            {
                stud->playSound(SOUND_ENEMY_FIRE);
                stud->makeBullet(x+1, y, right);
                resetTicks();
                
                return true;
            }
            else if(ap!=nullptr && (bp!=nullptr || kp!=nullptr || wp!=nullptr))
                break;
        }
        
        Actor* rp=stud->getActor(x+1, y);
        if(rp!=nullptr && rp->blocksRobots()==false)
        {
            moveTo(++x,y);
            resetTicks();
            return true;
        }
        else if(rp!=nullptr && rp->blocksRobots()) //if it's a wall or boulder or something
        {
            setDirection(left);
            resetTicks();
            return true;
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
            KleptoBots* kp=dynamic_cast<KleptoBots*>(qp);
            Wall* wp=dynamic_cast<Wall*>(qp);
            if(qp!=nullptr && pp!=nullptr)
            {
                stud->playSound(SOUND_ENEMY_FIRE);
                stud->makeBullet(x-1, y, left);
                resetTicks();
                return true;
            }else if(qp!=nullptr && (bp!=nullptr || kp!=nullptr || wp!=nullptr))
                break;
        }
        Actor* qp=stud->getActor(x-1, y);
        if(qp!=nullptr && qp->blocksRobots()==false)
        {
            moveTo(--x,y);
            resetTicks();
            return true;
        }else if(qp!=nullptr && qp->blocksRobots()) //if it's a wall or boulder or something
        {
            setDirection(right);
            resetTicks();
            return true;
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
            KleptoBots* kp=dynamic_cast<KleptoBots*>(zp);
             Wall* wp=dynamic_cast<Wall*>(zp);
            if(zp!= nullptr && pp!=nullptr)
            {
                stud->playSound(SOUND_ENEMY_FIRE);
                stud->makeBullet(x, y+1, up);
                resetTicks();
                return true;
            }
            else if(zp!=nullptr && (bp!=nullptr||kp!=nullptr || wp!=nullptr ))
                break;
        }
        Actor* zp= stud->getActor(x, y+1);
        if(zp!=nullptr && zp->blocksRobots()==false) //if nothing is blocking
        {
            moveTo(x,++y);
            resetTicks();
            return true;
        }else if(zp!=nullptr && zp->blocksRobots()) //if it's a wall or boulder or something
        {
            setDirection(down);
            resetTicks();
            return true;
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
            KleptoBots* kp=dynamic_cast<KleptoBots*>(fp);
             Wall* wp=dynamic_cast<Wall*>(fp);
            if(fp!=nullptr && pp!=nullptr)
            {
                stud->playSound(SOUND_ENEMY_FIRE);
                stud->makeBullet(x, y-1, down);
                resetTicks();
                return true;
            }else if(fp!=nullptr && (bp!=nullptr || kp!=nullptr || wp!=nullptr))
                break;
        }
        Actor* fp= stud->getActor(x, y-1);
        if(fp!=nullptr && fp->blocksRobots()==false)
        {
            moveTo(x, --y);
            resetTicks();
            return true;
        }else if(fp!=nullptr && fp->blocksRobots())
        {
            setDirection(up);
            resetTicks();
            return true;
        }else if(fp==nullptr)
            moveTo(x,--y);
    }
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
    
    decrementHitPoints(2);
    if(getHitPoints()<=0)
    {
        stud->playSound(SOUND_ROBOT_DIE);
        stud->increaseScore(100);
        setDead();
    }else
        stud->playSound(SOUND_ROBOT_IMPACT);
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

    GraphObject::Direction dir= getDirection();
        robotShoot(x, y, dir);
        resetTicks();
    }else
        return;    
}

//////////////
//FACTORIES//
////////////

Factories::Factories(int startX, int startY, StudentWorld* world, bool isNormal):Actor(IID_ROBOT_FACTORY,startX, startY, none, world, 0)
{
    setVisible(true);
    m_isNormal=isNormal;
}

void Factories::doSomething()
{
    int x=getX();
    int y=getY();
    int count=0;
    
    StudentWorld* stud=getWorld();
    
    for(int i=x-3; i<=6; i++) //left and right
    {
        for(int j=y-3; j<=6; j++)
        {
            Actor* ap= getWorld()-> getActor(i, j);
            KleptoBots* kb= dynamic_cast<KleptoBots*>(ap);
            if(ap!=nullptr && kb!=nullptr) //if there is a kleptobot on the square
            {
                count++;
            }
        }
    }
    
    Actor* ap= getWorld()-> getActor(getX(), getY());
    KleptoBots* klepto = dynamic_cast<KleptoBots*>(ap);
    if(ap!=nullptr && klepto!=nullptr) //if there is already a kleptobot on the factory
        return;

    if(count<3 && m_isNormal)
    {
        int r=rand()%50;
        if(r==1) //1 in 50 chance of this
        {
            stud->playSound(SOUND_ROBOT_BORN);
            stud->makeKlepto(x,y,right, true);
            return;
        }
    }
    else if(count<3 && !m_isNormal)
    {
        int r=rand()%50;
        if(r==1) //1 in 50 chance of this
        {
            stud->playSound(SOUND_ROBOT_BORN);
            stud->makeKlepto(x,y,right, false);
            return;
        }
    }
}


//////////////
//KLEPTOBOTS//
/////////////

KleptoBots::KleptoBots(int ImageID, int startX, int startY, Direction dir, StudentWorld* world, int hitPoints):Robots(ImageID, startX, startY, dir, world, hitPoints)
{
    m_distanceBeforeTurning=rand()% 6+1; //picks random number between 1 and 6
    setVisible(true);
}

void KleptoBots::decrementDistance()
{
    m_distanceBeforeTurning=m_distanceBeforeTurning-1;
}

bool KleptoBots::bulletWillHarm()
{
        decrementHitPoints(2);
        if(getHitPoints()<=0)
        {
            getWorld()->increaseScore(10); //10 for normal kleptobots
            getWorld()->playSound(SOUND_ROBOT_DIE);
            setDead();
        }
        else
            getWorld()->playSound(SOUND_ROBOT_IMPACT);
    return true;
}


void KleptoBots:: doSomething()
{
    if(isDead())
        return;

        int x=getX();
        int y=getY();
        
        StudentWorld *stud= getWorld();
        Actor* a= stud->getActor(x, y);
        Items* ip=dynamic_cast<Items*>(a);
        if(a!=nullptr && ip!=nullptr && ip->getX()==x && ip->getY()==y)
        {
            int r=rand()%10; //one in ten chance of picking up item
            if(r==4)
            {
                ip->setVisible(false); //make the item invisible
                ip->setPlayerCanPickUp(false);
                stud->playSound(SOUND_ROBOT_MUNCH);
                return;
            }
        }
    
    bool encounteredObstruction=false;
    
        if(m_distanceBeforeTurning>0)
        {
            m_distanceBeforeTurning--;
            if(getDirection()==right)
            {
                Actor* b=stud->getActor(x+1, y);
                if(b!=nullptr)
                {
                    if(b->blocksRobots()==false)
                {
                    moveTo(++x, y);
                    return;
                }else if(b==nullptr)
                {
                    moveTo(++x,y);
                    return;
                }
                    encounteredObstruction=true;
                }
            }
            if(getDirection()==left)
            {
                Actor* b=stud->getActor(x-1, y);
                    if(b!=nullptr)
                    {
                        if(b->blocksRobots()==false)
                    {
                        moveTo(--x, y);
                        return;
                    }else if(b==nullptr)
                    {
                        moveTo(--x,y);
                        return;
                    }
                        encounteredObstruction=true;
                }
            }
            if(getDirection()==up)
            {
                Actor* b=stud->getActor(x, y+1);
                if(b!=nullptr && b->blocksRobots()==false)
                {
                    moveTo(x, y);
                    return;
                }else if(b==nullptr)
                {
                    moveTo(x,y);
                    
                    return;
                }
                encounteredObstruction=true;
            }
            if(getDirection()==down)
            {
                Actor* b=stud->getActor(x, y-1);
                if(b!=nullptr && b->blocksRobots()==false)
                {
                    moveTo(x, y);
                    return;
                }else if(b==nullptr)
                {
                    moveTo(x,y);
                    return;
                }
                encounteredObstruction=true;
            }
             m_distanceBeforeTurning++;
        }
    
    if(m_distanceBeforeTurning<=0 || encounteredObstruction)
        {
            encounteredObstruction=false;
            m_distanceBeforeTurning=rand()% 6+1;
            
            int dirRand=rand()%4+1;
            
            GraphObject::Direction d;
            
            switch(dirRand)
            {
                case 1: {d= right; break;}
                case 2: {d= left; break;}
                case 3: {d= up; break;}
                default: {d= down; break;}
            }
            
            bool check1 =false;
            bool check2=false;
            bool check3=false;
            bool check4=false;
            bool check=(check1 && check2 && check3 && check4); //check to see if direction has been checked
            
            while(!check)
            {
              if(d==right)
                {
                    Actor* ap= getWorld()->getActor(x+1, y);
                    if(ap!=nullptr && ap->blocksRobots())
                    {
                        check1=true;
                        if(check2 == false)
                            d=left;
                        else if(check3==false)
                            d=up;
                        else if(check4==false)
                            d=down;
                        else
                            break;
                    }else
                    {
                        setDirection(right);
                        if(ap==nullptr || (ap!=nullptr && ap->blocksRobots()==false))
                        {
                            moveTo(x, y);
                            m_distanceBeforeTurning--;
                            return;
                        }
                    }
                }
                if(d==left)
                {
                    Actor* ap= getWorld()->getActor(x-1, y);
                    if(ap!=nullptr && ap->blocksRobots())
                    {
                        check2=true;
                        if(check1 == false)
                            d=right;
                        else if(check3==false)
                            d=up;
                        else if(check4==false)
                            d=down;
                        else
                            break;
                    }else
                    {
                        setDirection(left);
                        if(ap==nullptr || (ap!=nullptr && ap->blocksRobots()==false))
                        {
                            moveTo(x, y);
                            m_distanceBeforeTurning--;
                            return;
                        }
                    }
                }
                if(d==up)
                {
                    Actor* ap= getWorld()->getActor(x, y+1);
                    if(ap!=nullptr && ap->blocksRobots())
                    {
                        check3=true;
                        if(check2 == false)
                            d=left;
                        else if(check1==false)
                            d=right;
                        else if(check4==false)
                            d=down;
                        else
                            break;
                    }else
                    {
                        setDirection(up);
                        if(ap==nullptr || (ap!=nullptr && ap->blocksRobots()==false))
                        {
                            moveTo(x, y);
                            m_distanceBeforeTurning--;
                            return;
                        }
                    }
                }
                if(d==down)
                {
                    Actor* ap= getWorld()->getActor(x, y-1);
                    if(ap!=nullptr && ap->blocksRobots())
                    {
                        check4=true;
                        if(check2 == false)
                            d=left;
                        else if(check3==false)
                            d=up;
                        else if(check1==false)
                            d=right;
                        else
                            break;
                    }else
                    {
                        setDirection(down);
                        if(ap==nullptr || (a!=nullptr && ap->blocksRobots()==false))
                        {
                            moveTo(x, y);
                            m_distanceBeforeTurning--;
                            return;
                        }
                    }
                }
            }
            setDirection(d);
            return;
        }
}

///////////////////////
////NORMAL KLEPTOBOTS//
//////////////////////

NormalKleptoBots::NormalKleptoBots(int startX, int startY, Direction dir, StudentWorld* world, int hitPoints):KleptoBots(IID_KLEPTOBOT, startX, startY, right, world, 5)
{
    setVisible(true);
    
}

bool NormalKleptoBots::bulletWillHarm()
{
    decrementHitPoints(2);
    if(getHitPoints()<=0)
    {
        getWorld()->increaseScore(10); //10 for normal kleptobots
        getWorld()->playSound(SOUND_ROBOT_DIE);
        setDead();
    }
    else
        getWorld()->playSound(SOUND_ROBOT_IMPACT);
    return true;
}

void NormalKleptoBots::doSomething()
{
    if(getTicks()>0)
    {
        decrTicks();
        return;
    }else
    {
        resetTicks();
        KleptoBots::doSomething();
    }
  
}

///////////////////////
////ANGRY KLEPTOBOTS//
/////////////////////

AngryKleptoBots::AngryKleptoBots(int startX, int startY, Direction dir, StudentWorld* world, int hitPoints):KleptoBots(IID_ANGRY_KLEPTOBOT, startX, startY, right, world, 8)
{
    setVisible(true);
}

bool AngryKleptoBots::bulletWillHarm()
{
    decrementHitPoints(2);
    if(getHitPoints()<=0)
    {
        getWorld()->increaseScore(20); //10 for normal kleptobots
        getWorld()->playSound(SOUND_ROBOT_DIE);
        setDead();
    }
    else
        getWorld()->playSound(SOUND_ROBOT_IMPACT);
    return true; 
}

void AngryKleptoBots::doSomething()
{
    /*Otherwise, the Angry KleptoBot must determine whether it should fire its laser cannon: If the Player is in the same row or column as the Angry KleptoBot AND the Angry KleptoBot is currently facing the Player AND there are no obstacles (specifically, Walls, Boulders, robots, or robot factories) in the way, then the Angry KleptoBot will fire a bullet toward the Player and then do nothing more during the current tick.*/
    
    if(getTicks()>0)
    {
        decrTicks();
        return;
    }else
    {
        resetTicks();
        if(robotShoot(getX(), getY(), getDirection()))
            return;
        KleptoBots::doSomething();
    }
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
    
        decHealth();
        decrementHitPoints(2);
        if(getHitPoints()<=0)
        {
            stud->decLives();
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
                if(getAmmo()==0)
                    return;
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
        
        Actor* lp=stud->getActor(x,y);
        if(lp!=nullptr && lp->bulletWillHarm())
        {
            setDead();
            return;
        }
        moveTo(x,++y);
    }
    if(getDirection()==down)
    {
        
        Actor* lp=stud->getActor(x,y);
        if(lp!=nullptr && lp->bulletWillHarm())
        {
            setDead();
            return;
        }
        moveTo(x,--y);
    }
    if(getDirection()==right)
    {
        
        Actor* lp=stud->getActor(x,y);
        if(lp!=nullptr && lp->bulletWillHarm())
        {
            setDead();
            return;
        }
        moveTo(++x, y);
    }
    if(getDirection()==left)
    {
        
        Actor* lp=stud->getActor(x,y);
        if(lp!=nullptr && lp->bulletWillHarm())
        {
            setDead();
            return;
        }
        moveTo(--x, y);
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
    m_pickUp=true;
}
    
void Items::setPlayerCanPickUp(bool yesorno)
{
    m_pickUp=yesorno;
}

bool Items::playerCanPickUp()
{
    return m_pickUp;
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
        if(hp!=nullptr && playerCanPickUp())
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
        if(hp!=nullptr && playerCanPickUp())
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
        if(hp!=nullptr && playerCanPickUp())
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
        if(hp!=nullptr && playerCanPickUp())
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