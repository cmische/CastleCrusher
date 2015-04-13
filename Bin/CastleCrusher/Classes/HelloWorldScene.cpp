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

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto rootNode = CSLoader::createNode("MainScene.csb");

    addChild(rootNode);

    return true;
}

void HelloWorld::transitionToLevel1Scene()
{
    auto size = Director::getInstance()->getWinSize();
    
    
    this->tileMap = TMXTiledMap::create("Dungeon_Level1.tmx");
    this->background = _tileMap->layerNamed("Background");
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

}

void HelloWorld::toLevel1()
{
    auto scene = Level_1::createScene();
    Director::getInstance()->replaceScene(scene);
}
