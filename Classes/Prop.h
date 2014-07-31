#pragma once

#include "cocos2d.h"

class PropManager;
enum GameSceneType
{
	GameScene1, GameScene2, GameScene3, GameScene4, GameScene5
};

enum PropType
{
	type1, type2, type3
};

class Prop : public cocos2d::Sprite
{
public:
	Prop();
	~Prop();

	static Prop* createProp(GameSceneType sceneType, PropType propType);

	CREATE_FUNC(Prop);

private:
	PropType		m_type;
};

