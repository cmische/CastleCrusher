#include "Enemies.h"
#include "Level1.h"

int ccx;
int ccy;

cocos2d::Point tileCoordForPosition(cocos2d::Point position, cocos2d::TMXTiledMap *map)
{
    int x = position.x / map->getTileSize().width;
    int y = ((map->getMapSize().height * map->getTileSize().height) - position.y) / map->getTileSize().height;
    return cocos2d::ccp(x, y);
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
	HP = 100;
	AI = 0;
	scoreWorth = 10;
	scale = (float)0.032;
	setPosition(PosX, PosY);
	setScale(scale);
	setGlobalZOrder(-1);
	schedule(CC_SCHEDULE_SELECTOR(Snake::move), (float).5);
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
	int x = PosX;
	int y = PosY;
	bool swapdirection = true;
	if (swapdirection)
	{
		MOVE_NORTH
	}
	if (swapdirection == false)
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
	schedule(CC_SCHEDULE_SELECTOR(Snake::move), (float).5);
	return true;
}

void Ogre::shoot(float dt)
{
}

void Ogre::move(float dt)
{
	switch (AI)
	{
	case 0: MOVE_WEST; AI++; break;
	case 1: MOVE_WEST; AI++; break;
	case 2: MOVE_WEST; AI++; break;
	case 3: MOVE_EAST; AI++; break;
	case 4: MOVE_EAST; AI++; break;
	case 5: MOVE_EAST; AI=0; break;
	default: CCLOG("invalid snake index"); break;
	}
}