#include "Flare.h"

Flare::Flare(int width, int height) {
	this->collisionType     = entityNS::NONE;
	this->spriteData.height = height;
	this->spriteData.scale  = 1;
	this->spriteData.width  = width;
}