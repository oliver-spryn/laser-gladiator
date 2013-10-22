#include "Explode.h"

Explode::Explode(Graphics* g, Game* gamePtr) : 
	flareOne(new Flare(explodeNS::FLARE_WIDTH, explodeNS::FLARE_HEIGHT)),
	flareTwo(new Flare(explodeNS::FLARE_WIDTH, explodeNS::FLARE_HEIGHT)), gamePtr(gamePtr), sparkCounter(0),
	spark(explodeNS::SPARK_COUNT, Spark(explodeNS::SPARK_WIDTH, explodeNS::SPARK_LENGTH)) {
//Reserve room in the vector of Spark objects
	this->spark.reserve(explodeNS::SPARK_COUNT);

//Create a color which all of the sparks will use
	srand(time(0));

	int blue = rand() % 255;
	int green = rand() % 255;
	int red = rand() % 255;

//Calculate how much each hex color must be increased by in each frame in order to go from white to the chosen color
	this->transBlue = (255.0f - static_cast<float>(blue)) / static_cast<float>(explodeNS::SPARK_COLOR_TRANSITION);
	this->transGreen = (255.0f - static_cast<float>(green)) / static_cast<float>(explodeNS::SPARK_COLOR_TRANSITION);
	this->transRed = (255.0f - static_cast<float>(red)) / static_cast<float>(explodeNS::SPARK_COLOR_TRANSITION);

//Generate the flare sprites
	if (!this->flareOneTexture.initialize(g, FLARE_ONE_IMAGE))
		throw GameError(gameErrorNS::FATAL_ERROR, "Error initializing the explosion flare");

	if (!this->flareOne->initialize(this->gamePtr, explodeNS::FLARE_WIDTH, explodeNS::FLARE_HEIGHT, 1, &this->flareOneTexture))
		throw GameError(gameErrorNS::FATAL_ERROR, "Error initializing the explosion flare");

	if (!this->flareTwoTexture.initialize(g, FLARE_TWO_IMAGE))
		throw GameError(gameErrorNS::FATAL_ERROR, "Error initializing the explosion flare");

	if (!this->flareTwo->initialize(gamePtr, explodeNS::FLARE_WIDTH, explodeNS::FLARE_HEIGHT, 1, &this->flareTwoTexture))
		throw GameError(gameErrorNS::FATAL_ERROR, "Error initializing the explosion flare");

//Generate the spark sprites
	if (!this->sparkTexture.initialize(g, SPARK_TEXTURE))
		throw GameError(gameErrorNS::FATAL_ERROR, "Error initializing the explosion sparks");

	for(int i = 0; i < explodeNS::SPARK_COUNT; ++i) {
		if (!this->spark[i].initialize(this->gamePtr, explodeNS::SPARK_WIDTH, explodeNS::SPARK_LENGTH, 1, &this->sparkTexture))
			throw GameError(gameErrorNS::FATAL_ERROR, "Error initializing the explosion sparks");

		this->spark[i].setEnd(blue, green, red);
		this->spark[i].setFriction(explodeNS::SPARK_FRICTION);
		this->spark[i].setTrans(this->transBlue, this->transGreen, this->transRed);
	}
}

Explode::~Explode() {
	delete this->flareOne;
	delete this->flareTwo;
}

void Explode::explodeAt(int x, int y) {
	if (!this->spark[0].transitionCompleted()) {
	//Randomly choose a flare to activate
		if (this->flareOneAlpha <= 0 && this->flareTwoAlpha <= 0) {
			rand() % 2 == 1 ? (this->flareOneAlpha = 255) : (this->flareTwoAlpha = 255);
	//Fade out the first flare
		} else if (this->flareOneAlpha > 0) {
			this->flareOneAlpha -= explodeNS::FLARE_FADE_CONST;

			if (this->flareOneAlpha <= 0) {
				this->flareOneAlpha = 1;
			}

			this->flareOne->setX(x - explodeNS::FLARE_WIDTH / 2);
			this->flareOne->setY(y - explodeNS::FLARE_HEIGHT / 2);
			this->flareOne->draw(D3DCOLOR_ARGB(this->flareOneAlpha, 255, 255, 255));
	//Fade out the second flare
		} else {
			this->flareTwoAlpha -= explodeNS::FLARE_FADE_CONST;

			if (this->flareTwoAlpha <= 0) {
				this->flareTwoAlpha = 1;
			}

			this->flareTwo->setX(x - explodeNS::FLARE_WIDTH / 2);
			this->flareTwo->setY(y - explodeNS::FLARE_HEIGHT / 2);
			this->flareTwo->draw(D3DCOLOR_ARGB(this->flareTwoAlpha, 255, 255, 255));
		}
	} else {
		this->sparkCounter = 0;
		this->flareOneAlpha = 0;
		this->flareTwoAlpha = 0;

		int blue = rand() % 255;
		int green = rand() % 255;
		int red = rand() % 255;

		this->transBlue = (255.0f - static_cast<float>(blue)) / static_cast<float>(explodeNS::SPARK_COLOR_TRANSITION);
		this->transGreen = (255.0f - static_cast<float>(green)) / static_cast<float>(explodeNS::SPARK_COLOR_TRANSITION);
		this->transRed = (255.0f - static_cast<float>(red)) / static_cast<float>(explodeNS::SPARK_COLOR_TRANSITION);

		for (int i = 0; i < explodeNS::SPARK_COUNT; ++i) {
			this->spark[i].setEnd(blue, green, red);
			this->spark[i].setTrans(this->transBlue, this->transGreen, this->transRed);
			this->spark[i].reset();
		}
	}

//Activate more sparks, if needed
	if (this->sparkCounter < explodeNS::SPARK_COUNT) {
		float deg, xVec, yVec;

		for(int i = 0; i < explodeNS::SPARK_GROUP_CONSTRUCT && this->sparkCounter < explodeNS::SPARK_COUNT; ++i) {
		//Calculate the vectors of each of the sparks
			deg = rand() % 360;
			xVec = explodeNS::SPARK_SPEED_CONST * cos(deg * PI / 180.0f + PI / 2.0f);
			yVec = explodeNS::SPARK_SPEED_CONST * sin(deg * PI / 180.0f + PI / 2.0f);

		//Initialize and position the spark
			this->spark[this->sparkCounter].setColorFilter(D3DCOLOR_ARGB(255, 255, 255, 255));
			this->spark[this->sparkCounter].setDegrees(deg);
			this->spark[this->sparkCounter].setScale(1);
			this->spark[this->sparkCounter].setVelocity(D3DXVECTOR2(xVec, yVec));
			this->spark[this->sparkCounter].setX(x);
			this->spark[this->sparkCounter].setY(y - explodeNS::SPARK_LENGTH / 2);

		//Increment total spark counter
			++this->sparkCounter;

		//Random cool stuff, by accident
			//this->spark[this->sparkCounter].setVelocity(D3DXVECTOR2(cos(deg * PI/180.0f) + PI/2, sin(deg * PI/180.0f) + PI/2));
			//this->spark[this->sparkCounter].setVelocity(D3DXVECTOR2(cos(deg * PI/180.0f), sin(deg * PI/180.0f) + PI/2));
			//this->spark[this->sparkCounter].setVelocity(D3DXVECTOR2(cos(deg * PI/180.0f) + PI/2, sin(deg * PI/180.0f)));
			//this->spark[this->sparkCounter].setVelocity(D3DXVECTOR2(cos(deg * PI/180.0f), sin(deg * PI/180.0f)));
			//this->spark[this->sparkCounter].setVelocity(D3DXVECTOR2(sin(deg * PI/180.0f), cos(deg * PI/180.0f)));
		}
	}

//Keep existing sparks in motion
	for (int i = 0; i < this->sparkCounter; ++i) {
		this->spark[i].draw();
	}
}