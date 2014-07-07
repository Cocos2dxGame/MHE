#ifndef __BULLET_H__
#define __BULLET_H__

#include "cocos2d.h"

class Bullet: public cocos2d::Sprite
{
public:
	Bullet();
	void create(int power, float angle);

private:
	int coolDown;
	int damage;
	char* type;
	int speed;
	int quality;
	int speedPerPower;
};

#endif