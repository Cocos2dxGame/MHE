#ifndef __STATE_CONTROLLER__
#define __STATE_CONTROLLER__

#include "NPC.h"
#include "Player.h"
#include "BulletManager.h"

class StateController
{
public:
	StateController();
	~StateController();

	static StateController* create(NPC* curNPC, Player* curPlayer, cocos2d::Vec2 gravity, BulletManager* m_pBulletManger);

	void playerShooting(cocos2d::Vec2 shootPositon, cocos2d::Vec2 velocity);

	void avoid();

	void fire();

	void update(float dt);

private:
	Player* curPlayer;
	NPC* curNPC;
	BulletManager* m_pBulletMangeer;
	cocos2d::Vec2 gravity;
	cocos2d::Vec2 velocity;
	cocos2d::Vec2 shootPositon;
	cocos2d::Vec2 hitPosition;
	bool playerShoot;
	cocos2d::Vec2 npcDestination;

	cocos2d::Size visibleSize;
    cocos2d::Vec2 origin;

	float time;
};



#endif