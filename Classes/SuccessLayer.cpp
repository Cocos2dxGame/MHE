#include "SuccessLayer.h"
USING_NS_CC;

SuccessLayer::SuccessLayer()
{
}

SuccessLayer::~SuccessLayer()
{
}

SuccessLayer* SuccessLayer::create(GameSceneType type)
{
	SuccessLayer* successLayer = new SuccessLayer();
	successLayer->curType = type;

	if(successLayer->init())
	{
		successLayer->autorelease();
		return successLayer;
	}
	return NULL;
}

bool SuccessLayer::init()
{
	auto success_background = Sprite::create("background/pause_background.png");
	success_background->setPosition(Director::sharedDirector()->getVisibleSize()/2);
	addChild(success_background,10);

	auto success_sprite = Sprite::create("background/success.png");
	success_sprite->setPosition(Director::sharedDirector()->getVisibleSize()/2 + Size(0,80));
	addChild(success_sprite, 999);

	auto reBeginItem = MenuItemImage::create(
		"button/rebegin.png",
		"button/rebegin_selected.png",
		CC_CALLBACK_1(SuccessLayer::reBegin, this));
	reBeginItem->setPosition(Vec2(Director::sharedDirector()->getVisibleSize()/2));

	auto goChapterItem = MenuItemImage::create(
		"button/goChapter.png",
		"button/goChapter_selected.png",
		CC_CALLBACK_1(SuccessLayer::goChapter, this));
	goChapterItem->setPosition(Director::sharedDirector()->getVisibleSize()/2 + Size(70,0));

	auto menu = Menu::create(reBeginItem, goChapterItem,NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 999);

	return true;
}

void SuccessLayer::reBegin(Ref* pSender)
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

void SuccessLayer::goChapter(Ref* pSender)
{
	CCDirector::sharedDirector()->resume();  
	CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();  
	CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeAllEffects();

	Scene* pScene = ChapterScene::createScene();
	SceneManager::go(pScene);
}