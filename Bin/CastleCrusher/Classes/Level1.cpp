#include "Level1.h"

USING_NS_CC;

//declare some private variables for camFollowMethod so it doesn't have to create new ones 60 times a second
int camX, camY;
float camAdjustSpeed = (float)0.15;


Scene* Level1::createScene()
{
    auto scene = Scene::create();   
    auto layer = Level1::create();
    scene->addChild(layer);
    return scene;
}

void Level1::setViewPoint(Point position) {
	//winSize has to be in this function for some reason or the camera messes up, no idea why.
	auto winSize = Director::getInstance()->getWinSize();
	//make sure the camera center never updates with a center less than half the width of the window
    int x = MAX(position.x, winSize.width / 2);
	//make sure the camera center never updates with a center less than half the height of the window
    int y = MAX(position.y, winSize.height / 2);
	//make sure the camera center never updates past map width minus half the width of the window
    x = MIN(x, (_tileMap->getMapSize().width * this->_tileMap->getTileSize().width) - winSize.width / 2);
	//make sure the camera center never updates past map height minus half the height of the window
    y = MIN(y, (_tileMap->getMapSize().height * _tileMap->getTileSize().height) - winSize.height / 2);
    auto actualPosition = Point(x, y);
    auto centerOfView = Point(winSize.width / 2, winSize.height / 2);
    auto viewPoint = centerOfView - actualPosition;
	//get the difference from center of camera to where you want to go and go there
    this->setPosition(viewPoint);
}

void Level1::camFollowPlayer(float dt)
{
	//set it up this way so if _playerPosX == camX, nothing happens
	camX += (camAdjustSpeed * (_playerPosX - camX));
	camY += (camAdjustSpeed * (_playerPosY - camY));
	this->setViewPoint(Point(camX, camY));
}

void Level1::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	//makes the player do a rotate when he changes directions
	auto actionTo1 = RotateTo::create(0, 0, 180);
	auto actionTo2 = RotateTo::create(0, 0, 0);
	//supports wasd or arrow keys, update player position if within map bounds
	if (keyCode == EventKeyboard::KeyCode::KEY_W || keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW) {
		if ( _playerPosY + _tileMap->getTileSize().height <= _tileMap->getMapSize().height * _tileMap->getTileSize().height){
			_playerPosY += _tileMap->getTileSize().height;
		}
	}
	if (keyCode == EventKeyboard::KeyCode::KEY_A || keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW) {
		if (_playerPosX - _tileMap->getTileSize().width >= 0) {
			_playerPosX -= _tileMap->getTileSize().width;
			_player->runAction(actionTo1);
		}
	}
	if (keyCode == EventKeyboard::KeyCode::KEY_S || keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW) {
		if (_playerPosY - _tileMap->getTileSize().height >= 0) {
		_playerPosY -= _tileMap->getTileSize().height;
		}
	}
	if (keyCode == EventKeyboard::KeyCode::KEY_D || keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW) {
		if ( _playerPosX + _tileMap->getTileSize().width <= _tileMap->getMapSize().width * _tileMap->getTileSize().width) {
			_playerPosX += _tileMap->getTileSize().width;
			_player->runAction(actionTo2);
		}
	}
	 _player->setPosition(_playerPosX, _playerPosY);
}


void Level1::startUI(){
	/*
	int x = 32;
	int y = 32;
	auto moveTo = MoveTo::create(15, Vec2(1000, 0));
	_bar = Sprite::create("Good.png");
	_bar->setScale(0.25);
	_bar->setPosition(x + _tileMap->getTileSize().width / 2, y + _tileMap->getTileSize().height / 2);
	_bar->runAction(moveTo);
	addChild(_bar);
	*/
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
	//add tile map as a background
	addChild(_tileMap, -1);

	//gets spawn location from the object layer of the tilemap
	TMXObjectGroup *objects = _tileMap->getObjectGroup("Objects");
	auto playerShowUpPoint = objects->getObject("SpawnPoint");
	int x = playerShowUpPoint["x"].asInt();
	int y = playerShowUpPoint["y"].asInt();

	_player = Sprite::create("SirBrawnley.png");
	//put player positions on spawnpoint
	_playerPosX = (float)(x + _tileMap->getTileSize().width / 2);
	_playerPosY = (float)(y + _tileMap->getTileSize().height / 2);
	_player->setPosition(_playerPosX, _playerPosY);
	//make our player image the right size
	_player->setScale((float)0.037);
	addChild(_player);

	//makes the camera start on the spawn instead of panning to it
	camX = _playerPosX;
	camY = _playerPosY;
	setViewPoint(_player->getPosition());

	//adds listener for any keyboard event, calls onKeyPressed with the event and passes key
	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(Level1::onKeyPressed, this);
	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	
	startUI();
	//this method runs camFollowPlayer on every frame update
	this->schedule(schedule_selector(Level1::camFollowPlayer));



    return true;
}