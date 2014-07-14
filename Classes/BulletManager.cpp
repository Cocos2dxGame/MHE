#include "BulletManager.h"

USING_NS_CC;

BulletManager::BulletManager()
{
}

BulletManager::~BulletManager()
{
	clean();
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
		pBullet->update(m_g, deltaTime);
	}
}

void BulletManager::shoot(bulletType type, Point pos, Vec2 velocity)
{
	Bullet* pBullet = Bullet::create(type, pos, velocity, this);
	m_layer->addChild(pBullet, 0);
	m_BulletVector.pushBack(pBullet);
}

void BulletManager::clean()
{
	for( Bullet* pBullet : m_BulletVector )
	{
		pBullet->removeBullet();
	}

	m_BulletVector.clear();
}

cocos2d::Vector<Bullet*>* BulletManager::getBulletVector()
{
	return &m_BulletVector;
}

cocos2d::Layer* BulletManager::getLayer()
{
	return m_layer;
}