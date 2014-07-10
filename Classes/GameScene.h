#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "Person.h"
#include "Bullet.h"
#include "Role.h"
#include "BulletManager.h"

#define FIX_POS(_pos, _min, _max) \
 if (_pos < _min)        \
 _pos = _min;        \
else if (_pos > _max)   \
 _pos = _max;        \

typedef enum {
    Normal_Action = 0,
    Move_Action,
	Jump_Action,
	Fire_Action,
    Attacked_Action,
    Vectory_Action,
	Fail_Action,
} ActionState;

class GameScene : public cocos2d::Layer
{
public:
	GameScene();
    
	//创建场景
    static cocos2d::Scene* createScene();

    //初始化
    virtual bool init();  
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

	//血条、怒气条设置
	void setProgressBar();
	void setRoleHp(unsigned int roleCurrentHp);
	void setRoleRage(unsigned int roleCurrentRage);
	void setNpcHp(unsigned int npcCurrentHp);
	void setNpcRage(unsigned int npcCurrrentRage);
	
	//重力加速器
	void onAcceleration(cocos2d::Acceleration* acc, cocos2d::Event* unused_event);

	//单点触摸函数
	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event  *event);
    void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event  *event);
    void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event  *event);
    void onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event  *event);
	bool contaiinsTouchLocation(cocos2d::Touch* touch);

	//更新
	virtual void update(float deltaTime);

private:

	Role1* _role1;
	Role2* _role2;
	Role3* _role3;
	Role4* _role4;

	cocos2d::ProgressTimer* roleHPProgressTimer;
	cocos2d::ProgressTimer* roleSPProgressTimer;
	cocos2d::ProgressTimer* npcHpProgressTimer;

	unsigned int roleCurrentHP;
	unsigned int roleCurrentSP;

	unsigned int npcCurrentHP;
	unsigned int npcCurrrentSP;

	cocos2d::Animate* cache;
	cocos2d::Animate* freeAction;

	cocos2d::Size visibleSize;
    cocos2d::Vec2 origin;

	cocos2d::Vec2 startPosition;
	cocos2d::Vec2 endPosition;

	unsigned currentState;
	unsigned nextState;

    CREATE_FUNC(GameScene);
};

#endif // __HELLOWORLD_SCENE_H__
