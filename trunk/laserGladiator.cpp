#include "laserGladiator.h"

LaserGladiator::LaserGladiator()
{
	activeEnemies = 4;
	numFrames = 1;
	playerScore = 0;
	srand(time(0));
	numMirrors = 10 + rand() % 20;
	numWalls = 4;
	debug.open("debug.txt");
	debug << "starting\n";
	int arenaWidth = gladiatorNS::ARENA_WIDTH;
	int arenaHeight = gladiatorNS::ARENA_HEIGHT;
	int mirrorSpace = mirrorNS::HEIGHT + mirrorNS::HEIGHT/3;
	rows = arenaHeight/mirrorSpace-2;
	columns = arenaWidth/mirrorSpace-3;
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
				mirrorPositions[i].push_back(Position((gladiatorNS::ARENA_START_X+gladiatorNS::DISTANCE_BETWEEN_ARENA_AND_ENEMY_WALLS_V+(mirrorSpace*j)
				+mirrorNS::WIDTH/2),(gladiatorNS::ARENA_START_Y+gladiatorNS::DISTANCE_BETWEEN_ARENA_AND_ENEMY_WALLS_H+(mirrorSpace*i)+mirrorNS::HEIGHT/2)));
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
	Wall* left = new Wall(gladiatorNS::ARENA_HEIGHT,gladiatorNS::WALL_WIDTH);
	walls.push_back(left);
	left = 0;
	if (!walls[0]->initialize(this, gladiatorNS::WALL_WIDTH, gladiatorNS::ARENA_HEIGHT, wallNS::TEXTURE_COLS, &wallTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing wall1"));
    walls[0]->setFrames(wallNS::WALL_START_FRAME, wallNS::WALL_END_FRAME);
    walls[0]->setCurrentFrame(wallNS::WALL_START_FRAME);
    walls[0]->setX(gladiatorNS::ARENA_START_X);
    walls[0]->setY(gladiatorNS::ARENA_START_Y);

	//wall right
	Wall* right = new Wall(gladiatorNS::ARENA_HEIGHT,gladiatorNS::WALL_WIDTH);
	walls.push_back(right);
	right = 0;
	if (!walls[1]->initialize(this, gladiatorNS::WALL_WIDTH, gladiatorNS::ARENA_HEIGHT, wallNS::TEXTURE_COLS, &wallTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing wall1"));
    walls[1]->setFrames(wallNS::WALL_START_FRAME, wallNS::WALL_END_FRAME);
    walls[1]->setCurrentFrame(wallNS::WALL_START_FRAME);
    walls[1]->setX(gladiatorNS::ARENA_WIDTH + gladiatorNS::ARENA_START_X);
    walls[1]->setY(gladiatorNS::ARENA_START_Y);

	//wall top
	Wall* top = new Wall(gladiatorNS::WALL_WIDTH,gladiatorNS::ARENA_WIDTH);
	walls.push_back(top);
	top = 0;
	//reverse height and width for rotated wall
	if (!walls[2]->initialize(this, gladiatorNS::ARENA_WIDTH, gladiatorNS::WALL_WIDTH, 1, &hWallTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing wall1"));
    walls[2]->setFrames(wallNS::WALL_START_FRAME, wallNS::WALL_END_FRAME);
    walls[2]->setCurrentFrame(wallNS::WALL_START_FRAME);
    walls[2]->setX(gladiatorNS::ARENA_START_X);
    walls[2]->setY(gladiatorNS::ARENA_START_Y);

	//wall bottom
	Wall* bottom = new Wall(gladiatorNS::WALL_WIDTH,gladiatorNS::ARENA_WIDTH);
	walls.push_back(bottom);
	bottom = 0;
	//reverse height and width for rotated wall
	if (!walls[3]->initialize(this, gladiatorNS::ARENA_WIDTH, gladiatorNS::WALL_WIDTH, 1, &hWallTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing wall1"));
    walls[3]->setFrames(wallNS::WALL_START_FRAME, wallNS::WALL_END_FRAME);
    walls[3]->setCurrentFrame(wallNS::WALL_START_FRAME);
    walls[3]->setX(gladiatorNS::ARENA_START_X);
    walls[3]->setY(gladiatorNS::ARENA_START_Y + gladiatorNS::ARENA_HEIGHT);

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
			m->setScale(gladiatorNS::MIRROR_SIZE);
			mirrors.push_back(m);
			m = 0;
		}
	}

	//mirrors for corners
	//top left
	Mirror* m = new Mirror(mirrorNS::CORNER_COLOR);
	if(!m->initialize(this, mirrorNS::WIDTH, mirrorNS::HEIGHT, mirrorNS::TEXTURE_COLS, &mirrorTexture))
			throw(GameError(gameErrorNS::FATAL_ERROR, "error initializing Mirror"));
	m->setX(gladiatorNS::ARENA_START_X - (mirrorNS::WIDTH * mirrorNS::CORNER_RATIO)/4);
	m->setY(gladiatorNS::ARENA_START_Y - (mirrorNS::HEIGHT * mirrorNS::CORNER_RATIO)/4);
	m->setVelocity(VECTOR2(mirrorNS::SPEED,-mirrorNS::SPEED));
	m->setScale(mirrorNS::CORNER_RATIO);
	mirrors.push_back(m);
	
	//top right
	m = new Mirror(mirrorNS::CORNER_COLOR);
	if(!m->initialize(this, mirrorNS::WIDTH, mirrorNS::HEIGHT, mirrorNS::TEXTURE_COLS, &mirrorTexture))
			throw(GameError(gameErrorNS::FATAL_ERROR, "error initializing Mirror"));
	m->setX(gladiatorNS::ARENA_START_X + gladiatorNS::ARENA_WIDTH - (mirrorNS::WIDTH * mirrorNS::CORNER_RATIO)/2);
	m->setY(gladiatorNS::ARENA_START_Y - (mirrorNS::HEIGHT * mirrorNS::CORNER_RATIO)/4);
	m->setVelocity(VECTOR2(mirrorNS::SPEED,-mirrorNS::SPEED));
	m->setScale(mirrorNS::CORNER_RATIO);
	mirrors.push_back(m);

	//bottom left
	m = new Mirror(mirrorNS::CORNER_COLOR);
	if(!m->initialize(this, mirrorNS::WIDTH, mirrorNS::HEIGHT, mirrorNS::TEXTURE_COLS, &mirrorTexture))
			throw(GameError(gameErrorNS::FATAL_ERROR, "error initializing Mirror"));
	m->setX(gladiatorNS::ARENA_START_X - (mirrorNS::WIDTH * mirrorNS::CORNER_RATIO)/4);
	m->setY(gladiatorNS::ARENA_START_Y + gladiatorNS::ARENA_HEIGHT - (mirrorNS::HEIGHT * mirrorNS::CORNER_RATIO)/2);
	m->setVelocity(VECTOR2(mirrorNS::SPEED,-mirrorNS::SPEED));
	m->setScale(mirrorNS::CORNER_RATIO);
	mirrors.push_back(m);

	//bottom right
	m = new Mirror(mirrorNS::CORNER_COLOR);
	if(!m->initialize(this, mirrorNS::WIDTH, mirrorNS::HEIGHT, mirrorNS::TEXTURE_COLS, &mirrorTexture))
			throw(GameError(gameErrorNS::FATAL_ERROR, "error initializing Mirror"));
	m->setX(gladiatorNS::ARENA_START_X + gladiatorNS::ARENA_WIDTH - (mirrorNS::WIDTH * mirrorNS::CORNER_RATIO)/2);
	m->setY(gladiatorNS::ARENA_START_Y + gladiatorNS::ARENA_HEIGHT - (mirrorNS::HEIGHT * mirrorNS::CORNER_RATIO)/2);
	m->setVelocity(VECTOR2(mirrorNS::SPEED,-mirrorNS::SPEED));
	m->setScale(mirrorNS::CORNER_RATIO);
	mirrors.push_back(m);
	m=0;

	//left enemy
	//construction takes the direction the turret should be pointing
	Enemy* e = new Enemy(RIGHT);
	if(!e->initialize(this, enemyNS::WIDTH, enemyNS::HEIGHT, enemyNS::TEXTURE_COLS, &enemyTexture))
			throw(GameError(gameErrorNS::FATAL_ERROR, "error initializing Enemy"));
	e->setX(gladiatorNS::ARENA_START_X + enemyNS::HEIGHT/2);
	e->setY(gladiatorNS::ARENA_START_Y + gladiatorNS::DISTANCE_BETWEEN_ARENA_AND_ENEMY_WALLS_H + enemyNS::WIDTH/2);
	e->setVelocity(VECTOR2(0,enemyNS::SPEED));
	e->setDegrees(270);
	enemies.push_back(e);
	e=0;

	//right enemy
	e = new Enemy(LEFT);
	if(!e->initialize(this, enemyNS::WIDTH, enemyNS::HEIGHT, enemyNS::TEXTURE_COLS, &enemyTexture))
			throw(GameError(gameErrorNS::FATAL_ERROR, "error initializing Enemy"));
	e->setX(gladiatorNS::ARENA_START_X+gladiatorNS::ARENA_WIDTH - enemyNS::HEIGHT);
	e->setY(gladiatorNS::ARENA_START_Y + gladiatorNS::ARENA_HEIGHT - gladiatorNS::DISTANCE_BETWEEN_ARENA_AND_ENEMY_WALLS_H - enemyNS::WIDTH*2);
	e->setDegrees(90);
	e->setVelocity(VECTOR2(0,-enemyNS::SPEED));
	e->setDirection(LEFT);
	enemies.push_back(e);
	e=0;

	//top enemy
	e = new Enemy(DOWN);
	if(!e->initialize(this, enemyNS::WIDTH, enemyNS::HEIGHT, enemyNS::TEXTURE_COLS, &enemyTexture))
			throw(GameError(gameErrorNS::FATAL_ERROR, "error initializing Enemy"));
	e->setX(gladiatorNS::ARENA_START_X + gladiatorNS::ARENA_WIDTH - gladiatorNS::DISTANCE_BETWEEN_ARENA_AND_ENEMY_WALLS_V - enemyNS::WIDTH*2);
	e->setY(gladiatorNS::ARENA_START_Y + enemyNS::HEIGHT/3);
	e->setVelocity(VECTOR2(-enemyNS::SPEED,0));
	e->setDirection(DOWN);
	enemies.push_back(e);
	e=0;

	//bottom enemy
	e = new Enemy(UP);
	if(!e->initialize(this, enemyNS::WIDTH, enemyNS::HEIGHT, enemyNS::TEXTURE_COLS, &enemyTexture))
			throw(GameError(gameErrorNS::FATAL_ERROR, "error initializing Enemy"));
	e->setX(gladiatorNS::ARENA_START_X + gladiatorNS::DISTANCE_BETWEEN_ARENA_AND_ENEMY_WALLS_V + enemyNS::WIDTH*2);
	e->setY(gladiatorNS::ARENA_START_Y + gladiatorNS::ARENA_HEIGHT - enemyNS::HEIGHT);
	e->setDegrees(180);
	e->setVelocity(VECTOR2(enemyNS::SPEED,0));
	e->setDirection(UP);
	enemies.push_back(e);
	e=0;

	//enemy walls
	//left
	Wall* w = new Wall(gladiatorNS::ARENA_HEIGHT-gladiatorNS::DISTANCE_BETWEEN_ARENA_AND_ENEMY_WALLS_H*2,gladiatorNS::WALL_WIDTH);
	if (!w->initialize(this, gladiatorNS::WALL_WIDTH, gladiatorNS::ARENA_HEIGHT-gladiatorNS::DISTANCE_BETWEEN_ARENA_AND_ENEMY_WALLS_H*2,
		wallNS::TEXTURE_COLS, &enemyWallTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing wall1"));
    w->setFrames(wallNS::WALL_START_FRAME, wallNS::WALL_END_FRAME);
    w->setCurrentFrame(wallNS::WALL_START_FRAME);
    w->setX(gladiatorNS::ARENA_START_X + gladiatorNS::DISTANCE_BETWEEN_ARENA_AND_ENEMY_WALLS_V);
    w->setY(gladiatorNS::ARENA_START_Y + gladiatorNS::DISTANCE_BETWEEN_ARENA_AND_ENEMY_WALLS_H);
	walls.push_back(w);
	w=0;

	//right
	w = new Wall(gladiatorNS::ARENA_HEIGHT-gladiatorNS::DISTANCE_BETWEEN_ARENA_AND_ENEMY_WALLS_H*2,gladiatorNS::WALL_WIDTH);
	if (!w->initialize(this, gladiatorNS::WALL_WIDTH, gladiatorNS::ARENA_HEIGHT-gladiatorNS::DISTANCE_BETWEEN_ARENA_AND_ENEMY_WALLS_H*2,
		wallNS::TEXTURE_COLS, &enemyWallTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing wall1"));
    w->setFrames(wallNS::WALL_START_FRAME, wallNS::WALL_END_FRAME);
    w->setCurrentFrame(wallNS::WALL_START_FRAME);
    w->setX(gladiatorNS::ARENA_START_X + gladiatorNS::ARENA_WIDTH - gladiatorNS::DISTANCE_BETWEEN_ARENA_AND_ENEMY_WALLS_V);
    w->setY(gladiatorNS::ARENA_START_Y + gladiatorNS::DISTANCE_BETWEEN_ARENA_AND_ENEMY_WALLS_H);
	walls.push_back(w);
	w=0;

	//top
	w = new Wall(gladiatorNS::WALL_WIDTH,gladiatorNS::ARENA_WIDTH-gladiatorNS::DISTANCE_BETWEEN_ARENA_AND_ENEMY_WALLS_V*2 - gladiatorNS::ENEMY_WALL_GAP_SIZE * 2);
	if (!w->initialize(this, gladiatorNS::ARENA_WIDTH-gladiatorNS::DISTANCE_BETWEEN_ARENA_AND_ENEMY_WALLS_V*2 - gladiatorNS::ENEMY_WALL_GAP_SIZE * 2,
		gladiatorNS::WALL_WIDTH, 1, &hEnemyWallTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing wall1"));
    w->setFrames(wallNS::WALL_START_FRAME, wallNS::WALL_END_FRAME);
    w->setCurrentFrame(wallNS::WALL_START_FRAME);
    w->setX(gladiatorNS::ARENA_START_X + gladiatorNS::DISTANCE_BETWEEN_ARENA_AND_ENEMY_WALLS_V + gladiatorNS::ENEMY_WALL_GAP_SIZE);
    w->setY(gladiatorNS::ARENA_START_Y + gladiatorNS::DISTANCE_BETWEEN_ARENA_AND_ENEMY_WALLS_H);
    w->setVelocity(VECTOR2(wallNS::SPEED,-wallNS::SPEED)); // VECTOR2(X, Y)
	walls.push_back(w);
	w=0;

	//bottom
	w = new Wall(gladiatorNS::WALL_WIDTH,gladiatorNS::ARENA_WIDTH-gladiatorNS::DISTANCE_BETWEEN_ARENA_AND_ENEMY_WALLS_V*2 - gladiatorNS::ENEMY_WALL_GAP_SIZE * 2);
	if (!w->initialize(this, gladiatorNS::ARENA_WIDTH-gladiatorNS::DISTANCE_BETWEEN_ARENA_AND_ENEMY_WALLS_V*2 - gladiatorNS::ENEMY_WALL_GAP_SIZE * 2,
		gladiatorNS::WALL_WIDTH, 1, &hEnemyWallTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing wall1"));
    w->setFrames(wallNS::WALL_START_FRAME, wallNS::WALL_END_FRAME);
    w->setCurrentFrame(wallNS::WALL_START_FRAME);
    w->setX(gladiatorNS::ARENA_START_X + gladiatorNS::DISTANCE_BETWEEN_ARENA_AND_ENEMY_WALLS_V + gladiatorNS::ENEMY_WALL_GAP_SIZE);
    w->setY(gladiatorNS::ARENA_START_Y + gladiatorNS::ARENA_HEIGHT - gladiatorNS::DISTANCE_BETWEEN_ARENA_AND_ENEMY_WALLS_H);
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
	//end game
	if(activeEnemies == 0)
	{
		endGamePlayerWins();
	}
}

void LaserGladiator::ai()
{}

void LaserGladiator::collisions()
{
	VECTOR2 collisionVector;
	//check collision between all entities with lasers

	//wall collisions
	//may need to add in some mechanism to make sure lasers do not get stuck in walls, that is the commented out code
	for(int i = 0; i < walls.size(); i++)
	{
		for(int j = 0; j < lasers.size(); j++)
		{
			if(lasers[j]->collidesWith(*walls[i],collisionVector))
			{
				if(walls[i]->getWidth() > walls[i]->getHeight())
				{
					lasers[j]->setVelocity(VECTOR2(lasers[j]->getVelocity().x,lasers[j]->getVelocity().y*-1));
					//lasers[j]->setY((walls[i]->getY()>GAME_HEIGHT/2) ? walls[i]->getY() - 10 : walls[i]->getY() + 10);
				}
				else
				{
					lasers[j]->setVelocity(VECTOR2(lasers[j]->getVelocity().x*-1,lasers[j]->getVelocity().y));
					//lasers[j]->setX((walls[i]->getX()>GAME_HEIGHT) ? walls[i]->getX() - 10 : walls[i]->getX() + 10);
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
				activeEnemies--;
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

void LaserGladiator::endGamePlayerWins()
{
	//do something cool here
	exitGame();
}