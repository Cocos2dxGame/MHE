#ifndef __MODE_SELECTE_SCENE__
#define __MODE_SELECTE_SCENE__

#include "cocos2d.h"
#include "SceneManager.h"

class ModeSelecteScene :public cocos2d::Layer
{
public:
	ModeSelecteScene();
	~ModeSelecteScene();

	static cocos2d::Scene* createScene();

	bool init();

	void goClassicalScene(Ref* pSender);
	void goSurvivalScene(Ref* pSender);
	void goCompeteScene(Ref* pSender);

	CREATE_FUNC(ModeSelecteScene);

private:

};

#endif