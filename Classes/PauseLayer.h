#ifndef __PAUSE_LAYER__
#define __PAUSE_LAYER__

#include "cocos2d.h"
#include "SceneManager.h"
#include "GameScene.h"
#include "ChapterScene.h"

class PauseLayer :public cocos2d::Layer
{
public:
	PauseLayer();
	~PauseLayer();
	bool init();
	
	void goBack(Ref* pSender);
	void reBegin(Ref* pSender);
	void goChapter(Ref* pSender);

	CREATE_FUNC(PauseLayer);
};

#endif