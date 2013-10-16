#include "Mirror.h"

Mirror::Mirror(COLOR_ARGB color) : Entity()
{
	spriteData.width = mirrorNS::WIDTH;           // size of wall
    spriteData.height = mirrorNS::HEIGHT;
    spriteData.x = mirrorNS::X;                   // location on screen
    spriteData.y = mirrorNS::Y;
    spriteData.rect.bottom = mirrorNS::HEIGHT;    // rectangle to select parts of an image
    spriteData.rect.right = mirrorNS::WIDTH;
    velocity.x = 0;                             // velocity X
    velocity.y = 0;                             // velocity Y
    currentFrame = startFrame;
    radius = mirrorNS::WIDTH/2.0;
    collisionType = entityNS::CIRCLE;
	rotatedBoxReady = true;
	spriteData.angle = 0;
	mass = mirrorNS::MASS;
	mirrorColor = color;
}

void Mirror::update(float frameTime)
{
	Entity::update(frameTime);
}