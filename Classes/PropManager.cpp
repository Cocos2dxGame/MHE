#include "cocos2d.h"
#include "PropManager.h"
#include "BulletManager.h"

USING_NS_CC;

float getRandom(float basic, float variance)
{
	return basic+(0.5-CCRANDOM_0_1())*variance*2;
}


PropManager::PropManager(void)
{
}


PropManager::~PropManager(void)
{
}

PropManager* PropManager::create(BulletManager* pBulletManger)
{
	PropManager* newManager = new PropManager;
	newManager->m_bulletManager = pBulletManger;

	return newManager;
}

void PropManager::update(float deltaTime)
{
	float time = 15.0f;
	float timeVariance = 5.0f;
	float speed = 20.0f;
	float speedVariance = 5.0f;

	static float curTime = 0;
	static float nextTime = getRandom(time, timeVariance);

	if(curTime < nextTime)
	{
		curTime+=deltaTime;
	}
	else
	{
		// set time
		curTime = 0;
		nextTime = getRandom(time, timeVariance);

		// add prop
		float curSpeed = getRandom(speed, speedVariance);
		Prop* newProp = Prop::createProp(m_bulletManager->SceneType, type1);
		float x = CCRANDOM_0_1()*(Director::getInstance()->getVisibleSize().width);
		newProp->setPosition(x, Director::getInstance()->getVisibleSize().height);
		m_bulletManager->getLayer()->addChild(newProp);
		m_propVector.pushBack(newProp);

		newProp->runAction(Sequence::create(
			MoveBy::create(curSpeed, Vec2(0, -Director::getInstance()->getVisibleSize().height)),
			CallFuncN::create([&](Node* sender){
				sender->getParent()->removeChild(sender);
			}),
			NULL));
	}

	// delete prop
	for( Prop* pProp : m_propDeleteVector )
	{
		Vector<Prop*>::iterator iter = m_propVector.find(pProp);
		if(iter != m_propVector.end())
		{
			// run animate
			m_bulletManager->getLayer()->removeChild(*iter);
			m_propVector.erase(iter);
		}
	}
	m_propDeleteVector.clear();
}

Vector<Prop*>* PropManager::getPropVector()
{
	return &m_propVector;
}

void PropManager::deleteProp(Prop* pProp)
{
	m_propDeleteVector.pushBack(pProp);
}