#include "Bullet.h"

USING_NS_CC;

Bullet::Bullet()
{
}

Bullet* Bullet::create(bulletType type, cocos2d::Point pos, Vec2 velocity)
{
	Bullet* bullet = new Bullet();
	if(bullet && bullet->initWithFile("ball.png"))
	{	
		bullet->m_type = type;
		bullet->m_velocity = velocity;
		bullet->setPosition(pos);
		return bullet;
	}

	return NULL;
}

void Bullet::move(Vec2 acceleration, float deltaTime)
{
	Point pos = this->getPosition();
	setPosition(pos+=m_velocity*deltaTime+acceleration*deltaTime*deltaTime/2);
	m_velocity+=acceleration*deltaTime;
}