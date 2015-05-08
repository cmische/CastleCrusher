#include "Level1.h"
#include "Enemies.h"
#include "Win.h"
#include "Lose.h"

USING_NS_CC;

//declare some private variables for camFollowMethod so it doesn't have to create new ones 60 times a second
int camX, camY;
float camAdjustSpeed = (float)0.15;


Scene* Level1::createScene()
{
    Scene* scene = Scene::create();   
    Layer* layer = Level1::create();
	layer->setName("level");
    scene->addChild(layer);
    return scene;
}

void Level1::setViewPoint(Point position) {
	//winSize has to be in this function for some reason or the camera messes up, no idea why.
	Size winSize = Director::getInstance()->getWinSize();
	//make sure the camera center never updates with a center less than half the width of the window
    int x = MAX(position.x, winSize.width / 2);
	//make sure the camera center never updates with a center less than half the height of the window
    int y = MAX(position.y, winSize.height / 2);
	//make sure the camera center never updates past map width minus half the width of the window
    x = MIN(x, (_tileMap->getMapSize().width * this->_tileMap->getTileSize().width) - winSize.width / 2);
	//make sure the camera center never updates past map height minus half the height of the window
    y = MIN(y, (_tileMap->getMapSize().height * _tileMap->getTileSize().height) - winSize.height / 2);
    Vec2 actualPosition = Point(x, y);
    Vec2 centerOfView = Point(winSize.width / 2, winSize.height / 2);
    Vec2 viewPoint = centerOfView - actualPosition;
	//get the difference from center of camera to where you want to go and go there
    this->setPosition(viewPoint);
}

//note, float dt parameter is required here due to the way the schedule method that calls this function works
void Level1::camFollowPlayer(float dt)
{
	//This method is called with every frame update, it simply moves the camera 15% closer to the distance between where it is and the player with every frame
	//set it up this way so if _playerPosX == camX, nothing happens
	camX += (camAdjustSpeed * (_playerPosX - camX));
	camY += (camAdjustSpeed * (_playerPosY - camY));
	//Move the camera to the new position
	this->setViewPoint(Point(camX, camY));
	for (int i = 0; i < this->getChildrenCount(); i++)
	{

		if ( this->getChildren().at(i)->getName() == "snake" || this->getChildren().at(i)->getName() == "ogre")
		{
			float x = this->getChildren().at(i)->getPositionX();
			float y = this->getChildren().at(i)->getPositionY();
			if ((abs(_playerPosX - x) < 30) && (abs(_playerPosY - y) < 30) )
			{
				_player->setVisible(false);
				auto scene = Lose::createScene();
				Director::getInstance()->replaceScene(scene);
			}
		}

	}

	TMXObjectGroup *objects = _tileMap->getObjectGroup("win");
	auto winPoint = objects->getObject("win");
	float x = winPoint["x"].asFloat();
	float y = winPoint["y"].asFloat();

	if ((abs(_playerPosX - x) < 40) && (abs(_playerPosY - y) < 40) )
			{
				_player->setVisible(false);
				auto scene = Win::createScene();
				Director::getInstance()->replaceScene(scene);
			}
}

void Level1::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	int x = _playerPosX;
	int y = _playerPosY;

	//makes the player do a rotate when he changes directions
	auto actionTo1 = RotateTo::create(0, 0, 180);
	auto actionTo2 = RotateTo::create(0, 0, 0);
	//supports wasd or arrow keys, update player position if within map bounds
	if (keyCode == EventKeyboard::KeyCode::KEY_W || keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW) {
		if ( _playerPosY + _tileMap->getTileSize().height <= _tileMap->getMapSize().height * _tileMap->getTileSize().height){
			//if new position is within map bounds, change it to the new position
			_playerPosY += _tileMap->getTileSize().height;
			if (brawnleyHasSword)
			{
				_player->setTexture((CCTextureCache::getInstance()->addImage("SirBrawnleyWSwordUp.png")));
			}
			//_arrow->setPosition(_player->getPosition());
		}
	}
	if (keyCode == EventKeyboard::KeyCode::KEY_A || keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW) {
		if (_playerPosX - _tileMap->getTileSize().width >= 0) {
			_playerPosX -= _tileMap->getTileSize().width;
			//_arrow->setPosition(_player->getPosition());
			_player->runAction(actionTo1);
			if (brawnleyHasSword)
			{
				_player->setTexture((CCTextureCache::getInstance()->addImage("SirBrawnleyWSword.png")));
			}
			//_arrow->runAction(actionTo2);
		}
	}
	if (keyCode == EventKeyboard::KeyCode::KEY_S || keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW) {
		if (_playerPosY - _tileMap->getTileSize().height >= 0) {
		_playerPosY -= _tileMap->getTileSize().height;
		//_arrow->setPosition(_player->getPosition());
		if (brawnleyHasSword)
			{
				_player->setTexture((CCTextureCache::getInstance()->addImage("SirBrawnleyWSwordDown.png")));
			}
		}
	}
	if (keyCode == EventKeyboard::KeyCode::KEY_D || keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW) {
		if ( _playerPosX + _tileMap->getTileSize().width <= _tileMap->getMapSize().width * _tileMap->getTileSize().width) {
			_playerPosX += _tileMap->getTileSize().width;
			//_arrow->setPosition(_player->getPosition());
			_player->runAction(actionTo2);
			if (brawnleyHasSword)
			{
				_player->setTexture((CCTextureCache::getInstance()->addImage("SirBrawnleyWSword.png")));
			}
			//_arrow->runAction(actionTo1);
		}
	}

	//shooting projectile(still in progress)
	/*
	if (keyCode == EventKeyboard::KeyCode::KEY_SPACE)
	{
		Vec2 offset = _player->getPosition();

		offset.normalize();
		auto shootAmount = offset * 1000;

		auto realDest = shootAmount + _player->getPosition();

		auto actionMove = MoveTo::create(1.0f, realDest);
		auto actionRemove = RemoveSelf::create();
		_arrow->runAction(Sequence::create(actionMove, actionRemove, nullptr));
	}
	*/
	//collide layer on tileMap has a transparent red tile, this checks to see if a players position will be on a red tile
	Value properties = _tileMap->getPropertiesForGID(_collide->tileGIDAt(tileCoordForPosition(Point(_playerPosX, _playerPosY))));
	if(! properties.isNull()) {
		ValueMap dict = properties.asValueMap();
		if (dict.at("collide").asString().compare("true") == 0) {
			//if so, revert new position to same position it had when it started, nullifying any movement
			_playerPosX = x;
			_playerPosY = y;
		}
	}
	//actually move the player
	 _player->setPosition(_playerPosX, _playerPosY);
	 //addChild(_arrow);
}

void Level1::startUI()
{
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

void Level1::scanEnemyLayer() 
{
	CCLOG(std::to_string(_tileMap->getMapSize().width).c_str());
	CCLOG(std::to_string(_tileMap->getMapSize().height).c_str());
	for( int i = 0; i < _tileMap->getMapSize().width; i++ )
   {
	   for( int j = 0; j < _tileMap->getMapSize().height; j++ )
	   {
		   Value properties = _tileMap->getPropertiesForGID(enemyLayer->tileGIDAt(Point(i, j)));
			if(! properties.isNull()) {
				ValueMap dict = properties.asValueMap();
				if (dict.at("enemy").asString().compare("snake") == 0) {
					snakes[snakeSize] = Snake::createSnake( 16 + ((float)i * _tileMap->getTileSize().width), (float)16 + (((float)_tileMap->getMapSize().height * _tileMap->getTileSize().height) - ((float)j * _tileMap->getTileSize().height)), _tileMap, _collide);
					addChild(snakes[snakeSize]);
					snakeSize++;
				}
				if (dict.at("enemy").asString().compare("ogre") == 0) {
					ogres[ogreSize] = Ogre::createOgre( 16 + ((float)i * _tileMap->getTileSize().width), (float)16 + (((float)_tileMap->getMapSize().height * _tileMap->getTileSize().height) - ((float)j * _tileMap->getTileSize().height)), _tileMap, _collide);
					addChild(ogres[ogreSize]);
					ogreSize++;
				}
			}
	   }
   }
	
}

Point Level1::tileCoordForPosition(Point position)
{
    int x = position.x / _tileMap->getTileSize().width;
    int y = ((_tileMap->getMapSize().height * _tileMap->getTileSize().height) - position.y) / _tileMap->getTileSize().height;
    return Vec2(x, y);
}

void Level1::onMouseDown(Event *event)
{
	if (brawnleyHasSword)
	{
		EventMouse* e = (EventMouse*)event;
		Size winSize = Director::getInstance()->getWinSize();
		_player->setTexture((CCTextureCache::getInstance()->addImage("SirBrawnley.png")));
		Point click = e->getLocation();
		int centerX = winSize.width / 2;
		int centerY = winSize.height / 2;
		int targetX = click.x - centerX;
		int targetY = click.y - centerY;
		targetX = _playerPosX + targetX;
		targetY = _playerPosY - targetY;
		addChild(Sword::createSword(playerPosXpointer, playerPosYpointer, _tileMap, enemyLayer, Point(targetX, targetY)));
	}

}

bool Level1::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
	//FINALLY  http://discuss.cocos2d-x.org/t/scheduler-not-firing/21373
	//create snake one liner

	

	_tileMap = TMXTiledMap::create("tileMap.tmx");
	_tileMap = TMXTiledMap::create("tileMap.tmx");
	_collide = _tileMap->getLayer("collide");
	enemyLayer = _tileMap->getLayer("enemies");
	_collide->setVisible(false);
	enemyLayer->setVisible(false);

	_tileMap->getLayer("Background")->setGlobalZOrder(-2);
	_tileMap->getLayer("Tile Layer 2")->setGlobalZOrder(0);
	_tileMap->getLayer("Tile Layer 3")->setGlobalZOrder(0);
	_tileMap->getLayer("Tile Layer 4")->setGlobalZOrder(0);

	//add tile map as a background
	addChild(_tileMap);

	//gets spawn location from the object layer of the tilemap
	TMXObjectGroup *objects = _tileMap->getObjectGroup("spawnlayer");
	auto playerShowUpPoint = objects->getObject("spawn");
	int x = playerShowUpPoint["x"].asInt();
	int y = playerShowUpPoint["y"].asInt();

	

	_player = Sprite::create("SirBrawnleyWSword.png");
	//put player positions on spawnpoint
	_playerPosX = (float)(x + _tileMap->getTileSize().width / 2);
	_playerPosY = (float)(y + _tileMap->getTileSize().height / 2);
	_player->setPosition(_playerPosX, _playerPosY);
	//make our player image the right size
	_player->setScale((float)0.032);
	_player->setGlobalZOrder(-1);
	addChild(_player);
	_player->setName("player");

	/*
	//Add arrow (or any projectile)
	_arrow = Sprite::create("LeftArrow.png");
	_arrow->setPosition(_player->getPosition());
	//made it larger so I could see it better
	_arrow->setScale((float)0.5);
	_arrow->setGlobalZOrder(-1);
	addChild(_arrow);
	*/

	//makes the camera start on the spawn instead of panning to it
	camX = _playerPosX;
	camY = _playerPosY;
	setViewPoint(_player->getPosition());

	//adds listener for any keyboard event, calls onKeyPressed with the event and passes key
	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(Level1::onKeyPressed, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	auto _mouseListener = EventListenerMouse::create();
	_mouseListener->onMouseDown = CC_CALLBACK_1(Level1::onMouseDown, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(_mouseListener, this);
	
	startUI();
	//this method runs camFollowPlayer on every frame update
	schedule(schedule_selector(Level1::camFollowPlayer));
	//schedule(schedule_selector(Level1::rotateSwords));

	playerPosXpointer = &_playerPosX;
	playerPosYpointer = &_playerPosY;

	snakeSize=0;
	ogreSize=0;
	scanEnemyLayer();

    return true;
}

/* Going to need this snippet for item pickup
	 if (tileGid) {
        ValueMap properties = _tilemap->getPropertiesForGID(tileGid).asValueMap();
        if (properties.size() > 0) {
            const String collision = properties.at("Collidable").asString();
            if (collision.boolValue() && collision.compare("true") == 0) {
                return;
            }

           const String collectable = properties.at("Collectable").asString();
            if (collectable.boolValue() && collectable.compare("true") == 0) {
                meta->removeTileAt(tileCoord);
                foreground->removeTileAt(tileCoord);
                numCollected++;
                hud->numCollectedChanged(_numCollected);
            }
        }
    }
*/