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

//Initialize the player turret
	if (!this->playerTexture.initialize(this->graphics, TURRET_IMAGE))
		throw GameError(gameErrorNS::FATAL_ERROR, "Error initializing the player turret texture");

//Initialize the laser object
	if (!this->laser.initialize(this, 1, 1, 1, &this->laserTexture))
		throw GameError(gameErrorNS::FATAL_ERROR, "Error initializing the laser object");

//Initialize the plauer turret object
	if (!this->player.initialize(this, 74, 104, 1, &this->playerTexture))
		throw GameError(gameErrorNS::FATAL_ERROR, "Error initializing the player turret object");

	this->laser.setSelfDestructMethod(Laser::TIMER_DESTROY, 5000);
}

void TestGame::releaseAll() {
	this->laserTexture.onLostDevice();
	Game::releaseAll();
}

void TestGame::render() {
	this->graphics->spriteBegin();
	this->laser.draw();
	this->player.draw();
    this->graphics->spriteEnd();   
}

void TestGame::resetAll() {
	this->laserTexture.onResetDevice();
	Game::resetAll();
}

void TestGame::update() {
	this->laser.update(this->frameTime);
	this->player.update(this->input->getMouseX(), this->input->getMouseY(), this->frameTime);

	if (this->input->getMouseLButton()) {
		this->player.fire(this->laser);
	}
}