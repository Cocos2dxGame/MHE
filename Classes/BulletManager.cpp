#include "BulletManager.h"

USING_NS_CC;

BulletManager::BulletManager()
{
}

BulletManager::~BulletManager()
{
	clean();
}

BulletManager* BulletManager::create(GameSceneType gamescenetype, Layer* curLayer, Vector<Sprite*>* pSpriteVector, Vec2 g)
{
	BulletManager* newManager = new BulletManager();
	newManager->m_g = g;
	newManager->m_layer = curLayer;
	newManager->m_pSpriteVector = pSpriteVector;
	return newManager;
}

void BulletManager::update(float deltaTime)
{
	Vector<Bullet*>::iterator iter;
	for( Bullet* pBullet : m_BulletVector )
	{
		pBullet->update(m_g, deltaTime);
	}

	for( Bullet* pBullet : m_BulletDeleteVector )
	{
		iter = m_BulletVector.find(pBullet);
		if(iter != m_BulletVector.end())
		{
			m_layer->removeChild(*iter);
			m_BulletVector.erase(iter);
		}
	}
	m_BulletDeleteVector.clear();
}

void BulletManager::shoot(bulletType type, Point pos, Vec2 velocity)
{
	Bullet* pBullet = Bullet::create(type, pos, velocity, this);
	m_layer->addChild(pBullet, 0);
	m_BulletVector.pushBack(pBullet);
}

void BulletManager::clean()
{
}

Vector<Bullet*>* BulletManager::getBulletVector()
{
	return &m_BulletVector;
}

cocos2d::Layer* BulletManager::getLayer()
{
	return m_layer;
}

void BulletManager::deleteBullet(Bullet* pBullet)
{
	m_BulletDeleteVector.pushBack(pBullet);
}

cocos2d::Vector<cocos2d::Sprite*>* BulletManager::getSpriteVector()
{
	return m_pSpriteVector;
}