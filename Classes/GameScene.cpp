#include "GameScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

BulletManager* g_BulletManager;

GameScene::GameScene()
	:roleCurrentHP(0),roleCurrentSP(0),npcCurrentHP(0),npcCurrrentSP(0),
	skill1CoolDownTime(0.2),skill2CoolDownTime(5.0),skill3CoolDownTime(10.0),
	skill1NeedTime(0.0),skill2NeedTime(0.0), skill3NeedTime(0.0),
	currentBulletState(NormalBullet),_npc1(nullptr),_npc2(nullptr),_npc3(nullptr),background(nullptr)
{
	//curScene = GameScene3;
}

Scene* GameScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
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

	//触摸监听
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);

    listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	this->setAccelerometerEnabled(true);

    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
	
	//music
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("music/background.mp3", true);

	
	//设置角色的血条、怒气条
	setRoleProgressBar();

	//设置npc的血条、怒气条
	setNpcProgressBar();
	//设置技能按钮
	setMenu(curScene);

	switch (curScene)
	{
	case GameScene1:
		//背景
		background = Sprite::create("background/bg_002.png");

		//设置npc
		_npc1 = NPC1::create();
		_curNPC = (NPC*)_npc1;
		//_curNPC = NPC2::create();

		//中间障碍物
		obstacle = Sprite::create("obstacle1.png");

		g = Vec2(0, -800);
		break;
	case GameScene2:
		background = Sprite::create("background/bg_003.png");

		//设置npc
		_npc2 = NPC2::create();
		_curNPC = (NPC*)_npc2;
		//_curNPC = NPC2::create();

		//中间障碍物
		obstacle = Sprite::create("obstacle2.png");

		g = Vec2(0, -800);
		break;
	case GameScene3:
		background = Sprite::create("background/bg_004.png");
		
		//设置npc
		_npc3 = NPC3::create();
		_curNPC = (NPC*)_npc3;
		//_curNPC = NPC2::create();

		//中间障碍物
		obstacle = Sprite::create("obstacle3.png");

		g = Vec2(0, -800);
		break;
	default:
		break;
	}
	
	//设置背景坐标，以及添加到层
	background->setScaleX(visibleSize.width/background->getContentSize().width);
	background->setScaleY(visibleSize.height/background->getContentSize().height);
	background->setPosition(visibleSize.width/2, visibleSize.height/2);
	addChild(background,0);

	//设置player
	_player = Player::create();
	_player->retain();
	_player->setPosition(100,200);
	_player->setScale(0.5);
	_player->setTag(1);
	addChild(_player,1);
	_player->normalAction();

	//设置npc
	_curNPC->setPosition(700,200);
	_curNPC->setScale(0.5);
	_curNPC->setTag(2);
	addChild(_curNPC,1);
	_curNPC->attackedAction();

	//设置障碍物坐标，以及添加到层
	obstacle->setPosition(Vec2(visibleSize.width/2, 220));
	obstacle->setTag(3);
	addChild(obstacle,1);
	
	//将player添加到spriteVector中
	spritesVector.pushBack(_player);
	spritesVector.pushBack(_curNPC);
	spritesVector.pushBack(obstacle);

	//设置重力以及初始化BulletManager
	
	g_BulletManager = BulletManager::create(curScene,(Layer*)this, &spritesVector, g);

	this->scheduleUpdate();

    return true;
}

void GameScene::setRoleProgressBar()
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

	roleSPProgressTimer->setPercentage(0);

	roleSPProgressTimer->setPosition(bgSprite->getPosition().x + 29, bgSprite->getPosition().y -5);
	addChild(roleSPProgressTimer,1);

}

void GameScene::setNpcProgressBar()
{
	Sprite* bgSprite = Sprite::create("system/ProgressBarBackground1.png");
	bgSprite ->setScaleX(-1.0);
	bgSprite->setPosition(visibleSize.width - bgSprite->getContentSize().width/2 - 70, visibleSize.height-20);
	addChild(bgSprite,1);

	//设置npc的血量
	Sprite* npcHPSprite = Sprite::create("system/HPTotal.png");

	npcHPProgressTimer = ProgressTimer::create(npcHPSprite);
	npcHPProgressTimer->setType(kCCProgressTimerTypeBar);

	npcHPProgressTimer->setMidpoint(ccp(1,0.5));
	npcHPProgressTimer->setBarChangeRate(ccp(1,0));

	npcHPProgressTimer->setPercentage(100);

	npcHPProgressTimer->setPosition(bgSprite->getPosition().x - 33, bgSprite->getPosition().y + 9);
	addChild(npcHPProgressTimer,1);
	
	//设置npc的怒气
	Sprite* npcSPSprite = Sprite::create("system/SPTotal.png");

	npcSPProgressTimer = ProgressTimer::create(npcSPSprite);
	npcSPProgressTimer->setType(kCCProgressTimerTypeBar);

	npcSPProgressTimer->setMidpoint(ccp(1,0.5));
	npcSPProgressTimer->setBarChangeRate(ccp(1,0));

	npcSPProgressTimer->setPercentage(0);

	npcSPProgressTimer->setPosition(bgSprite->getPosition().x - 29, bgSprite->getPosition().y -5);
	addChild(npcSPProgressTimer,1);
}

void GameScene::setMenu(GameSceneType curScene)
{
	//暂停按钮
	auto pauseItem = MenuItemImage::create(
										"button/pause.png",
										"button/pause_selected.png",
										CC_CALLBACK_1(GameScene::doPause, this));
	pauseItem->setScale(visibleSize.width/20/pauseItem->getContentSize().width);

	pauseItem->setPosition(Vec2(visibleSize.width - visibleSize.width/12/2,
		visibleSize.height - visibleSize.height/12/2));

	//退出按钮
	auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(GameScene::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

	//Jump按钮
	auto jumpItem = MenuItemImage::create(
                                           "button/jump.png",
                                           "button/jump.png",
                                           CC_CALLBACK_1(GameScene::jump, this));
    
	jumpItem->setPosition(Vec2(visibleSize.width - 100, jumpItem->getContentSize().height/2));

	switch (curScene)
	{
	case GameScene1:
		//技能1按钮
		skill1Item = MenuItemSprite::create(Sprite::create("skill/skill11.png"),
			Sprite::create("skill/skill11_selected.png"),
			Sprite::create("skill/skill11_disabled.png"),
			CC_CALLBACK_1(GameScene::selectedSkill1,this));

		//技能2按钮
		skill2Item = MenuItemSprite::create(Sprite::create("skill/skill12.png"),
			Sprite::create("skill/skill12_selected.png"),
			Sprite::create("skill/skill12_disabled.png"),
			CC_CALLBACK_1(GameScene::selectedSkill2,this));

		//技能3按钮
		skill3Item = MenuItemSprite::create(Sprite::create("skill/skill13.png"),
			Sprite::create("skill/skill13_selected.png"),
			Sprite::create("skill/skill13_disabled.png"),
			CC_CALLBACK_1(GameScene::selectedSkill3,this));

		//设置Skill1的冷却条
		skill1CoolSprite = Sprite::create("skill/skill11_disabled.png");
		skill1CoolBar = ProgressTimer::create(skill1CoolSprite);

		//设置Skill2的冷却条
		skill2CoolSprite = Sprite::create("skill/skill12_disabled.png");
		skill2CoolBar = ProgressTimer::create(skill2CoolSprite);

		//设置Skill3的冷却条
		skill3CoolSprite = Sprite::create("skill/skill13_disabled.png");
		skill3CoolBar = ProgressTimer::create(skill3CoolSprite);
		break;
	case GameScene2:
		//技能1按钮
		skill1Item = MenuItemSprite::create(Sprite::create("skill/skill21.png"),
			Sprite::create("skill/skill21_selected.png"),
			Sprite::create("skill/skill21_disabled.png"),
			CC_CALLBACK_1(GameScene::selectedSkill1,this));

		//技能2按钮
		skill2Item = MenuItemSprite::create(Sprite::create("skill/skill22.png"),
			Sprite::create("skill/skill22_selected.png"),
			Sprite::create("skill/skill22_disabled.png"),
			CC_CALLBACK_1(GameScene::selectedSkill2,this));

		//技能3按钮
		skill3Item = MenuItemSprite::create(Sprite::create("skill/skill23.png"),
			Sprite::create("skill/skill23_selected.png"),
			Sprite::create("skill/skill23_disabled.png"),
			CC_CALLBACK_1(GameScene::selectedSkill3,this));

		//设置Skill1的冷却条
		skill1CoolSprite = Sprite::create("skill/skill21_disabled.png");
		skill1CoolBar = ProgressTimer::create(skill1CoolSprite);

		//设置Skill2的冷却条
		skill2CoolSprite = Sprite::create("skill/skill22_disabled.png");
		skill2CoolBar = ProgressTimer::create(skill2CoolSprite);

		//设置Skill3的冷却条
		skill3CoolSprite = Sprite::create("skill/skill23_disabled.png");
		skill3CoolBar = ProgressTimer::create(skill3CoolSprite);
		break;
	case GameScene3:
		//技能1按钮
		skill1Item = MenuItemSprite::create(Sprite::create("skill/skill31.png"),
			Sprite::create("skill/skill31_selected.png"),
			Sprite::create("skill/skill31_disabled.png"),
			CC_CALLBACK_1(GameScene::selectedSkill1,this));

		//技能2按钮
		skill2Item = MenuItemSprite::create(Sprite::create("skill/skill32.png"),
			Sprite::create("skill/skill32_selected.png"),
			Sprite::create("skill/skill32_disabled.png"),
			CC_CALLBACK_1(GameScene::selectedSkill2,this));

		//技能3按钮
		skill3Item = MenuItemSprite::create(Sprite::create("skill/skill33.png"),
			Sprite::create("skill/skill33_selected.png"),
			Sprite::create("skill/skill33_disabled.png"),
			CC_CALLBACK_1(GameScene::selectedSkill3,this));

		//设置Skill1的冷却条
		skill1CoolSprite = Sprite::create("skill/skill31_disabled.png");
		skill1CoolBar = ProgressTimer::create(skill1CoolSprite);

		//设置Skill2的冷却条
		skill2CoolSprite = Sprite::create("skill/skill32_disabled.png");
		skill2CoolBar = ProgressTimer::create(skill2CoolSprite);

		//设置Skill3的冷却条
		skill3CoolSprite = Sprite::create("skill/skill33_disabled.png");
		skill3CoolBar = ProgressTimer::create(skill3CoolSprite);
		break;
	default:
		break;
	}
   
    
	skill1Item->setPosition(Vec2(skill1Item->getContentSize().width/2+200,
                                skill1Item->getContentSize().height/2));

	skill2Item->setPosition(Vec2(skill1Item->getPosition().x + 60 ,
                                skill1Item->getPosition().y));

	skill3Item->setPosition(Vec2(skill2Item->getPosition().x + 60 ,
                                skill2Item->getPosition().y));

	skill1CoolBar->setType(kCCProgressTimerTypeBar);
	skill1CoolBar->setMidpoint(ccp(0.5,0));
	skill1CoolBar->setBarChangeRate(ccp(0,1));
	skill1CoolBar->setPercentage(0);
	skill1CoolBar->setPosition(skill1Item->getPosition().x, skill1Item->getPosition().y);
	addChild(skill1CoolBar,2);

	skill2CoolBar->setType(kCCProgressTimerTypeBar);
	skill2CoolBar->setMidpoint(ccp(0.5,0));
	skill2CoolBar->setBarChangeRate(ccp(0,1));
	skill2CoolBar->setPercentage(0);
	skill2CoolBar->setPosition(skill2Item->getPosition().x, skill2Item->getPosition().y);
	addChild(skill2CoolBar,2);

	skill3CoolBar->setType(kCCProgressTimerTypeBar);
	skill3CoolBar->setMidpoint(ccp(0.5,0));
	skill3CoolBar->setBarChangeRate(ccp(0,1));
	skill3CoolBar->setPercentage(0);
	skill3CoolBar->setPosition(skill3Item->getPosition().x, skill3Item->getPosition().y);
	addChild(skill3CoolBar,2);

	//添加菜单 
	auto menu = Menu::create(pauseItem, closeItem, jumpItem, skill1Item, skill2Item, skill3Item, NULL);
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
	//更新血量，怒气
	
	//更新bullet的选择状态
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

	//更新技能1冷却时间
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
	//更新技能2冷却时间
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
	//更新技能3冷却时间
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

//重力加速器方法  
void GameScene::onAcceleration(Acceleration* acc, Event* event)
{
	if(acc->x > 0.25)
	{
		if((_player->getPosition().x + _player->getContentSize().width/2) < obstacle->getPosition().x - obstacle->getContentSize().width/2)
		{
			_player->setFlippedX(false);
			_player->setPosition(_player->getPosition().x+2, _player->getPosition().y);
			_player->normalAction();
		}
	}

	if(acc->x < -0.25)
	{
		if(_player->getPosition().x - _player->getContentSize().width/2 > 0)
		{
			_player->setFlippedX(true);
			_player->setPosition(_player->getPosition().x-2, _player->getPosition().y);
			_player->normalAction();
		}
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
	return _player->getBoundingBox().containsPoint(convertTouchToNodeSpace(touch));
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

			Vec2 pos = _player->getPosition();
			Vec2 velocity;
			velocity.x= (endPosition.x - startPosition.x) / visibleSize.width * 2000 ;
			velocity.y= (endPosition.y - startPosition.y) / visibleSize.height * 2000;

			if(_player->isFlippedX())
				if(velocity.x > 0)
					_player->setFlippedX(-1);
			else
				if(velocity.x < 0)
					_player->setFlippedX(-1);

			g_BulletManager->shoot(NormalBullet, pos, velocity);
			//CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect();
			_player->fireAction();
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
			
			Vec2 pos = _player->getPosition();
			Vec2 velocity;
			velocity.x= (endPosition.x - startPosition.x) / visibleSize.width * 2000 ;
			velocity.y= (endPosition.y - startPosition.y) / visibleSize.height * 2000;

			g_BulletManager->shoot(SpecialBullet, pos, velocity);
			//CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect();
			_player->fireAction();
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

			Vec2 pos = _player->getPosition();
			Vec2 velocity;
			velocity.x= (endPosition.x - startPosition.x) / visibleSize.width * 2000 ;
			velocity.y= (endPosition.y - startPosition.y) / visibleSize.height * 2000;

			g_BulletManager->shoot(StunBullet, pos, velocity);
			//CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect();
			_player->fireAction();
		}
		break;
	default:
		break;
	}	
}

void GameScene::collisionDetection()
{
	roleHPProgressTimer->setPercentage(_player->getHP()*100 / _player->getTotalHP());
	roleSPProgressTimer->setPercentage(_player->getSP()*100 / _player->getTotalSP());

	npcHPProgressTimer->setPercentage(_curNPC->getHP()*100 / _curNPC->getTotalHP());
	npcSPProgressTimer->setPercentage(_curNPC->getSP()*100 / _curNPC->getTotalSP());
}

void GameScene::jump(Ref* pSender)
{
	_player->jumpAction();
}

void GameScene::doPause(Ref* pSender)
{
	CCDirector::sharedDirector()->pause();  
    CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();  
    CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseAllEffects();  
    PauseLayer *pauseLayer = PauseLayer::create();  
    addChild(pauseLayer,9999); 
}