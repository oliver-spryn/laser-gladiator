#ifndef EXPLODE_H
#define EXPLODE_H
#define WIN32_LEAN_AND_MEAN

#include <cmath>
#include <ctime>
#include <stdlib.h>
#include <vector>

#include "Flare.h"
#include "game.h"
#include "gameError.h"
#include "graphics.h"
#include "Spark.h"
#include "TextureManager.h"

using std::cos;
using std::sin;
using std::vector;

namespace explodeNS {
	const float FLARE_FADE_CONST     = 3.5f;
	const int FLARE_HEIGHT           = 427;
	const int FLARE_WIDTH            = 640;
	const int SPARK_COLOR_TRANSITION = 100;
	const int SPARK_COUNT            = 500;
	const float SPARK_FRICTION       = 0.997f;
	const int SPARK_GROUP_CONSTRUCT  = 20;
	const int SPARK_LENGTH           = 50;
	const float SPARK_SPEED_CONST    = 3.5f;
	const int SPARK_WIDTH            = 1;
}

class Explode {
private : 
	Flare* flareOne;
	int flareOneAlpha;
	TextureManager flareOneTexture;
	Flare* flareTwo;
	int flareTwoAlpha;
	TextureManager flareTwoTexture;
	Game* gamePtr;
	vector<Spark> spark;
	int sparkCounter;
	TextureManager sparkTexture;
	float transBlue;
	float transGreen;
	float transRed;

public : 
	Explode(Graphics* g, Game* gamePtr);
	~Explode();
	
	bool completed();
	void explodeAt(int x, int y);
};

#endif