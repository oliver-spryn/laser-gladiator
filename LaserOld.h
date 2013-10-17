#ifndef _LASER_H
#define _LASER_H

#include "entity.h"
#include "constants.h"

namespace laserNS
{
	const int WIDTH = 4;                   // image width
    const int HEIGHT = 4;               // image height
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
	int getCollisions() {return collisions;}
	void loseEnergy();
	void increaseCollisions() {collisions++;}
private:
	int collisions;
};

#endif