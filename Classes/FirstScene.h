#ifndef __FIRST_SCENE_H__
#define __FIRST_SCENE_H__

#include "cocos2d.h"
#include "GameScene.h"

class FirstScene : public GameScene
{
public:
	FirstScene();
	~FirstScene();

	virtual bool init();  
    
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    CREATE_FUNC(FirstScene);
};

#endif // __FirstScene_SCENE_H__
