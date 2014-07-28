#ifndef __SURVIVAL_SCENE__
#define __SURVIVAL_SCENE__

#include "cocos2d.h"
#include "Player.h"

class SurvivalScene :public cocos2d::Layer
{
public:
	SurvivalScene();
	~SurvivalScene();

	//��������
    static cocos2d::Scene* createScene();

	bool init();
	void setSkillCoolDownBar();
	void setMenu();

	void doPause(Ref* pSender);
	 //�˳���ť
    void menuCloseCallback(cocos2d::Ref* pSender);

	void update(float dt);

	CREATE_FUNC(SurvivalScene);	
private:
	Player* _curPlayer;
	cocos2d::ProgressTimer* skillCoolDownBar;
	float skillCoolDownNeedTime;
	float skillCoolDownTime;
	GameSceneType curScene;
};



#endif