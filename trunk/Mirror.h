#ifndef _MIRROR_H
#define _MIRROR_H

#include "entity.h"
#include "constants.h"

namespace mirrorNS
{
	const int WIDTH = 36;                   // image width
    const int HEIGHT = 36;               // image height
    const int X = GAME_WIDTH/2;   // location on screen
    const int Y = GAME_HEIGHT/2;
    const float SPEED = 0;                // 100 pixels per second
    const float MASS = 0;              // mass
    const int   TEXTURE_COLS = 1;           // texture has 2 columns
	const COLOR_ARGB CORNER_COLOR = graphicsNS::LIME;
	const float CORNER_RATIO = 0.7f;
}

class Mirror : public Entity
{
public:
	Mirror(COLOR_ARGB color = graphicsNS::WHITE);
	COLOR_ARGB getColor() {return mirrorColor;}
	void update(float frameTime);
private:
	COLOR_ARGB mirrorColor;
};

#endif