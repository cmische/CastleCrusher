#include "Enemies.h"

Snake* Snake::createSnake(float x, float y)
{
    Snake* snake = Snake::create();
	snake->PosX = x;
	snake->PosY = y;
	snake->Sprite = Sprite::create("snake.png");
	snake->alive = true;
	snake->scoreWorth = 10;
	snake->scale = (float)0.032;
	snake->Sprite->setScale(snake->scale);
	snake->HP = 100;
	snake->Sprite->setPosition(snake->PosX, snake->PosY);
	snake->Sprite->setGlobalZOrder(-1);
    return snake;
}

void Snake::shoot(float dt)
{
	//I suppose snakes shoot venom?
	/*
    if(!GameLayer::isDie && _target->alive())
    {
        //get angle to player;
        float angle = (getPosition()-_target->getPosition()).getAngle();
        auto bullet =BulletController::spawnBullet(kEnemyBullet, getPosition(), Vec2(cosf(angle)*-500, sinf(angle)*-500));
        //auto bullet =BulletController::spawnBullet(kEnemyBullet, getPosition(), Vec2(0,-500));
        bullet->setRotation(-CC_RADIANS_TO_DEGREES(angle)-90);
        //log("aaaaaaa");
    }
    else{
        //log("player is dead,hahahaha");
    }
	*/
}

void Snake::move(float dt)
{
	//I suppose snakes shoot venom?
	/*
    if(!GameLayer::isDie && _target->alive())
    {
        //get angle to player;
        float angle = (getPosition()-_target->getPosition()).getAngle();
        auto bullet =BulletController::spawnBullet(kEnemyBullet, getPosition(), Vec2(cosf(angle)*-500, sinf(angle)*-500));
        //auto bullet =BulletController::spawnBullet(kEnemyBullet, getPosition(), Vec2(0,-500));
        bullet->setRotation(-CC_RADIANS_TO_DEGREES(angle)-90);
        //log("aaaaaaa");
    }
    else{
        //log("player is dead,hahahaha");
    }
	*/
}