#ifndef __BULLET_H__
#define __BULLET_H__

#include "cocos2d.h"

class Bullet: public cocos2d::Sprite
{
public:
	Bullet();
	static Bullet* create();
	void setVelocity(cocos2d::Vec2 velocity);
	cocos2d::Vec2 getVelocity();

	void setAngle(float angle);
	float getAngle();

private:
	int coolDown;
	int damage;
	char* type;
	cocos2d::Vec2 velocity;
	int quality;
	int speedPerPower;
};

#endif