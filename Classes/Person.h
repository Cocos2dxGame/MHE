#ifndef __PERSON_H__
#define __PERSON_H__

#include "cocos2d.h"

typedef enum {
    Normal_Action = 0,
    Move_Action,
	Jump_Action,
	Fire_Action,
    Attacked_Action,
    Vectory_Action,
	Fail_Action,
} ActionState;

class Person: public cocos2d::Sprite
{
public:
	Person();
	~Person();

	void normalAction();
	void fireAction();
	void attackedAction();
	void moveAction();
	void jumpAction();
	void victoryAction();
	void failAction();

	 // 定义每个状态动作的get/set方法
    CC_SYNTHESIZE_RETAIN(cocos2d::Action*, _normalAction, NormalAction);
	CC_SYNTHESIZE_RETAIN(cocos2d::Action*, _attackedAction, AttackedAction);
    CC_SYNTHESIZE_RETAIN(cocos2d::Action*, _fireAction, FireAction);
    CC_SYNTHESIZE_RETAIN(cocos2d::Action*, _moveAction, MoveAction);
	CC_SYNTHESIZE_RETAIN(cocos2d::Action*, _jumpAction, JumpAction);
    CC_SYNTHESIZE_RETAIN(cocos2d::Action*, _victoryAction, VictoryAction);


	//设置血条、怒气条
	CC_SYNTHESIZE(unsigned int, _hp, HP); // 生命值
    CC_SYNTHESIZE(unsigned int, _sp, SP); // 怒气值

protected:
	cocos2d::Animation* createAnimation(const char* fmt, int count, float fps);

	int totalHP;
	int HP;
	int SP;
	char roleName[100];

	cocos2d::SpriteFrameCache* cache;

private:
	bool changeState(ActionState state);
	ActionState _currentState;

};

#endif