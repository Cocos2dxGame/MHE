#ifndef __PERSON_H__
#define __PERSON_H__

#include "cocos2d.h"

class Person: public cocos2d::Sprite
{
public:
	Person();
	static Person* create();
	
	void setMoveToLeft();
	void setMoveToRight();

	cocos2d::RepeatForever* freeAction();
	void hurtAction();
	void jump();
	cocos2d::RepeatForever* moveAction();

private:
	int HP;
	int Rage;
	int jumpSpeed;
	int speed;
	bool moveRight;
	cocos2d::RepeatForever* repeatAction;
};

#endif