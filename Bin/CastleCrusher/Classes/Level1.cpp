#include "Level1.h"

USING_NS_CC;

//gonna comment up this file more in a bit

int camX;
int camY;
float camAdjustSpeed = 0.05;

Scene* Level1::createScene()
{
    auto scene = Scene::create();   
    auto layer = Level1::create();
    scene->addChild(layer);
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

void Level1::camFollowPlayer(float dt)
{
	//set it up this way so if _playerPosX == camX, nothing happens
	if (_playerPosX > camX) { 
		camX += (camAdjustSpeed * (_playerPosX - camX));
	} else { 
		if (_playerPosX < camX) {
			camX -= (camAdjustSpeed * (camX - _playerPosX));
		}
	}
	if (_playerPosY > camY) { 
		camY += (camAdjustSpeed * (_playerPosY - camY));
	} else { 
		if (_playerPosX < camX) {
			camY -= (camAdjustSpeed * (camY - _playerPosY));
		}
	}
	this->setViewPointCenter(Point(camX, camY));
}

void Level1::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	auto actionTo1 = RotateTo::create(0, 0, 180);
	auto actionTo2 = RotateTo::create(0, 0, 0);
	if (keyCode == EventKeyboard::KeyCode::KEY_W || keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW) {
		_playerPosY += _tileMap->getTileSize().height;
	}
	if (keyCode == EventKeyboard::KeyCode::KEY_A || keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW) {
		_playerPosX -= _tileMap->getTileSize().width;
		_player->runAction(actionTo1);
	}
	if (keyCode == EventKeyboard::KeyCode::KEY_S || keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW) {
		_playerPosY -= _tileMap->getTileSize().height;
	}
	if (keyCode == EventKeyboard::KeyCode::KEY_D || keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW) {
		_playerPosX += _tileMap->getTileSize().width;
		_player->runAction(actionTo2);
	}
	if (_playerPosX <= (_tileMap->getMapSize().width * _tileMap->getTileSize().width) &&
	 _playerPosY <= (_tileMap->getMapSize().height * _tileMap->getTileSize().height) &&
	 _playerPosY >= 0 &&
	 _playerPosX >= 0) 
	{
	 _player->setPosition(_playerPosX, _playerPosY);
	}
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

bool Level1::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
	this->_tileMap = TMXTiledMap::create("TileMap.tmx");
	this->_background = _tileMap->getLayer("Background");
	addChild(_tileMap, -1);
	TMXObjectGroup *objects = _tileMap->getObjectGroup("Objects");
	CCASSERT(NULL != objects, "'Objects' object group not found");
	auto playerShowUpPoint = objects->getObject("SpawnPoint");
	CCASSERT(!playerShowUpPoint.empty(), "PlayerShowUpPoint object not found");
	int x = playerShowUpPoint["x"].asInt();
	int y = playerShowUpPoint["y"].asInt();
	_player = Sprite::create("SirBrawnley.png");
	_playerPosX = (float)(x + _tileMap->getTileSize().width / 2);
	_playerPosY = (float)(y + _tileMap->getTileSize().height / 2);
	_player->setPosition(_playerPosX, _playerPosY);
	_player->setScale((float)0.04);
	addChild(_player);
	setViewPointCenter(_player->getPosition());
	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(Level1::onKeyPressed, this);
	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	startUI();
	//working on camera system so it updates with every frame and follows the player rather than jolting onto him.
	this->schedule(schedule_selector(Level1::camFollowPlayer));

	camX = _playerPosX;
	camY = _playerPosY;

	std::ostringstream ss;
	std::string s;
	std::wstring stemp;
	
	s = "Debugging info \n";
	stemp = std::wstring(s.begin(), s.end());
	OutputDebugString(stemp.c_str());

	ss << camX;
	s = "camX is: " + ss.str() + "\n";
	stemp = std::wstring(s.begin(), s.end());
	OutputDebugString(stemp.c_str());
	ss.str("");

	ss << camY;
	s = "camY is: " + ss.str() + "\n";
	stemp = std::wstring(s.begin(), s.end());
	OutputDebugString(stemp.c_str());
	ss.str("");

	ss << _playerPosX;
	s = "playerPosX is: " + ss.str() + "\n";
	stemp = std::wstring(s.begin(), s.end());
	OutputDebugString(stemp.c_str());
	ss.str("");

	ss << _playerPosY;
	s = "playerPosY is: " + ss.str() + "\n";
	stemp = std::wstring(s.begin(), s.end());
	OutputDebugString(stemp.c_str());
	ss.str("");

    return true;
}