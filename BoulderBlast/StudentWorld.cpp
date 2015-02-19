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
        delete (*it); //come back...did you delete everything?
}

vector<Actor*> StudentWorld::getActor()
{
    return m_container;
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
        
        }else if(item==Level::empty || item!=Level::player || item!=Level::wall)
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
		  // This code is here merely to allow the game to build, run, and terminate after hitting enter a few times
    
    
    m_playerContainer->doSomething(); //brmi.
    
    decLives();
    return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::cleanUp()
{
    
}