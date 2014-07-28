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

	// add background image
	Sprite* bg = Sprite::create("background/bg_000.png");
	bg->setPosition(visibleSize.width/2, visibleSize.height/2);
	bg->setScaleX(visibleSize.width/bg->getContentSize().width);
	bg->setScaleY(visibleSize.height/bg->getContentSize().height);
	this->addChild(bg, 0);

	// create new scene
	MenuItemImage *newgame = MenuItemImage::create("button/bt_000.png", "button/bts_000.png", CC_CALLBACK_1(StartScene::onNewGame, this));
	MenuItemImage *config = MenuItemImage::create("button/bt_001.png", "button/bts_001.png", CC_CALLBACK_1(StartScene::onNewGame, this));
	MenuItemImage *help = MenuItemImage::create("button/bt_002.png", "button/bts_002.png", CC_CALLBACK_1(StartScene::onNewGame, this));
	float scale = visibleSize.height/860;
	newgame->setScale(scale);
	config->setScale(scale);
	help->setScale(scale);

	Menu *menu = Menu::create(newgame, config ,help, NULL);

	menu->setPosition(visibleSize.width*0.26, visibleSize.height*0.33);
	menu->alignItemsVerticallyWithPadding(0.014*visibleSize.height);
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