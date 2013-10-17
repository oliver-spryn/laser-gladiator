#include "laserGladiator.h"

LaserGladiator::LaserGladiator()
{
	numFrames = 1;
	playerScore = 0;
	srand(time(0));
	numMirrors = 10 + rand() % 20;
	numWalls = 4;
	laser = new Laser;
	debug.open("debug.txt");
	debug << "starting\n";
	int arenaWidth = GAME_WIDTH-50;
	int arenaHeight = GAME_HEIGHT-50;
	int mirrorSpace = 50;
	rows = arenaHeight/mirrorSpace-1;
	columns = arenaWidth/mirrorSpace-2;
	//sets up grid system for mirror placement
	for(int i = 0; i < rows; i++)
	{
		mirrorPositions.push_back(vector<Position>());
		for(int j = 0; j < columns; j++)
		{
			//checks if it is the middle and puts in dummy data
			if(i==(rows/2) && j == (columns/2))
			{
				mirrorPositions[i-1][j-1] = Position(0,0);
				mirrorPositions[i-1][j] = Position(0,0);
				mirrorPositions[i-1][j+1] = Position(0,0);
				mirrorPositions[i][j-1]=Position(0,0);
				mirrorPositions[i].push_back(Position(0,0));
				mirrorPositions[i].push_back(Position(0,0));
				j++;
			}
			if(i==(rows/2)+1 && j == (columns/2))
			{
				mirrorPositions[i][j-1]=Position(0,0);
				mirrorPositions[i].push_back(Position(0,0));
				mirrorPositions[i].push_back(Position(0,0));
				j++;
			}
			else
				mirrorPositions[i].push_back(Position((100+(mirrorSpace*j)),(65+(mirrorSpace*i))));
		}
	}
}

LaserGladiator::~LaserGladiator()
{
	debug.close();
	releaseAll();
}

void LaserGladiator::initialize(HWND hwnd)
{
	Game::initialize(hwnd);
	//initialize all textures
	//wall texture
	if(!wallTexture.initialize(graphics,WALL_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing wall texture"));

	//hwall texture
	if(!hWallTexture.initialize(graphics,WALL_IMAGE_HORIZONTAL))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing hwall texture"));

	//laser texture
	if(!laserTexture.initialize(graphics,LASER_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing laser texture"));

	//mirror texture
	if(!mirrorTexture.initialize(graphics,MIRROR_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing mirror texture"));

	//enemy wall texture
	if(!enemyWallTexture.initialize(graphics,ENEMY_WALL_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing enemy wall texture"));

	//h Enemy Wall texture
	//enemy wall texture
	if(!hEnemyWallTexture.initialize(graphics,ENEMY_WALL_IMAGE_HORIZONTAL))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing h enemy wall texture"));

	//enemy texture
	if(!enemyTexture.initialize(graphics,ENEMY_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing enemy texture"));

	//initialize all entities
	//wall left
	Wall* left = new Wall(400,4);
	walls.push_back(left);
	left = 0;
	if (!walls[0]->initialize(this, 4, 450, wallNS::TEXTURE_COLS, &wallTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing wall1"));
    walls[0]->setFrames(wallNS::WALL_START_FRAME, wallNS::WALL_END_FRAME);
    walls[0]->setCurrentFrame(wallNS::WALL_START_FRAME);
    walls[0]->setX(20);
    walls[0]->setY(10);
    walls[0]->setVelocity(VECTOR2(wallNS::SPEED,-wallNS::SPEED)); // VECTOR2(X, Y)

	//wall right
	Wall* right = new Wall(400,4);
	walls.push_back(right);
	right = 0;
	if (!walls[1]->initialize(this, 4, 450, wallNS::TEXTURE_COLS, &wallTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing wall1"));
    walls[1]->setFrames(wallNS::WALL_START_FRAME, wallNS::WALL_END_FRAME);
    walls[1]->setCurrentFrame(wallNS::WALL_START_FRAME);
    walls[1]->setX(GAME_WIDTH-20);
    walls[1]->setY(10);
    walls[1]->setVelocity(VECTOR2(wallNS::SPEED,-wallNS::SPEED)); // VECTOR2(X, Y)

	//wall top
	Wall* top = new Wall(4,620);
	walls.push_back(top);
	top = 0;
	//reverse height and width for rotated wall
	if (!walls[2]->initialize(this, 600, 4, 1, &hWallTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing wall1"));
    walls[2]->setFrames(wallNS::WALL_START_FRAME, wallNS::WALL_END_FRAME);
    walls[2]->setCurrentFrame(wallNS::WALL_START_FRAME);
    walls[2]->setX(20);
    walls[2]->setY(10);
    walls[2]->setVelocity(VECTOR2(wallNS::SPEED,-wallNS::SPEED)); // VECTOR2(X, Y)

	//wall bottom
	Wall* bottom = new Wall(4,620);
	walls.push_back(bottom);
	bottom = 0;
	//reverse height and width for rotated wall
	if (!walls[3]->initialize(this, 600, 4, 1, &hWallTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing wall1"));
    walls[3]->setFrames(wallNS::WALL_START_FRAME, wallNS::WALL_END_FRAME);
    walls[3]->setCurrentFrame(wallNS::WALL_START_FRAME);
    walls[3]->setX(20);
    walls[3]->setY(460);
    walls[3]->setVelocity(VECTOR2(wallNS::SPEED,-wallNS::SPEED)); // VECTOR2(X, Y)

	//mirrors
	//more or less randomly chooses the mirror positions
	for(int i = rand()%1; i < mirrorPositions.size(); i+=(2+rand()%1))
	{
		int mirrorsInRows = 4+rand()%3;
		int numMirrors=0;
		for(int j = rand()%2; j < mirrorPositions[i].size() && numMirrors < mirrorsInRows; j+=(2+rand()%3), numMirrors++)
		{
			int xLocation = mirrorPositions[i][j].x;
			int yLocation = mirrorPositions[i][j].y;
			if(xLocation == 0 && yLocation == 0)
				continue;
			Mirror* m = new Mirror();
			if (!m->initialize(this, mirrorNS::WIDTH, mirrorNS::HEIGHT, mirrorNS::TEXTURE_COLS, &mirrorTexture))
				throw(GameError(gameErrorNS::FATAL_ERROR, "error initializing Mirror"));
			m->setX(xLocation);
			m->setY(yLocation);
			m->setVelocity(VECTOR2(mirrorNS::SPEED,-mirrorNS::SPEED));
			m->setScale(0.75);
			mirrors.push_back(m);
			m = 0;
		}
	}

	//mirrors for corners
	Mirror* m = new Mirror(mirrorNS::CORNER_COLOR);
	if(!m->initialize(this, mirrorNS::WIDTH, mirrorNS::HEIGHT, mirrorNS::TEXTURE_COLS, &mirrorTexture))
			throw(GameError(gameErrorNS::FATAL_ERROR, "error initializing Mirror"));
	m->setX(15);
	m->setY(5);
	m->setVelocity(VECTOR2(mirrorNS::SPEED,-mirrorNS::SPEED));
	m->setScale(mirrorNS::CORNER_RATIO);
	mirrors.push_back(m);
	
	m = new Mirror(mirrorNS::CORNER_COLOR);
	if(!m->initialize(this, mirrorNS::WIDTH, mirrorNS::HEIGHT, mirrorNS::TEXTURE_COLS, &mirrorTexture))
			throw(GameError(gameErrorNS::FATAL_ERROR, "error initializing Mirror"));
	m->setX(GAME_WIDTH-35);
	m->setY(5);
	m->setVelocity(VECTOR2(mirrorNS::SPEED,-mirrorNS::SPEED));
	m->setScale(mirrorNS::CORNER_RATIO);
	mirrors.push_back(m);

	m = new Mirror(mirrorNS::CORNER_COLOR);
	if(!m->initialize(this, mirrorNS::WIDTH, mirrorNS::HEIGHT, mirrorNS::TEXTURE_COLS, &mirrorTexture))
			throw(GameError(gameErrorNS::FATAL_ERROR, "error initializing Mirror"));
	m->setX(15);
	m->setY(445);
	m->setVelocity(VECTOR2(mirrorNS::SPEED,-mirrorNS::SPEED));
	m->setScale(mirrorNS::CORNER_RATIO);
	mirrors.push_back(m);

	m = new Mirror(mirrorNS::CORNER_COLOR);
	if(!m->initialize(this, mirrorNS::WIDTH, mirrorNS::HEIGHT, mirrorNS::TEXTURE_COLS, &mirrorTexture))
			throw(GameError(gameErrorNS::FATAL_ERROR, "error initializing Mirror"));
	m->setX(GAME_WIDTH-35);
	m->setY(445);
	m->setVelocity(VECTOR2(mirrorNS::SPEED,-mirrorNS::SPEED));
	m->setScale(mirrorNS::CORNER_RATIO);
	mirrors.push_back(m);
	m=0;

	//left enemy
	Enemy* e = new Enemy;
	if(!e->initialize(this, enemyNS::WIDTH, enemyNS::HEIGHT, enemyNS::TEXTURE_COLS, &enemyTexture))
			throw(GameError(gameErrorNS::FATAL_ERROR, "error initializing Enemy"));
	e->setX(35);
	e->setY(70);
	e->setVelocity(VECTOR2(0,enemyNS::SPEED));
	e->setDegrees(270);
	//direction it is pointing
	e->setDirection(RIGHT);
	enemies.push_back(e);
	e=0;

	//right enemy
	e = new Enemy;
	if(!e->initialize(this, enemyNS::WIDTH, enemyNS::HEIGHT, enemyNS::TEXTURE_COLS, &enemyTexture))
			throw(GameError(gameErrorNS::FATAL_ERROR, "error initializing Enemy"));
	e->setX(GAME_WIDTH-55);
	e->setY(GAME_HEIGHT-110);
	e->setDegrees(90);
	e->setVelocity(VECTOR2(0,-enemyNS::SPEED));
	e->setDirection(LEFT);
	enemies.push_back(e);
	e=0;

	//top enemy
	e = new Enemy;
	if(!e->initialize(this, enemyNS::WIDTH, enemyNS::HEIGHT, enemyNS::TEXTURE_COLS, &enemyTexture))
			throw(GameError(gameErrorNS::FATAL_ERROR, "error initializing Enemy"));
	e->setX(GAME_WIDTH-125);
	e->setY(20);
	e->setVelocity(VECTOR2(-enemyNS::SPEED,0));
	e->setDirection(DOWN);
	enemies.push_back(e);
	e=0;

	//bottom enemy
	e = new Enemy;
	if(!e->initialize(this, enemyNS::WIDTH, enemyNS::HEIGHT, enemyNS::TEXTURE_COLS, &enemyTexture))
			throw(GameError(gameErrorNS::FATAL_ERROR, "error initializing Enemy"));
	e->setX(100);
	e->setY(GAME_HEIGHT-55);
	e->setDegrees(180);
	e->setVelocity(VECTOR2(enemyNS::SPEED,0));
	e->setDirection(UP);
	enemies.push_back(e);
	e=0;

	//enemy walls
	//left
	Wall* w = new Wall(GAME_HEIGHT-130,4);
	if (!w->initialize(this, 4, GAME_HEIGHT-130, wallNS::TEXTURE_COLS, &enemyWallTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing wall1"));
    w->setFrames(wallNS::WALL_START_FRAME, wallNS::WALL_END_FRAME);
    w->setCurrentFrame(wallNS::WALL_START_FRAME);
    w->setX(70);
    w->setY(60);
    w->setVelocity(VECTOR2(wallNS::SPEED,-wallNS::SPEED)); // VECTOR2(X, Y)
	walls.push_back(w);
	w=0;

	//right
	w = new Wall(GAME_HEIGHT-130,4);
	if (!w->initialize(this, 4, GAME_HEIGHT-130, wallNS::TEXTURE_COLS, &enemyWallTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing wall1"));
    w->setFrames(wallNS::WALL_START_FRAME, wallNS::WALL_END_FRAME);
    w->setCurrentFrame(wallNS::WALL_START_FRAME);
    w->setX(GAME_WIDTH-70);
    w->setY(60);
    w->setVelocity(VECTOR2(wallNS::SPEED,-wallNS::SPEED)); // VECTOR2(X, Y)
	walls.push_back(w);
	w=0;

	//top
	w = new Wall(4,GAME_WIDTH-200);
	if (!w->initialize(this, GAME_WIDTH-200, 4, 1, &hEnemyWallTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing wall1"));
    w->setFrames(wallNS::WALL_START_FRAME, wallNS::WALL_END_FRAME);
    w->setCurrentFrame(wallNS::WALL_START_FRAME);
    w->setX(105);
    w->setY(52);
    w->setVelocity(VECTOR2(wallNS::SPEED,-wallNS::SPEED)); // VECTOR2(X, Y)
	walls.push_back(w);
	w=0;

	//bottom
	w = new Wall(4,GAME_WIDTH-200);
	if (!w->initialize(this, GAME_WIDTH-200, 4, 1, &hEnemyWallTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing wall1"));
    w->setFrames(wallNS::WALL_START_FRAME, wallNS::WALL_END_FRAME);
    w->setCurrentFrame(wallNS::WALL_START_FRAME);
    w->setX(105);
    w->setY(GAME_HEIGHT-65);
    w->setVelocity(VECTOR2(wallNS::SPEED,-wallNS::SPEED)); // VECTOR2(X, Y)
	walls.push_back(w);
	w=0;

	//enemy lasers
	for(int i = 0; i < enemies.size(); i++)
	{
		for(int j = 0; j < enemyNS::TOTAL_LASERS; j++)
		{
			if (!enemies[i]->getLasers()[j]->initialize(this, laserNS::WIDTH, laserNS::HEIGHT, laserNS::TEXTURE_COLS, &laserTexture))
				throw(GameError(gameErrorNS::FATAL_ERROR, "error initializing laser"));
			enemies[i]->getLasers()[j]->setX(0);
			enemies[i]->getLasers()[j]->setY(0);
			enemies[i]->getLasers()[j]->setVisible(false);
			enemies[i]->getLasers()[j]->setActive(false);
			//creates more pointers to control
			lasers.push_back(enemies[i]->getLasers()[j]);
		}
	}
}

void LaserGladiator::update()
{
	//call updates for all entities
	for(int i = 0; i < walls.size(); i++)
	{
		walls[i]->update(frameTime);
	}
	for(int i = 0; i < mirrors.size(); i++)
	{
		mirrors[i]->update(frameTime);
	}
	for(int i = 0; i < enemies.size(); i++)
	{
		if(enemies[i]->getActive())
		{
			enemies[i]->update(frameTime);
		}
	}
	for(int i = 0; i < lasers.size(); i++)
	{
		if(lasers[i]->getActive())
		{
			if(lasers[i]->getCollisions() > gladiatorNS::COLLISIONS_PER_LASER)
				lasers[i]->loseEnergy();
			lasers[i]->update(frameTime);
		}
	}
	//fire a laser from enemy turret
	if(numFrames%(500+rand()%1000)==0)
	{
		int enemyChosen = rand()%4;
		if(enemies[enemyChosen]->getActive())
			enemies[enemyChosen]->fireLaser();
		else
		{
			//if it chooses an inactive turret it fires the first active durret it finds
			for(int i = 0; i < enemies.size(); i++)
			{
				if(enemies[i]->getActive())
					enemies[i]->fireLaser();
			}
		}
		numFrames=0;
	}
	numFrames++;
}

void LaserGladiator::ai()
{}

void LaserGladiator::collisions()
{
	VECTOR2 collisionVector;
	//check collision between all entities with every other entity

	for(int i = 0; i < walls.size(); i++)
	{
		for(int j = 0; j < lasers.size(); j++)
		{
			if(lasers[j]->collidesWith(*walls[i],collisionVector))
			{
				//it is debatable if this is the best system to respond to the collision
				if(walls[i]->getWidth() > walls[i]->getHeight())
				{
					//laser->bounce(collisionVector, *walls[i]);
					lasers[j]->setVelocity(VECTOR2(lasers[j]->getVelocity().x,lasers[j]->getVelocity().y*-1));
					lasers[j]->setY((walls[i]->getY()>GAME_HEIGHT/2) ? walls[i]->getY() - 10 : walls[i]->getY() + 10);
				}
				else
				{
					lasers[j]->setVelocity(VECTOR2(lasers[j]->getVelocity().x*-1,lasers[j]->getVelocity().y));
					lasers[j]->setX((walls[i]->getX()>GAME_HEIGHT) ? walls[i]->getX() - 10 : walls[i]->getX() + 10);
				}
				lasers[j]->increaseCollisions();
			}
		}
	}

	//colisisions with mirrors
	for(int i = 0; i < mirrors.size(); i++)
	{
		for(int j = 0; j < lasers.size(); j++)
		{
			if(lasers[j]->collidesWith(*mirrors[i], collisionVector))
			{
				lasers[j]->bounce(collisionVector, *mirrors[i]);
				lasers[j]->increaseCollisions();
				//laser->setVelocity(VECTOR2(laserNS::SPEED,laserNS::SPEED));
			}
		}
	}

	//collisions with turrets
	for(int i = 0; i < enemies.size(); i++)
	{
		for(int j = 0; j < lasers.size(); j++)
		{
			if(lasers[j]->collidesWith(*enemies[i], collisionVector))
			{
				lasers[j]->bounce(collisionVector, *enemies[i]);
				lasers[j]->increaseCollisions();
				//laser->setVelocity(VECTOR2(laserNS::SPEED,laserNS::SPEED));
				enemies[i]->blowUp();
				playerScore+=100;
			}
		}
	}
}

void LaserGladiator::render()
{
	graphics->spriteBegin();
	for(int i = 0; i < walls.size(); i++)
	{
		walls[i]->draw();
	}
	for(int i = 0; i < mirrors.size(); i++)
	{
		mirrors[i]->draw(mirrors[i]->getColor());
	}
	for(int i = 0; i < enemies.size(); i++)
	{
		if(enemies[i]->getActive())
			enemies[i]->draw();
	}
	for(int i = 0; i < lasers.size(); i++)
	{
		if(lasers[i]->getActive())
		{
			lasers[i]->draw();
		}
	}
	//do all of the entity draws
	graphics->spriteEnd();
}

void LaserGladiator::releaseAll()
{
	//do the onLostDevice function for all textures
	wallTexture.onLostDevice();
	hWallTexture.onLostDevice();
	laserTexture.onLostDevice();
	mirrorTexture.onLostDevice();
	enemyWallTexture.onLostDevice();
	enemyTexture.onLostDevice();
	Game::releaseAll();
	return;
}

void LaserGladiator::resetAll()
{
	//call onResetDevice for all textures
	wallTexture.onResetDevice();
	hWallTexture.onResetDevice();
	laserTexture.onResetDevice();
	mirrorTexture.onResetDevice();
	enemyWallTexture.onResetDevice();
	enemyTexture.onResetDevice();
	Game::resetAll();
	return;
}