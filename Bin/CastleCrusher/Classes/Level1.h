#ifndef __Level1_SCENE_H__
#define __Level1_SCENE_H__

#include "cocos2d.h"

class Level1 : public cocos2d::Layer
{
	cocos2d::TMXTiledMap *_tileMap;
	cocos2d::TMXLayer *_background;
	cocos2d::Sprite *_player;
	cocos2d::Sprite *_bar;
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    // implement the "static create()" method manually

	void setViewPointCenter(cocos2d::Point position);
	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void startUI();
	void setPlayerPosition(cocos2d::Point position);
    CREATE_FUNC(Level1);
};

#endif // __Level1_SCENE_H__