#include "FirstScene.h"

USING_NS_CC;

FirstScene::FirstScene()
{
	curScene = GameScene1;
}

FirstScene::~FirstScene()
{

}

Scene* FirstScene::createScene()
{
	 // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = FirstScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}