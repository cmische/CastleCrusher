#ifndef __Enemies_H__
#define __Enemies_H__

#include "cocos2d.h"

USING_NS_CC;

class Snake : public Sprite
{
public:
    CREATE_FUNC(Snake);

	cocos2d::Sprite *Sprite;
	float PosX;
	float PosY;
	bool alive;
	int scoreWorth;
	float scale;
	int HP;

	static Snake* createSnake(float PosX, float PosY);

    virtual void shoot(float dt);
	virtual void move(float dt);

	
};

#endif // __Enemies_H__
