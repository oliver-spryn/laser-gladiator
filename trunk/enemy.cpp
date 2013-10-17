#include "enemy.h"

Enemy::Enemy()
{
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
	}
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
	if(distanceMoved > 300)
	{
		velocity.x*=-1;
		velocity.y*=-1;
		distanceMoved = 0;
	}
}

void Enemy::blowUp()
{
	this->setActive(false);
	this->setVisible(false);
}

void Enemy::fireLaser()
{
	//need to find way to identify horizontal vs. vertical laser
	for(int i = 0; i < enemyNS::TOTAL_LASERS; i++)
	{
		//if there is an available laser use it 
		if(!lasers[i]->getActive())
		{
			int xLocation = spriteData.x,yLocation = spriteData.y,xSpeed = laserNS::SPEED,ySpeed=laserNS::SPEED;
			//turret faces down
			switch(direction)
			{
			case UP:
				yLocation-=50;
				xSpeed = laserNS::SPEED/2;
				break;
			case DOWN:
				yLocation+=50;
				xSpeed = laserNS::SPEED/2;
				break;
			case LEFT:
				xLocation-=50;
				ySpeed = laserNS::SPEED/2;
				break;
			case RIGHT:
				xLocation+=50;
				ySpeed = laserNS::SPEED/2;
				break;
			}
			lasers[i]->setX(xLocation);
			lasers[i]->setY(yLocation);
			lasers[i]->setActive(true);
			lasers[i]->setVisible(true);
			lasers[i]->setVelocity(VECTOR2(xSpeed,ySpeed));
			break;
		}
	}
}