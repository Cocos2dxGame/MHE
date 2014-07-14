#pragma once

#include "cocos2d.h"

class BulletManager;

typedef enum {
	NormalBullet,
	SpecialBullet,
	StunBullet
}bulletType;

class Bullet: public cocos2d::Sprite
{
public:
	Bullet();
	~Bullet();
	static Bullet* create(bulletType type, cocos2d::Point pos, cocos2d::Vec2 velocity, BulletManager* pBulletManager);
	void update(cocos2d::Vec2 acceleration, float deltaTime);

	bulletType getType();
	void removeBullet();

private:

	bulletType m_type;
	cocos2d::Vec2 m_velocity;
	BulletManager* m_pBulletManager;
};
