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
this->addChild(backgroundSprite);

// Main menu with 3 items
auto playItem = MenuItemImage::create("playbutton.png","playbutton.png", CC_CALLBACK_1(MainMenu::onNewGame, this));
//MenuItemFont* item2 = MenuItemFont::create( "Options", this, menu_selector(MainMenu::onOptions) );
//MenuItemFont* item3 = MenuItemFont::create( "Quit", this, menu_selector(MainMenu::onQuit) );

// combine to form a menu and allign Vertically
playItem->setPosition( Point( winSize.width / 2, winSize.height / 2));
auto menu = Menu::create( playItem, NULL );
menu->setPosition( Point( winSize.width / 2, winSize.height / 2));
//menu->alignItemsVertically();

// add this to the layer
this->addChild( menu);


return true;
}


void MainMenu::onNewGame(cocos2d::Ref *sender)
{
	auto scene = Level1::createScene();
	//Director::getInstance()->replaceScene(TransitionFade::create(2, scene ));
	Director::getInstance()->replaceScene(scene);
}

/*
void MainMenu::onOptions(Object* pSender)
{
// Will do this on next step
}


void MainMenu::onQuit(Object* pSender)
{
// Exit game
CCDirector::sharedDirector()->end();
}