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
	newManager->m_BulletArray = Array::create();
	newManager->m_BulletArray->retain();
	return newManager;
}

void BulletManager::update(float deltaTime)
{
	Object *pObj;
	CCARRAY_FOREACH(m_BulletArray, pObj)
	{
		((Bullet*)pObj)->move(m_g, deltaTime);
	}
}

void BulletManager::shoot(bulletType type, Point pos, Vec2 velocity)
{
	auto pBullet = Bullet::create(type, pos, velocity);
	//auto pBullet = Sprite::create("ball.png");
	m_layer->addChild(pBullet, 0);
	m_BulletArray->addObject(pBullet);
}

void BulletManager::deleteBullet(Bullet* pBullet)
{

}

void BulletManager::clean()
{

}