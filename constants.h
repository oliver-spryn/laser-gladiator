// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Chapter 6 constants.h v1.0

#ifndef _CONSTANTS_H            // Prevent multiple definitions if this 
#define _CONSTANTS_H            // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include <windows.h>

//-----------------------------------------------
// Useful macros
//-----------------------------------------------
// Safely delete pointer referenced item
#define SAFE_DELETE(ptr)       { if (ptr) { delete (ptr); (ptr)=NULL; } }
// Safely release pointer referenced item
#define SAFE_RELEASE(ptr)      { if(ptr) { (ptr)->Release(); (ptr)=NULL; } }
// Safely delete pointer referenced array
#define SAFE_DELETE_ARRAY(ptr) { if(ptr) { delete [](ptr); (ptr)=NULL; } }
// Safely call onLostDevice
#define SAFE_ON_LOST_DEVICE(ptr)    { if(ptr) { ptr->onLostDevice(); } }
// Safely call onResetDevice
#define SAFE_ON_RESET_DEVICE(ptr)   { if(ptr) { ptr->onResetDevice(); } }
#define TRANSCOLOR  SETCOLOR_ARGB(0,255,0,255)  // transparent color (magenta)

//-----------------------------------------------
//                  Constants
//-----------------------------------------------
// graphic images
const char LASER_IMAGE[] = "source\\pictures\\laser.jpg";
const char TURRET[] = "source\\pictures\\turret.png";
const char TURRET_RING[] = "source\\pictures\\ring.png";
const char TURRET_MIRROR[] = "source\\pictures\\turret-mirror.png";
const char WALL_IMAGE[] = "pictures\\wall.png";	//wall
const char WALL_IMAGE_HORIZONTAL[] = "pictures\\hwall.png";//horizontal wall
const char MIRROR_IMAGE[] = "pictures\\mirror.jpg";
const char ENEMY_WALL_IMAGE[] = "pictures\\enemyWall.png";
const char ENEMY_IMAGE[] = "pictures\\enemy.jpg";
const char ENEMY_WALL_IMAGE_HORIZONTAL[] = "pictures\\hEnemyWall.png";
const char HEALTH_IMAGE[] = "pictures\\HealthText.png";

// window
const char CLASS_NAME[] = "LaserGladiator";
const char GAME_TITLE[] = "Laser Gladiator";
const bool FULLSCREEN = false;              // windowed or fullscreen
const UINT GAME_WIDTH =  640;               // width of game in pixels
const UINT GAME_HEIGHT = 480;               // height of game in pixels

// game
const double PI = 3.14159265;
const float FRAME_RATE = 200.0f;                // the target frame rate (frames/sec)
const float MIN_FRAME_RATE = 10.0f;             // the minimum frame rate
const float MIN_FRAME_TIME = 1.0f/FRAME_RATE;   // minimum desired time for 1 frame
const float MAX_FRAME_TIME = 1.0f/MIN_FRAME_RATE; // maximum time used in calculations
const float GRAVITY = 6.67428e-11f;             // gravitational constant

// key mappings
// In this game simple constants are used for key mappings. If variables were used
// it would be possible to save and restore key mappings from a data file.
const UCHAR ESC_KEY      = VK_ESCAPE;       // escape key
const UCHAR ALT_KEY      = VK_MENU;         // Alt key
const UCHAR ENTER_KEY    = VK_RETURN;       // Enter key

namespace enemyNS
{
	const int WIDTH = 25;            
    const int HEIGHT = 31;           
    const int X = GAME_WIDTH/4;   
    const int Y = GAME_HEIGHT/4;
    const float SPEED = 80;    
    const float MASS = 0.0f;    
    const int   TEXTURE_COLS = 1;
	const int	TOTAL_LASERS=3;
}

namespace gladiatorNS
{
	const int COLLISIONS_PER_LASER = 20;
	const int ARENA_HEIGHT = 400;
	const int ARENA_WIDTH = 600;
	const int WALL_WIDTH = 4;
	const int ARENA_START_X = 20;
	const int ARENA_START_Y = 60;
	const int ENEMY_WALL_GAP_SIZE = 20;
	//for horizontal enemy walls
	const int DISTANCE_BETWEEN_ARENA_AND_ENEMY_WALLS_H = enemyNS::HEIGHT + enemyNS::HEIGHT/2;
	//for verticle enemy walls
	const int DISTANCE_BETWEEN_ARENA_AND_ENEMY_WALLS_V = 2*enemyNS::WIDTH;
	const float MIRROR_SIZE = 0.75;
	const int NUM_HEALTH_BARS = 10;
}


#endif
