#pragma once

#include "cocos2d.h"
#include "Prop.h"

class BulletManager;

class PropManager
{
public:
	PropManager(void);
	~PropManager(void);

	static PropManager* create(BulletManager* pBulletManager);
	void update(float deltaTime);
	cocos2d::Vector<Prop*>* getPropVector();
	void deleteProp(Prop* pProp);

private:
	BulletManager* m_bulletManager;
	cocos2d::Vector<Prop*> m_propVector;
	cocos2d::Vector<Prop*> m_propDeleteVector;
};

