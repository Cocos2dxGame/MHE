#include "Bullet.h"

Bullet::Bullet()
{
	coolDown = 5;
	damage = 10;
	speed = 0;
	quality = 0;
	speedPerPower = 10;
}

void Bullet::create(int power, float angle)
{
	speed = speedPerPower * power;
}