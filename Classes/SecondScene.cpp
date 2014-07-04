#include "SecondScene.h"

USING_NS_CC;

Scene* SecondScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::createWithPhysics();
    
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

    // 'layer' is an autorelease object
    auto layer = SecondScene::create();
	layer->setPhyWorld(scene->getPhysicsWorld());

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool SecondScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	this->setAccelerometerEnabled(true);

    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(SecondScene::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

	_ball = Sprite::create("ball.png",Rect(0,0,72,72));
    _ball->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));	
	auto ballBody = PhysicsBody::createCircle(_ball->getContentSize().width/2);
	_ball->setPhysicsBody(ballBody);
    this->addChild(_ball, 0);

	//Texture2D* texture = TextureCache::sharedTextureCache()->addImage("picgirl.png");

	//_sprite = Sprite::create("picgirl.png", Rect(0,0,32,48));
	//_sprite->setPosition(100,100);
	//this->addChild(_sprite);

	//auto animation = Animation::create();
	//for (int i = 2; i < 3; i++)
	//{
	//	for (int j = 0; j < 4; j++)
	//	{
	//		SpriteFrame* frame = SpriteFrame::createWithTexture(texture, Rect(32*j,48*i,32,48));
	//		animation->addSpriteFrame(frame);
	//	}
	//}

	//animation->setDelayPerUnit(0.2f);
	//animation->setRestoreOriginalFrame(true);
	//auto action = Animate::create(animation);

	//auto repeatAction = RepeatForever::create(Sequence::create(action, NULL));

	////_sprite->runAction(Sequence::create(action, action->reverse(), NULL));
	//_sprite->runAction(repeatAction);

	_person = Person::create();
	_person->setPosition(200,200);
	addChild(_person,0);
	_person->setMoveToRight();
	_person->runAction(_person->freeAction());
	

	auto edgeSp = Sprite::create();
	auto boundBody = PhysicsBody::createEdgeBox(visibleSize,PHYSICSBODY_MATERIAL_DEFAULT,3);
	edgeSp->setPosition(Point(visibleSize.width/2,visibleSize.height/2));
	edgeSp->setPhysicsBody(boundBody);
	this->addChild(edgeSp);
	edgeSp->setTag(0);
    
    return true;
}

void SecondScene::setPhyWorld(cocos2d::PhysicsWorld* world)
{
	m_world = world;
	Vect gravity(0, -50);
	m_world->setGravity(gravity);
}

//重写重力加速器方法  
void SecondScene::onAcceleration(Acceleration* acc, Event* event)
{
	if(acc->x > 0)
	{
		_person->setMoveToRight();
		_person->runAction(_person->moveAction());
	}
	else
	{
		_person->setMoveToLeft();
		_person->runAction(_person->moveAction());
	}
}  

void SecondScene::menuCloseCallback(Ref* pSender)
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
