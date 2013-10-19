#ifndef PLAYER_H
#define PLAYER_H
#define WIN32_LEAN_AND_MEAN

#include <cmath>

#include "entity.h"
#include "Laser.h"

#if defined(DEBUG) | defined(_DEBUG)
#include <sstream>

#include "textDX.h"
#endif

using std::atan;

namespace playerNS {
    const int HEIGHT = 74;                            // Height of the image
	const int WIDTH  = 102;                           // Width of the image
    const int X      = GAME_WIDTH / 2 - WIDTH / 2;    // X position of the image
    const int Y      = GAME_HEIGHT / 2 - HEIGHT / 2;  // Y position of the image
}

class Player : public Entity {
private : 
	#if defined(DEBUG) | defined(_DEBUG)
	TextDX* debugText;
	std::stringstream sin;
	#endif

	float degrees;

public : 
	#if defined(DEBUG) | defined(_DEBUG)
	bool initialize(Game *gamePtr, int width, int height, int ncols, TextureManager *textureM);
	void draw();
	#endif

	Player();
	
	void fire(Laser &laser);
	void update(int mouseX, int mouseY, float frameTime);
};

#endif