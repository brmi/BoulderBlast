#include "StudentWorld.h"
#include "Actor.h"
#include "Level.h"
#include <string>
using namespace std;

GameWorld* createStudentWorld(string assetDir)
{
	return new StudentWorld(assetDir);
}

// Students:  Add code to this file (if you wish), StudentWorld.h, Actor.h and Actor.cpp
StudentWorld::StudentWorld(std::string assetDir): GameWorld(assetDir)
{
    
}

StudentWorld::~StudentWorld()
{
    delete m_playerContainer;
    
    vector<Actor*>::iterator it;
    
    for(it=m_container.begin(); it!=m_container.end(); it++)
    {
        
        it=m_container.erase(it);
        delete (*it); //delete Actor
    }
}

vector<Actor*> StudentWorld::getActorContainer()
{
    return m_container;
}

Actor* StudentWorld::getActor(int x, int y)
{
    vector<Actor*> ptr = getActorContainer();
    vector<Actor*>::iterator itr;
    for(itr=ptr.begin(); itr!=ptr.end();)
    {
    
        if((*itr)->getX() ==x && (*itr)->getY()==y)
            return (*itr);
        else
            itr++;
    }
    return nullptr;
}

bool StudentWorld::playerDied()
{
    int lives= getLives();
    if(lives<=0)
        return true;
    return false;
}

bool StudentWorld::playerCompletedLevel()
{
    if(getLevel()==3) //fix this later lol... basically set equal to last level
        return true;
    return false;
}

void StudentWorld::removeDeadGameObjects()
{
    if(playerDied())
        delete m_playerContainer;
    
    vector<Actor*>::iterator itr;
    for(itr=m_container.begin(); itr!=m_container.end(); itr++)
    {
        if((*itr)->isDead()==true)
        {
            delete *itr;
            m_container.erase(itr);
            itr--;
            
        }
    }
    
}

void StudentWorld::makeBullet(int x, int y, GraphObject::Direction dir)
{
    
    m_container.push_back(new Bullets(x,y,dir, this));
    
}

int StudentWorld::init()
{
    
    
    //////////////////////
    //load current level//
    /////////////////////
    
    string curLevel= "level00.dat";
    Level lev(assetDirectory());
    Level::LoadResult result = lev.loadLevel(curLevel);
    
    if(result==Level::load_fail_file_not_found || result==Level::load_fail_bad_format)
        return -1; //something bad happened
    
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
           
        } else if(item==Level::jewel)
        {
            m_container.push_back(new Jewels(x,y,this));
            x++;
            if(x==15 && y<15)
            {
                y++;
                x=0;
            }
            continue;
        }else if(item==Level::empty || item!=Level::player || item!=Level::wall|| item!=Level::boulder || item!=Level::hole)
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
    if(m_playerContainer->isDead()==false)
    {
        m_playerContainer->doSomething();
        
        if(playerDied())
            return GWSTATUS_PLAYER_DIED;
        
        if(playerCompletedLevel())
            return GWSTATUS_FINISHED_LEVEL;
    }else
        return GWSTATUS_PLAYER_DIED;
    
    vector<Actor*>::iterator itr;
    for(itr=m_container.begin(); itr!=m_container.end(); itr++)
    {
        if((*itr)->isDead()==false)
        {
            (*itr)->doSomething();
        
            if(playerDied())
                return GWSTATUS_PLAYER_DIED;
        
            if(playerCompletedLevel())
                return GWSTATUS_FINISHED_LEVEL;
        }
        
    }
    
    removeDeadGameObjects();
    
    
    

    
    return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::cleanUp()
{
    delete m_playerContainer;
    
    vector<Actor*>::iterator it;
   
    for(it=m_container.begin(); it!=m_container.end(); it++)
    {
        
        it=m_container.erase(it);
        delete (*it); //delete Actor
    }
}