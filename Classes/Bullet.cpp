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
	if(bullet && bullet->initWithFile("bullet/bl_001.png"))
	{	
		bullet->m_type = type;
		bullet->m_velocity = velocity;
		bullet->setPosition(pos);
		bullet->m_pBulletManager = pBulletManager;
		bullet->setScale(Director::getInstance()->getVisibleSize().height/12/bullet->getContentSize().height);
		return bullet;
	}

	return NULL;
}

bool Bullet::update(Vec2 acceleration, float deltaTime)
{
	
	// update position
	Point pos = this->getPosition();
	setPosition(pos+=m_velocity*deltaTime+acceleration*deltaTime*deltaTime/2);
	m_velocity+=acceleration*deltaTime;

	// if the bullet leave the screen
	if((this->getBoundingBox().getMaxY()<0))
	{
		m_pBulletManager->getLayer()->removeChild(this);
		return true;
	}
	else
	{
		// detect bullet collision
		std::list<Bullet*>::iterator iter;
		for(iter=m_pBulletManager->getBulletList()->begin(); iter!=m_pBulletManager->getBulletList()->end(); iter++)
		{
			if(*iter != this)
			{
				if((*iter)->getBoundingBox().intersectsRect(this->getBoundingBox()))
				{
					m_pBulletManager->getLayer()->removeChild(this);
					m_pBulletManager->getLayer()->removeChild(*iter);
					m_pBulletManager->getBulletList()->erase(iter);
					return true;
				}
			}
		}
	}

	// update rotation
	if(m_velocity.x == 0)
	{
		if(m_velocity.y>0)
		{
			setRotation(270);
		}
		else if(m_velocity.y<0)
		{
			setRotation(90);
		}
	}
	else
	{
		float cita = atan(m_velocity.y/m_velocity.x);
		setRotation(-cita*180/3.14);
	}

	// update scale
	if(m_velocity.x < 0)
	{
		setScaleX(-abs(this->getScaleX()));
	}
	else 
	{
		setScaleX(abs(this->getScaleX()));
	}

	return false;
}

bulletType Bullet::getType()
{
	return m_type;
}

void Bullet::removeBullet()
{	
	m_pBulletManager->getLayer()->removeChild(this);
}