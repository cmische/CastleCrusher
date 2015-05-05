#ifndef __Enemies_H__
#define __Enemies_H__

#include "cocos2d.h"

USING_NS_CC;

class Snake : public cocos2d::Sprite
{
public:
    
	float PosX;
	float PosY;
	bool alive;
	int scoreWorth;
	float scale;
	int HP;

	static Snake* createSnake(float PosX, float PosY);

	virtual bool init();
    virtual void shoot(float dt);
	virtual void move(float dt);

	CREATE_FUNC(Snake);

};

#endif // __Enemies_H__
