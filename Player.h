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
    const int X      = gladiatorNS::ARENA_START_X + gladiatorNS::ARENA_WIDTH/2 - gladiatorNS::DISTANCE_BETWEEN_ARENA_AND_ENEMY_WALLS_V;    // X position of the image
    const int Y      = gladiatorNS::ARENA_START_Y + gladiatorNS::ARENA_HEIGHT/2 - gladiatorNS::DISTANCE_BETWEEN_ARENA_AND_ENEMY_WALLS_H;  // Y position of the image
	const int TOTAL_LASERS = 100;
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
	int playerHealth;
	TextureManager turretTexture;
	Laser* lasers[playerNS::TOTAL_LASERS];

public : 
	Player();
	void setTurretActive(bool a) {turret.setActive(a);}
	void setTurretColor(COLOR_ARGB c) {turret.setColor(c);}
	int getHealth() {return playerHealth;}
	void reduceHealth(int hit) {playerHealth-=hit;}
	PlayerMirror getMirror() {return mirror;}
	PlayerTurret getTurret() {return turret;}
	Laser** getLasers() {return lasers;}
	void draw();
	void fire(Laser &laser);
	bool initialize(Game *gamePtr, int width, int height, int ncols, TextureManager *textureM);
	bool mirrorCollidesWith(Entity &ent, VECTOR2 &collisionVector);
	bool turretCollidesWith(Entity &ent, VECTOR2 &collisionVector);
	void update(int mouseX, int mouseY, float frameTime);
};

#endif