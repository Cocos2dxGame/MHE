#include "SurvivalScene.h"
#include "PauseLayer.h"

USING_NS_CC;

SurvivalScene::SurvivalScene()
{
	curScene = GameScene1;
}

SurvivalScene::~SurvivalScene()
{
}

Scene* SurvivalScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = SurvivalScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

bool SurvivalScene::init()
{
	EventListenerTouchOneByOne* listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);

	listener->onTouchBegan = CC_CALLBACK_2(SurvivalScene::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(SurvivalScene::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(SurvivalScene::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	auto bg = Sprite::create("background/bg_003.png");
	bg->setScale(Director::sharedDirector()->getVisibleSize().width/bg->getContentSize().width);
	bg->setPosition(Director::sharedDirector()->getVisibleSize()/2);
	addChild(bg,1);

	setSkillCoolDownBar();
	setMenu();

	_curPlayer = Player::create();


}

void SurvivalScene::setSkillCoolDownBar()
{
	auto skillCoolDownBg = Sprite::create("skill/skill21.png");
	skillCoolDownBg->setPosition(40,40);
	addChild(skillCoolDownBg, 2);

	auto skill1CoolSprite = Sprite::create("skill/skill21_disabled.png");
	skillCoolDownBar = ProgressTimer::create(skill1CoolSprite);

	skillCoolDownBar->setType(kCCProgressTimerTypeBar);
	skillCoolDownBar->setMidpoint(ccp(0.5,0));
	skillCoolDownBar->setBarChangeRate(ccp(0,1));
	skillCoolDownBar->setPercentage(0);
	skillCoolDownBar->setPosition(40,40);
	addChild(skillCoolDownBar,3);
}

void SurvivalScene::setMenu()
{
	auto visibleSize = Director::sharedDirector()->getVisibleSize();
	auto origin = Director::sharedDirector()->getVisibleOrigin();

	//ÔİÍ£°´Å¥
	auto pauseItem = MenuItemImage::create(
										"button/pause.png",
										"button/pause_selected.png",
										CC_CALLBACK_1(SurvivalScene::doPause, this));
	pauseItem->setScale(visibleSize.width/20/pauseItem->getContentSize().width);

	pauseItem->setPosition(Vec2(visibleSize.width - visibleSize.width/12/2,
		visibleSize.height - visibleSize.height/12/2));

	//ÍË³ö°´Å¥
	auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(SurvivalScene::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

	auto menu = Menu::create(pauseItem, closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
}

void SurvivalScene::doPause(Ref* pSender)
{
	CCDirector::sharedDirector()->pause();  
    CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();  
    CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseAllEffects();  
    Scene *pauseLayer = PauseLayer::createScene(curScene);  
    addChild(pauseLayer,999);
}

void SurvivalScene::menuCloseCallback(cocos2d::Ref* pSender)
{
	Director::getInstance()->end();
}