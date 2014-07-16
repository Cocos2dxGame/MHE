#include "BulletManager.h"

USING_NS_CC;

BulletManager::BulletManager()
{
}

BulletManager::~BulletManager()
{
	clean();
}

BulletManager* BulletManager::create(Layer* curLayer, Vector<Sprite*>* pSpriteVector, Vec2 g)
{
	BulletManager* newManager = new BulletManager();
	newManager->m_g = g;
	newManager->m_layer = curLayer;
	return newManager;
}

void BulletManager::update(float deltaTime)
{
	std::list<Bullet*>::iterator iter;
	for( iter=m_BulletList.begin(); iter!=m_BulletList.end(); )
	{
		if((*iter)->update(m_g, deltaTime))
		{
			iter = m_BulletList.erase(iter);
		}
		else
		{
			if(iter!=m_BulletList.end())
			{
				iter++;
			}
		}
	}
}

void BulletManager::shoot(bulletType type, Point pos, Vec2 velocity)
{
	Bullet* pBullet = Bullet::create(type, pos, velocity, this);
	m_layer->addChild(pBullet, 0);
	m_BulletList.push_back(pBullet);
}

void BulletManager::clean()
{
	for( Bullet* pBullet : m_BulletList )
	{
		m_layer->removeChild(pBullet);
	}

	m_BulletList.clear();
}

std::list<Bullet*>* BulletManager::getBulletList()
{
	return &m_BulletList;
}

cocos2d::Layer* BulletManager::getLayer()
{
	return m_layer;
}