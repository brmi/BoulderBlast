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
    
    vector<Actor*>::iterator it;
    
    for(it=m_container.begin(); it!=m_container.end();)
    {
        delete (*it); //delete Actor
        it=m_container.erase(it);
    }
}

string StudentWorld::levelAsFileName()
{
    int i=getLevel();
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

vector<Actor*>* StudentWorld::getActorContainer()
{
    vector<Actor*> *ptr =&m_container;
    return ptr;
}

Player* StudentWorld::getPlayer()
{
    return m_playerContainer;
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
    
    Actor* playa=getPlayer();
    if(playa!=nullptr)
    {
        if(playa->getX()==x && playa->getY()==y)
            return playa;
    }
    
    vector<Actor*>* ptr = getActorContainer();
    vector<Actor*>::iterator itr;
    for(itr=(*ptr).begin(); itr!=(*ptr).end();itr++)
    {
        
        if((*itr)->getX() ==x && (*itr)->getY()==y)
        {
            Boulders* bp = dynamic_cast<Boulders*>(*itr); //return boulder highest precedence
            Wall* wp=dynamic_cast<Wall*>(*itr);
            SnarlBots* sp=dynamic_cast<SnarlBots*>(*itr);
            Items* ip= dynamic_cast<Items*>(*itr);
            NormalKleptoBots* kp= dynamic_cast<NormalKleptoBots*>(*itr);
            AngryKleptoBots* ang= dynamic_cast<AngryKleptoBots*>(*itr);
            if(bp!=nullptr)
                return (*itr);
            else if(wp!=nullptr)
                return (*itr);
            else if(sp!=nullptr)
                return (*itr);
            else if(kp!=nullptr)
                return (*itr);
            else if(ip!=nullptr)
                return (*itr);
            else if(ang!=nullptr)
                return(*itr);
            else
                actr=(*itr);
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
    
    vector<Actor*>::iterator itr;
    for(itr=m_container.begin(); itr!=m_container.end(); itr++)
    {
        if((*itr)!=nullptr && (*itr)->isDead()==true)
        {
            delete *itr;
            itr=m_container.erase(itr);
            itr--;
        
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
        cout<<"normal "<<m_container.size()<<endl;
        m_container.push_back(new NormalKleptoBots(x,y, dir, this, 5));
        cout<<m_container.size()<<endl<<endl;
        return;
    }
    else
    {
        cout<<"angry "<<m_container.size()<<endl;
        m_container.push_back(new AngryKleptoBots(x,y,dir, this, 8));
        cout<<m_container.size()<<endl;
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
    
    vector<Actor*>::iterator itr;
    for(itr=m_container.begin(); itr!=m_container.end(); itr++)
    {
        if((*itr)!=nullptr && (*itr)->isDead()==false)
        {
            (*itr)->doSomething();
            
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
    
    removeDeadGameObjects();

    return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::cleanUp()
{
    delete m_playerContainer;
    
    vector<Actor*>::iterator it;
    
    for(it=m_container.begin(); it!=m_container.end();)
    {
        delete (*it); //delete Actor
        it=m_container.erase(it);
    }
}