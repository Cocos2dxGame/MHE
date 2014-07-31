#include "ConfigureScene.h"

USING_NS_CC;
//using namespace ui;

bool OpenMusic;
bool OpenMusicEffect;

ConfigureScene::ConfigureScene()
{
	OpenMusic = true;
	OpenMusicEffect = true;
}

ConfigureScene::~ConfigureScene()
{
}

Scene* ConfigureScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();
	
	// 'layer' is an autorelease object
	auto layer = ConfigureScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool ConfigureScene::init()
{
	visibleSize = Director::sharedDirector()->getVisibleSize();

	auto bg = Sprite::create("background/bg_002.png");
	bg->setScale(visibleSize.width/bg->getContentSize().width,
		visibleSize.height/bg->getContentSize().height);
	bg->setPosition(visibleSize/2);
	addChild(bg);

	auto musicSetLabel =  LabelTTF::create("Music", "Arial", 24);
	musicSetLabel->setPosition(visibleSize.width/4,
		visibleSize.height*3/4);
	addChild(musicSetLabel,1);

	//CheckBox* musicCheckBox = CheckBox::create("button/check_box_normal.png",
	//										  "button/check_box_normal_press.png",
	//										  "button/check_box_active.png",
	//										  "button/check_box_normal_disable.png",
	//										  "button/check_box_active_disable.png");
	//musicCheckBox->setPosition(Vec2(visibleSize.width*3/4, visibleSize.height*3/4));	
	//musicCheckBox->addEventListener(CC_CALLBACK_2(ConfigureScene::selectedMusicEvent, this));
	//addChild(musicCheckBox,1);

	auto* musicEffectSetLabel =  LabelTTF::create("MusicEffect", "Arial", 24);
	musicEffectSetLabel->setPosition(visibleSize.width/4,
		visibleSize.height/4);
	addChild(musicEffectSetLabel,1);

	//CheckBox* musicEffectCheckBox = CheckBox::create("button/check_box_normal.png",
	//										  "button/check_box_normal_press.png",
	//										  "button/check_box_active.png",
	//										  "button/check_box_normal_disable.png",
	//										  "button/check_box_active_disable.png");
	//musicEffectCheckBox->setPosition(Vec2(visibleSize.width*3/4, visibleSize.height/4));	
	//musicEffectCheckBox->addEventListener(CC_CALLBACK_2(ConfigureScene::selectedMusicEffectEvent, this));
	//addChild(musicEffectCheckBox,1);

	return true;
}

//void ConfigureScene::selectedMusicEvent(Ref* pSender, CheckBox::EventType type)
//{
//	switch (type)
//	{
//	case cocos2d::ui::CheckBox::EventType::SELECTED:
//		OpenMusic = true;
//		break;
//	case cocos2d::ui::CheckBox::EventType::UNSELECTED:
//		OpenMusic = false;
//		break;
//	default:
//		break;
//	}
//}
//
//void ConfigureScene::selectedMusicEffectEvent(Ref* pSender, CheckBox::EventType type)
//{
//	switch (type)
//	{
//	case cocos2d::ui::CheckBox::EventType::SELECTED:
//		OpenMusicEffect = true;
//		break;
//	case cocos2d::ui::CheckBox::EventType::UNSELECTED:
//		OpenMusicEffect = false;
//		break;
//	default:
//		break;
//	}
//}



