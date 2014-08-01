#include "ModeSelectScene.h"
#include "ChapterScene.h"
#include "SurvivalScene.h"
#include "CompeteScene.h"

USING_NS_CC;

ModeSelectScene::ModeSelectScene()
{
}

ModeSelectScene::~ModeSelectScene()
{
}

Scene* ModeSelectScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();
	
	// 'layer' is an autorelease object
	auto layer = ModeSelectScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool ModeSelectScene::init()
{
	Size visibleSize = Director::sharedDirector()->getVisibleSize();

	auto bg = Sprite::create("background/bg_005.png");
	bg->setScale(visibleSize.width/bg->getContentSize().width, 
		visibleSize.height/bg->getContentSize().height);
	bg->setPosition(visibleSize/2);
	addChild(bg, 1);
	

	auto classical = MenuItemImage::create(
		"button/classical.png",
		"button/classical_selected.png",
		CC_CALLBACK_1(ModeSelectScene::goClassicalScene, this));

	classical->setScale((visibleSize.height/8)/classical->getContentSize().height);
	classical->setPosition(visibleSize.width/2,visibleSize.height*3/4);

	auto survival = MenuItemImage::create(
		"button/survival.png",
		"button/survival_selected.png",
		CC_CALLBACK_1(ModeSelectScene::goSurvivalScene,this));

	survival->setScale((visibleSize.height/8)/classical->getContentSize().height);
	survival->setPosition(visibleSize.width/2,visibleSize.height*2/4);

	auto compete = MenuItemImage::create(
		"button/compete.png",
		"button/compete_selected.png",
		CC_CALLBACK_1(ModeSelectScene::goCompeteScene, this));
		
	compete->setScale((visibleSize.height/8)/classical->getContentSize().height);
	compete->setPosition(visibleSize.width/2,visibleSize.height/4);

	auto menu = Menu::create(classical, survival, compete, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	return true;
}

void ModeSelectScene::goClassicalScene(Ref* pSender)
{
	Scene* pScene = ChapterScene::createScene();
	SceneManager::go(pScene);
}

void ModeSelectScene::goSurvivalScene(Ref* pSender)
{
	Scene* pScene = SurvivalScene::createScene();
	SceneManager::go(pScene);
}

void ModeSelectScene::goCompeteScene(Ref* pSender)
{
	Scene* pScene = CompeteScene::createScene();
	SceneManager::go(pScene);
}