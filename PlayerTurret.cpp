#include "PlayerTurret.h"

PlayerTurret::PlayerTurret() {
	this->collisionType     = entityNS::BOX;
	this->spriteData.height = playerTurretNS::HEIGHT;
	this->spriteData.scale  = 1;
	this->spriteData.width  = playerTurretNS::WIDTH;
}