#ifndef __Second_SCENE_H__
#define __Second_SCENE_H__

#include "cocos2d.h"
#include "Person.h"
#include "Bullet.h"

#define FIX_POS(_pos, _min, _max) \
 if (_pos < _min)        \
 _pos = _min;        \
else if (_pos > _max)   \
 _pos = _max;        \

typedef enum {
    Normal_Action = 0,
    Fire_Action,
    Move_Action,
    Jump_Action,
    Attacked_Action,
    Vectory_Action,
} ActionState;

class SecondScene : public cocos2d::Layer
{
public:
	SecondScene();
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
	void setPhyWorld(cocos2d::PhysicsWorld* world);
	          
	void onAcceleration(cocos2d::Acceleration* acc, cocos2d::Event* unused_event);

	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event  *event);
    void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event  *event);
    void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event  *event);
    void onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event  *event);
	bool contaiinsTouchLocation(cocos2d::Touch* touch);

private:
	cocos2d::Sprite* _sprite;
	cocos2d::Sprite* _ball;
	cocos2d::PhysicsWorld* m_world;
	Person* _person;
	Bullet* _bullet;

	cocos2d::Animate* cache;
	cocos2d::Animate* freeAction;

	cocos2d::Size visibleSize;
    cocos2d::Vec2 origin;

	cocos2d::Vec2 startPosition;
	cocos2d::Vec2 endPosition;

    CREATE_FUNC(SecondScene);
};

#endif // __HELLOWORLD_SCENE_H__
