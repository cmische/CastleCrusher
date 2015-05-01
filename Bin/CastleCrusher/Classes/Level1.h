//This ifndef, define, and endif stuff just protects header files from being defined more than once or recursively. That causes problems.
#ifndef __Level1_SCENE_H__
#define __Level1_SCENE_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

class Level1 : public cocos2d::Layer
{
	/*After messing around for 3 hours trying to make these static variables for the class,
	I found out cocos2d just plain doesn't support static variables unless they are "POD",
	here's a quote from some documentation:

	"Objects with static storage duration, including global variables, static variables,
	static class member variables, and function static variables, must be Plain Old Data (POD):
	only ints, chars, floats, or pointers, or arrays/structs of POD."

	So yeah, that's really annoying. */

	/* Additionally, for some reason, the common coding style seems to be to declare your variables
	as pointers and then use the -> operator to dereference them when you use them. The . operater
	and -> operator are basically the same, all the -> operator does is convert a pointer to it's
	object it was pointing at first. Aka object->method() == *object.method. The way cocos developers
	use pointers makes me want to tear my hair out a bit, although I'm sure they have their reasons.
	
	Basically, if it has a * here, you have to use ->
	if it doesn't, you use a . operator */

	cocos2d::TMXTiledMap *_tileMap;
	cocos2d::TMXLayer *_collide;
	cocos2d::Sprite *_player;
	cocos2d::Sprite *_snake;
	cocos2d::Sprite *_bar;
	cocos2d::Sprite *_ogre;
	float _playerPosX;
	float _playerPosY;
	float _snakePosX;
	float _snakePosY;
	float _snakeBasePosX;
	float _snakeBasePosY;
	int _snakePosIndex;
	float _ogrePosX;
	float _ogrePosY;
	float _ogreBasePosX;
	float _ogreBasePosY;
	int _ogrePosIndex;

	//declare our functions
	void setViewPoint(cocos2d::Point position);
	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void startUI();
	void setPlayerPosition(cocos2d::Point position);
	void camFollowPlayer(float dt);
	void enemyAI(float dt);
	cocos2d::Point tileCoordForPosition(cocos2d::Point position);

public:

	//important cocos stuff
	static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(Level1);
};

#endif // __Level1_SCENE_H__