#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

using namespace cocostudio::timeline;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

void HelloWorld::setViewPointCenter(Point position) {
    auto winSize = Director::getInstance()->getWinSize();

    int x = MAX(position.x, winSize.width / 2);
    int y = MAX(position.y, winSize.height / 2);
    x = MIN(x, (_tileMap->getMapSize().width * this->_tileMap->getTileSize().width) - winSize.width / 2);
    y = MIN(y, (_tileMap->getMapSize().height * _tileMap->getTileSize().height) - winSize.height / 2);
    auto actualPosition = Point(x, y);

    auto centerOfView = Point(winSize.width / 2, winSize.height / 2);
    auto viewPoint = centerOfView - actualPosition;
    this->setPosition(viewPoint);
}

void HelloWorld::setPlayerPosition(Point position)
{
    _player->setPosition(position);
}

void HelloWorld::onTouchEnded(Touch *touch, Event *unused_event)
{
	auto actionTo1 = RotateTo::create(0, 0, 180);
	auto actionTo2 = RotateTo::create(0, 0, 0);
	auto touchLocation = touch->getLocation();

	touchLocation = this->convertToNodeSpace(touchLocation);

	auto playerPos = _player->getPosition();
	auto diff = touchLocation - playerPos;
	if (abs(diff.x) > abs(diff.y)) {
		if (diff.x > 0) {
			playerPos.x += _tileMap->getTileSize().width / 2;
			_player->runAction(actionTo2);
		}
		else {
			playerPos.x -= _tileMap->getTileSize().width / 2;
			_player->runAction(actionTo1);
		}
	}
	else {
	 if (diff.y > 0) {
	    playerPos.y += _tileMap->getTileSize().height / 2;
	 }
		else {
		 playerPos.y -= _tileMap->getTileSize().height / 2;
		}
 }

	if (playerPos.x <= (_tileMap->getMapSize().width * _tileMap->getMapSize().width) &&
	 playerPos.y <= (_tileMap->getMapSize().height * _tileMap->getMapSize().height) &&
	 playerPos.y >= 0 &&
	 playerPos.x >= 0)
	{
	 this->setPlayerPosition(playerPos);

 }

	this->setViewPointCenter(_player->getPosition());
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
//	HelloWorld:: 
//    auto rootNode = CSLoader::createNode("MainScene.csb");
//
//    addChild(rootNode);

	this->_tileMap = TMXTiledMap::create("TileMap.tmx");
	this->_background = _tileMap->layerNamed("Background");
	addChild(_tileMap, -1);

	TMXObjectGroup *objects = _tileMap->getObjectGroup("Objects");
	CCASSERT(NULL != objects, "'Objects' object group not found");
	auto playerShowUpPoint = objects->getObject("SpawnPoint");
	CCASSERT(!playerShowUpPoint.empty(), "PlayerShowUpPoint object not found");

	int x = playerShowUpPoint["x"].asInt();
	int y = playerShowUpPoint["y"].asInt();

	_player = Sprite::create("SirBrawnlyTemp.png");
	_player->setPosition(x + _tileMap->getTileSize().width / 2, y + _tileMap->getTileSize().height / 2);
	_player->setScale(0.5);

	addChild(_player);
	setViewPointCenter(_player->getPosition());

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [&](Touch *touch, Event *unused_event)->bool {return true;};
	listener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    return true;
}
