#include "StateController.h"
USING_NS_CC;

StateController::StateController():
	shootPositon(-1,-1),hitPosition(-1,-1),
	curNPC(nullptr), curPlayer(nullptr), 
	gravity(0,0),velocity(0,0), 
	playerShoot(false),time(0.0)
{
	visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
}

StateController::~StateController()
{
}

StateController* StateController::create(NPC* curNPC, Player* curPlayer, Vec2 gravity, BulletManager* bulletManager)
{
	StateController* newStateController = new StateController();
	newStateController->curNPC = curNPC;
	newStateController->curPlayer = curPlayer;
	newStateController->gravity =gravity;
	newStateController->m_pBulletMangeer = bulletManager;

	return newStateController;
}

void StateController::playerShooting(cocos2d::Vec2 shootPositon, cocos2d::Vec2 velocity)
{
	this->hitPosition = shootPositon + Vec2(velocity.x * (2*velocity.y)/(-gravity.y), 0);
	playerShoot = true;
	CCLOG("the hit position is x=%f, y=%f",hitPosition.x, hitPosition.y);
}

bool StateController::isCollision()
{
	if(hitPosition.x > curNPC->getBoundingBox().getMinX() && hitPosition.x < curNPC->getBoundingBox().getMaxX())
		if(hitPosition.y > curNPC->getBoundingBox().getMinY() && hitPosition.y< curNPC->getBoundingBox().getMaxY())
			return true;

	return false;
}

void StateController::update(float dt)
{
	time += dt;
	CCLOG("hitposition x=%f, y=%f", hitPosition.x, hitPosition.y);
	if(playerShoot && curNPC->getBoundingBox().intersectsRect(Rect(hitPosition.x-5, hitPosition.y-5, 10, 10)))
	{
		playerShoot = false;
		avoid();
	}
	else if(time > 4)
	{
		time = 0.0;
		fire();
	}

	if(curNPC->getActionState() == Move_Action)
	{
		if(curNPC->getActionState() == Move_Action)
		{
			if(npcDestination.x > curNPC->getPosition().x+1)
				curNPC->setPosition(curNPC->getPosition() + Vec2(2,0));
			else if(npcDestination.x < curNPC->getPosition().x-1)
				curNPC->setPosition(curNPC->getPosition() - Vec2(2,0));
		}
	}
}

void StateController::fire()
{
	Vec2 playerPositon = curPlayer->getPosition();
	Vec2 shootVelocity;
	shootVelocity.x =- sqrt((-gravity.y) * (curNPC->getPosition().x - playerPositon.x) / 4);
	shootVelocity.y = 2 * (-shootVelocity.x);
	
	curNPC->fireAction();
	m_pBulletMangeer->shoot(NormalBullet,curNPC->getPosition(),shootVelocity);

}

void StateController::avoid()
{
	Vec2 temp = curNPC->getPosition();
	if(hitPosition.x < visibleSize.width* 5/8)
	{
		curNPC->moveAction();
		npcDestination = hitPosition + Vec2(visibleSize.width/8,0);
	}
	else if(hitPosition.x < visibleSize.width * 7/8)
	{
		curNPC->moveAction();
		if(hitPosition.x < curNPC->getPosition().x)
			npcDestination = hitPosition + Vec2(visibleSize.width/8,0);
		else
			npcDestination = hitPosition - Vec2(visibleSize.width/8,0);
	}
	else if(hitPosition.x < visibleSize.width)
	{
		curNPC->moveAction();
		npcDestination = hitPosition - Vec2(visibleSize.width/8,0);
	}
}