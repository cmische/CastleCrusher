#ifndef __Enemies_H__
#define __Enemies_H__

#include "cocos2d.h"

class Snake : public cocos2d::Sprite
{
public:
    
	float PosX;
	float PosY;
	bool alive;
	int scoreWorth;
	float scale;
	int HP;
	int AI;
	cocos2d::TMXTiledMap *_tileMap;
	cocos2d::TMXLayer *_collide;

	static Snake* createSnake(float PosX, float PosY, cocos2d::TMXTiledMap *_tileMap, cocos2d::TMXLayer *enemyLayer);

	virtual bool init();
    virtual void shoot(float dt);
	virtual void move(float dt);

	CREATE_FUNC(Snake);

};

class Ogre : public cocos2d::Sprite
{
public:
    
	float PosX;
	float PosY;
	bool alive;
	int scoreWorth;
	float scale;
	int HP;
	int AI;
	cocos2d::TMXTiledMap *_tileMap;
	cocos2d::TMXLayer *_collide;

	static Ogre* createOgre(float PosX, float PosY, cocos2d::TMXTiledMap *_tileMap, cocos2d::TMXLayer *enemyLayer);

	virtual bool init();
    virtual void shoot(float dt);
	virtual void move(float dt);

	CREATE_FUNC(Ogre);

};

#define MOVE_NORTH \
ccx = PosX; \
ccy = PosY + 32; \
if (checkCollide(cocos2d::Point(ccx, ccy),  _tileMap, _collide)) \
{ \
	PosX = ccx; \
	PosY = ccy; \
	setPosition(PosX, PosY); \
}

#define MOVE_EAST \
ccx = PosX + 32; \
ccy = PosY; \
if (checkCollide(cocos2d::Point(ccx, ccy),  _tileMap, _collide)) \
{ \
	PosX = ccx; \
	PosY = ccy; \
	setPosition(PosX, PosY); \
}

#define MOVE_SOUTH \
ccx = PosX; \
ccy = PosY - 32; \
if (checkCollide(cocos2d::Point(ccx, ccy),  _tileMap, _collide)) \
{ \
	PosX = ccx; \
	PosY = ccy; \
	setPosition(PosX, PosY); \
}

#define MOVE_WEST \
ccx = PosX - 32; \
ccy = PosY; \
if (checkCollide(cocos2d::Point(ccx, ccy),  _tileMap, _collide)) \
{ \
	PosX = ccx; \
	PosY = ccy; \
	setPosition(PosX, PosY); \
}

#define MOVE_NE \
ccx = PosX + 32; \
ccy = PosY + 32; \
if (checkCollide(cocos2d::Point(ccx, ccy),  _tileMap, _collide)) \
{ \
	PosX = ccx; \
	PosY = ccy; \
	setPosition(PosX, PosY); \
}

#define MOVE_SE \
ccx = PosX + 32; \
ccy = PosY - 32; \
if (checkCollide(cocos2d::Point(ccx, ccy),  _tileMap, _collide)) \
{ \
	PosX = ccx; \
	PosY = ccy; \
	setPosition(PosX, PosY); \
}

#define MOVE_SW \
ccx = PosX - 32; \
ccy = PosY - 32; \
if (checkCollide(cocos2d::Point(ccx, ccy),  _tileMap, _collide)) \
{ \
	PosX = ccx; \
	PosY = ccy; \
	setPosition(PosX, PosY); \
}

#define MOVE_NW \
ccx = PosX - 32; \
ccy = PosY + 32; \
if (checkCollide(cocos2d::Point(ccx, ccy),  _tileMap, _collide)) \
{ \
	PosX = ccx; \
	PosY = ccy; \
	setPosition(PosX, PosY); \
}

#endif // __Enemies_H__
