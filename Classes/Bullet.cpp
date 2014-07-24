#include "Bullet.h"
#include "BulletManager.h"
#include "Person.h"

USING_NS_CC;

Bullet::Bullet()
{
}

Bullet::~Bullet()
{
}

Bullet* Bullet::createBullet(bulletType type, Point pos, Vec2 velocity, BulletManager* pBulletManager)
{
	Bullet* bullet = Bullet::create();
	switch (pBulletManager->SceneType*3+type)
	{
	case 0:
		bullet->initWithFile("bullet/bl_000.png");
		bullet->m_emitter = ParticleMeteor::create();
		bullet->m_emitter->setEmissionRate(30);
		bullet->m_emitter->setLife(0.5);
		bullet->m_emitter->setLifeVar(0.2);
		break;
	case 1:
		bullet->initWithFile("bullet/bl_001.png");
		bullet->m_emitter = ParticleMeteor::create();
		bullet->m_emitter->setEmissionRate(30);
		bullet->m_emitter->setLife(0.5);
		bullet->m_emitter->setLifeVar(0.2);
		break;
	case 2:
		bullet->initWithFile("bullet/bl_002.png");
		bullet->m_emitter = ParticleMeteor::create();
		bullet->m_emitter->setEmissionRate(30);
		bullet->m_emitter->setLife(0.5);
		bullet->m_emitter->setLifeVar(0.2);
		break;
	case 3:
		bullet->initWithFile("bullet/bl_003.png");
		bullet->m_emitter = ParticleMeteor::create();
		bullet->m_emitter->setEmissionRate(30);
		bullet->m_emitter->setLife(0.5);
		bullet->m_emitter->setLifeVar(0.2);

		break;
	case 4:
		bullet->initWithFile("bullet/bl_004.png");
		bullet->m_emitter = ParticleMeteor::create();
		bullet->m_emitter->setEmissionRate(30);
		bullet->m_emitter->setLife(0.5);
		bullet->m_emitter->setLifeVar(0.2);
		break;
	case 5:
		bullet->initWithFile("bullet/bl_005.png");
		bullet->m_emitter = ParticleMeteor::create();
		bullet->m_emitter->setEmissionRate(30);
		bullet->m_emitter->setLife(0.5);
		bullet->m_emitter->setLifeVar(0.2);
		break;
	case 6:
		bullet->initWithFile("bullet/bl_006.png");
		bullet->m_emitter = ParticleMeteor::create();
		bullet->m_emitter->setEmissionRate(30);
		bullet->m_emitter->setLife(0.5);
		bullet->m_emitter->setLifeVar(0.2);
		break;
	case 7:
		bullet->initWithFile("bullet/bl_007.png");
		bullet->m_emitter = ParticleMeteor::create();
		bullet->m_emitter->setEmissionRate(30);
		bullet->m_emitter->setLife(0.5);
		bullet->m_emitter->setLifeVar(0.2);
		break;
	case 8:
		bullet->initWithFile("bullet/bl_008.png");
		bullet->m_emitter = ParticleMeteor::create();
		bullet->m_emitter->setEmissionRate(30);
		bullet->m_emitter->setLife(0.5);
		bullet->m_emitter->setLifeVar(0.2);
		break;

	default:
		break;
	}

	bullet->m_type = type;
	bullet->m_velocity = velocity;
	bullet->m_leave = false;
	bullet->m_pBulletManager = pBulletManager;
	bullet->m_emitter->setPosition(pos);
	bullet->setPosition(pos);

		//根据速度的x分量设置子弹的缩放
	if(velocity.x < 0)
	{
		bullet->setScale(-(Director::getInstance()->getVisibleSize().height/bullet->getContentSize().height*0.05), 
			Director::getInstance()->getVisibleSize().height/bullet->getContentSize().height*0.05);
	}
	else
	{
		bullet->setScale(Director::getInstance()->getVisibleSize().height/bullet->getContentSize().height*0.05);
	}

	return bullet;
}


void Bullet::update(Vec2 acceleration, float deltaTime)
{
	
	// update position
	Point pos = this->getPosition();
	pos+=m_velocity*deltaTime+acceleration*deltaTime*deltaTime/2;
	setPosition(pos);
	m_emitter->setPosition(pos);
	m_velocity+=acceleration*deltaTime;

	if(m_leave)
	{
		// if the bullet leave the screen
		if((this->getBoundingBox().getMaxY()<Director::getInstance()->getVisibleSize().height*0.18))
		{
			m_pBulletManager->deleteBullet(this);
			return ;
		}
		else
		{
			//std::list<Bullet*>::iterator iter;
			// detect person collision
			for(Sprite* pSprite : *(m_pBulletManager->getSpriteVector()))
			{
				if(pSprite->getBoundingBox().intersectsRect(this->getBoundingBox()))
				{
					m_pBulletManager->deleteBullet(this);

					switch (pSprite->getTag())
					{
					case 1:
						((Person*)pSprite)->attacked(this->m_type);
						break;
					case 2:
						((Person*)pSprite)->attacked(this->m_type);
						break;
					default:
						break;
					}
				}
			}

			// detect bullet collision
			for(Bullet* pBullet : *(m_pBulletManager->getBulletVector()))
			{
				if(pBullet != this)
				{
					if(pBullet->getBoundingBox().intersectsRect(this->getBoundingBox()))
					{
						m_pBulletManager->deleteBullet(pBullet);
						m_pBulletManager->deleteBullet(this);
						return ;
					}
				}
			}
		}
	}
	else
	{
		m_leave = true;
		for(Sprite* pSprite : *(m_pBulletManager->getSpriteVector()))
		{
			if(pSprite->getTag() < 3)
			{
				if(pSprite->getBoundingBox().intersectsRect(this->getBoundingBox()))
				{
					m_leave = false;
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

}

bulletType Bullet::getType()
{
	return m_type;
}

ParticleSystemQuad* Bullet::getEmitter()
{
	return m_emitter;
}
