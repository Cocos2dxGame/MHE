#ifndef __PERSON_H__
#define __PERSON_H__

#include "cocos2d.h"
#include "Bullet.h"

typedef enum {
    Normal_Action = 0,
    Move_Action,
	Jump_Action,
	Fire_Action,
    Attacked_Action,
    Vectory_Action,
	Fail_Action,
	Frozen_Action,
} ActionState;

class Person: public cocos2d::Sprite
{
public:
	Person();
	~Person();

	void normalAction();
	void fireAction();
	void attackedAction();
	void frozen();
	void moveAction();
	void jumpAction();
	void victoryAction();
	void failAction();
	void jumpActionEnd();
	void attacked(bulletType type);

	 // ����ÿ��״̬������get/set����
    CC_SYNTHESIZE_RETAIN(cocos2d::Action*, _normalAction, NormalAction);
	CC_SYNTHESIZE_RETAIN(cocos2d::Action*, _attackedAction, AttackedAction);
	CC_SYNTHESIZE(cocos2d::Action*, _frozenAction, FrozenAction);
    CC_SYNTHESIZE_RETAIN(cocos2d::Action*, _fireAction, FireAction);
    CC_SYNTHESIZE_RETAIN(cocos2d::Action*, _moveAction, MoveAction);
	CC_SYNTHESIZE_RETAIN(cocos2d::Action*, _jumpAction, JumpAction);
    CC_SYNTHESIZE(cocos2d::Action*, _victoryAction, VictoryAction);
	CC_SYNTHESIZE(cocos2d::Action*, _failAction, FailAction);

	// ����ĵ�ǰ״̬
    CC_SYNTHESIZE(ActionState, _currentState, ActionState);

	//����Ѫ����ŭ����
	CC_SYNTHESIZE(int, _hp, HP); // ����ֵ
    CC_SYNTHESIZE(int, _sp, SP); // ŭ��ֵ

	CC_SYNTHESIZE(int, _totalHp, TotalHP); // ����ֵ
    CC_SYNTHESIZE(int, _totalSp, TotalSP); // ŭ��ֵ

protected:
	cocos2d::Animation* createAnimation(const char* fmt, int count, float fps);

	char roleName[100];
	cocos2d::SpriteFrameCache* cache;

private:
	bool changeState(ActionState state);
	bool isJumping;

};

#endif