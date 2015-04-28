//
//  Level_1.cpp
//  
//
//  Created by Spanky Clayton on 4/8/15.
//
//

#include "Level_1.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

using namespace cocostudio::timeline;

Scene* Level_1::createScene()
{
    auto scene = Scene::create();
    
    auto layer = Level_1::create();
    
    scene->addChild(layer);
    
    return scene;
}

void Level_1::setViewPointCenter(Point position)
{
    auto winSize = Director::getInstance()->getWinSize();
    
    int x = MAX(position.x, winSize.width /2);
    int y = MAX(position.y, winSize.height /2);
    x = MIN(x, (_tileMap->getMapSize().width * this->_tileMap->getTileSize().width) - winSize.width/2);
    y = MIN(y, (_tileMap->getMapSize().height * _tileMap->getTileSize().height) - winSize.height/2);
    auto actualPosition = Point(x,y);
    
    auto centerOfView = Point(winSize.width/2, winSize.height/2);
    auto viewPoint = centerOfView - actualPosition;
    this->setPosition(viewPoint);
}

void Level_1::setPlayerPosition(Point position)
{
    _player->setPosition(position);
}

void Level_1::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
    auto actionTo1 = RotateTo::create(0, 0, 180);
    auto actionTo2 = RotateTo::create(0, 0, 0);
    auto playerPos = _player->getPosition();
    
    
    if (keyCode == EventKeyboard::KeyCode::KEY_W) {
        playerPos.y += _tileMap->getTileSize().height;
    }
    if (keyCode == EventKeyboard::KeyCode::KEY_A) {
        playerPos.x -= _tileMap->getTileSize().height;
        _player->runAction(actionTo1);
    }
    if (keyCode == EventKeyboard::KeyCode::KEY_S) {
        playerPos.y -= _tileMap->getTileSize().width;
    }
    if (keyCode == EventKeyboard::KeyCode::KEY_D) {
        playerPos.x += _tileMap->getTileSize().width;
        _player->runAction(actionTo2);
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

bool Level_1::init()
{
    if(!Layer::init())
    {
        return false;
    }
    
    auto size = Director::getInstance()->getWinSize();
    
    this->_tileMap = TMXTiledMap::create("Dungeon_Level1.tmx");
    this->_background = _tileMap->layerNamed("Background");
    addChild(_tileMap, -1);
    
    
    TMXObjectGroup *objects = _tileMap->getObjectGroup("Objects");
    CCASSERT(NULL!= objects, "'Objects' object group not found");
    auto playerShowUpPoint = objects->getObject("SpawnPoint");
    CCASSERT(!playerShowUpPoint.empty(), "PlayerShowUpPoint object not found");
    
    int x = playerShowUpPoint["x"].asInt();
    int y = playerShowUpPoint["y"].asInt();
    
    _player = Sprite::create("SirBrawnleyTemp.png");
    _player->setPosition(x + _tileMap->getTileSize().width / 2, y + _tileMap->getTileSize().height / 2);
    _player->setScale(0.5);
    
    addChild(_player);
    setViewPointCenter(_player->getPosition());
    
    auto listener = EventListenerKeyboard::create();
    listener->onKeyPressed = CC_CALLBACK_2(Level_1::onKeyPressed, this);
    this->_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
 
    
    return true;
    
}