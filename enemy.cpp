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
}

void Enemy::update(float frameTime)
{
	Entity::update(frameTime);

    spriteData.x += frameTime * velocity.x;         // move ship along X 
    spriteData.y += frameTime * velocity.y;         // move ship along Y
}