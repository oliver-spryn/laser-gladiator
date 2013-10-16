#include "entity.h"
#include "constants.h"

namespace enemyNS
{
	const int WIDTH = 25;            
    const int HEIGHT = 31;           
    const int X = GAME_WIDTH/4;   
    const int Y = GAME_HEIGHT/4;
    const float SPEED = 0;    
    const float MASS = 0.0f;    
    const int   TEXTURE_COLS = 1;
}

class Enemy : public Entity
{
public:
	Enemy();
	void update(float frameTime);
private:

};