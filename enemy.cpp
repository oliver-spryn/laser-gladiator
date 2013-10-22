#include "enemy.h"

Enemy::Enemy(Direction direction)
{
	numHits = 0;
	aValue = 255;
	this->direction = direction;
	spriteData.width = enemyNS::WIDTH;           // size of enemy
    spriteData.height = enemyNS::HEIGHT;
    spriteData.x = enemyNS::X;                   // location on screen
    spriteData.y = enemyNS::Y;
    spriteData.rect.bottom = enemyNS::HEIGHT;    // rectangle to select parts of an image
    spriteData.rect.right = enemyNS::WIDTH;
    velocity.x = 0;                             // velocity X
    velocity.y = 0;                             // velocity Y
    currentFrame = startFrame;
    radius = enemyNS::WIDTH/2.0;
    collisionType = entityNS::ROTATED_BOX;
	edge.left = (enemyNS::WIDTH/2)*-1;
	edge.right = enemyNS::WIDTH/2;
	edge.top = (enemyNS::HEIGHT/2)*-1;
	edge.bottom = (enemyNS::HEIGHT/2);
	spriteData.angle = 0;
	mass = enemyNS::MASS;
	distanceMoved = 0;
	for(int i = 0; i < enemyNS::TOTAL_LASERS; i++)
	{
		lasers[i] = new Laser();
		lasers[i]->setEnemyLaser(true);
	}
	distanceToTravel = (direction == LEFT||direction == RIGHT)?gladiatorNS::ARENA_HEIGHT-gladiatorNS::DISTANCE_BETWEEN_ARENA_AND_ENEMY_WALLS_H*2 - enemyNS::WIDTH*2:
		gladiatorNS::ARENA_WIDTH-gladiatorNS::DISTANCE_BETWEEN_ARENA_AND_ENEMY_WALLS_V*2 - gladiatorNS::ENEMY_WALL_GAP_SIZE * 2 - enemyNS::HEIGHT*2;
}

void Enemy::update(float frameTime)
{
	Entity::update(frameTime);
	float oldX = spriteData.x;
	float oldY = spriteData.y;
    spriteData.x += frameTime * velocity.x;         // move ship along X 
    spriteData.y += frameTime * velocity.y;         // move ship along Y
	distanceMoved += abs((spriteData.x - oldX));
	distanceMoved += abs((spriteData.y - oldY));
	if(distanceMoved > distanceToTravel)
	{
		velocity.x*=-1;
		velocity.y*=-1;
		distanceMoved = 0;
	}
}

void Enemy::blowUp()
{
	numHits++;
	if(numHits >= enemyNS::HITS_TO_KILL)
	{
		this->setActive(false);
		this->setVisible(false);
	}
	else
	{
		//slowy decreases the visibility of turret until it is destroyed
		aValue -= (200/enemyNS::HITS_TO_KILL);
		color = SETCOLOR_ARGB(aValue,255,0,0);
	}
}

void Enemy::fireLaser()
{
	for(int i = 0; i < enemyNS::TOTAL_LASERS; i++)
	{
		//if there is an available laser use it 
		if(!lasers[i]->getActive())
		{
			float xLocation = spriteData.x,yLocation = spriteData.y,xSpeed = laserNS::VELOCITY,ySpeed=laserNS::VELOCITY;
			//turret faces down
			switch(direction)
			{
			case UP:
				yLocation = gladiatorNS::ARENA_START_Y + gladiatorNS::ARENA_HEIGHT - gladiatorNS::DISTANCE_BETWEEN_ARENA_AND_ENEMY_WALLS_H - gladiatorNS::WALL_WIDTH*2;
				xSpeed = laserNS::VELOCITY/2;
				ySpeed*=-1;
				break;
			case DOWN:
				yLocation=gladiatorNS::ARENA_START_Y + gladiatorNS::DISTANCE_BETWEEN_ARENA_AND_ENEMY_WALLS_H + gladiatorNS::WALL_WIDTH*2;
				xSpeed = laserNS::VELOCITY/2;
				break;
			case LEFT:
				xLocation=gladiatorNS::ARENA_START_X + gladiatorNS::ARENA_WIDTH - gladiatorNS::DISTANCE_BETWEEN_ARENA_AND_ENEMY_WALLS_V - gladiatorNS::WALL_WIDTH*2;
				ySpeed = laserNS::VELOCITY/2;
				xSpeed*=-1;
				break;
			case RIGHT:
				xLocation=gladiatorNS::ARENA_START_X + gladiatorNS::DISTANCE_BETWEEN_ARENA_AND_ENEMY_WALLS_V + gladiatorNS::WALL_WIDTH*2;
				ySpeed = laserNS::VELOCITY/2;
				break;
			}
			lasers[i]->fire(xLocation, yLocation);
			lasers[i]->setVelocity(VECTOR2(xSpeed,ySpeed));
			break;
		}
	}
}