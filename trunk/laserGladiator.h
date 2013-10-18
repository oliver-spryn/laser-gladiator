#ifndef _LASERGLADIATOR_H             // Prevent multiple definitions if this 
#define _LASERGLADIATOR_H	          // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "game.h"
#include "textureManager.h"
#include "image.h"
#include "wall.h"
#include "LaserOld.h"
#include "Mirror.h"
#include "enemy.h"
#include <vector>
using std::vector;
#include <ctime>
#include <fstream>
using std::ofstream;

struct Position
{
	Position(float X, float Y) {x=X;y=Y;}
	float x, y;
};

//this is the laserGladiator class
class LaserGladiator : public Game
{
private:
	//game items
	TextureManager wallTexture, laserTexture, hWallTexture, mirrorTexture, enemyWallTexture, hEnemyWallTexture, enemyTexture;
	int numWalls;
	vector<Wall*> walls;
	int numMirrors;
	vector<Mirror*> mirrors;
	vector<Enemy*> enemies;
	vector<Laser*> lasers;
	vector<vector<Position>> mirrorPositions;
	int rows, columns;
	int playerScore;
	int numFrames;
	int activeEnemies;

public:
	ofstream debug;

	//constructor
	LaserGladiator();

	//destructor
	~LaserGladiator();

	// Initialize the game
    void initialize(HWND hwnd);
    void update();      // must override pure virtual from Game
    void ai();          // "
    void collisions();  // "
    void render();      // "
    void releaseAll();
    void resetAll();
	void endGamePlayerWins();
};

#endif