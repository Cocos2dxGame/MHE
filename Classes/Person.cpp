#include "Person.h"

USING_NS_CC;

Person::Person()
{
	_normalAction = NULL;
	_fireAction = NULL;
	_attackedAction = NULL;
	_frozenAction = NULL;
	_moveAction = NULL;
	_jumpAction = NULL;
	_victoryAction = NULL;
	_failAction = NULL;

	isJumping =false;
	strcpy(roleName, "Role2");
	
	char plistFileName[100];
	sprintf(plistFileName,"character/%s.plist", roleName);  
	cache = SpriteFrameCache::sharedSpriteFrameCache();
}

Person::~Person()
{

}

Animation* Person::createAnimation(const char* fmt, int count, float fps)
{
	auto frames = Animation::create();

	for(int i = 1; i < count; i++)
	{
		const char* png = String::createWithFormat("%s%d.png", fmt, i)->getCString();
		frames->addSpriteFrame(cache->spriteFrameByName(png));
	}
	frames->setDelayPerUnit(1/fps);

	return frames;
}

void Person::normalAction()
{
	if(changeState(Normal_Action))
	{
		runAction(_normalAction);
	}
}

void Person::fireAction()
{
	if(changeState(Fire_Action))
	{
		runAction(_fireAction);
	}
}

void Person::attackedAction()
{
	if(changeState(Attacked_Action))
	{
		runAction(_attackedAction);
	}
}

void Person::moveAction()
{
	if(changeState(Move_Action))
	{
		runAction(_moveAction);
	}
}

void Person::jumpAction()
{
	if(changeState(Jump_Action))
	{
		runAction(_jumpAction);
	}
}

void Person::jumpActionEnd()
{
	_currentState = Normal_Action;
	runAction(_normalAction);
}

void Person::attacked(bulletType type)
{
	switch (type)
	{
	case NormalBullet:
		//设置HP
		if(getHP()-10 > 0)
			setHP(getHP()-10);
		else
			setHP(0);

		//设置SP
		if(getSP() + 20 < getTotalSP())
			setSP(getSP()+20);
		else
			setSP(getTotalSP());

		//动作
		if(changeState(Attacked_Action))
			runAction(_attackedAction);
		break;

	case SpecialBullet:
		//设置HP
		if(getHP()-20 > 0)
			setHP(getHP()-20);
		else
			setHP(0);

		//设置SP
		if(getSP() + 20 < getTotalSP())
			setSP(getSP()+20);
		else
			setSP(getTotalSP());

		//动作
		if(changeState(Attacked_Action))
			runAction(_attackedAction);
		break;
	case StunBullet:
		//设置HP
		if(getHP()-30 > 0)
			setHP(getHP()-30);
		else
			setHP(0);

		//设置SP
		if(getSP() + 20 < getTotalSP())
			setSP(getSP() + 20);
		else
			setSP(getTotalSP());

		//动作
		if(changeState(Frozen_Action))
			runAction(_frozenAction);
		break;
	default:
		break;
	}
}

void Person::frozenAction()
{
	if(changeState(Frozen_Action))
		runAction(_frozenAction);
}

void Person::failAction()
{
	if(changeState(Fail_Action))
		runAction(_failAction);
}

void Person::getProp()
{
	if(getHP()+10 < getTotalHP())
			setHP(getHP()+10);
		else
			setHP(getTotalHP());
}

bool Person::changeState(ActionState state)
{
	// 已经胜利，就不能再出发其他动作了！
	if (_currentState == Vectory_Action) 
		return false;

	// 已经失败，就不能再出发其他动作了！
	if(_currentState == Fail_Action)
		return false;

	// 被冻住，就不能再出发其他动作了！时间到了正常状态可以触发
	if(state != Normal_Action)
		if (_currentState == Frozen_Action)
			return false;
		
	//处于跳跃状态时，不执行动作
	if(_currentState == Jump_Action)
		return false;

	// 已经处于要改变的状态，就没必要在改变了！
	if (_currentState == state) 
	{
		return false;
	}

	// 改变动作之前，先停止所有动作
	this->stopAllActions();

	_currentState = state;
	return true;
}