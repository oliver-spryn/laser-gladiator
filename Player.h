#ifndef PLAYER_H
#define PLAYER_H
#define WIN32_LEAN_AND_MEAN

#include <cmath>
#include "entity.h"
#include "gameError.h"
#include "Laser.h"
#include "PlayerMirror.h"
#include "PlayerTurret.h"
#include "TextureManager.h"

using std::atan2;
using std::cos;
using std::sin;

namespace playerNS {
    const int HEIGHT = 71;                            // Height of the image
	const int MASS   = 1;                             // The mass of the object
	const int WIDTH  = 71;                            // Width of the image
    const int X      = GAME_WIDTH / 2 - WIDTH / 2;    // X position of the image
    const int Y      = GAME_HEIGHT / 2 - HEIGHT / 2;  // Y position of the image
}

class Player : public Entity {
private : 
	PlayerMirror mirror;
	TextureManager mirrorTexture;
	int mirrorRadius;
	float radians;
	int trueCenterX;
	int trueCenterY;
	PlayerTurret turret;
	int turretRadius;
	TextureManager turretTexture;

public : 
	Player();
	
	void draw();
	void fire(Laser &laser);
	bool initialize(Game *gamePtr, int width, int height, int ncols, TextureManager *textureM);
	bool mirrorCollidesWith(Entity &ent, VECTOR2 &collisionVector);
	bool turretCollidesWith(Entity &ent, VECTOR2 &collisionVector);
	void update(int mouseX, int mouseY, float frameTime);
};

#endif