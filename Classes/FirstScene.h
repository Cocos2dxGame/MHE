#ifndef __FIRST_SCENE_H__
#define __FIRST_SCENE_H__

#include "cocos2d.h"
#include "Box2D\Box2D.h";

class FirstScene : public cocos2d::Layer
{
	//Texture2D* _spriteTexture;
	//b2World* world;

public:
	/*FirstScene();
	~FirstScene();

	void initPhysics();

	void createResetButton();

	virtual void draw(Renderer* renderer, const Mat4 &transform, uint32_t flage) override;

	void addNewSpriteAtPosition(Vec2 p);

	void update(float dt);

	void onTouchesEnable(const std::vector<Touch*>& touches, Event* event);*/
    // 
    static cocos2d::Scene* createScene();

    // 
	virtual bool init();  
    
    //a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    


    // implement the "static create()" method manually
    CREATE_FUNC(FirstScene);
};

#endif // __StartScene_SCENE_H__
