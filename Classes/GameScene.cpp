#include "GameScene.h"

USING_NS_CC;

BulletManager* g_BulletManager;

GameScene::GameScene()
	:roleCurrentHP(0),roleCurrentSP(0),npcCurrentHP(0),npcCurrrentSP(0),
	skill1CoolDownTime(0.2),skill2CoolDownTime(5.0),skill3CoolDownTime(10.0),
	skill1NeedTime(0.0),skill2NeedTime(0.0), skill3NeedTime(0.0),
	currentBulletState(NormalBullet),currentActionState(Normal_Action),nextActionState(Normal_Action)
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

	//���ý�ɫ��npc��Ѫ����ŭ����
	setRoleProgressBar();
	setNpcProgressBar();
	//���ü��ܰ�ť
	setMenu();
	
	_role1 = Role1::create();
	_role1->setPosition(100,200);
	addChild(_role1,1);
	_role1->setMoveToRight();
	_role1->runAction(_role1->getNormalAction());

	_role2 = Role2::create();
	_role2->setPosition(200,200);
	addChild(_role2,1);
	_role2->setMoveToRight();
	_role2->runAction(_role2->getNormalAction());

	//_role3 = Role3::create();
	//_role3->setPosition(300,200);
	//addChild(_role3,1);
	//_role3->setMoveToRight();
	//_role3->runAction(_role3->getNormalAction());

	//_role4 = Role4::create();
	//_role4->setPosition(400,200);
	//addChild(_role4,1);
	//_role4->setMoveToRight();
	//_role4->runAction(_role4->getNormalAction());

	//���������Լ���ʼ��BulletManager
	Vec2 g(0, -800);
	g_BulletManager = BulletManager::create((Layer*)this, g);

	this->scheduleUpdate();

    return true;
}

void GameScene::setRoleProgressBar()
{
	Sprite* bgSprite = Sprite::create("system/ProgressBarBackground1.png");
	bgSprite->setPosition(bgSprite->getContentSize().width/2 + 10, visibleSize.height-20);
	addChild(bgSprite,1);

	//����role��Ѫ��
	Sprite* roleHPSprite = Sprite::create("system/HPTotal.png");

	roleHPProgressTimer = ProgressTimer::create(roleHPSprite);
	roleHPProgressTimer->setType(kCCProgressTimerTypeBar);

	roleHPProgressTimer->setMidpoint(ccp(0,0.5));
	roleHPProgressTimer->setBarChangeRate(ccp(1,0));

	roleHPProgressTimer->setPercentage(100);

	roleHPProgressTimer->setPosition(bgSprite->getPosition().x + 33, bgSprite->getPosition().y + 9);
	addChild(roleHPProgressTimer,1);
	
	//����role��ŭ��
	Sprite* roleSPSprite = Sprite::create("system/SPTotal.png");

	roleSPProgressTimer = ProgressTimer::create(roleSPSprite);
	roleSPProgressTimer->setType(kCCProgressTimerTypeBar);

	roleSPProgressTimer->setMidpoint(ccp(0,0.5));
	roleSPProgressTimer->setBarChangeRate(ccp(1,0));

	roleSPProgressTimer->setPercentage(0);

	roleSPProgressTimer->setPosition(bgSprite->getPosition().x + 29, bgSprite->getPosition().y -5);
	addChild(roleSPProgressTimer,1);

}

void GameScene::setNpcProgressBar()
{
	Sprite* bgSprite = Sprite::create("system/ProgressBarBackground1.png");
	bgSprite ->setScaleX(-1.0);
	bgSprite->setPosition(visibleSize.width - bgSprite->getContentSize().width/2 - 10, visibleSize.height-20);
	addChild(bgSprite,1);

	//����npc��Ѫ��
	Sprite* npcHPSprite = Sprite::create("system/HPTotal.png");

	npcHPProgressTimer = ProgressTimer::create(npcHPSprite);
	npcHPProgressTimer->setType(kCCProgressTimerTypeBar);

	npcHPProgressTimer->setMidpoint(ccp(1,0.5));
	npcHPProgressTimer->setBarChangeRate(ccp(1,0));

	npcHPProgressTimer->setPercentage(100);

	npcHPProgressTimer->setPosition(bgSprite->getPosition().x - 33, bgSprite->getPosition().y + 9);
	addChild(npcHPProgressTimer,1);
	
	//����npc��ŭ��
	Sprite* npcSPSprite = Sprite::create("system/SPTotal.png");

	npcSPProgressTimer = ProgressTimer::create(npcSPSprite);
	npcSPProgressTimer->setType(kCCProgressTimerTypeBar);

	npcSPProgressTimer->setMidpoint(ccp(1,0.5));
	npcSPProgressTimer->setBarChangeRate(ccp(1,0));

	npcSPProgressTimer->setPercentage(0);

	npcSPProgressTimer->setPosition(bgSprite->getPosition().x - 29, bgSprite->getPosition().y -5);
	addChild(npcSPProgressTimer,1);
}

void GameScene::setMenu()
{
	//�˳���ť
	auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(GameScene::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

   //����1��ť
	skill1Item = MenuItemSprite::create(Sprite::create("skill/skill1.png"),
		Sprite::create("skill/skill1_selected.png"),
		Sprite::create("skill/skill1_disabled.png"),
		CC_CALLBACK_1(GameScene::selectedSkill1,this));
    
	skill1Item->setPosition(Vec2(skill1Item->getContentSize().width/2+200,
                                skill1Item->getContentSize().height/2));

	//����Skill1����ȴ��
	Sprite* skill1CoolSprite = Sprite::create("skill/skill1_disabled.png");

	skill1CoolBar = ProgressTimer::create(skill1CoolSprite);
	skill1CoolBar->setType(kCCProgressTimerTypeBar);
	skill1CoolBar->setMidpoint(ccp(0.5,0));
	skill1CoolBar->setBarChangeRate(ccp(0,1));
	skill1CoolBar->setPercentage(0);
	skill1CoolBar->setPosition(skill1Item->getPosition().x, skill1Item->getPosition().y);
	addChild(skill1CoolBar,2);

	//����2��ť
	skill2Item = MenuItemSprite::create(Sprite::create("skill/skill2.png"),
		Sprite::create("skill/skill2_selected.png"),
		Sprite::create("skill/skill2_disabled.png"),
		CC_CALLBACK_1(GameScene::selectedSkill2,this));
    
	skill2Item->setPosition(Vec2(skill1Item->getPosition().x + 60 ,
                                skill1Item->getPosition().y));

	//����Skill2����ȴ��
	Sprite* skill2CoolSprite = Sprite::create("skill/skill2_disabled.png");

	skill2CoolBar = ProgressTimer::create(skill2CoolSprite);
	skill2CoolBar->setType(kCCProgressTimerTypeBar);
	skill2CoolBar->setMidpoint(ccp(0.5,0));
	skill2CoolBar->setBarChangeRate(ccp(0,1));
	skill2CoolBar->setPercentage(0);
	skill2CoolBar->setPosition(skill2Item->getPosition().x, skill2Item->getPosition().y);
	addChild(skill2CoolBar,2);

	//����3��ť
	skill3Item = MenuItemSprite::create(Sprite::create("skill/skill3.png"),
		Sprite::create("skill/skill3_selected.png"),
		Sprite::create("skill/skill3_disabled.png"),
		CC_CALLBACK_1(GameScene::selectedSkill3,this));
    
	skill3Item->setPosition(Vec2(skill2Item->getPosition().x + 60 ,
                                skill2Item->getPosition().y));

	//����Skill����ȴ��
	Sprite* skill3CoolSprite = Sprite::create("skill/skill3_disabled.png");

	skill3CoolBar = ProgressTimer::create(skill3CoolSprite);
	skill3CoolBar->setType(kCCProgressTimerTypeBar);
	skill3CoolBar->setMidpoint(ccp(0.5,0));
	skill3CoolBar->setBarChangeRate(ccp(0,1));
	skill3CoolBar->setPercentage(0);
	skill3CoolBar->setPosition(skill3Item->getPosition().x, skill3Item->getPosition().y);
	addChild(skill3CoolBar,2);

	auto menu = Menu::create(closeItem, skill1Item, skill2Item, skill3Item, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
}

void GameScene::selectedSkill1(Ref* pSender)
{
	currentBulletState = NormalBullet;
}

void GameScene::selectedSkill2(Ref* pSender)
{
	currentBulletState = SpecialBullet;
}


void GameScene::selectedSkill3(Ref* pSender)
{
	currentBulletState = StunBullet;
}

void GameScene::update(float deltaTime)
{
	g_BulletManager->update(deltaTime);
	//����Ѫ����ŭ��
	
	//����bullet��ѡ��״̬
	switch (currentBulletState)
	{
	case NormalBullet:
		skill1Item->selected();
		skill2Item->unselected();
		skill3Item->unselected();
		break;
	case SpecialBullet:
		skill2Item->selected();
		skill1Item->unselected();
		skill3Item->unselected();
		break;
	case StunBullet:
		skill3Item->selected();
		skill1Item->unselected();
		skill2Item->unselected();
		break;
	default:
		break;
	}

	//���¼���1��ȴʱ��
	if(skill1NeedTime - deltaTime> 0)
	{
		skill1NeedTime -= deltaTime;
		skill1CoolBar->setPercentage(skill1NeedTime/skill1CoolDownTime * 100);
	}
	else
	{
		skill1NeedTime = 0.0f;
		skill1CoolBar->setPercentage(0);
	}
	//���¼���2��ȴʱ��
	if(skill2NeedTime - deltaTime> 0)
	{
		skill2NeedTime -= deltaTime;
		skill2CoolBar->setPercentage(skill2NeedTime/skill2CoolDownTime * 100);
	}
	else
	{
		skill2NeedTime = 0.0f;
		skill2CoolBar->setPercentage(0);
	}
	//���¼���3��ȴʱ��
	if(skill3NeedTime - deltaTime> 0)
	{
		skill3NeedTime -= deltaTime;
		skill3CoolBar->setPercentage(skill3NeedTime/skill3CoolDownTime * 100);
	}
	else
	{
		skill3NeedTime = 0.0f;
		skill3CoolBar->setPercentage(0);
	}

	collisionDetection();
}

//��������������  
void GameScene::onAcceleration(Acceleration* acc, Event* event)
{
	if(acc->x > 10)
	{
		_role1->setMoveToRight();
		currentActionState = Move;
		if((_role1->getPosition().x + 32) < visibleSize.width)
			_role1->setPosition(_role1->getPosition().x+2,_role1->getPosition().y);
	}
	else
	{
		_role1->setMoveToLeft();
		_role1->runAction(_role1->getNormalAction());
		
		if(_role1->getPosition().x > 0)
			_role1->setPosition(_role1->getPosition().x-2,_role1->getPosition().y);
	}
}

void GameScene::dealAction()
{
	switch (currentActionState)
	{
	case Attacked:
		break;
	case Fire:
		break;
	case Jump:
		break;
	case Move:
		break;
	case Normal:
		break;
	case Victory:
		break;
	case Fail:
		break;
	default:
		break;
	}
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
	if ( !contaiinsTouchLocation(touch) ) return false;
    
	startPosition = touch->getLocation();
    return true;
}

void GameScene::onTouchMoved(Touch* touch, Event* event)
{

}

void GameScene::onTouchEnded(Touch* touch, Event* event)
{
	endPosition = touch->getLocation();
	
	dealEndTouch();
}

void GameScene::onTouchCancelled(Touch* touches, Event* event)
{

}

void GameScene::dealEndTouch()
{
	switch (currentBulletState)
	{
	case NormalBullet:
		if(skill1NeedTime > 0)
		{
			CCLOG("cd time");
		}
		else
		{
			skill1NeedTime = skill1CoolDownTime;

			Vec2 pos = _role1->getPosition();
			Vec2 velocity;
			velocity.x= (endPosition.x - startPosition.x) / visibleSize.width * 2000 ;
			velocity.y= (endPosition.y - startPosition.y) / visibleSize.height * 2000;

			g_BulletManager->shoot(NormalBullet, pos, velocity);
		}
		break;
	case SpecialBullet:
		if(skill2NeedTime > 0)
		{
			CCLOG("cd time");
		}
		else
		{
			skill2NeedTime = skill2CoolDownTime;
			
			Vec2 pos = _role1->getPosition();
			Vec2 velocity;
			velocity.x= (endPosition.x - startPosition.x) / visibleSize.width * 2000 ;
			velocity.y= (endPosition.y - startPosition.y) / visibleSize.height * 2000;

			g_BulletManager->shoot(SpecialBullet, pos, velocity);
		}
		break;
	case StunBullet:
		if(skill3NeedTime > 0)
		{
			CCLOG("cd time");
		}
		else
		{
			skill3NeedTime = skill3CoolDownTime;

			Vec2 pos = _role1->getPosition();
			Vec2 velocity;
			velocity.x= (endPosition.x - startPosition.x) / visibleSize.width * 2000 ;
			velocity.y= (endPosition.y - startPosition.y) / visibleSize.height * 2000;

			g_BulletManager->shoot(StunBullet, pos, velocity);
		}
		break;
	default:
		break;
	}	
}

void GameScene::collisionDetection()
{
	_role1->decreaseHP(50);
	roleHPProgressTimer->setPercentage(float(_role1->getCurrentHP() * 100 / _role1->getTotalHP()));
	
	_role1->increaseSP(1);
	roleSPProgressTimer->setPercentage(float(_role1->getCurrentSP() * 100 / _role1->getTotalSP()));

	_role2->decreaseHP(1);
	npcHPProgressTimer->setPercentage(float(_role2->getCurrentHP() * 100 / _role2->getTotalHP()));
	
	_role2->increaseSP(1);
	npcSPProgressTimer->setPercentage(float(_role2->getCurrentSP() * 100 / _role2->getTotalSP()));
}