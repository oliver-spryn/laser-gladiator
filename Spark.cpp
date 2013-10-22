#include "Spark.h"

Spark::Spark(int width, int height) : startBlue(255), startGreen(255), startRed(255),
	transitioned(false) {
	this->collisionType     = entityNS::NONE;
	this->spriteData.height = height;
	this->spriteData.scale  = 1;
	this->spriteData.width  = width;
}

void Spark::draw() {
	if (!this->transitioned) {
		if (this->startBlue > this->endBlue &&
			this->startGreen > this->endGreen &&
			this->startRed > this->endRed) {
			this->startBlue -= this->transBlue;
			this->startGreen -= this->transGreen;
			this->startRed -= this->transRed;
		}

		this->velocity.x *= this->friction;
		this->velocity.y *= this->friction;

		this->spriteData.x += this->velocity.x;
		this->spriteData.y += this->velocity.y;

		Entity::draw(D3DCOLOR_ARGB(
			255, 
			static_cast<int>(this->startRed), 
			static_cast<int>(this->startGreen), 
			static_cast<int>(this->startBlue)
		));
	
		this->spriteData.scale *= 0.99;

		if (this->spriteData.scale < 0.01) {
			this->transitioned = true;
		}
	}
}

void Spark::reset() {
	this->transitioned = false;

	this->startBlue = 255;
	this->startGreen = 255;
	this->startRed = 255;
}

void Spark::setEnd(float endBlue, float endGreen, float endRed) {
	this->endBlue = endBlue;
	this->endGreen = endGreen;
	this->endRed = endRed;
}

void Spark::setFriction(float friction) {
	this->friction = friction;
}


void Spark::setTrans(float transBlue, float transGreen, float transRed) {
	this->transBlue = transBlue;
	this->transGreen = transGreen;
	this->transRed = transRed;
}

bool Spark::transitionCompleted() {
	return this->transitioned;
}