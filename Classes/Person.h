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
	cocos2d::RepeatForever* getNormalAction();

	void setMoveAction(cocos2d::SpriteFrameCache* cache);
	cocos2d::RepeatForever* getMoveAction();

	void setAttackedAction(cocos2d::SpriteFrameCache* cache);
	cocos2d::Animate* getAttackedAction();

	void setJumpAction(cocos2d::SpriteFrameCache* cache);
	cocos2d::Animate* getJumpAction();

	void setFireAction(cocos2d::SpriteFrameCache* cache);
	cocos2d::Animate* getFireAction();

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

	cocos2d::SpriteFrameCache* cache;

	cocos2d::RepeatForever* normalAction;
	cocos2d::Animate* attackedAction;
	cocos2d::Animate* jumpAction;
	cocos2d::Animate* fireAction;

	cocos2d::Animate* moveLeftAction;
	cocos2d::Animate* moveRightAction;
	cocos2d::RepeatForever* moveAction;

};

#endif