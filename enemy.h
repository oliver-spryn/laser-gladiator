#include "entity.h"
#include "LaserOld.h"
#include "constants.h"

enum Direction {UP,DOWN,LEFT,RIGHT};

class Enemy : public Entity
{
public:
	Enemy(Direction direction = UP);
	void blowUp();
	void update(float frameTime);
	Laser** getLasers() { return lasers; }
	void fireLaser();
	char getDirection() { return direction; }
	void setDirection(Direction x) {direction = x;}
	//use direction character to determine orientation instead of angle
private:
	int distanceToTravel;
	Laser* lasers[3];
	float distanceMoved;
	Direction direction;
};