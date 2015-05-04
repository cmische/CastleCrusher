#include "Enemies.h"

Snake* Snake::createSnake(cocos2d::Layer layer)
{
    Snake* snake = Snake::create();   
    layer.addChild(snake);
    return snake;
}

bool Snake::init()
{
	Sprite = Sprite::create("Snake.png");
	alive = true;
	scoreWorth = 10;
	scale = 0.2;
	HP = 100;
	addChild(Sprite);
    return true;
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