#include "ChapterScene.h"

USING_NS_CC;

Scene* ChapterScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = ChapterScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool ChapterScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(ChapterScene::menuCloseCallback, this));
    


	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = LabelTTF::create("Hello World", "Arial", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "ChapterScene" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);

	// add the menu icon
	std::string images[] = {"background/bg_002.jpg", "background/bg_003.jpg", "background/bg_004.jpg"};
	int imagesNum = 3;
	float imageWidth = visibleSize.width * 0.6;
	float imageHeight = visibleSize.height * 0.6;
	float imageSpace = visibleSize.width * 0.05;
	float imageOrigin = imageSpace + imageWidth/2;

	for(int i=0; i<imagesNum; i++)
	{
		std::string image = images[i];
		Sprite *pSprite = Sprite::create(image);
		pSprite->setScaleX(imageWidth/pSprite->getContentSize().width);
		pSprite->setScaleY(imageHeight/pSprite->getContentSize().height);
		float offset = imageOrigin + (imageWidth + imageSpace) * i;
		pSprite->setPosition(origin.x+offset, origin.y+visibleSize.height/2);
		this->addChild(pSprite, 0);
		m_menuIconVector.pushBack(pSprite);
	}
    
	// register event listener
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(ChapterScene::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(ChapterScene::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(ChapterScene::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    return true;
}


void ChapterScene::menuCloseCallback(Ref* pSender)
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

void ChapterScene::move(float distance)
{
	Vec2 moveVec(distance, 0);

	for(Sprite *pSprite : m_menuIconVector)
	{
		pSprite->runAction(MoveBy::create(0, moveVec));
	}
}

bool ChapterScene::onTouchBegan(Touch *touch, Event *unused_event)
{
	m_touchBegan = this->convertTouchToNodeSpace(touch);
	m_velocity = 0;

	return true;
}

void ChapterScene::onTouchMoved(Touch *touch, Event *unused_event)
{
	Point touchEnded = this->convertTouchToNodeSpace(touch);
	move(touchEnded.x-m_touchBegan.x);
	m_touchBegan = touchEnded;
}

void ChapterScene::onTouchEnded(Touch *touch, Event *unused_event)
{

}

void ChapterScene::update(float delta)
{

}