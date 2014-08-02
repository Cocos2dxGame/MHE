#ifndef __COMPETE_STATE_CONTROLLER__
#define __COMPETE_STATE_CONTROLLER__

#include "cocos2d.h"
#include "NPC.h"

class CompeteStateController
{
public:
	CompeteStateController();
	~CompeteStateController();

	static CompeteStateController* create(NPC* curNPC, cocos2d::Vec2 gravity, BulletManager* m_pBulletManger);

	void firet();
private:
	NPC* curNPC;
	cocos2d::Vec2 hitPosition;
};

#endif