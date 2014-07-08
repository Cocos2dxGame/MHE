#include "Bullet.h"

USING_NS_CC;

Bullet::Bullet()
{
	coolDown = 5;
	damage = 10;
	velocity.x = 0;
	velocity.y = 0;
	quality = 0;
	speedPerPower = 10;
}

Bullet* Bullet::create()
{
	Bullet* bullet = new Bullet();
	if(bullet && bullet->initWithFile("ball.png"))
	{
		auto bulletBody = PhysicsBody::createCircle(bullet->getContentSize().width/2);
		bullet->setPhysicsBody(bulletBody);		
		bullet->autorelease();
		return bullet;
	}

	return NULL;
}

void Bullet::setVelocity(Vec2 velocity)
{
	this->velocity = velocity* speedPerPower;
}

Vec2 Bullet::getVelocity()
{
	return velocity;
}