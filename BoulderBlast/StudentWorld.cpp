#include "StudentWorld.h"
#include "Actor.h"
#include "Level.h"
#include <string>

#include <iostream>
#include <sstream>
#include <iomanip>
using namespace std;

GameWorld* createStudentWorld(string assetDir)
{
    return new StudentWorld(assetDir);
}

StudentWorld::StudentWorld(std::string assetDir): GameWorld(assetDir)
{
    m_numJewels=0;
    m_playerCompletedLvl=false;
    m_bonus=1000;
}

string StudentWorld::format(int score, int level, int lives, int health, int ammo, unsigned int bonus)
{
    ostringstream oss;
    
    oss.fill('0');
    
    oss << "Score: " << setw(7)<< score << "  Level: "<< setw(2)<< level;
    
    oss.fill(' ');
    oss << "  Lives: "<< setw(2)<<lives<<"  Health: "<< setw(3)<<health<<"%"<<"  Ammo: "<<setw(3)<<ammo<<"  Bonus: " << setw(4)<<bonus;
    
    string s = oss.str();
  
    return s;
}

StudentWorld::~StudentWorld()
{
    delete m_playerContainer;
    
    for(int i=0; i<m_container.size();)
    {
        delete m_container[i]; //delete Actor
        m_container.erase(m_container.begin());
    }
}

string StudentWorld::levelAsFileName()
{
    int i=1;
    //int i=getLevel();
    if(i<10)
    {
        ostringstream oss;
        oss << "level"<<0<<i<<".dat";
        string s = oss.str();
        return s;
    }
    
    ostringstream oss;
    oss << "level"<< i<<".dat";
    string s = oss.str();
    
      return s;
}

void StudentWorld::resetBonus()
{
    m_bonus=1000;
}

void StudentWorld::setBonus()
{
    if(m_bonus==0)
        return;
    else
        m_bonus-=1;
}

void StudentWorld::updateDisplayText()
{
    
}

void StudentWorld::setDisplayText()
{
    int score=getScore();
    int level=getLevel();
    unsigned int bonus = m_bonus;
    int lives=getLives();
    int health=m_playerContainer->getHealth();
    int ammo=m_playerContainer->getAmmo();

    string s = format(score, level, lives, health, ammo, bonus);

    setGameStatText(s);
}

int StudentWorld::numJewels()
{
    return m_numJewels;
}

void StudentWorld::decNumJewels()
{
    m_numJewels-=1;
}

Actor* StudentWorld::getActor(int x, int y)
{
    Actor* actr=nullptr;
    
    Actor* playa=m_playerContainer;
    if(playa!=nullptr)
    {
        if(playa->getX()==x && playa->getY()==y)
            return playa;
    }
    

    for(int i=0; i<m_container.size();i++)
    {
        
        if((m_container[i])->getX() ==x && (m_container[i])->getY()==y)
        {
            Boulders* bp = dynamic_cast<Boulders*>(m_container[i]); //return boulder highest precedence
            Wall* wp=dynamic_cast<Wall*>(m_container[i]);
            SnarlBots* sp=dynamic_cast<SnarlBots*>(m_container[i]);
            Items* ip= dynamic_cast<Items*>(m_container[i]);
            NormalKleptoBots* kp= dynamic_cast<NormalKleptoBots*>(m_container[i]);
            AngryKleptoBots* ang= dynamic_cast<AngryKleptoBots*>(m_container[i]);
            if(bp!=nullptr)
                return (m_container[i]);
            else if(wp!=nullptr)
                return (m_container[i]);
            else if(sp!=nullptr)
                return (m_container[i]);
            else if(kp!=nullptr)
                return (m_container[i]);
            else if(ip!=nullptr)
                return (m_container[i]);
            else if(ang!=nullptr)
                return(m_container[i]);
            else
                actr=(m_container[i]);
        }
    }
    return actr; //this will return the actual actor
}

bool StudentWorld::playerDied()
{
    return m_playerContainer->isDead();
}

void StudentWorld::setPlayerCompletedLevel()
{
    m_playerCompletedLvl=true;
}

bool StudentWorld::playerCompletedLevel()
{
    return m_playerCompletedLvl;
}

void StudentWorld::removeDeadGameObjects()
{
    if(m_playerContainer->isDead()==true)
        delete m_playerContainer;
    
    for(int i=0; i<m_container.size(); i++)
    {
        if(m_container[i]->isDead()==true)
        {
            delete m_container[i];
            m_container.erase(m_container.begin()+i);
            i--;
        }
    }
}

void StudentWorld::makeBullet(int x, int y, GraphObject::Direction dir)
{
    m_container.push_back(new Bullets(x,y,dir, this));
}

void StudentWorld::makeKlepto(int x, int y,GraphObject::Direction dir, bool isNormal)
{
    if(isNormal)
    {
        m_container.push_back(new NormalKleptoBots(x,y, dir, this, 5));
        return;
    }
    else
    {
        m_container.push_back(new AngryKleptoBots(x,y,dir, this, 8));
        return;
    }
}

void StudentWorld::makeItems(string typeGoodie, int x, int y)
{
    if(typeGoodie=="restore")
    {
        m_container.push_back(new RestoreHealthGoodies(x,y,this));
        return;
    }
    if(typeGoodie=="extra")
    {
        m_container.push_back(new ExtraLifeGoodies(x,y,this));
        return;
    }
    if(typeGoodie=="ammo")
    {
        m_container.push_back(new AmmoGoodies(x,y,this));
        return;
    }
}

int StudentWorld::init()
{
    srand(static_cast<unsigned int>(time(nullptr)));
    m_playerCompletedLvl=false;
    
    //////////////////////
    //load current level//
    /////////////////////
    
    string curLevel= levelAsFileName();
    Level lev(assetDirectory());
    Level::LoadResult result = lev.loadLevel(curLevel);
    
    if(result==Level::load_fail_file_not_found || result==Level::load_fail_bad_format)
        return GWSTATUS_LEVEL_ERROR; //something bad happened
    
    //load was successful, can access contents
    
    int x =0;
    int y=0;
    
    while(x<=15 && y<=15) //maybe replace this with constants later
    {
        //getContentsOf(col,row)
        Level::MazeEntry item = lev.getContentsOf(x, y);
        if(item==Level::player)
        {
            m_playerContainer= new Player(x, y, this);
            x++;
            if(x==15 && y<15)
            {
                y++;
                x=0;
            }
            continue;
        }else if(item==Level::wall)
        {
            m_container.push_back(new Wall(x,y, this));
            x++;
            if(x==15 && y<15)
            {
                y++;
                x=0;
            }
            continue;
            
        }else if(item==Level::boulder)
        {
            m_container.push_back(new Boulders(x,y,this));
            x++;
            if(x==15 && y<15)
            {
                y++;
                x=0;
            }
            continue;
            
        }else if(item==Level::hole)
        {
            m_container.push_back(new Holes(x,y,this));
            x++;
            if(x==15 && y<15)
            {
                y++;
                x=0;
            }
            continue;
            
        }else if(item==Level::jewel)
        {
            m_numJewels++;
            m_container.push_back(new Jewels(x,y,this));
            x++;
            if(x==15 && y<15)
            {
                y++;
                x=0;
            }
            continue;
        }else if(item==Level::extra_life)
        {
            m_container.push_back(new ExtraLifeGoodies(x,y,this));
            x++;
            if(x==15 && y<15)
            {
                y++;
                x=0;
            }
            continue;
        }else if(item==Level::exit)
        {
            m_container.push_back(new Exit(x,y,this));
            x++;
            if(x==15 && y<15)
            {
                y++;
                x=0;
            }
            continue;
        }else if(item==Level::restore_health)
        {
            m_container.push_back(new RestoreHealthGoodies(x,y,this));
            x++;
            if(x==15 && y<15)
            {
                y++;
                x=0;
            }
            continue;
        }else if(item==Level::ammo)
        {
            m_container.push_back(new AmmoGoodies(x,y,this));
            x++;
            if(x==15 && y<15)
            {
                y++;
                x=0;
            }
            continue;
        }else if(item==Level::horiz_snarlbot)
        {
            m_container.push_back(new SnarlBots(x,y, GraphObject::right, this));
            x++;
            if(x==15 && y<15)
            {
                y++;
                x=0;
            }
            continue;
        }else if(item==Level::vert_snarlbot)
        {
            
            m_container.push_back(new SnarlBots(x,y, GraphObject::down, this));
            x++;
            if(x==15 && y<15)
            {
                y++;
                x=0;
            }
            continue;
        }else if(item==Level::angry_kleptobot_factory)
        {
            m_container.push_back(new Factories(x,y, this, false));
            x++;
            if(x==15 && y<15)
            {
                y++;
                x=0;
            }
            continue;
        }else if(item==Level::kleptobot_factory)
        {
            m_container.push_back(new Factories(x,y, this, true));
            x++;
            if(x==15 && y<15)
            {
                y++;
                x=0;
            }
            continue;
        }
        else
        {
            x++;
            if(x==15 && y<15)
            {
                y++;
                x=0;
            }
            continue;
        }
    }
    return GWSTATUS_CONTINUE_GAME;
}


int StudentWorld:: move()
{
    setDisplayText();
    setBonus();
    
    if(m_playerContainer->isDead()==false)
    {
        m_playerContainer->doSomething();
        
        if(playerDied())
        {
            resetBonus();
            return GWSTATUS_PLAYER_DIED;
        }
        
        if(playerCompletedLevel())
            return GWSTATUS_FINISHED_LEVEL;
    }else
    {
        resetBonus();
        return GWSTATUS_PLAYER_DIED;
    }
    
    for(int i=0; i<m_container.size(); i++)
    {
        if(m_container[i]->isDead()==false)
        {
            m_container[i]->doSomething();
            
            if(playerDied())
                return GWSTATUS_PLAYER_DIED;
            
            if(playerCompletedLevel())
            {
                increaseScore(m_bonus);
                m_bonus=1000;
                return GWSTATUS_FINISHED_LEVEL;
            }
        }
    }
    removeDeadGameObjects();

    return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::cleanUp()
{
    delete m_playerContainer;
    
    for(int i=0; i<m_container.size();)
    {
        delete m_container[i]; //delete Actor
        m_container.erase(m_container.begin());
    }
}