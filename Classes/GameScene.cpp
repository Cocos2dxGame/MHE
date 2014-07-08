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
    
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

    // 'layer' is an autorelease object
    auto layer = GameScene::create();
	layer->setPhyWorld(scene->getPhysicsWorld());

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

	this->setAccelerometerEnabled(true);

    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(GameScene::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

	_ball = Sprite::create("ball.png");
	_ball->setPosition(Vec2(visibleSize.width/2 + origin.x, _ball->getContentSize().height/2));	
	auto ballBody = PhysicsBody::createBox(_ball->getContentSize());
	_ball->setPhysicsBody(ballBody);
	_ball->getPhysicsBody()->setVelocity(Vec2(0,900));
    this->addChild(_ball, 0);

	_person = Person::create();
	_person->setPosition(200,100);
	addChild(_person,0);
	
	_person->setMoveToRight();
	_person->runAction(_person->getNormalAction());
	
	_bullet = Bullet::create();
	_bullet->setPosition(_person->getPosition());
	_bullet->getPhysicsBody()->setVelocity(Vec2(0,0));
	addChild(_bullet,0);

	auto edgeSp = Sprite::create();
	auto boundBody = PhysicsBody::createEdgeBox(visibleSize,PHYSICSBODY_MATERIAL_DEFAULT,3);
	edgeSp->setPosition(Point(visibleSize.width/2,visibleSize.height/2));
	edgeSp->setPhysicsBody(boundBody);
	this->addChild(edgeSp);
	edgeSp->setTag(0);
    
    return true;
}

void GameScene::setPhyWorld(cocos2d::PhysicsWorld* world)
{
	m_world = world;
	Vect gravity(0, -1000);
	m_world->setGravity(gravity);
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
	CCLOG("Offset position x = %f, y = %f",_person->getPhysicsBody()->getPositionOffset().x, _person->getPhysicsBody()->getPositionOffset().y);
	
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
	
	//auto director = Director::getInstance();
	//director->getActionManager()->addAction(_person->getFireAction(), _person, true);

	_bullet->setVelocity(vertex);
	_bullet->setPosition(_person->getPosition());
	_bullet->getPhysicsBody()->setVelocity(_bullet->getVelocity());
}

void GameScene::onTouchCancelled(Touch* touches, Event* event)
{

}