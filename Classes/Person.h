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

	static Person* create();

	void setMoveToLeft();
	void setMoveToRight();

	void setAction(cocos2d::SpriteFrameCache* cache);

	void setNormalAction(cocos2d::SpriteFrameCache* cache);
	cocos2d::Action* getNormalAction();
	void normalAction();

	void setMoveAction(cocos2d::SpriteFrameCache* cache);
	cocos2d::Action* getMoveAction();

	void setAttackedAction(cocos2d::SpriteFrameCache* cache);
	cocos2d::Action* getAttackedAction();
	void attackedAction();

	void setJumpAction(cocos2d::SpriteFrameCache* cache);
	cocos2d::Action* getJumpAction();
	void jumpAction();

	void setFireAction(cocos2d::SpriteFrameCache* cache);
	cocos2d::Action* getFireAction();
	void fireAction();

	//设置血条、怒气条
	void increaseHP(int hp);
	void decreaseHP(int hp);
	int getTotalHP();
	int getCurrentHP();
	
	//设置怒气条
	void increaseSP(int sp);
	void descreaseSP(int sp);
	int getTotalSP();
	int getCurrentSP();
	
	cocos2d::Rect getRect();
protected:
	int totalHP;
	int HP;
	int SP;
	int jumpSpeed;
	int speed;
	bool moveRight;
	char roleName[100];
	//cocos2d::String* roleName;

	cocos2d::CallFunc *callbackNormal;
	cocos2d::SpriteFrameCache* cache;

	cocos2d::Action* _normalAction;
	cocos2d::Action* _attackedAction;
	cocos2d::Action* _jumpAction;
	cocos2d::Action* _fireAction;

	cocos2d::Action* _moveLeftAction;
	cocos2d::Action* _moveRightAction;
	cocos2d::Action* _moveAction;
private:
	bool changeState(ActionState state);
	ActionState _currentState;

};

#endif