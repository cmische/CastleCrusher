#include "Level1.h"

USING_NS_CC;

//using namespace cocostudio::timeline;

Scene* Level1::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();   
    // 'layer' is an autorelease object
    auto layer = Level1::create();
    // add layer as a child to scene
    scene->addChild(layer);
    // return the scene
    return scene;
}

void Level1::setViewPointCenter(Point position) {
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

void Level1::setPlayerPosition(Point position)
{
    _player->setPosition(position);
}

void Level1::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	auto actionTo1 = RotateTo::create(0, 0, 180);
	auto actionTo2 = RotateTo::create(0, 0, 0);
	auto playerPos = _player->getPosition();
	if (keyCode == EventKeyboard::KeyCode::KEY_W || keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW) {
		playerPos.y += _tileMap->getTileSize().height;
	}
	if (keyCode == EventKeyboard::KeyCode::KEY_A || keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW) {
		playerPos.x -= _tileMap->getTileSize().width;
		_player->runAction(actionTo1);
	}
	if (keyCode == EventKeyboard::KeyCode::KEY_S || keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW) {
		playerPos.y -= _tileMap->getTileSize().height;
	}
	if (keyCode == EventKeyboard::KeyCode::KEY_D || keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW) {
		playerPos.x += _tileMap->getTileSize().width;
		_player->runAction(actionTo2);
	}
	if (playerPos.x <= (_tileMap->getMapSize().width * _tileMap->getTileSize().width) &&
	 playerPos.y <= (_tileMap->getMapSize().height * _tileMap->getTileSize().height) &&
	 playerPos.y >= 0 &&
	 playerPos.x >= 0) 
	{
	 this->setPlayerPosition(playerPos);
	}
	this->setViewPointCenter(_player->getPosition());
}

void Level1::startUI(){
	int x = 32;
	int y = 32;
	auto moveTo = MoveTo::create(15, Vec2(1000, 0));
	_bar = Sprite::create("Good.png");
	_bar->setScale(0.25);
	_bar->setPosition(x + _tileMap->getTileSize().width / 2, y + _tileMap->getTileSize().height / 2);
	_bar->runAction(moveTo);
	addChild(_bar);
}


// on "init" you need to initialize your instance
bool Level1::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
	this->_tileMap = TMXTiledMap::create("TileMap.tmx");
	this->_background = _tileMap->layerNamed("Background");
	addChild(_tileMap, -1);
	TMXObjectGroup *objects = _tileMap->getObjectGroup("Objects");
	CCASSERT(NULL != objects, "'Objects' object group not found");
	auto playerShowUpPoint = objects->getObject("SpawnPoint");
	CCASSERT(!playerShowUpPoint.empty(), "PlayerShowUpPoint object not found");
	int x = playerShowUpPoint["x"].asInt();
	int y = playerShowUpPoint["y"].asInt();
	_player = Sprite::create("SirBrawnley.png");
	_player->setPosition(x + _tileMap->getTileSize().width / 2, y + _tileMap->getTileSize().height / 2);
	_player->setScale(0.05);
	addChild(_player);
	setViewPointCenter(_player->getPosition());
	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(Level1::onKeyPressed, this);
	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	startUI();
    return true;
}