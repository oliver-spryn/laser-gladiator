#include "Player.h"

Player::Player() : radians(PI / 2.0f) {
	this->collisionType     = entityNS::CIRCLE;
	this->mass              = playerNS::MASS;
	this->radius            = playerNS::WIDTH / 2;
	this->spriteData.height = playerNS::HEIGHT;
	this->spriteData.scale  = 1;
	this->spriteData.width  = playerNS::WIDTH;
	this->spriteData.x      = playerNS::X;
	this->spriteData.y      = playerNS::Y;

//Calculate several values regarding the position of the turret ring
	this->mirrorRadius = playerNS::HEIGHT / 2 + 10;
	this->trueCenterX = playerNS::X + playerNS::WIDTH / 2;
	this->trueCenterY = playerNS::Y + playerNS::HEIGHT / 2;
	this->turretRadius = playerNS::HEIGHT / 2 + 6;
}

void Player::draw() {
	Image::draw();
	this->mirror.draw();
	this->turret.draw();
}

void Player::fire(Laser &laser) {
	//int x = this->trueCenterX - playerTurretNS::WIDTH + this->turretRadius * cos(this->radians + PI / 2);
	//int y = this->trueCenterY - playerTurretNS::HEIGHT + this->turretRadius * sin(this->radians + PI / 2);

	laser.fireRad(GAME_WIDTH / 2, GAME_HEIGHT / 2, -this->radians + 3*PI/2);
}

bool Player::initialize(Game *gamePtr, int width, int height, int ncols, TextureManager *textureM) {
	bool retVal = Entity::initialize(gamePtr, width, height, ncols, textureM);

//Initialize the mirror texture
	if (!this->mirrorTexture.initialize(this->graphics, TURRET_MIRROR))
		throw GameError(gameErrorNS::FATAL_ERROR, "Error initializing the player turret mirror texture");

//Initialize the turret texture
	if (!this->turretTexture.initialize(this->graphics, TURRET))
		throw GameError(gameErrorNS::FATAL_ERROR, "Error initializing the player turret texture");

//Initialize the mirror object
	if (!this->mirror.initialize(gamePtr, playerMirrorNS::WIDTH, playerMirrorNS::HEIGHT, 1, &this->mirrorTexture))
		throw GameError(gameErrorNS::FATAL_ERROR, "Error initializing the player turret mirror object");

//Initialize the turret object
	if (!this->turret.initialize(gamePtr, playerTurretNS::WIDTH, playerTurretNS::HEIGHT, 1, &this->turretTexture))
		throw GameError(gameErrorNS::FATAL_ERROR, "Error initializing the player turret object");

	return retVal;
}

bool Player::mirrorCollidesWith(Entity &ent, VECTOR2 &collisionVector) {
	return this->mirror.collidesWith(ent, collisionVector);
}

bool Player::turretCollidesWith(Entity &ent, VECTOR2 &collisionVector) {
	return this->turret.collidesWith(ent, collisionVector);
}

void Player::update(int mouseX, int mouseY, float frameTime) {
    Entity::update(frameTime);

//Calculate the necessary angle for the turret based on the X and Y location of the pointer
	int newX = mouseX - GAME_WIDTH / 2;
	int newY = GAME_HEIGHT / 2 - mouseY;
	this->radians = atan2((float)newX, (float)newY);

//Set the angle and position of the mirror
	this->mirror.setRadians(this->radians);
	this->mirror.setX(this->trueCenterX - playerMirrorNS::WIDTH / 2 - this->mirrorRadius * cos(this->radians + PI / 2));
	this->mirror.setY(this->trueCenterY - playerMirrorNS::HEIGHT / 2 - this->mirrorRadius * sin(this->radians + PI / 2));

//Set the angle and position of the turret
	this->turret.setRadians(this->radians);
	this->turret.setX(this->trueCenterX - playerTurretNS::WIDTH / 2 + this->turretRadius * cos(this->radians + PI / 2));
	this->turret.setY(this->trueCenterY - playerTurretNS::HEIGHT / 2 + this->turretRadius * sin(this->radians + PI / 2));
}