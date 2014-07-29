#include "ModeSelecteScene.h"
#include "ChapterScene.h"
#include "SurvivalScene.h"
#include "CompeteScene.h"

USING_NS_CC;

ModeSelecteScene::ModeSelecteScene()
{
}

ModeSelecteScene::~ModeSelecteScene()
{
}

Scene* ModeSelecteScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();
	
	// 'layer' is an autorelease object
	auto layer = ModeSelecteScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool ModeSelecteScene::init()
{
	Size visibleSize = Director::sharedDirector()->getVisibleSize();

	auto bg = Sprite::create("background/bg_002.png");
	bg->setScale(visibleSize.width/bg->getContentSize().width, 
		visibleSize.height/bg->getContentSize().height);
	bg->setPosition(visibleSize/2);
	addChild(bg, 1);
	

	auto classical = MenuItemImage::create(
		"button/bt_000.png",
		"button/bts_000.png",
		CC_CALLBACK_1(ModeSelecteScene::goClassicalScene, this));

	classical->setScale((visibleSize.height/8)/classical->getContentSize().height);
	classical->setPosition(visibleSize.width/2,visibleSize.height*3/4);

	auto survival = MenuItemImage::create(
		"button/bt_000.png",
		"button/bts_000.png",
		CC_CALLBACK_1(ModeSelecteScene::goSurvivalScene,this));

	survival->setScale((visibleSize.height/8)/classical->getContentSize().height);
	survival->setPosition(visibleSize.width/2,visibleSize.height*2/4);

	auto compete = MenuItemImage::create(
		"button/bt_000.png",
		"button/bts_000.png",
		CC_CALLBACK_1(ModeSelecteScene::goCompeteScene, this));
		
	compete->setScale((visibleSize.height/8)/classical->getContentSize().height);
	compete->setPosition(visibleSize.width/2,visibleSize.height/4);

	auto menu = Menu::create(classical, survival, compete, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	return true;
}

void ModeSelecteScene::goClassicalScene(Ref* pSender)
{
	Scene* pScene = ChapterScene::createScene();
	SceneManager::go(pScene);
}

void ModeSelecteScene::goSurvivalScene(Ref* pSender)
{
	Scene* pScene = SurvivalScene::createScene();
	SceneManager::go(pScene);
}

void ModeSelecteScene::goCompeteScene(Ref* pSender)
{
	Scene* pScene = CompeteScene::createScene();
	SceneManager::go(pScene);
}