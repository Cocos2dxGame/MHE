#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "Person.h"
#include "Bullet.h"
#include "Role.h"
#include "BulletManager.h"
//#include "SkillManager.h"

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

	//血条、怒气条、技能冷却条设置
	void setProgressBar();
	void setRoleHp(unsigned int roleCurrentHp);
	void setRoleRage(unsigned int roleCurrentRage);
	void setNpcHp(unsigned int npcCurrentHp);
	void setNpcRage(unsigned int npcCurrrentRage);
	
	//技能栏设置
	void setMenu();
	void selectedSkill1(cocos2d::Ref* pSender);
	void selectedSkill2(cocos2d::Ref* pSender);
	void selectedSkill3(cocos2d::Ref* pSender);

	//重力加速器
	void onAcceleration(cocos2d::Acceleration* acc, cocos2d::Event* unused_event);

	//单点触摸函数
	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event  *event);
    void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event  *event);
    void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event  *event);
    void onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event  *event);
	bool contaiinsTouchLocation(cocos2d::Touch* touch);

	//触摸结束后处理事件
	void dealEndTouch();

	//更新
	virtual void update(float deltaTime);

private:

	Role1* _role1;
	Role2* _role2;
	Role3* _role3;
	Role4* _role4;

	//人物的血条、怒气条
	cocos2d::ProgressTimer* roleHPProgressTimer;
	cocos2d::ProgressTimer* roleSPProgressTimer;
	cocos2d::ProgressTimer* npcHPProgressTimer;
	cocos2d::ProgressTimer* npcSPProgressTimer;

	//3个技能的按钮
	cocos2d::MenuItemSprite* skill1Item;
	cocos2d::MenuItemSprite* skill2Item;
	cocos2d::MenuItemSprite* skill3Item;

	//3个技能的冷却条
	cocos2d::ProgressTimer* skill1CoolBar;
	cocos2d::ProgressTimer* skill2CoolBar;
	cocos2d::ProgressTimer* skill3CoolBar;

	//3种技能默认的冷却时间
	float skill1CoolDownTime;
	float skill2CoolDownTime;
	float skill3CoolDownTime;

	//3种技能当前还需的冷却时间
	float skill1NeedTime;
	float skill2NeedTime;
	float skill3NeedTime;

	//当前选择的子弹类型
	unsigned int currentBulletState;

	//角色当期的血量和怒气值
	unsigned int roleCurrentHP;
	unsigned int roleCurrentSP;

	//npc当前血量和怒气值
	unsigned int npcCurrentHP;
	unsigned int npcCurrrentSP;

	cocos2d::Size visibleSize;
    cocos2d::Vec2 origin;

	//触摸的开始点和结束点
	cocos2d::Vec2 startPosition;
	cocos2d::Vec2 endPosition;

	//角色当前动作的状态值
	unsigned int currentActionState;
	unsigned int nextActionState;

    CREATE_FUNC(GameScene);
};

#endif // __HELLOWORLD_SCENE_H__
