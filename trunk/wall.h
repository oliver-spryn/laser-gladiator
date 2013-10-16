#ifndef _WALL_H             // Prevent multiple definitions if this 
#define _WALL_H             // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"

namespace wallNS
{
    const float SPEED = 0;                // 100 pixels per second
    const float MASS = 300.0f;              // mass
    const int   TEXTURE_COLS = 4;           // texture has 2 columns
    const int   WALL_START_FRAME = 0;       // ship starts at frame 0
    const int   WALL_END_FRAME = 2;         // ship animation frames 0,1,2
    const float WALL_ANIMATION_DELAY = 0.3f; // time between frames
}

class Wall : public Entity
{
	int height;
	int width;
	int x, y;
public:
	Wall(int height, int width);

	void update(float frameTime);
};

#endif