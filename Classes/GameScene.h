#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "Person.h"
#include "Bullet.h"
#include "Player.h"
#include "NPC.h"
#include "BulletManager.h"
#include "PauseLayer.h"

#define FIX_POS(_pos, _min, _max) \
 if (_pos < _min)        \
 _pos = _min;        \
else if (_pos > _max)   \
 _pos = _max;        \


class GameScene : public cocos2d::Layer
{
public:
	GameScene();
    
	//创建场景
    static cocos2d::Scene* createScene();

    //初始化
    virtual bool init();  
    
    //退出按钮
    void menuCloseCallback(cocos2d::Ref* pSender);
	//跳跃按钮
	void jump(Ref* pSender);
	//暂停
	void doPause(Ref* pSender);


	//血条、怒气条、技能冷却条设置
	void setRoleProgressBar();
	void setNpcProgressBar();
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

	
	//获取player指针
	Player* getPlayer();
	
	//获取npc指针
	NPC* getNPC();

	//获取中间障碍物指针
	cocos2d::Sprite* getObstacle();

	//碰撞检测
	void collisionDetection();

	//更新
	virtual void update(float deltaTime);

	

private:

	Player* _player;
	NPC1* _npc;
	cocos2d::Sprite* obstacle;

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

    CREATE_FUNC(GameScene);
};

#endif // __HELLOWORLD_SCENE_H__
