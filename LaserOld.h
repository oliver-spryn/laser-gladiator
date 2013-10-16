#ifndef _LASER_H
#define _LASER_H

#include "entity.h"
#include "constants.h"

namespace laserNS
{
	const int WIDTH = 10;                   // image width
    const int HEIGHT = 10;               // image height
    const int X = GAME_WIDTH/2;   // location on screen
    const int Y = GAME_HEIGHT/2;
    const float SPEED = 200;                // 100 pixels per second
    const float MASS = 0.0f;              // mass
    const int   TEXTURE_COLS = 1;           // texture has 2 columns
}

class Laser : public Entity
{
public:
	Laser();
	void update(float frameTime);
private:

};

#endif