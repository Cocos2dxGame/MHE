#include "GameScene.h"

USING_NS_CC;

GameScene::GameScene()
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

    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(GameScene::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

	_person = Person::create();
	_person->setPosition(200,100);
	addChild(_person,0);
	
	_person->setMoveToRight();
	_person->runAction(_person->getNormalAction());
	
	_bullet = Bullet::create();
	_bullet->setPosition(_person->getPosition());
	addChild(_bullet,0);

    return true;
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
	return _person->getRect().containsPoint(convertTouchToNodeSpace(touch));
}

bool GameScene::onTouchBegan(Touch* touch, Event* event)
{
	CCLOG("Paddle::onTouchBegan id = %d, x = %f, y = %f", touch->getID(), touch->getLocation().x, touch->getLocation().y);
	CCLOG("Person's position x = %f, y = %f", _person->getPosition().x, _person->getPosition().y);
	
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
	
	_bullet->setVelocity(vertex);
	_bullet->setPosition(_person->getPosition());
	nextState = Fire_Action;
}

void GameScene::onTouchCancelled(Touch* touches, Event* event)
{

}