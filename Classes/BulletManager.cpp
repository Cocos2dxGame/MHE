#include "BulletManager.h"

USING_NS_CC;

BulletManager::BulletManager()
{
	m_normalAction = NULL;
	m_specialAction = NULL;
	m_stunAction = NULL;
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
	newManager->SceneType = gamescenetype;

	// create action
	auto cache = SpriteFrameCache::sharedSpriteFrameCache();
	Animation* normalAnimation = NULL;
	Animation* specialAnimation = NULL;
	Animation* stunAnimation = NULL;

	switch (gamescenetype)
	{
	case GameScene1:
		break;
	case GameScene2:
		cache->addSpriteFramesWithFile("bullet/blef_003.plist");
		normalAnimation = Animation::create();
		for(int i = 0; i < 7; i++)
		{
			const char* png = String::createWithFormat("%d.png", i)->getCString();
			normalAnimation->addSpriteFrame(SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(png));
		}
		normalAnimation->setDelayPerUnit(0.07);
		
		break;
	case GameScene3:
		break;
	case GameScene4:
		break;
	case GameScene5:
		break;
	default:
		break;
	}

	if(normalAnimation)
	{
		newManager->setNormalAction(Sequence::create(
			Animate::create(normalAnimation),
			CallFuncN::create([&](Node* sender){
				sender->getParent()->removeChild(sender);
		}),
			NULL));
	}

	if(specialAnimation)
	{
		newManager->setSpecialAction(Sequence::create(
			Animate::create(specialAnimation),
			CallFuncN::create([&](Node* sender){
				sender->getParent()->removeChild(sender);
		}),
			NULL));
	}

	if(stunAnimation)
	{
		newManager->setStunlAction(Sequence::create(
			Animate::create(stunAnimation),
			CallFuncN::create([&](Node* sender){
				sender->getParent()->removeChild(sender);
		}),
			NULL));
	}

	return newManager;
}

void BulletManager::update(float deltaTime)
{
	Vector<Bullet*>::iterator iter;
	for( Bullet* pBullet : m_BulletVector )
	{
		pBullet->update(m_g, deltaTime);
	}

	// remove bullet per second
	for( Bullet* pBullet : m_BulletDeleteVector )
	{
		iter = m_BulletVector.find(pBullet);
		if(iter != m_BulletVector.end())
		{
			// run animate
			bulletExplode(*iter);
			(*iter)->getEmitter()->setAutoRemoveOnFinish(true);
			(*iter)->getEmitter()->stopSystem();
			//m_layer->removeChild(*iter);
			m_BulletVector.erase(iter);
		}
	}
	m_BulletDeleteVector.clear();

}

void BulletManager::shoot(bulletType type, Owner owner, Point pos, Vec2 velocity)
{
	Bullet* pBullet = Bullet::createBullet(type, pos, velocity, this);
	m_layer->addChild(pBullet->getEmitter(), 1);
	m_layer->addChild(pBullet, 1);
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

void BulletManager::bulletExplode(Bullet* pBullet)
{
	switch (pBullet->getType())
	{
	case NormalBullet:
		if(m_normalAction)
		{
			pBullet->runAction(m_normalAction);
		}
		break;
	case SpecialBullet:

		break;
	case StunBullet:

		break;
	default:
		break;
	}
}