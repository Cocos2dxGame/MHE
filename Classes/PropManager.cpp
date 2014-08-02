#include "cocos2d.h"
#include "PropManager.h"
#include "BulletManager.h"
#include "SurvivalScene.h"

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

	switch (pBulletManger->SceneType)
	{
	case GameScene4:
		newManager->m_time = 6.0f;
		newManager->m_timeVariance = 2.0f;
		newManager->m_duration = 20.0f;
		newManager->m_durationVariance = 5.0f;
		break;
	case GameScene5:
		newManager->m_time = 15.0f;
		newManager->m_timeVariance = 5.0f;
		newManager->m_duration = 20.0f;
		newManager->m_durationVariance = 5.0f;
		break;
	default:
		//gamescene1-3
		newManager->m_time = 15.0f;
		newManager->m_timeVariance = 5.0f;
		newManager->m_duration = 20.0f;
		newManager->m_durationVariance = 5.0f;
		break;
	}

	newManager->m_curTime = 0;
	newManager->m_nextTime = getRandom(newManager->m_time, newManager->m_timeVariance);

	return newManager;
}

void PropManager::update(float deltaTime)
{
	if(m_curTime < m_nextTime)
	{
		m_curTime+=deltaTime;
	}
	else
	{
		m_curTime = 0;
		m_nextTime=getRandom(m_time, m_timeVariance);
		switch(m_bulletManager->SceneType)
		{
		case GameScene4:
			survivalUpdate(deltaTime);
			break;
		case GameScene5:
			competitionUpdate(deltaTime);
			break;
		default:
			classicUpdate(deltaTime);
			break;
		}
	}

	// delete prop
	for( Prop* pProp : m_propDeleteVector )
	{
		Vector<Prop*>::iterator iter = m_propVector.find(pProp);
		if(iter != m_propVector.end())
		{
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

void PropManager::classicUpdate(float deltaTime)
{
	// add prop
	float curDuration = getRandom(m_duration, m_durationVariance);
	Prop* newProp = Prop::createProp(m_bulletManager->SceneType, normal);
	float x = CCRANDOM_0_1()*(Director::getInstance()->getVisibleSize().width);
	newProp->setPosition(x, Director::getInstance()->getVisibleSize().height);
	m_bulletManager->getLayer()->addChild(newProp);
	m_propVector.pushBack(newProp);

	newProp->runAction(Sequence::create(
		MoveBy::create(curDuration, Vec2(0, -Director::getInstance()->getVisibleSize().height)),
		CallFuncN::create([&](Node* sender){
			sender->getParent()->removeChild(sender);
	}),
		NULL));
}

void PropManager::survivalUpdate(float deltaTime)
{
	// add prop
	float bombRate = 0.15;
	float curDuration = getRandom(m_duration, m_durationVariance);
	Prop* newProp;
	if(CCRANDOM_0_1()<bombRate)
	{
		newProp = Prop::createProp(m_bulletManager->SceneType,bomb);
	}
	else
	{
		newProp = Prop::createProp(m_bulletManager->SceneType,normal);
	}
	
	float x = CCRANDOM_0_1()*(Director::getInstance()->getVisibleSize().width);
	newProp->setPosition(x, Director::getInstance()->getVisibleSize().height);
	m_bulletManager->getLayer()->addChild(newProp);
	m_propVector.pushBack(newProp);

	newProp->runAction(Sequence::create(
		MoveBy::create(curDuration, Vec2(0, -Director::getInstance()->getVisibleSize().height)),
		CallFuncN::create([&](Node* sender){
			sender->getParent()->removeChild(sender);
	}),
		NULL));

	// prop drop
	for( Prop* pProp : m_propVector )
	{
		if(pProp->getPositionY() < Director::getInstance()->getVisibleSize().height * 0.15)
		{
			m_propDeleteVector.pushBack(pProp);
			Person* pPerson = (Person*)m_bulletManager->getSpriteVector()->getRandomObject();
			pPerson->notHit();
		}
	}
}

void PropManager::competitionUpdate(float deltaTime)
{

}