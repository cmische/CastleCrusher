#include "Lose.h"
//Include level1 header so we can call its scene create method and transition our scene to it
#include "Level1.h"

USING_NS_CC;

Scene* Lose::createScene() 
{
	//constructs our scene, constructs a layer, adds layer to the scene, returns the scene
	auto scene = Scene::create();
	auto layer = Lose::create();
	scene->addChild(layer);
	return scene;
}

bool Lose::init()
{
	//No idea what superinit does.
	//////////////////////////////
	// 1. super init first
	if ( !Layer::init() )
	{
		return false;
	}
	//new image
	auto backgroundSprite = Sprite::create("DefeatWindow.png");


	//grabs window size from the director for the scenes, the director is basically a static object that manages which scene we are on and transitions and stuff
	auto winSize = Director::getInstance()->getWinSize();
	//Center the background
	backgroundSprite->setPosition( Point( winSize.width / 2, winSize.height / 2));
	//Add the background with z level -1, anything with a greater z level will be displayed above a lower z level
	this->addChild(backgroundSprite, -1);
	//buttonheight variable for easier button placement adjusting
	int buttonheight = winSize.height / 10;
	//create button objects with callbacks to event methods

	auto newGameItem = MenuItemImage::create("newGame.png","newGameSelected.png", CC_CALLBACK_1(Lose::onNewGame, this));
	auto optionsItem = MenuItemImage::create("options.png","optionsSelected.png", CC_CALLBACK_1(Lose::onOptions, this));
	auto exitItem = MenuItemImage::create("exit.png","exitSelected.png", CC_CALLBACK_1(Lose::onExit, this));
	//Position the buttons with an x value and a y value of buttonheight
	newGameItem->setPosition( winSize.width / 2, buttonheight);
	optionsItem->setPosition( winSize.width / 10, buttonheight );
	exitItem->setPosition( winSize.width * 0.9, buttonheight);
	//create a menu object of our buttons, last parameter is always NULL I think
	auto menu = Menu::create( newGameItem, optionsItem, exitItem, NULL );
	//I think the button position is placed relative to the menu origin position from experimentation; so I just made the menu position 0,0
	menu->setPosition( 0, 0);
	//add menu to the scene
	this->addChild( menu);


	/* display floats on debug console for adjusting
	std::ostringstream ss;
	std::string s;
	std::wstring stemp;
	
	s = "Debugging info \n";
	stemp = std::wstring(s.begin(), s.end());
	OutputDebugString(stemp.c_str());

	ss << winSize.width / 2;
	s = "window width is: " + ss.str() + "\n";
	stemp = std::wstring(s.begin(), s.end());
	OutputDebugString(stemp.c_str());
	ss.str("");

	ss << winSize.height / 2;
	s = "window height is: " + ss.str() + "\n";
	stemp = std::wstring(s.begin(), s.end());
	OutputDebugString(stemp.c_str());
	ss.str("");
	*/

	return true;
}

void Lose::onNewGame(cocos2d::Ref *sender)
{
	//runs when new game is selected on main menu
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("titlescreenping.wav");
	auto scene = Level1::createScene();

	Director::getInstance()->replaceScene(TransitionFade::create(2, scene ));
	//1Director::getInstance()->replaceScene(scene);
}

void Lose::onOptions(cocos2d::Ref *sender)
{
	//runs when options is selected on main menu
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("titlescreenping.wav");
	Director::getInstance()->end();
}

void Lose::onExit(cocos2d::Ref *sender)
{
	//runs when exit is selected on main menu
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("titlescreenping.wav");
	Director::getInstance()->end();
}
