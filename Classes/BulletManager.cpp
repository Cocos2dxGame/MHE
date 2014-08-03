#include "BulletManager.h"

USING_NS_CC;

BulletManager::BulletManager()
{
	m_normalAnimation = NULL;
	m_specialAnimation = NULL;
	m_stunAnimation = NULL;
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
	newManager->m_propManager = PropManager::create(newManager);

	// create action
	auto cache = SpriteFrameCache::sharedSpriteFrameCache();
	Animation* normalAnimation = NULL;
	Animation* specialAnimation = NULL;
	Animation* stunAnimation = NULL;

	switch (gamescenetype)
	{
	case GameScene1:
		cache->addSpriteFramesWithFile("bullet/blef_003.plist");
		normalAnimation = Animation::create();
		for(int i = 0; i < 7; i++)
		{
			const char* png = String::createWithFormat("%d.png", i)->getCString();
			normalAnimation->addSpriteFrame(SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(png));
		}
		normalAnimation->setDelayPerUnit(0.07);
		newManager->setNormalAnimation(normalAnimation);
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
		newManager->setNormalAnimation(normalAnimation);
		
		break;
	case GameScene3:
		cache->addSpriteFramesWithFile("bullet/blef_003.plist");
		normalAnimation = Animation::create();
		for(int i = 0; i < 7; i++)
		{
			const char* png = String::createWithFormat("%d.png", i)->getCString();
			normalAnimation->addSpriteFrame(SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(png));
		}
		normalAnimation->setDelayPerUnit(0.07);
		newManager->setNormalAnimation(normalAnimation);
		break;
	case GameScene4:
		cache->addSpriteFramesWithFile("bullet/blef_003.plist");
		normalAnimation = Animation::create();
		for(int i = 0; i < 7; i++)
		{
			const char* png = String::createWithFormat("%d.png", i)->getCString();
			normalAnimation->addSpriteFrame(SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(png));
		}
		normalAnimation->setDelayPerUnit(0.07);
		newManager->setNormalAnimation(normalAnimation);
		break;
	case GameScene5:
		cache->addSpriteFramesWithFile("bullet/blef_003.plist");
		normalAnimation = Animation::create();
		for(int i = 0; i < 7; i++)
		{
			const char* png = String::createWithFormat("%d.png", i)->getCString();
			normalAnimation->addSpriteFrame(SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(png));
		}
		normalAnimation->setDelayPerUnit(0.07);
		newManager->setNormalAnimation(normalAnimation);
		break;
	default:
		break;
	}

	return newManager;
}

void BulletManager::update(float deltaTime)
{
	m_propManager->update(deltaTime);

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
			m_BulletVector.erase(iter);
		}
	}
	m_BulletDeleteVector.clear();
}

void BulletManager::shoot(bulletType type, Owner owner, Point pos, Vec2 velocity)
{
	Bullet* pBullet = Bullet::createBullet(type, pos, velocity, owner, this);
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
	if(m_BulletDeleteVector.find(pBullet)==m_BulletDeleteVector.end())
	{
		m_BulletDeleteVector.pushBack(pBullet);
	}
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
		if(m_normalAnimation)
		{
			Action *action = Sequence::create(
				Animate::create(m_normalAnimation),
				CallFuncN::create([&](Node* sender){
					sender->getParent()->removeChild(sender);
			}),
			NULL);
			pBullet->runAction(action);
		}
		break;
	case SpecialBullet:
		if(m_normalAnimation)
		{
			Action *action = Sequence::create(
				Animate::create(m_normalAnimation),
				CallFuncN::create([&](Node* sender){
					sender->getParent()->removeChild(sender);
			}),
				NULL);
			pBullet->runAction(action);
		}
		break;
	case StunBullet:
		if(m_normalAnimation)
		{
			Action *action = Sequence::create(
				Animate::create(m_normalAnimation),
				CallFuncN::create([&](Node* sender){
					sender->getParent()->removeChild(sender);
			}),
				NULL);
			pBullet->runAction(action);
		}
		break;
	default:
		break;
	}
}

PropManager* BulletManager::getPropManager()
{
	return m_propManager;
}