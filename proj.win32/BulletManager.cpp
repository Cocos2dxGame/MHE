#include "BulletManager.h"

BulletManager::BulletManager()
{
}

BulletManager::~BulletManager()
{
}

BulletManager* BulletManager::create(float g)
{
	BulletManager* newManager = new BulletManager();
	newManager->m_g = g;
	return newManager;
}

void BulletManager::update(float deltaTime)
{
	
}

void BulletManager::shoot(cocos2d::Point, float, float)
{

}

void BulletManager::deleteBullet(Bullet*)
{

}

void BulletManager::clean()
{

}