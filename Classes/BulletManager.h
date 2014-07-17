#pragma once

#include "cocos2d.h"
#include "Bullet.h"

enum GameSceneType
{
	GameScene1, GameScene2, GameScene3
};

class BulletManager
{
public:
	BulletManager();
	~BulletManager();

	static BulletManager* create(GameSceneType gamescenetype, cocos2d::Layer* curLayer, cocos2d::Vector<cocos2d::Sprite*>* pSpriteVector, cocos2d::Vec2 g);	/* init bullet manager */
	void update(float deltaTime);												/* return true delete bullet */
	void shoot(bulletType type, cocos2d::Point pos, cocos2d::Vec2 velocity);
	void deleteBullet(Bullet* pBullet);
	cocos2d::Vector<Bullet*>* getBulletVector();
	cocos2d::Vector<cocos2d::Sprite*>* getSpriteVector();
	cocos2d::Layer* getLayer();

	void clean();

private:

	cocos2d::Layer*					m_layer;
	cocos2d::Vector<Bullet*>		m_BulletVector;
	cocos2d::Vector<Bullet*>		m_BulletDeleteVector;
	cocos2d::Vec2					m_g;
	cocos2d::Vector<cocos2d::Sprite*>*		m_pSpriteVector;
};
