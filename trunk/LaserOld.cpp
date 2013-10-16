#include "Laser.h"

Laser::Laser() : Entity()
{
	spriteData.width = laserNS::WIDTH;           // size of wall
    spriteData.height = laserNS::HEIGHT;
    spriteData.x = laserNS::X;                   // location on screen
    spriteData.y = laserNS::Y;
    spriteData.rect.bottom = laserNS::HEIGHT;    // rectangle to select parts of an image
    spriteData.rect.right = laserNS::WIDTH;
    velocity.x = 0;                             // velocity X
    velocity.y = 0;                             // velocity Y
    currentFrame = startFrame;
    radius = laserNS::WIDTH/2.0;
    collisionType = entityNS::BOX;
	edge.left = (laserNS::WIDTH/2)*-1;
	edge.right = laserNS::WIDTH/2;
	edge.top = (laserNS::HEIGHT/2)*-1;
	edge.bottom = (laserNS::HEIGHT/2);
	spriteData.angle = 0;
	mass = laserNS::MASS;
}

void Laser::update(float frameTime)
{
	Entity::update(frameTime);

    spriteData.x += frameTime * velocity.x;         // move ship along X 
    spriteData.y += frameTime * velocity.y;         // move ship along Y
	
    // Bounce off walls
    if (spriteData.x > GAME_WIDTH-laserNS::WIDTH)    // if hit right screen edge
    {
        spriteData.x = GAME_WIDTH-laserNS::WIDTH;    // position at right screen edge
        velocity.x = -velocity.x;                   // reverse X direction
    } else if (spriteData.x < 0)                    // else if hit left screen edge
    {
        spriteData.x = 0;                           // position at left screen edge
        velocity.x = -velocity.x;                   // reverse X direction
    }
    if (spriteData.y > GAME_HEIGHT-laserNS::HEIGHT)  // if hit bottom screen edge
    {
        spriteData.y = GAME_HEIGHT-laserNS::HEIGHT;  // position at bottom screen edge
        velocity.y = -velocity.y;                   // reverse Y direction
    } else if (spriteData.y < 0)                    // else if hit top screen edge
    {
        spriteData.y = 0;                           // position at top screen edge
        velocity.y = -velocity.y;                   // reverse Y direction
    }
}