#ifndef __MainMenu_SCENE_H__
#define __MainMenu_SCENE_H__

#include "cocos2d.h"

class MainMenu : public cocos2d::Layer
{
	// functions for click even handling
	void onNewGame(cocos2d::Ref *sender);
//	void onOptions(Object* pSender);
	void onQuit(cocos2d::Ref *sender);
public:
	// there’s no ‘id’ in cpp, so we recommand to return the exactly class pointer
	static cocos2d::Scene* createScene();
	// Here’s a difference. Method ‘init’ in cocos2d-x returns bool, instead of returning ‘id’ in cocos2d-iphone
	virtual bool init();

	// implement the “static node()” method manually
	CREATE_FUNC(MainMenu);
};

#endif // __MainMenu_SCENE_H__