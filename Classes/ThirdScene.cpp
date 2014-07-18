#include "ThirdScene.h"

USING_NS_CC;

ThirdScene::ThirdScene()
{
	curScene = GameScene3;
}

ThirdScene::~ThirdScene()
{

}

Scene* ThirdScene::createScene()
{
	 // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = ThirdScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}