#include "Person.h"

USING_NS_CC;

Person::Person()
{
	HP = 200;
	Rage = 200;
	speed = 10;
	jumpSpeed  = 10;
	moveRight = true;
	strcpy(roleName, "Role2");
	
	char plistFileName[100];
	sprintf(plistFileName,"character/%s.plist", roleName);  
	cache = SpriteFrameCache::sharedSpriteFrameCache();
	//cache->addSpriteFramesWithFile(plistFileName);
}

Person* Person::create()
{
	Person* person = new Person();

	char keyname[100];
	sprintf(keyname,"%sNormal1.plist", person->roleName);

	if(person && person->initWithSpriteFrame(person->cache->spriteFrameByName(keyname)))
	{
		person->setAction(person->cache);
		person->autorelease();
		return person;
	}

	return NULL;
}

void Person::setAction(SpriteFrameCache* cache)
{
	this->setNormalAction(cache);
	this->setAttackedAction(cache);
	this->setJumpAction( cache);
	this->setFireAction(cache);
	this->setMoveAction(cache);
}

void Person::setMoveToLeft()
{
	moveRight = false;
}

void Person::setMoveToRight()
{
	moveRight = true;
}

void Person::setNormalAction(cocos2d::SpriteFrameCache* cache)
{
	char keyname[100];
	auto animation = Animation::create();
	for (int i = 1; i < 6; i++)
	{
		sprintf(keyname,"%sNormal%d.png", roleName, i);
        animation->addSpriteFrame(cache->spriteFrameByName(keyname));
	}

	animation->setDelayPerUnit(0.1f);
	animation->setRestoreOriginalFrame(true);
	auto action = Animate::create(animation);

	normalAction = RepeatForever::create(Sequence::create(action, NULL));
}
RepeatForever* Person::getNormalAction()
{
	return normalAction;
}

void Person::setMoveAction(cocos2d::SpriteFrameCache* cache)
{
	char keyname[100];
	auto animation = Animation::create();

	for (int i = 1; i < 3; i++)
	{
		sprintf(keyname, "%sMove%d.png", roleName, i);  
        animation->addSpriteFrame(cache->spriteFrameByName(keyname));  
	}

	animation->setDelayPerUnit(0.5f);
	animation->setRestoreOriginalFrame(true);
	auto action = Animate::create(animation);

	moveAction = RepeatForever::create(Sequence::create(action, NULL));
}

RepeatForever* Person::getMoveAction()
{
	return moveAction;
}

void Person::setAttackedAction(cocos2d::SpriteFrameCache* cache)
{
	char keyname[100];
	auto animation = Animation::create();
	for (int i = 1; i < 3; i++)
	{
		sprintf(keyname, "%sAttacked%d.png", roleName, i);  
        animation->addSpriteFrame(cache->spriteFrameByName(keyname));  
	}

	animation->setDelayPerUnit(0.1f);
	animation->setRestoreOriginalFrame(true);
	attackedAction = Animate::create(animation);

	//auto action = Animate::create(animation);
	//normalAction = RepeatForever::create(Sequence::create(action, NULL));
}
	
Animate* Person::getAttackedAction()
{
	return attackedAction;
}

void Person::setJumpAction(cocos2d::SpriteFrameCache* cache)
{
	char keyname[100];
	auto animation = Animation::create();
	sprintf(keyname, "%sJump.png", roleName);  
    animation->addSpriteFrame(cache->spriteFrameByName(keyname));  

	animation->setDelayPerUnit(0.1f);
	animation->setRestoreOriginalFrame(true);
	jumpAction = Animate::create(animation);

	//normalAction = RepeatForever::create(Sequence::create(action, NULL));
}

Animate* Person::getJumpAction()
{
	return jumpAction;
}

void Person::setFireAction(cocos2d::SpriteFrameCache* cache)
{
	char keyname[100];
	auto animation = Animation::create();

	//sprintf(keyname,"%s.png","BoyNormal1");
	//animation->addSpriteFrame(cache->spriteFrameByName(keyname));

	sprintf(keyname, "%sFire.png", roleName);
    animation->addSpriteFrame(cache->spriteFrameByName(keyname));  

	animation->setDelayPerUnit(0.5f);
	animation->setRestoreOriginalFrame(true);
	fireAction = Animate::create(animation);

	//moveAction = RepeatForever::create(Sequence::create(action, NULL));
}

Animate* Person::getFireAction()
{
	return fireAction;
}

Rect Person::getRect()
{
	auto s = getContentSize();
	return Rect(getPosition().x-s.width/2,getPosition().y-s.height/2, s.width, s.height);
}