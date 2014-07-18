#include "SecondScene.h"

USING_NS_CC;

SecondScene::SecondScene()
{
	curScene = GameScene2;
}

SecondScene::~SecondScene()
{

}

Scene* SecondScene::createScene()
{
	 // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = SecondScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}