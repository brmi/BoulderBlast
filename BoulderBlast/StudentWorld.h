#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "GameConstants.h"
#include "Level.h"
#include "Actor.h"
#include <string>
#include <vector>
using namespace std;
// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

// contains your StudentWorld class declaration

class StudentWorld : public GameWorld
{
public:
    
//    StudentWorld(int col, int row, int playercol, int playerrow, int wallcol, int wallrow);
    
	StudentWorld(std::string assetDir)
	 : GameWorld(assetDir)
	{
        
	}
    
    
	virtual int init()
	{
        vector<Actor*> container; //container for my objects
        
        //////////////////////
        //load current level//
        /////////////////////
        
        string curLevel= "level00.dat";
        Level lev(assetDirectory());
        Level::LoadResult result = lev.loadLevel(curLevel);
        
        if(result==Level::load_fail_file_not_found || result==Level::load_fail_bad_format)
            return -1; //something bad happened
        
        //load was successfull, can access contents
        int x =0;
        int y=0;
        
        while(x<=15 && y<=15)
        {
            //getContentsOf(col,row)
            Level::MazeEntry item = lev.getContentsOf(x, y);
            if(item==Level::player)
            {
                cout<<!"The player should be placed at"<< x <<","<< y <<" in the maze\n";
                if(x<=15 && y<=15)
                {
                    x++;
                    int row=y;
                }
                else if(x>15 && y<=15)
                {
                    
                  y++;
                }
                continue;
            }
            else if(item==Level::wall)
                    cout<<!"There should be a wall at" << x <<"," <<y<<" in the maze\n";
            
            //can add rest of objects after you finish part 1

//            x = 10;
//            y=7;
//            item=lev.getContentsOf(x,y);
        }
        
        
		return GWSTATUS_CONTINUE_GAME;
	}

	virtual int move()
	{
		  // This code is here merely to allow the game to build, run, and terminate after hitting enter a few times 
		decLives();
		return GWSTATUS_PLAYER_DIED;
	}

	virtual void cleanUp()
	{
	}

private:
    int m_playercol;
    int m_playerrow;
    
    int m_wallcol;
    int m_wallrow;
    
    
};

#endif // STUDENTWORLD_H_
