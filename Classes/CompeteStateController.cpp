#include "CompeteStateController.h"

USING_NS_CC;

CompeteStateController::CompeteStateController()
{
	time = 0;
	visibleSize = Director::sharedDirector()->getVisibleSize();
}

CompeteStateController::~CompeteStateController()
{
}

CompeteStateController* CompeteStateController::create(NPC* npc, Vec2 gravity, BulletManager* bulletManager)
{
	CompeteStateController* curStateController = new CompeteStateController();
	curStateController->curNPC = npc;
	curStateController->gravity = gravity;
	curStateController->bulletManager = bulletManager;

	//curStateController->propManager = curStateController->bulletManager->getPropManager();
	//curStateController->propVector = *(curStateController->propManager->getPropVector());

	return curStateController;
}

void CompeteStateController::update(float dt)
{
	time += dt;
	if(time > 3)
	{
		time = 0;
		PropManager* propManager = bulletManager->getPropManager();
		Vector<Prop*> propVector = *(propManager->getPropVector());

		Vector<Prop*>::iterator iter;
		for(iter = propVector.begin(); iter != propVector.end(); iter++)
		{
			if((*iter)->getPosition().x > 0 && (*iter)->getPosition().x <visibleSize.width)
			{
				hitPosition = (*iter)->getPosition();
				fire();
				break;
			}
		}
	}
}

void CompeteStateController::fire()
{
	Vec2 shootVelocity;

	//Ëæ»úÊý
	int temp = visibleSize.width/4 * rand()/(RAND_MAX+1.0);

	Vec2 tempPosition = curNPC->getPosition();
	tempPosition += Vec2(temp-visibleSize.width/4/2, 0);
	
	shootVelocity.x =- sqrt((-gravity.y) * (tempPosition.x - hitPosition.x) / 4);
	shootVelocity.y = 2 * (-shootVelocity.x);
	
	curNPC->fireAction();
	bulletManager->shoot(NormalBullet, npc,curNPC->getPosition(),shootVelocity);
}