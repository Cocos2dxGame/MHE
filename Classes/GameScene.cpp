#include "GameScene.h"

USING_NS_CC;

GameScene::GameScene()
	:roleCurrentHP(0),roleCurrentSP(0),npcCurrentHP(0),npcCurrrentSP(0)
{
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);

    listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

}

Scene* GameScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::createWithPhysics();
    
    // 'layer' is an autorelease object
    auto layer = GameScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }

	this->setAccelerometerEnabled(true);

    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();

	Sprite* background = Sprite::create("background/bg_003.png");
	background->setScaleX(visibleSize.width/background->getContentSize().width);
	background->setScaleY(visibleSize.height/background->getContentSize().height);
	background->setPosition(visibleSize.width/2, visibleSize.height/2);
	addChild(background,0);

	setProgressBar();

    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(GameScene::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
	
	_role1 = Role1::create();
	_role1->setPosition(100,100);
	addChild(_role1,1);
	_role1->setMoveToRight();
	_role1->runAction(_role1->getNormalAction());

	_role2 = Role2::create();
	_role2->setPosition(200,100);
	addChild(_role2,1);
	_role2->setMoveToRight();
	_role2->runAction(_role2->getNormalAction());

	_role3 = Role3::create();
	_role3->setPosition(300,100);
	addChild(_role3,1);
	_role3->setMoveToRight();
	_role3->runAction(_role3->getNormalAction());

	_role4 = Role4::create();
	_role4->setPosition(400,100);
	addChild(_role4,1);
	_role4->setMoveToRight();
	_role4->runAction(_role4->getNormalAction());

	schedule(schedule_selector(GameScene::update), 0.2f);

    return true;
}

void GameScene::setProgressBar()
{
	Sprite* bgSprite = Sprite::create("system/ProgressBarBackground1.png");
	bgSprite->setPosition(bgSprite->getContentSize().width/2 + 10, visibleSize.height-20);
	addChild(bgSprite,1);

	//设置role的血量
	Sprite* roleHPSprite = Sprite::create("system/HPTotal.png");

	roleHPProgressTimer = ProgressTimer::create(roleHPSprite);
	roleHPProgressTimer->setType(kCCProgressTimerTypeBar);

	roleHPProgressTimer->setMidpoint(ccp(0,0.5));
	roleHPProgressTimer->setBarChangeRate(ccp(1,0));

	roleHPProgressTimer->setPercentage(100);

	roleHPProgressTimer->setPosition(bgSprite->getPosition().x + 33, bgSprite->getPosition().y + 9);
	addChild(roleHPProgressTimer,1);
	
	//设置role的怒气
	Sprite* roleSPSprite = Sprite::create("system/SPTotal.png");

	roleSPProgressTimer = ProgressTimer::create(roleSPSprite);
	roleSPProgressTimer->setType(kCCProgressTimerTypeBar);

	roleSPProgressTimer->setMidpoint(ccp(0,0.5));
	roleSPProgressTimer->setBarChangeRate(ccp(1,0));

	roleSPProgressTimer->setPercentage(100);

	roleSPProgressTimer->setPosition(bgSprite->getPosition().x + 29, bgSprite->getPosition().y -5);
	addChild(roleSPProgressTimer,1);
}

void GameScene::update(float dt)
{
	//更新血量，怒气
	roleCurrentHP++;
	roleCurrentSP++;
	roleHPProgressTimer->setPercentage(roleCurrentHP);
	roleSPProgressTimer->setPercentage(roleCurrentSP);
}

void GameScene::setRoleHp(unsigned int roleCurrentHP)
{
}

//重写重力加速器方法  
void GameScene::onAcceleration(Acceleration* acc, Event* event)
{
	/*if(acc->x > 0)
	{
		_person->setMoveToRight();
		_person->runAction(_person->getMoveAction());
		
		if((_person->getPosition().x + 32) < visibleSize.width)
			_person->setPosition(_person->getPosition().x+2,_person->getPosition().y);
	}
	else
	{
		_person->setMoveToLeft();
		_person->runAction(_person->getMoveAction());
		
		if(_person->getPosition().x > 0)
			_person->setPosition(_person->getPosition().x-2,_person->getPosition().y);
	}*/
}  

void GameScene::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

bool GameScene::contaiinsTouchLocation(Touch* touch)
{
	return _role1->getRect().containsPoint(convertTouchToNodeSpace(touch));
}

bool GameScene::onTouchBegan(Touch* touch, Event* event)
{
	CCLOG("Paddle::onTouchBegan id = %d, x = %f, y = %f", touch->getID(), touch->getLocation().x, touch->getLocation().y);
	
	if ( !contaiinsTouchLocation(touch) ) return false;
    
	startPosition = touch->getLocation();
    CCLOG("return true");
    return true;
}

void GameScene::onTouchMoved(Touch* touch, Event* event)
{

}

void GameScene::onTouchEnded(Touch* touch, Event* event)
{
	endPosition = touch->getLocation();
	Vec2 vertex = endPosition - startPosition;
	


	nextState = Fire_Action;
}

void GameScene::onTouchCancelled(Touch* touches, Event* event)
{

}