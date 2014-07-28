#ifndef __COMPETE_SCENE__
#define __COMPETE_SCENE__

#include "cocos2d.h"
#include "Player.h"
#include "NPC.h"

class CompeteScene :public cocos2d::Layer
{
public:
	CompeteScene();
	~CompeteScene();

	static Scene* createScene();

	bool init();

	CREATE_FUNC(CompeteScene);

private:
	Player* _curPlayer;
	NPC* _curNPC;

};

#endif