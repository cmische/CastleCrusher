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
	cocos2d::TMXTiledMap *_tileMap;
	cocos2d::TMXLayer *enemyLayer;

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
	cocos2d::TMXTiledMap *_tileMap;
	cocos2d::TMXLayer *enemyLayer;

	static Ogre* createOgre(float PosX, float PosY, cocos2d::TMXTiledMap *_tileMap, cocos2d::TMXLayer *enemyLayer);

	virtual bool init();
    virtual void shoot(float dt);
	virtual void move(float dt);

	CREATE_FUNC(Ogre);

};

#endif // __Enemies_H__
