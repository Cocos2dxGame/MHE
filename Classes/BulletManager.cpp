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
		pBullet->move(m_g, deltaTime);
	}
}

void BulletManager::shoot(bulletType type, Point pos, Vec2 velocity)
{
	Bullet* pBullet = Bullet::create(type, pos, velocity);
	m_layer->addChild(pBullet, 0);
	m_BulletVector.pushBack(pBullet);
}

void BulletManager::deleteBullet(Bullet* pBullet)
{
	Vector<Bullet*>::iterator iter;
	iter = m_BulletVector.find(pBullet);
	pBullet->release();
	m_BulletVector.erase(iter);
	m_layer->removeChild(pBullet);
}

void BulletManager::clean()
{
	for( Bullet* pBullet : m_BulletVector )
	{
		m_layer->removeChild(pBullet);
		pBullet->release();
	}
	m_BulletVector.clear();
}

Vector<Bullet*> BulletManager::getBulletVector()
{
	return m_BulletVector;
}