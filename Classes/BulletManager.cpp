#include "BulletManager.h"

USING_NS_CC;

BulletManager::BulletManager()
{
}

BulletManager::~BulletManager()
{
}

BulletManager* BulletManager::create(Layer* curLayer, Vec2 g)
{
	BulletManager* newManager = new BulletManager();
	newManager->m_g = g;
	newManager->m_layer = curLayer;
	return newManager;
}

void BulletManager::update(float deltaTime)
{
	for( Bullet* pBullet : m_BulletVector )
	{
		pBullet->move(m_g, deltaTime);
	}
}

void BulletManager::shoot(bulletType type, Point pos, Vec2 velocity)
{
	Bullet* pBullet = Bullet::create(type, pos, velocity);
	//auto pBullet = Sprite::create("ball.png");
	m_layer->addChild(pBullet, 0);
	m_BulletVector.pushBack(pBullet);
	CCLOG("%d", m_BulletVector.size());
}

void BulletManager::deleteBullet(Bullet* pBullet)
{

}

void BulletManager::clean()
{

}