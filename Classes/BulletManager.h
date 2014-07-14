#pragma once

#include "cocos2d.h"
#include "Bullet.h"

class BulletManager
{
public:
	BulletManager();
	~BulletManager();

	static BulletManager* create(cocos2d::Layer* curLayer, cocos2d::Vec2 g); /* init bullet manager */
	void update(float deltaTime);
	void shoot(bulletType type, cocos2d::Point pos, cocos2d::Vec2 velocity);
	cocos2d::Vector<Bullet*>* getBulletVector();
	cocos2d::Layer* getLayer();

	void clean();

private:

	cocos2d::Layer*				m_layer;
	cocos2d::Vector<Bullet*>	m_BulletVector;
	cocos2d::Vec2				m_g;
};
