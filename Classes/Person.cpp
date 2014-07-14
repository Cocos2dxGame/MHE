#include "Person.h"

USING_NS_CC;

Person::Person()
{
	totalHP = 200;
	HP = 200;
	SP = 200;
	speed = 10;
	jumpSpeed  = 10;
	moveRight = true;
	strcpy(roleName, "Role2");
	
	char plistFileName[100];
	sprintf(plistFileName,"character/%s.plist", roleName);  
	cache = SpriteFrameCache::sharedSpriteFrameCache();
	//cache->addSpriteFramesWithFile(plistFileName);
	callbackNormal = CallFunc::create(std::bind(&Person::normalAction, this));
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

	animation->setDelayPerUnit(0.4f);
	//animation->setRestoreOriginalFrame(true);
	auto action = Animate::create(animation);

	_normalAction = RepeatForever::create(Sequence::create(action, NULL));
}
Action* Person::getNormalAction()
{
	return _normalAction;
}

void Person::normalAction()
{
	if(changeState(Normal_Action))
		runAction(_normalAction);
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

	animation->setDelayPerUnit(1.0f);
	animation->setRestoreOriginalFrame(true);
	auto action = Animate::create(animation);
	_moveLeftAction = Animate::create(animation);
	_moveRightAction = _moveLeftAction->reverse();

	_moveAction = RepeatForever::create(Sequence::create(action, NULL));
}

Action* Person::getMoveAction()
{
	return _moveAction;
}

void Person::setAttackedAction(cocos2d::SpriteFrameCache* cache)
{
	CallFunc *callbackNormal = CallFunc::create(std::bind(&Person::normalAction, this));

	char keyname[100];
	auto animation = Animation::create();
	for (int i = 1; i < 3; i++)
	{
		sprintf(keyname, "%sAttacked%d.png", roleName, i);  
        animation->addSpriteFrame(cache->spriteFrameByName(keyname));  
	}

	animation->setDelayPerUnit(0.1f);
	animation->setRestoreOriginalFrame(true);
	_attackedAction = Sequence::create(Animate::create(animation), callbackNormal, NULL);
}
	
Action* Person::getAttackedAction()
{
	return _attackedAction;
}

void Person::attackedAction()
{
	if(changeState(Attacked_Action))
		runAction(_attackedAction);
}

void Person::setJumpAction(cocos2d::SpriteFrameCache* cache)
{
	char keyname[100];
	auto animation = Animation::create();
	sprintf(keyname, "%sJump.png", roleName);
    animation->addSpriteFrame(cache->spriteFrameByName(keyname)); 

	animation->setDelayPerUnit(0.1f);
	animation->setRestoreOriginalFrame(true);
	_jumpAction = Animate::create(animation);

}

Action* Person::getJumpAction()
{
	return _jumpAction;
}

void Person::jumpAction()
{
	if(changeState(Jump_Action))
		runAction(_jumpAction);
}

void Person::setFireAction(cocos2d::SpriteFrameCache* cache)
{
	char keyname[100];
	auto animation = Animation::create();

	sprintf(keyname,"%sNormal1.png", roleName);
	animation->addSpriteFrame(cache->spriteFrameByName(keyname));

	sprintf(keyname, "%sFire.png", roleName);
    animation->addSpriteFrame(cache->spriteFrameByName(keyname));

	sprintf(keyname,"%sNormal1.png", roleName);
	animation->addSpriteFrame(cache->spriteFrameByName(keyname));

	animation->setDelayPerUnit(0.5f);

	_fireAction = Sequence::create(Animate::create(animation), callbackNormal, NULL);
}

Action* Person::getFireAction()
{
	return _fireAction;
}

void Person::fireAction()
{
	if(changeState(Fire_Action))
		runAction(_fireAction);
}

bool Person::changeState(ActionState state)
{
	// 已经胜利，就不能再出发其他动作了！
    if (_currentState == Vectory_Action) {
        return false;
    }
    
	if(_currentState == Fail_Action)
	{
		return false;
	}

    // 已经处于要改变的状态，就没必要在改变了！
    if (_currentState == state) {
        return false;
    }

    // 改变动作之前，先停止所有动作
    this->stopAllActions();

    _currentState = state;
    return true;
}

Rect Person::getRect()
{
	auto s = getContentSize();
	return Rect(getPosition().x-s.width/2,getPosition().y-s.height/2, s.width, s.height);
}

void Person::increaseHP(int hp)
{
	HP += hp;
	if(HP > totalHP)
	{
		HP = totalHP;
	}
}

void Person::decreaseHP(int hp)
{
	HP -= hp;
	if(HP<0)
	{
		HP = 0;
	}
}

int Person::getTotalHP()
{
	return totalHP;
}

int Person::getCurrentHP()
{
	return HP;
}

void Person::increaseSP(int sp)
{
	SP += sp;
	if(SP > 100)
	{
		SP = 100;
	}
}

void Person::descreaseSP(int sp)
{
	SP -= sp;
	if(SP<0)
	{
		SP = 0;
	}
}

int Person::getTotalSP()
{
	return 100;
}

int Person::getCurrentSP()
{
	return SP;
}