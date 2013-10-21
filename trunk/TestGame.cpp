#include "TestGame.h"

TestGame::TestGame() : Game() { }

TestGame::~TestGame() {
	this->releaseAll();
}

void TestGame::ai() {

}

void TestGame::collisions() {
	VECTOR2 collisionVector;

	//if (this->player.collidesWith(this->laser, collisionVector)) {
	//	this->laser.bounce(collisionVector, this->player);
	//}

	if (this->player.mirrorCollidesWith(this->laser, collisionVector)) {
		this->laser.destroy();
	}

	//if (this->player.turretCollidesWith(this->laser, collisionVector)) {
	//	this->laser.bounce(collisionVector, this->player);
	//}
}

void TestGame::initialize(HWND hwnd) {
	Game::initialize(hwnd);

//Initialize the laser texture
	if (!this->laserTexture.initialize(this->graphics, LASER_IMAGE))
		throw GameError(gameErrorNS::FATAL_ERROR, "Error initializing the laser texture");

//Initialize the player turret
	if (!this->playerTexture.initialize(this->graphics, TURRET_RING))
		throw GameError(gameErrorNS::FATAL_ERROR, "Error initializing the player turret texture");

//Initialize the laser object
	if (!this->laser.initialize(this, 1, 1, 1, &this->laserTexture))
		throw GameError(gameErrorNS::FATAL_ERROR, "Error initializing the laser object");

//Initialize the player turret object
	if (!this->player.initialize(this, 71, 71, 1, &this->playerTexture))
		throw GameError(gameErrorNS::FATAL_ERROR, "Error initializing the player turret ring object");
	
	this->laser.setSelfDestructMethod(Laser::TIMER_DESTROY, 20000);
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