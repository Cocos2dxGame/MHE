#include "Bullet.h"
#include "BulletManager.h"

USING_NS_CC;

Bullet::Bullet()
{
}

Bullet::~Bullet()
{
}

Bullet* Bullet::create(bulletType type, Point pos, Vec2 velocity, BulletManager* pBulletManager)
{
	Bullet* bullet = new Bullet();
	if(bullet && bullet->initWithFile("ball.png"))
	{	
		bullet->m_type = type;
		bullet->m_velocity = velocity;
		bullet->setPosition(pos);
		bullet->m_pBulletManager = pBulletManager;
		return bullet;
	}

	return NULL;
}

void Bullet::update(Vec2 acceleration, float deltaTime)
{
	
	// update position
	Point pos = this->getPosition();
	setPosition(pos+=m_velocity*deltaTime+acceleration*deltaTime*deltaTime/2);
	m_velocity+=acceleration*deltaTime;

	// if the bullet leave the screen
	Size visiblesize = Director::getInstance()->getVisibleSize();
	Rect screen(0, 0, visiblesize.width, visiblesize.height);
	if(!(this->getBoundingBox().intersectsRect(screen)))
	{
		this->removeBullet();
	}
	else
	{
		// detect bullet collision
		for(Bullet* pBullet : *(m_pBulletManager->getBulletVector()))
		{
			if(pBullet != this)
			{
				if(pBullet->getBoundingBox().intersectsRect(this->getBoundingBox()))
				{
					pBullet->removeBullet();
					this->removeBullet();
				}
			}
		}
	}
	
}

bulletType Bullet::getType()
{
	return m_type;
}

void Bullet::removeBullet()
{
	
	m_pBulletManager->getBulletVector()->erase(m_pBulletManager->getBulletVector()->find(this));
	m_pBulletManager->getLayer()->removeChild(this);
	this->release();
	
}