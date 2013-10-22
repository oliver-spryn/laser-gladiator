#ifndef SPARK_H
#define SPARK_H
#define WIN32_LEAN_AND_MEAN

#include "entity.h"

class Spark : public Entity {
private : 
	float endBlue;
	float endGreen;
	float endRed;
	float friction;
	float scale;
	float startBlue;
	float startGreen;
	float startRed;
	bool transitioned;
	float transBlue;
	float transGreen;
	float transRed;

public : 
	Spark(int width, int height);
	
	void draw();
	void reset();
	void setEnd(float endBlue, float endGreen, float endRed);
	void setFriction(float friction);
	void setTrans(float transBlue, float transGreen, float transRed);
	bool transitionCompleted();
};

#endif