#include "SceneManager.h"
#include "StartScene.h"
#include "ChapterScene.h"

USING_NS_CC;

Scene* StartScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = StartScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool StartScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

	Size visibleSize = Director::getInstance()->getVisibleSize();

	TTFConfig config_font96("Marker Felt.ttf", 96);
	TTFConfig config_font52("Marker Felt.ttf", 52);

	Label *titleLeft = Label::createWithTTF(config_font96, "Menu ");
	Label *titleRight = Label::createWithTTF(config_font96, " System");
	Label *titleQuotes = Label::createWithTTF(config_font96, ""                        "");
	Label *titleCenterTop = Label::createWithTTF(config_font52, "How to build a...");
	Label *titleCenterBottom = Label::createWithTTF(config_font96, "Part 1");

	//create new scene
	MenuItemFont *startNew = MenuItemFont::create("New Game", CC_CALLBACK_1(StartScene::onNewGame, this));
	MenuItemFont *credits = MenuItemFont::create("Credits", CC_CALLBACK_1(StartScene::onNewGame, this));

	Menu *menu = Menu::create(startNew, credits, NULL);

	titleCenterTop->setPosition(
		Point( (visibleSize.width - titleCenterTop->getContentSize().width)/2,
		visibleSize.height - 100) );
	this->addChild(titleCenterTop);

	titleQuotes->setPosition(
		Point((visibleSize.width - titleQuotes->getContentSize().width)/2,
		titleCenterTop->getPosition().y - titleQuotes->getContentSize().height - 40) );
	this->addChild(titleQuotes);

	int tileWidth = titleLeft->getContentSize().width + titleRight->getContentSize().width + 50;
	titleLeft->setPosition(
		Point( (visibleSize.width - tileWidth)/2,
		titleCenterTop->getPosition().y - titleLeft->getContentSize().height - 40) );
	this->addChild(titleLeft);

	titleRight->setPosition(
		Point( (visibleSize.width - tileWidth)/2 + titleLeft->getContentSize().width + 50,
		titleCenterTop->getPosition().y - titleRight->getContentSize().height - 40) );
	this->addChild(titleRight);

	titleCenterBottom->setPosition(
		Point( (visibleSize.width - titleCenterBottom->getContentSize().width)/2,
		titleRight->getPosition().y - titleCenterBottom->getContentSize().height - 40) );
	this->addChild(titleCenterBottom);

	menu->setPosition(
		Point( visibleSize.width / 2,
		titleCenterBottom->getPosition().y-150 ) );
	menu->alignItemsVerticallyWithPadding(80.0f);
	this->addChild(menu, 2);

	return true;

	/*
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(StartScene::menuCloseCallback, this));
    
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

    // add "StartScene" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
    
    return true;
	*/
}


void StartScene::menuCloseCallback(Ref* pSender)
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

void StartScene::onNewGame(Object* pSender)
{
	Scene* pChapterScene = ChapterScene::createScene();
	SceneManager::go(pChapterScene);
}