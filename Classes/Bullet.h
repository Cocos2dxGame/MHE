#pragma once

#include "cocos2d.h"

enum bulletType{ normalBullet,  };

class Bullet: public cocos2d::Sprite
{
public:
	Bullet();
	static Bullet* create();

private:
	
	
};
