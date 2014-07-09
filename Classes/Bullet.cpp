#include "Bullet.h"

USING_NS_CC;

Bullet::Bullet()
{
}

Bullet* Bullet::create()
{
	Bullet* bullet = new Bullet();
	if(bullet && bullet->initWithFile("ball.png"))
	{	
		bullet->autorelease();
		return bullet;
	}

	return NULL;
}


Vec2 Bullet::getVelocity()
{
	return velocity;
}