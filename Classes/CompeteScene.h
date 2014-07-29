#ifndef __COMPETE_SCENE__
#define __COMPETE_SCENE__

#include "cocos2d.h"
#include "Player.h"
#include "NPC.h"
#include "GameScene.h"

class CompeteScene :public cocos2d::Layer
{
public:
	CompeteScene();
	~CompeteScene();

	//创建场景
	static cocos2d::Scene* createScene();

	bool init();
	void setSkillCoolDownBar();
	void setMenu();

	void doPause(Ref* pSender);
	 //退出按钮
	void menuCloseCallback(cocos2d::Ref* pSender);

	virtual void update(float dt);

	CREATE_FUNC(CompeteScene);

private:
	Player* _curPlayer;
	NPC* _curNPC;
	GameSceneType curScene;
	cocos2d::ProgressTimer* skillCoolDownBar;
};

#endif