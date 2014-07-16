#include "PauseLayer.h"
USING_NS_CC;

PauseLayer::PauseLayer()
{
}

PauseLayer::~PauseLayer()
{
}

bool PauseLayer::init()
{
	auto reBeginItem = MenuItemImage::create(
		"button/rebegin.png",
		"button/rebegin_selected.png",
		CC_CALLBACK_1(PauseLayer::reBegin, this));
	reBeginItem->setPosition(Vec2(Director::sharedDirector()->getVisibleSize()/2));

	auto goBackItem = MenuItemImage::create(
		"button/begin.png",
		"button/begin_selected.png",
		CC_CALLBACK_1(PauseLayer::goBack, this));
	goBackItem->setPosition(Director::sharedDirector()->getVisibleSize()/2 + Size(0,50));


	auto goChapterItem = MenuItemImage::create(
		"button/goChapter.png",
		"button/goChapter_selected.png",
		CC_CALLBACK_1(PauseLayer::goChapter, this));
	goChapterItem->setPosition(Director::sharedDirector()->getVisibleSize()/2 - Size(0,50));

	auto menu = Menu::create(reBeginItem, goBackItem, goChapterItem,NULL);

	menu->setPosition(Vec2::ZERO);
    
	this->addChild(menu, 1);

	return true;
}

void PauseLayer::reBegin(Ref* pSender)
{

}

void PauseLayer::goBack(Ref* pSender)
{
	CCDirector::sharedDirector()->pause();  
    CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();  
    CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseAllEffects();  
}

void PauseLayer::goChapter(Ref* pSender)
{

}