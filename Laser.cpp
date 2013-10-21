#include "Laser.h"

/**
 * CONSTRUCTOR
 * 
 * This constructor initializes all of the variables and default
 * settings for this Laser object.
 *
 * The color of the laser is initialized to red and will not self
 * destruct, by default.
 *
 * @access public
 * @param  DWORD  color The color of the laser graphic
 * @return void
*/

Laser::Laser(DWORD color) : 
	collisions(0), color(color), destroyConst(0), destroyCounter(0), destroyMethod(Laser::NO_DESTROY),
	destroyPending(false), lastPixelIndex(0), timeConst(1000.0 / CLOCKS_PER_SEC), timeStart(0),
	tailImages(laserNS::TAIL, Image()) {
	this->collisionType     = entityNS::ROTATED_BOX;
	this->spriteData.height = laserNS::HEAD_HEIGHT;
	this->spriteData.scale  = 1;
	this->spriteData.width  = laserNS::HEAD_WIDTH;
	this->spriteData.x      = laserNS::X;
	this->spriteData.y      = laserNS::Y;
	this->velocity.x        = laserNS::VELOCITY;
	this->velocity.y        = laserNS::VELOCITY;
	mass = laserNS::MASS;
}

/**
 * Reactivates the laser head and tail and places the laser
 * at a given starting position. It will also start a clock
 * to keep track of amount of time that the laser has been
 * active, if the laser is set to self destruct after a certain
 * period of time.
 *
 * @access private
 * @param  float   x The X coordinate to place the laser
 * @param  float   y The Y coordinate to place the laser
 * @return void
*/

void Laser::activate(float x, float y) {
//Activate the head pixel of the laser and set its position
	this->setActive(true);
	this->setVisible(true);
	this->setX(x);
	this->setY(y);

//Activate each of the tail pixels and set their position
	for(vector<Image>::iterator it = this->tailImages.begin(); it != this->tailImages.end(); ++it) {
		it->setX(x);
		it->setY(y);
		it->setVisible(true);
	}

//Start the clock
	if (this->destroyMethod == Laser::TIMER_DESTROY)
		this->timeStart = clock();
}

/**
 * Determines whether or not the laser should self destruct.
 *
 * @access private
 * @return bool    Whether or not the laser has destroyed itself
*/

bool Laser::checkDestory() {
//Do not destroy the laser while in this state
	if (this->destroyMethod == Laser::NO_DESTROY)
		return false;

//Destroy the laser after N number of collisions
	if (this->destroyMethod == Laser::COLLISION_DESTROY && this->collisions >= this->destroyConst) {
		this->destroy();
		return true;
	}

//Destroy the laser after N milliseconds
	if (this->destroyMethod == Laser::TIMER_DESTROY && (clock() - this->timeStart) * this->timeConst >= this->destroyConst) {
		this->destroy();
		return true;
	}

	return false;
}

/**
 * DOES NOT DESTROY THE LASER.
 *
 * Sets an internal flag for the laser to be destroyed. The laser
 * is not fully destroyed until the tail of the laser has collapsed.
 *
 * @access public
 * @return void
*/

void Laser::destroy() {
	this->destroyPending = true;
}

/**
 * Draw the laser head and tail sprites on the screen.
 *
 * @access public
 * @return void
*/

void Laser::draw() {
	Image::draw(this->color);

	for(vector<Image>::iterator it = this->tailImages.begin(); it != this->tailImages.end(); ++it) {
		it->draw(this->color);
	}
}

/**
 * Called once tail of the laser has fully collapsed. This method will
 * deactivate and hide the laser head and tail, and reset all of the 
 * variables which have been used to track the state of the laser.
 *
 * In other words, this function removes the laser from the screen and
 * prepares it firing again later.
 *
 * @access private
 * @return void
*/

void Laser::finalizeDestruction() {
//Disable the laser and tail
	this->setActive(false);
	this->setVisible(false);

	for(vector<Image>::iterator it = this->tailImages.begin(); it != this->tailImages.end(); ++it) {
		it->setVisible(false);
	}

//Reset some of the variables used to track the state of the laser
	this->collisions = 0;
	this->destroyCounter = 0;
	this->destroyPending = false;
	this->lastPixelIndex = 0;
}

/**
 * DEGREE MODE
 * 
 * Reactivates the laser and fires it from a given X and Y position
 * at a given angle.
 *
 * This method follows the standards of the cartesian corrdinate system,
 * where an angle of 0 degrees will point along the positive X axis, 90
 * degrees will point along the positive Y axis, 180 degrees will point 
 * along the negative X axis, etc...
 *
 * @access public
 * @param  float   x     The X coordinate to place the laser
 * @param  float   y     The Y coordinate to place the laser
 * @param  float   angle The angle to fire the laser, in degrees
 * @return void
*/

void Laser::fireDeg(float x, float y, float angle) {
	if (!this->active) {
	//Calculate the angle of the velocity vector
		this->velocity.x = laserNS::VELOCITY * sin(PI/180.0f * (90.0f + angle));
		this->velocity.y = laserNS::VELOCITY * cos(PI/180.0f * (90.0f + angle));

	//Activate the laser
		this->activate(x, y);
	}
}

/**
 * RADIAN MODE
 * 
 * Reactivates the laser and fires it from a given X and Y position
 * at a given angle.
 *
 * This method follows the standards of the cartesian corrdinate system,
 * where an angle of 0 radians will point along the positive X axis, PI/2
 * radians will point along the positive Y axis, PI radians will point 
 * along the negative X axis, etc...
 *
 * @access public
 * @param  float   x     The X coordinate to place the laser
 * @param  float   y     The Y coordinate to place the laser
 * @param  float   angle The angle to fire the laser, in radians
 * @return void
*/

void Laser::fireRad(float x, float y, float angle) {
	if (!this->active) {
	//Calculate the angle of the velocity vector
		this->velocity.x = laserNS::VELOCITY * sin(PI/2.0f + angle);
		this->velocity.y = laserNS::VELOCITY * cos(PI/2.0f + angle);

	//Activate the laser
		this->activate(x, y);
	}
}

void Laser::fire(float x, float y)
{
	if(!this->active)
	{
		this->activate(x,y);
	}
}

/**
 * Return the number of collisions the laser has experienced since
 * it was last fired.
 *
 * @access public
 * @return int    The number of collisions the laser has experienced
*/

int Laser::getCollisions() {
	return this->collisions;
}

/**
 * Increment the number of collisions the laser has experienced.
 *
 * @access public
 * @param  int    number The number by which to incremement the collision counter
 * @return void
*/

void Laser::increaseCollision(int number) {
	this->collisions += number;
}

/**
 * Initialize the Laser object and each of the objects which 
 * constitue the tail.
 *
 * @access public
 * @param  Game*           gamePtr  A pointer to the Game object which controls the game logic
 * @param  int             width    The width of the head of laser
 * @param  int             height   The height of the head of the laser
 * @param  int             ncols    The number of columns in the texture
 * @param  TextureManager* textureM The object which contains the texture which is used by this object
 * @return void
*/

bool Laser::initialize(Game *gamePtr, int width, int height, int ncols, TextureManager *textureM) {
	bool retVal = Entity::initialize(gamePtr, width, height, ncols, textureM);
	this->setActive(false);
	this->setVisible(false);

	for(vector<Image>::iterator it = this->tailImages.begin(); it != this->tailImages.end(); ++it) {
		it->initialize(this->graphics, 1, 1, 1, textureM);
		it->setX(laserNS::X);
		it->setY(laserNS::Y);
		it->setVisible(false);
	}
	
	return retVal;
}

/**
 * Set the method by which the laser will self destruct.
 * 
 * For the first parameter, there are three possible options:
 *  - Laser::COLLISION_DESTROY - Self destruct after N collisions
 *  - Laser::NO_DESTROY        - Do not self destruct (default)
 *  - Laser::TIMER_DESTROY     - Self destruct after N milliseconds
 *
 * For the second parameter, there are three possible options:
 *  - Number of collisions which must occur before doing a self-
 *    destruct [if using the Laser::COLLISION_DESTROY option]
 *  - No value is needed if using the LASER::NO_DESTROY option
 *  - Number of milliseconds which must occur before doing a self-
 *    destruct [if using the Laser::TIMER_DESTROY option]
 *
 * @access public
 * @param  char   method       The method by which the laser will self-destruct
 * @param  int    destroyConst The number of collisions or milliseconds after which the laser will self-destruct
 * @return void
*/

void Laser::setSelfDestructMethod(char method, int destroyConst) {
	if (method == Laser::COLLISION_DESTROY || method == Laser::NO_DESTROY || method == Laser::TIMER_DESTROY)
		this->destroyMethod = method;

	if (destroyConst >= 0)
		this->destroyConst = destroyConst;
}

/**
 * This method will update the laser at each frame and perform the
 * following actions:
 *  - Check to see if the laser should self-destruct.
 *  - Update the position of the head of the laser.
 *  - Check the head for collisions against the edge of the window.
 *  - Update the collision counter when the laser hits the edge.
 *  - Update the tail to follow the path of the head of the laser.
 *  - Collapse the tail of the laser if it is set for destruction.
 *  - Hide the laser after it has been fully destroyed.
 *
 * @access public
 * @param  float  frameTime A constant used to maintain the speed of moving objects
 * @return void
*/

void Laser::update(float frameTime) {
	Entity::update(frameTime);

//Check to see if this laser should be destroyed
	this->checkDestory();
	
//Update the tail location
	this->tailImages[this->lastPixelIndex].setX(this->spriteData.x);
	this->tailImages[this->lastPixelIndex].setY(this->spriteData.y);
	this->lastPixelIndex = (this->lastPixelIndex == laserNS::TAIL - 1 ? 0 : ++this->lastPixelIndex);

	if (!this->destroyPending) {
	//Update the location of the head
		this->spriteData.x += frameTime * this->velocity.x;
		this->spriteData.y += frameTime * this->velocity.y;
	
	//Detect collisions against the edge of the window
		if (this->spriteData.x > GAME_WIDTH - laserNS::HEAD_WIDTH) {   // Right edge
			this->spriteData.x = GAME_WIDTH - laserNS::HEAD_WIDTH;
			this->velocity.x = -this->velocity.x;
			++this->collisions;
		} else if (this->spriteData.x < 0) {                           // Left edge
			this->spriteData.x = 0;
			this->velocity.x = -this->velocity.x;
			++this->collisions;
		}
	
		if (this->spriteData.y > GAME_HEIGHT - laserNS::HEAD_HEIGHT) { // Bottom edge
			this->spriteData.y = GAME_HEIGHT - laserNS::HEAD_HEIGHT;
			this->velocity.y = -this->velocity.y;
			++this->collisions;
		} else if (spriteData.y < 0) {                                 // Top edge
			this->spriteData.y = 0;
			this->velocity.y = -this->velocity.y;
			++this->collisions;
		}
	} else {
		if (++this->destroyCounter == laserNS::TAIL) {
			this->finalizeDestruction();
		}
	}
}