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
    
	//��������
    static cocos2d::Scene* createScene();

    //��ʼ��
    virtual bool init();  
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

	//Ѫ����ŭ������������ȴ������
	void setProgressBar();
	void setRoleHp(unsigned int roleCurrentHp);
	void setRoleRage(unsigned int roleCurrentRage);
	void setNpcHp(unsigned int npcCurrentHp);
	void setNpcRage(unsigned int npcCurrrentRage);
	
	//����������
	void setMenu();
	void selectedSkill1(cocos2d::Ref* pSender);
	void selectedSkill2(cocos2d::Ref* pSender);
	void selectedSkill3(cocos2d::Ref* pSender);

	//����������
	void onAcceleration(cocos2d::Acceleration* acc, cocos2d::Event* unused_event);

	//���㴥������
	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event  *event);
    void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event  *event);
    void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event  *event);
    void onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event  *event);
	bool contaiinsTouchLocation(cocos2d::Touch* touch);

	//�������������¼�
	void dealEndTouch();

	//����
	virtual void update(float deltaTime);

private:

	Role1* _role1;
	Role2* _role2;
	Role3* _role3;
	Role4* _role4;

	//�����Ѫ����ŭ����
	cocos2d::ProgressTimer* roleHPProgressTimer;
	cocos2d::ProgressTimer* roleSPProgressTimer;
	cocos2d::ProgressTimer* npcHPProgressTimer;
	cocos2d::ProgressTimer* npcSPProgressTimer;

	//3�����ܵİ�ť
	cocos2d::MenuItemSprite* skill1Item;
	cocos2d::MenuItemSprite* skill2Item;
	cocos2d::MenuItemSprite* skill3Item;

	//3�����ܵ���ȴ��
	cocos2d::ProgressTimer* skill1CoolBar;
	cocos2d::ProgressTimer* skill2CoolBar;
	cocos2d::ProgressTimer* skill3CoolBar;

	//3�ּ���Ĭ�ϵ���ȴʱ��
	float skill1CoolDownTime;
	float skill2CoolDownTime;
	float skill3CoolDownTime;

	//3�ּ��ܵ�ǰ�������ȴʱ��
	float skill1NeedTime;
	float skill2NeedTime;
	float skill3NeedTime;

	//��ǰѡ����ӵ�����
	unsigned int currentBulletState;

	//��ɫ���ڵ�Ѫ����ŭ��ֵ
	unsigned int roleCurrentHP;
	unsigned int roleCurrentSP;

	//npc��ǰѪ����ŭ��ֵ
	unsigned int npcCurrentHP;
	unsigned int npcCurrrentSP;

	cocos2d::Size visibleSize;
    cocos2d::Vec2 origin;

	//�����Ŀ�ʼ��ͽ�����
	cocos2d::Vec2 startPosition;
	cocos2d::Vec2 endPosition;

	//��ɫ��ǰ������״ֵ̬
	unsigned int currentActionState;
	unsigned int nextActionState;

    CREATE_FUNC(GameScene);
};

#endif // __HELLOWORLD_SCENE_H__
