#ifndef PLAYERMIRROR_H
#define PLAYERMIRROR_H
#define WIN32_LEAN_AND_MEAN

#include "Entity.h"

namespace playerMirrorNS {
	const int HEIGHT = 6;  // Mirror height
    const int WIDTH  = 55; // Mirror width
}

class PlayerMirror : public Entity {
public : 
	PlayerMirror();

	// Updates to this object will be managed by the Player class
};

#endif