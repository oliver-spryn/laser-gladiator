#ifndef PLAYERTURRET_H
#define PLAYERTURRET_H
#define WIN32_LEAN_AND_MEAN

#include "Entity.h"

namespace playerTurretNS {
	const int HEIGHT = 31; // Turret height
    const int WIDTH  = 25; // Turret width
}

class PlayerTurret : public Entity {
private:
	COLOR_ARGB color;

public : 
	PlayerTurret();
	void setColor(COLOR_ARGB c) {color = c;}
	COLOR_ARGB getColor() {return color;}
	// Updates to this object will be managed by the Player class
};

#endif