#include "Player.h"

Player::Player() : degrees(90.0f) {
	this->collisionType     = entityNS::BOX;
	this->spriteData.height = playerNS::HEIGHT;
	this->spriteData.scale  = 1;
	this->spriteData.width  = playerNS::WIDTH;
	this->spriteData.x      = playerNS::X;
	this->spriteData.y      = playerNS::Y;

	#if defined(DEBUG) | defined(_DEBUG)
	this->debugText = new TextDX();
	#endif
}

#if defined(DEBUG) | defined(_DEBUG)
void Player::draw() {
	Image::draw();

	this->sin.str("");
	this->sin << "Turret angle: " << this->spriteData.angle;
	
	this->debugText->setFontColor(graphicsNS::WHITE);
    this->debugText->print(this->sin.str(), 20, 20);
}
#endif

void Player::fire(Laser &laser) {
	laser.fireRad(GAME_WIDTH / 2, GAME_HEIGHT / 2, -this->degrees + 3*PI/2);
}

#if defined(DEBUG) | defined(_DEBUG)
bool Player::initialize(Game *gamePtr, int width, int height, int ncols, TextureManager *textureM) {
	bool retVal = Entity::initialize(gamePtr, width, height, ncols, textureM);

//Initialize the debug text
	if(!this->debugText->initialize(this->graphics, 15, true, false, "Arial"))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing DirectX font"));

	return retVal;
}
#endif

void Player::update(int mouseX, int mouseY, float frameTime) {
    Entity::update(frameTime);

	int newX = mouseX - GAME_WIDTH / 2;
	int newY = GAME_HEIGHT / 2 - mouseY;
	this->spriteData.angle = this->degrees = atan2(newX, newY);
}