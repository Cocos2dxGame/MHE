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
		//����HP
		if(getHP()-10 > 0)
			setHP(getHP()-10);
		else
			setHP(0);

		//����SP
		if(getSP() + 20 < getTotalSP())
			setSP(getSP()+20);
		else
			setSP(getTotalSP());

		//����
		if(changeState(Attacked_Action))
			runAction(_attackedAction);
		break;

	case SpecialBullet:
		//����HP
		if(getHP()-20 > 0)
			setHP(getHP()-20);
		else
			setHP(0);

		//����SP
		if(getSP() + 20 < getTotalSP())
			setSP(getSP()+20);
		else
			setSP(getTotalSP());

		//����
		if(changeState(Attacked_Action))
			runAction(_attackedAction);
		break;
	case StunBullet:
		//����HP
		if(getHP()-30 > 0)
			setHP(getHP()-30);
		else
			setHP(0);

		//����SP
		if(getSP() + 20 < getTotalSP())
			setSP(getSP() + 20);
		else
			setSP(getTotalSP());

		//����
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
	// �Ѿ�ʤ�����Ͳ����ٳ������������ˣ�
	if (_currentState == Vectory_Action) 
		return false;

	// �Ѿ�ʧ�ܣ��Ͳ����ٳ������������ˣ�
	if(_currentState == Fail_Action)
		return false;

	// ����ס���Ͳ����ٳ������������ˣ�ʱ�䵽������״̬���Դ���
	if(state != Normal_Action)
		if (_currentState == Frozen_Action)
			return false;
		
	//������Ծ״̬ʱ����ִ�ж���
	if(_currentState == Jump_Action)
		return false;

	// �Ѿ�����Ҫ�ı��״̬����û��Ҫ�ڸı��ˣ�
	if (_currentState == state) 
	{
		return false;
	}

	// �ı䶯��֮ǰ����ֹͣ���ж���
	this->stopAllActions();

	_currentState = state;
	return true;
}