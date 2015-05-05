#include "Enemies.h"




Snake* Snake::createSnake(float x, float y)
{
    Snake* snake = Snake::create();
	snake->PosX = x;
	snake->PosY = y;
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
	PosX = PosX + 10;
	setPosition(PosX, PosY);
}