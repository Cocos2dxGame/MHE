#include "Bullet.h"
#include "BulletManager.h"
#include "Person.h"
#include "Player.h"
#include "NPC.h"
#include "SurvivalScene.h"

USING_NS_CC;

Bullet::Bullet()
{
}

Bullet::~Bullet()
{
}

Bullet* Bullet::createBullet(bulletType type, Point pos, Vec2 velocity, Owner owner, BulletManager* pBulletManager)
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
	case 9:
		bullet->initWithFile("bullet/bl_003.png");
		bullet->m_emitter = ParticleMeteor::create();
		bullet->m_emitter->setEmissionRate(30);
		bullet->m_emitter->setLife(0.5);
		bullet->m_emitter->setLifeVar(0.2);
		break;
	case 12:
		bullet->initWithFile("bullet/bl_003.png");
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
	bullet->m_owner = owner;
	bullet->m_hit = 0;
	bullet->setPosition(pos);
	
	//float screenAera = Director::getInstance()->getVisibleSize().width * Director::getInstance()->getVisibleSize().height;
	float scale = Director::getInstance()->getVisibleSize().width*0.00034;

	if(velocity.x < 0)
	{
		bullet->setScale(-scale,scale);
	}
	else
	{
		bullet->setScale(scale);
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

	// if the bullet leave the screen
	if((this->getBoundingBox().getMaxY()<Director::getInstance()->getVisibleSize().height*0.18))
	{
		m_pBulletManager->deleteBullet(this);
		return ;
	}

	//detect prop collision
	propCollision();

	if(m_leave)
	{
		// detect person collision
		if(m_pBulletManager->SceneType != GameScene4)
		{
			personCollision();
		}

		// detect bullet collision
		bulletCollision();
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

void Bullet::propCollision()
{
	Person* pPerson; 

	for(Prop* pProp : *(m_pBulletManager->getPropManager()->getPropVector()))
	{
		if(pProp->getBoundingBox().intersectsRect(this->getBoundingBox()))
		{
			switch (this->m_pBulletManager->SceneType)
			{
			//survival mode
			case GameScene4:
				pPerson= (Person*)m_pBulletManager->getSpriteVector()->getRandomObject();
				pPerson->getProp(pProp->getType());
				((SurvivalScene*)(m_pBulletManager->getLayer()))->addPlayerMark(pow(2,m_hit++));
				//CCLOG("%d", pProp->getType());
				m_pBulletManager->getPropManager()->deleteProp(pProp);
				break;
			case GameScene5:
				m_pBulletManager->deleteBullet(this);
				m_pBulletManager->getPropManager()->deleteProp(pProp);
				break;
			default:
				m_pBulletManager->deleteBullet(this);
				m_pBulletManager->getPropManager()->deleteProp(pProp);
				switch (this->m_owner)
				{
				case player:
					for(Sprite* pSprite : *(m_pBulletManager->getSpriteVector()))
					{
						if(pSprite->getTag() == 1)
						{
							((Person*)pSprite)->getProp(normal);
						}
					}
					break;
				case npc:
					for(Sprite* pSprite : *(m_pBulletManager->getSpriteVector()))
					{
						if(pSprite->getTag() == 2)
						{
							((Person*)pSprite)->getProp(normal);
						}
					}
					break;
				default:
					break;
				}
				break;
			}
			
		}
	}
}

void Bullet::personCollision()
{
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
}

void Bullet::bulletCollision()
{
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