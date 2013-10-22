#include "PlayerTurret.h"

PlayerTurret::PlayerTurret() {
	this->collisionType     = entityNS::ROTATED_BOX;
	this->spriteData.height = playerTurretNS::HEIGHT;
	this->spriteData.scale  = 1;
	this->spriteData.width  = playerTurretNS::WIDTH;
	edge.left = (playerTurretNS::WIDTH/2)*-1;
	edge.right = playerTurretNS::WIDTH/2;
	edge.top = (playerTurretNS::HEIGHT/2)*-1;
	edge.bottom = (playerTurretNS::HEIGHT/2);
}