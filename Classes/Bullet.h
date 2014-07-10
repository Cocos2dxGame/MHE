#pragma once

#include "cocos2d.h"

enum bulletType{ NormalBullet, SpecialBullet, StunBullet };

class Bullet: public cocos2d::Sprite
{
public:
	Bullet();
	static Bullet* create(bulletType type, cocos2d::Point pos, cocos2d::Vec2 velocity);
	void move (cocos2d::Vec2 acceleration, float deltaTime);

private:
	
	bulletType m_type;
	cocos2d::Vec2 m_velocity;
};
