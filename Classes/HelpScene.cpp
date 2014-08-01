#include "HelpScene.h"
USING_NS_CC;

HelpScene::HelpScene()
{
}

HelpScene::~HelpScene()
{
}

Scene* HelpScene::createScene()
{
	Scene* scene = Scene::create();

	auto layer = HelpScene::create();

	scene->addChild(layer,0);

	return scene;
}

bool HelpScene::init()
{
	visibleSize = Director::sharedDirector()->getVisibleSize();

	auto bg = Sprite::create("background/bg_configure.png");
	bg->setScale(visibleSize.width/bg->getContentSize().width,
		visibleSize.height/bg->getContentSize().height);
	bg->setPosition(visibleSize/2);
	addChild(bg,0);

	auto help = Sprite::create("background/help.png");
	help->setScale(visibleSize.width*3/4/help->getContentSize().width);
	help->setPosition(visibleSize/2);
	addChild(help,1);

	return true;
}

