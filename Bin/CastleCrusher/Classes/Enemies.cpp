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
	snake->enemyLayer = layer;
	CCLOG("Created Snake");
    return snake;
}

bool Snake::init()
{
	initWithFile("Snake.png");
	alive = true;
	HP = 100;
	scoreWorth = 10;
	scale = (float)0.032;
	setPosition(PosX, PosY);
	setScale(scale);
	setGlobalZOrder(-1);
	schedule(CC_SCHEDULE_SELECTOR(Snake::move), (float).5);
	CCLOG("Created Scheduler");
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
	CCLOG("Moved");
	ccx = PosX + 32;
	ccy = PosY;
	if (checkCollide(cocos2d::Point(ccx, ccy),  _tileMap, enemyLayer))
	{
		PosX = ccx;
		PosY = ccy;
		setPosition(PosX, PosY);
	}
}

//---------------------------- OGRE --------------------------------

Ogre* Ogre::createOgre(float x, float y, cocos2d::TMXTiledMap *map, cocos2d::TMXLayer *layer)
{
    Ogre* snake = Ogre::create();
	snake->PosX = x;
	snake->PosY = y;
	snake->_tileMap = map;
	snake->enemyLayer = layer;
	CCLOG("Created Ogre");
    return snake;
}

bool Ogre::init()
{
	initWithFile("Ogre.png");
	alive = true;
	HP = 100;
	scoreWorth = 10;
	scale = (float)0.032;
	setPosition(PosX, PosY);
	setScale(scale);
	setGlobalZOrder(-1);
	schedule(CC_SCHEDULE_SELECTOR(Snake::move), (float).5);
	CCLOG("Created Scheduler");
	return true;
}

void Ogre::shoot(float dt)
{
}

void Ogre::move(float dt)
{
	CCLOG("Moved");
	ccx = PosX;
	ccy = PosY + 32;
	if (checkCollide(cocos2d::Point(ccx, ccy),  _tileMap, enemyLayer))
	{
		PosX = ccx;
		PosY = ccy;
		setPosition(PosX, PosY);
	}
}