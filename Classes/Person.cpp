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
		auto personBody = PhysicsBody::createBox(person->getContentSize());
		person->setPhysicsBody(personBody);
		person->getPhysicsBody()->addMass(20000.0f);
		person->setAction(cache);
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

void Person::setAttackedAction(cocos2d::SpriteFrameCache* cache)
{
	char keyname[100];
	auto animation = Animation::create();
	for (int i = 1; i < 3; i++)
	{
		sprintf(keyname,"%s%d.png","BoyAttacked",i);  
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
	sprintf(keyname,"%s.png","BoyNormal1");  
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

	sprintf(keyname,"%s.png","BoyFire");  
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