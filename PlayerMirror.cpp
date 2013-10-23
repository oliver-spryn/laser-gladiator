#include "PlayerMirror.h"

PlayerMirror::PlayerMirror() {
	this->collisionType     = entityNS::ROTATED_BOX;
	this->edge.bottom       = playerMirrorNS::HEIGHT / 2;
	this->edge.left         = playerMirrorNS::WIDTH / -2;
	this->edge.right        = playerMirrorNS::WIDTH / 2;
	this->edge.top          = playerMirrorNS::HEIGHT / -2;
	this->mass              = 0;
	this->spriteData.height = playerMirrorNS::HEIGHT;
	this->spriteData.scale  = 1;
	this->spriteData.width  = playerMirrorNS::WIDTH;
	this->velocity.x = 0;
	this->velocity.y = 0;
}