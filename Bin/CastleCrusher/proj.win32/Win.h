#ifndef __MainMenu_SCENE_H__
#define __MainMenu_SCENE_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

class Win : public cocos2d::Layer
{
	//declare private functions for click event handling
	void onNewGame(cocos2d::Ref *sender);
	void onOptions(cocos2d::Ref *sender);
	void onExit(cocos2d::Ref *sender);

public:

	//important cocos stuff
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(Win);
};

#endif // __MainMenu_SCENE_H__