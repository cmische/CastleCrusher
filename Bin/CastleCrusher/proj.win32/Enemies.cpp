#include "Enemies.h"
#include "Level1.h"

int ccx;
int ccy;
std::default_random_engine generator;
std::uniform_int_distribution<int> distribution(0,3);

cocos2d::Point tileCoordForPosition(cocos2d::Point position, cocos2d::TMXTiledMap *map)
{
    int x = position.x / map->getTileSize().width;
    int y = ((map->getMapSize().height * map->getTileSize().height) - position.y) / map->getTileSize().height;
    return cocos2d::Vec2(x, y);
}

bool checkCollide(cocos2d::Point pos, cocos2d::TMXTiledMap *map, cocos2d::TMXLayer *layer)
{
	cocos2d::Value properties = map->getPropertiesForGID(layer->tileGIDAt(tileCoordForPosition(pos, map)));
	if(! properties.isNull()) {
		cocos2d::ValueMap dict = properties.asValueMap();
		if (dict.at("collide").asString().compare("true") == 0) {
			return false;
		}
	}
	return true;
}

//---------------------------- Snake --------------------------------

Snake* Snake::createSnake(float x, float y, cocos2d::TMXTiledMap *map, cocos2d::TMXLayer *layer)
{
    Snake* snake = Snake::create();
	snake->PosX = x;
	snake->PosY = y;
	snake->_tileMap = map;
	snake->_collide = layer;
    return snake;
}

bool Snake::init()
{
	initWithFile("Snake.png");
	alive = true;
	swapdirection = true;
	HP = 100;
	AI = 0;
	scoreWorth = 10;
	scale = (float)0.032;
	setPosition(PosX, PosY);
	setScale(scale);
	setGlobalZOrder(-1);
	schedule(CC_SCHEDULE_SELECTOR(Snake::move), (float)0.1);
	this->setName("snake");
	return true;
}

void Snake::shoot(float dt)
{
	//I suppose snakes shoot venom?
	/*
	empty for now
	*/
}

void Snake::move(float dt)
{
	float x = PosX;
	float y = PosY;
	
	if (swapdirection)
	{
		MOVE_NORTH
	}
	if (!swapdirection)
	{
		MOVE_SOUTH
	}
	if ((PosX == x) && (PosY == y))
	{
		swapdirection = !swapdirection;
	}
	
}

//---------------------------- OGRE --------------------------------

Ogre* Ogre::createOgre(float x, float y, cocos2d::TMXTiledMap *map, cocos2d::TMXLayer *layer)
{
    Ogre* snake = Ogre::create();
	snake->PosX = x;
	snake->PosY = y;
	snake->_tileMap = map;
	snake->_collide = layer;
    return snake;
}

bool Ogre::init()
{
	initWithFile("Ogre.png");
	alive = true;
	HP = 100;
	AI = 0;
	scoreWorth = 10;
	scale = (float)0.030;
	setPosition(PosX, PosY);
	setScale(scale);
	setGlobalZOrder(-1);
	schedule(CC_SCHEDULE_SELECTOR(Snake::move), (float)0.1);
	this->setName("ogre");
	return true;
}

void Ogre::shoot(float dt)
{
}

void Ogre::move(float dt)
{
	int random = distribution(generator);
	switch (random)
	{
	case 0: MOVE_NORTH; AI++; break;
	case 1: MOVE_EAST; AI++; break;
	case 2: MOVE_SOUTH; AI++; break;
	case 3: MOVE_WEST; AI++; break;
	case 4: MOVE_NE; AI++; break;
	case 5: MOVE_SE; AI++; break;
	case 6: MOVE_SW; AI++; break;
	case 7: MOVE_NW; AI=0; break;
	default: CCLOG("invalid snake index"); break;
	}
}

//---------------------------- SWORD --------------------------------


Sword* Sword::createSword(float *playerPosX, float *playerPosY, cocos2d::TMXTiledMap *map, cocos2d::TMXLayer *layer, cocos2d::Point target)
{
    Sword* sword = Sword::create();
	sword->PosX = *playerPosX;
	sword->PosY = *playerPosY;
	sword->playerPosXpointer = playerPosX;
	sword->playerPosYpointer = playerPosY;
	sword->_tileMap = map;
	sword->_collide = layer;
	sword->target = target;
	int xOffset = sword->target.x - *(sword->playerPosXpointer);
	int yOffset = sword->target.y - *(sword->playerPosYpointer);
	sword->target.x = sword->PosX + (xOffset * 1.5);
	sword->target.y = sword->PosY + (yOffset * 1.5);
	

    return sword;
}

bool Sword::init()
{
	initWithFile("BoomerangSword.png");
	alive = true;
	endThrowReached = false;
	scale = ((float)0.13);
	setPosition(PosX, PosY);
	setScale(scale);
	setGlobalZOrder(-1);
	swordSpeed = (float)0.05;
	schedule(CC_SCHEDULE_SELECTOR(Sword::update));
	cocos2d::Vector<cocos2d::Node *> layers = cocos2d::Director::getInstance()->getRunningScene()->getChildren();
	for (int i = 0; i < layers.size(); i++)
	{
		if (layers.at(i)->getName() == "level")
		{
			level1layer = layers.at(i);
		}
	}
	return true;
}

void Sword::update(float dt)
{
	//This method is called with every frame update, it simply moves the camera 15% closer to the distance between where it is and the player with every frame
	//set it up this way so if _playerPosX == camX, nothing happens
	if (endThrowReached)
	{
		PosX += (0.02 * (*playerPosXpointer - PosX));
		PosY += (0.02 * (*playerPosYpointer - PosY));
	}
	else
	{
		PosX += (swordSpeed * (target.x - PosX));
		PosY += (swordSpeed * (target.y - PosY));
	}

	setRotation(getRotation() + 13);
	setPosition(PosX, PosY);

	if ((abs(PosX - target.x) < 3) && (abs(PosY - target.y) < 3) )
	{
		endThrowReached = true;
	}
	
	for (int i = 0; i < level1layer->getChildrenCount(); i++)
	{

		if ( level1layer->getChildren().at(i)->getName() == "snake" || level1layer->getChildren().at(i)->getName() == "ogre")
		{
			float x = level1layer->getChildren().at(i)->getPositionX();
			float y = level1layer->getChildren().at(i)->getPositionY();
			if ((abs(PosX - x) < 54) && (abs(PosY - y) < 54) )
			{
				level1layer->getChildren().at(i)->removeFromParentAndCleanup(true);
			}
		}

	}

	if ((abs(PosX - *playerPosXpointer) < 50) && (abs(PosY - *playerPosYpointer) < 50) && (endThrowReached) )
	{
		removeFromParentAndCleanup(true);
	}


}

/*
	//This method is called with every frame update, it simply moves the camera 15% closer to the distance between where it is and the player with every frame
	//set it up this way so if _playerPosX == camX, nothing happens
	camX += (camAdjustSpeed * (_playerPosX - camX));
	camY += (camAdjustSpeed * (_playerPosY - camY));
	//Move the camera to the new position
	this->setViewPoint(Point(camX, camY));
*/