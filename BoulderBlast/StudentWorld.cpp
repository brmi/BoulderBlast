#include "StudentWorld.h"
#include <string>
using namespace std;

GameWorld* createStudentWorld(string assetDir)
{
	return new StudentWorld(assetDir);
}

// Students:  Add code to this file (if you wish), StudentWorld.h, Actor.h and Actor.cpp
//StudentWorld::StudentWorld(int playercol, int playerrow, int wallcol, int wallrow):GameWorld(assetDirectory()), m_playercol(playercol), m_playerrow(playerrow), m_wallcol(wallcol), m_wallrow(wallrow)
//{
//    
//}

