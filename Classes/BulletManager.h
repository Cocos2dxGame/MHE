#pragma once

#include "cocos2d.h"
#include "Bullet.h"
#include <list>

class BulletManager
{
public:
	BulletManager();
	~BulletManager();

	static BulletManager* create(cocos2d::Layer* curLayer, cocos2d::Vector<cocos2d::Sprite*>* pSpriteVector, cocos2d::Vec2 g);	/* init bullet manager */
	void update(float deltaTime);												/* return true delete bullet */
	void shoot(bulletType type, cocos2d::Point pos, cocos2d::Vec2 velocity);
	std::list<Bullet*>* getBulletList();
	cocos2d::Layer* getLayer();

	void clean();

private:

	cocos2d::Layer*			m_layer;
	std::list<Bullet*>		m_BulletList;
	cocos2d::Vec2			m_g;
};
