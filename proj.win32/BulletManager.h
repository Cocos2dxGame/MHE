#pragma once

#include "cocos2d.h"
#include "Bullet.h"


class BulletManager
{
public:
	BulletManager();
	~BulletManager();

	static BulletManager* create(float);
	void update(float);
	void shoot(cocos2d::Point, float, float);
	void deleteBullet(Bullet*);
	void clean();

private:

	float m_g;
	cocos2d::Array m_PlayerBulletArray;
	cocos2d::Array m_EnemyBulletArray;
	
};
