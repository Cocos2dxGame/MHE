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
	Person* person = new Person();
	if(person && person->initWithFile("picgirl.png", Rect(0,0,32,48)))
	{
		person->autorelease();
		return person;
	}
	return NULL;
}

void Person::setMoveToLeft()
{
	moveRight = false;
}

void Person::setMoveToRight()
{
	moveRight = true;
}

RepeatForever* Person::freeAction()
{
	Texture2D* texture = TextureCache::sharedTextureCache()->addImage("picgirl.png");

	auto animation = Animation::create();
	for (int i = 0; i < 1; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			SpriteFrame* frame = SpriteFrame::createWithTexture(texture, Rect(32*j,48*i,32,48));
			animation->addSpriteFrame(frame);
		}
	}

	animation->setDelayPerUnit(0.2f);
	animation->setRestoreOriginalFrame(true);
	auto action = Animate::create(animation);

	repeatAction = RepeatForever::create(Sequence::create(action, NULL));

	//_sprite->runAction(Sequence::create(action, action->reverse(), NULL));
	return repeatAction;
}

RepeatForever* Person::moveAction()
{
	Texture2D* texture = TextureCache::sharedTextureCache()->addImage("picgirl.png");

	auto animation = Animation::create();

	int selectRow = (moveRight==true)?2:1; 
	
	for (int j = 0; j < 4; j++)
	{
		SpriteFrame* frame = SpriteFrame::createWithTexture(texture, Rect(32*j,48*selectRow,32,48));
		animation->addSpriteFrame(frame);
	}

	animation->setDelayPerUnit(0.2f);
	animation->setRestoreOriginalFrame(true);
	auto action = Animate::create(animation);

	repeatAction = RepeatForever::create(Sequence::create(action, NULL));

	//_sprite->runAction(Sequence::create(action, action->reverse(), NULL));
	return repeatAction;
}