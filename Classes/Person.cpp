#include "Person.h"

USING_NS_CC;

Person::Person()
{
	HP = 200;
	Rage = 200;
	speed = 10;
	jumpSpeed  = 10;
	moveRight = true;
}
Person* Person::create()
{
	SpriteFrameCache* cache = SpriteFrameCache::sharedSpriteFrameCache();
	cache->addSpriteFramesWithFile("character/Boy.plist");

	Person* person = new Person();
	if(person && person->initWithSpriteFrame(cache->spriteFrameByName("BoyNormal1.png")))
	{
		person->autorelease();
		person->setAction(cache);
		return person;
	}
	/*if(person && person->initWithFile("ball.png"))
	{
		person->autorelease();
		person->setAction(cache);
		return person;
	}*/

	return NULL;
}

void Person::setAction(SpriteFrameCache* cache)
{
	this->setNormalAction(cache);
	/*this->setAttachedAction(cache);
	this->setJumpAction( cache);
	this->setFireAction(cache);*/
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
		sprintf(keyname,"%s%d.png","BoyNormal",i);  
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

	//sprintf(keyname,"%s.png","BoyNormal1");
	//animation->addSpriteFrame(cache->spriteFrameByName(keyname));

	for (int i = 1; i < 3; i++)
	{
		sprintf(keyname,"%s%d.png","BoyRun",i);  
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

void Person::setAttachedAction(cocos2d::SpriteFrameCache* cache)
{
	char keyname[100];
	auto animation = Animation::create();

	//sprintf(keyname,"%s.png","BoyNormal1");
	//animation->addSpriteFrame(cache->spriteFrameByName(keyname));

	sprintf(keyname,"%s.png","BoyFire");  
    animation->addSpriteFrame(cache->spriteFrameByName(keyname));  

	animation->setDelayPerUnit(0.5f);
	animation->setRestoreOriginalFrame(true);
	fireAction = Animate::create(animation);

	//moveAction = RepeatForever::create(Sequence::create(action, NULL));
}
	
Animate* Person::getAttachedActon()
{
	return attachedAction;
}

void Person::setJumpAction(cocos2d::SpriteFrameCache* cache)
{

}

Animate* Person::getJumpAction()
{
	return jumpAction;
}

void Person::setFireAction(cocos2d::SpriteFrameCache* cache)
{

}

Animate* Person::getFireAction()
{
	return fireAction;
}