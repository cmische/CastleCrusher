#include "MainMenu.h"
#include "Level1.h"

USING_NS_CC;

Scene* MainMenu::createScene() 
{
	// ‘scene’ is an autorelease object
	auto scene = Scene::create();
	// ‘layer’ is an autorelease object
	auto layer = MainMenu::create();
	// add layer as a child to scene
	scene->addChild(layer);
	// return the Main menu scene
	return scene;
}

// on “init” you need to initialize your instance
bool MainMenu::init()
{
	//////////////////////////////
	// 1. super init first
	if ( !Layer::init() )
	{
		return false;
	}
	// Enable touch/click actions
	auto backgroundSprite = Sprite::create("background.png");
	auto winSize = Director::getInstance()->getWinSize();
	backgroundSprite->setPosition( Point( winSize.width / 2, winSize.height / 2));
	this->addChild(backgroundSprite, -1);
	// Main menu with 3 items
	int buttonheight = winSize.height / 10;
	auto newGameItem = MenuItemImage::create("newGame.png","newGameSelected.png", CC_CALLBACK_1(MainMenu::onNewGame, this));
	auto optionsItem = MenuItemImage::create("options.png","optionsSelected.png", CC_CALLBACK_1(MainMenu::onOptions, this));
	auto exitItem = MenuItemImage::create("exit.png","exitSelected.png", CC_CALLBACK_1(MainMenu::onExit, this));
	newGameItem->setPosition( winSize.width / 2, buttonheight);
	optionsItem->setPosition( winSize.width / 10, buttonheight );
	exitItem->setPosition( winSize.width * 0.9, buttonheight);
	auto menu = Menu::create( newGameItem, optionsItem, exitItem, NULL );
	menu->setPosition( 0, 0);
	//menu->alignItemsVertically();
	// add this to the layer
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

void MainMenu::onNewGame(cocos2d::Ref *sender)
{
	auto scene = Level1::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(2, scene ));
}

void MainMenu::onOptions(cocos2d::Ref *sender)
{
	Director::getInstance()->end();
}

void MainMenu::onExit(cocos2d::Ref *sender)
{
	Director::getInstance()->end();
}
