#ifndef TESTGAME_H
#define TESTGAME_H
#define WIN32_LEAN_AND_MEAN

#include "constants.h"
#include "Explode.h"
#include "game.h"
#include "gameError.h"
#include "Laser.h"
#include "Player.h"
#include "textureManager.h"

class TestGame : public Game {
private : 
	Explode* e;
	TextureManager laserTexture;
	TextureManager playerTexture;
	Laser laser;
	Player player;

public : 
	TestGame();
	virtual ~TestGame();

	void ai();
	void collisions();
	void initialize(HWND hwnd);
	void releaseAll();
	void render();
	void resetAll();
	void update();
};

#endif