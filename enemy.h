#include "entity.h"
#include "LaserOld.h"
#include "constants.h"

enum Direction {UP,DOWN,LEFT,RIGHT};

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

class Enemy : public Entity
{
public:
	Enemy();
	void blowUp();
	void update(float frameTime);
	Laser** getLasers() { return lasers; }
	void fireLaser();
	char getDirection() { return direction; }
	void setDirection(Direction x) {direction = x;}
	//use direction character to determine orientation instead of angle
private:
	Laser* lasers[3];
	float distanceMoved;
	char direction;
};