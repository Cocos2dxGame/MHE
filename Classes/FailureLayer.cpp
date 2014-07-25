#include "FailureLayer.h"
USING_NS_CC;

FailureLayer::FailureLayer()
{
}

FailureLayer::~FailureLayer()
{
}

FailureLayer* FailureLayer::create(GameSceneType type)
{
	FailureLayer* failureLayer = new FailureLayer();
	failureLayer->curType = type;

	if(failureLayer->init())
	{
		return failureLayer;
	}
	return NULL;
}

bool FailureLayer::init()
{
	auto failure_background = Sprite::create("background/pause_background.png");
	failure_background->setPosition(Director::sharedDirector()->getVisibleSize()/2);
	addChild(failure_background,10);

	auto reBeginItem = MenuItemImage::create(
		"button/rebegin.png",
		"button/rebegin_selected.png",
		CC_CALLBACK_1(FailureLayer::reBegin, this));
	reBeginItem->setPosition(Vec2(Director::sharedDirector()->getVisibleSize()/2));

	auto goChapterItem = MenuItemImage::create(
		"button/goChapter.png",
		"button/goChapter_selected.png",
		CC_CALLBACK_1(FailureLayer::goChapter, this));
	goChapterItem->setPosition(Director::sharedDirector()->getVisibleSize()/2 + Size(70,0));

	auto menu = Menu::create(reBeginItem, goChapterItem,NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 999);

	return true;
}

void FailureLayer::reBegin(Ref* pSender)
{
	CCDirector::sharedDirector()->resume();  
	CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();  
	CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeAllEffects();
	Scene* pScene;

	switch (curType)
	{
	case GameScene1:
		pScene = FirstScene::createScene();
		break;
	case GameScene2:
		pScene = SecondScene::createScene();
		break;
	case GameScene3:
		pScene = ThirdScene::createScene();
		break;
	default:
		break;
	}
	SceneManager::go(pScene);
}

void FailureLayer::goChapter(Ref* pSender)
{
	CCDirector::sharedDirector()->resume();  
	CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();  
	CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeAllEffects();

	Scene* pScene = ChapterScene::createScene();
	SceneManager::go(pScene);
}