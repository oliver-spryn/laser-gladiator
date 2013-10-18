#include "TestGame.h"

TestGame::TestGame() : Game() { }

TestGame::~TestGame() {
	this->releaseAll();
}

void TestGame::ai() {

}

void TestGame::collisions() {

}

void TestGame::initialize(HWND hwnd) {
	Game::initialize(hwnd);

//Initialize the laser texture
	if (!this->laserTexture.initialize(this->graphics, LASER_IMAGE))
		throw GameError(gameErrorNS::FATAL_ERROR, "Error initializing the laser texture");
	
//Initialize the laser object
	if (!this->laser.initialize(this, 1, 1, 1, &this->laserTexture))
		throw GameError(gameErrorNS::FATAL_ERROR, "Error initializing the laser object");

	this->laser.setSelfDestructMethod(Laser::TIMER_DESTROY, 5000);
}

void TestGame::releaseAll() {
	this->laserTexture.onLostDevice();
	Game::releaseAll();
}

void TestGame::render() {
	this->graphics->spriteBegin();
	this->laser.draw();
	this->laser.fireDeg(200, 200, 152);
    this->graphics->spriteEnd();   
}

void TestGame::resetAll() {
	this->laserTexture.onResetDevice();
	Game::resetAll();
}

void TestGame::update() {
	this->laser.update(this->frameTime);
}