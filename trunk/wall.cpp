#include "wall.h"

//wall cannot be longer than 450 pixels
//set wall height in the initialize call
Wall::Wall(int height, int width) : Entity()
{
	x = GAME_WIDTH/2 - width/2;
	y = GAME_HEIGHT/2 - height/2;
	this->height = height;
	this->width = width;
	spriteData.width = width;           // size of wall
    spriteData.height = height;
    spriteData.x = x;                   // location on screen
    spriteData.y = y;
    spriteData.rect.bottom = height;    // rectangle to select parts of an image
    spriteData.rect.right = width;
    velocity.x = 0;                             // velocity X
    velocity.y = 0;                             // velocity Y
    frameDelay = wallNS::WALL_ANIMATION_DELAY;
    startFrame = wallNS::WALL_START_FRAME;      // first frame of wall animation
    endFrame     = wallNS::WALL_END_FRAME;      // last frame of wall animation
    currentFrame = startFrame;
    radius = width/2.0;
    collisionType = entityNS::BOX;
	edge.left = (width/2)*-1;
	edge.right = width/2;
	edge.top = (height/2)*-1;
	edge.bottom = (height/2);
	rotatedBoxReady = true;
	spriteData.angle = 0;
	mass = wallNS::MASS;
}

void Wall::update(float frameTime)
{
	Entity::update(frameTime);
}