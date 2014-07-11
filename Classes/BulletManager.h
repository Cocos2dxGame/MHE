#pragma once

#include "cocos2d.h"
#include "Bullet.h"

class BulletManager
{
public:
	BulletManager();
	~BulletManager();

	static BulletManager* create(cocos2d::Layer* curLayer, cocos2d::Vec2 g);
	void update(float deltaTime);
	void shoot(bulletType type, cocos2d::Point pos, cocos2d::Vec2 velocity);
	void deleteBullet(Bullet* pBullet);
	void clean();
	cocos2d::Vector<Bullet*> getBulletVector();

private:

	cocos2d::Layer* m_layer;
	cocos2d::Vec2 m_g;
	cocos2d::Vector<Bullet*> m_BulletVector;
};
