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

	void setAction(cocos2d::SpriteFrameCache* cache);

	void setNormalAction(cocos2d::SpriteFrameCache* cache);
	cocos2d::RepeatForever* getNormalAction();

	void setMoveAction(cocos2d::SpriteFrameCache* cache);
	cocos2d::RepeatForever* getMoveAction();

	void setAttachedAction(cocos2d::SpriteFrameCache* cache);
	cocos2d::Animate* getAttachedActon();

	void setJumpAction(cocos2d::SpriteFrameCache* cache);
	cocos2d::Animate* getJumpAction();

	void setFireAction(cocos2d::SpriteFrameCache* cache);
	cocos2d::Animate* getFireAction();


private:
	int HP;
	int Rage;
	int jumpSpeed;
	int speed;
	bool moveRight;
	cocos2d::SpriteFrameCache* cache;
	cocos2d::RepeatForever* normalAction;
	cocos2d::Animate* attachedAction;
	cocos2d::Animate* jumpAction;
	cocos2d::Animate* fireAction;
	cocos2d::RepeatForever* moveAction;

};

#endif