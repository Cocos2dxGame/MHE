#include "Role.h"
USING_NS_CC;

//Role1
//--------------------------------------------------------------------------
//--------------------------------------------------------------------------

Role1::Role1()
{
	HP = 100;
	Rage = 100;
	speed = 10;
	jumpSpeed  = 10;
	moveRight = true;
	strcpy(roleName, "Role1");
	
	char plistFileName[100];
	sprintf(plistFileName,"character/%s.plist", roleName);  
	cache = SpriteFrameCache::sharedSpriteFrameCache();
	cache->addSpriteFramesWithFile(plistFileName);

}

Role1* Role1::create()
{
	Role1* role1 = new Role1();

	if(role1 && role1->initWithSpriteFrame(role1->cache->spriteFrameByName("Normal1.png")))
	{
		role1->setAction(role1->cache);
		role1->autorelease();
		return role1;
	}

	return NULL;
}


//Role2
//--------------------------------------------------------------------------
//--------------------------------------------------------------------------Role1

Role2::Role2()
{
	HP = 200;
	Rage = 200;
	speed = 20;
	jumpSpeed  = 20;
	moveRight = true;
	strcpy(roleName, "Role2");

	char plistFileName[100];
	sprintf(plistFileName,"character/%s.plist", roleName);  
	cache = SpriteFrameCache::sharedSpriteFrameCache();
	cache->addSpriteFramesWithFile(plistFileName);
}

Role2* Role2::create()
{
	Role2* role2 = new Role2();

	if(role2 && role2->initWithSpriteFrame(role2->cache->spriteFrameByName("Normal1.png")))
	{
		role2->setAction(role2->cache);
		role2->autorelease();
		return role2;
	}

	return NULL;
}


//Role3
//--------------------------------------------------------------------------
//--------------------------------------------------------------------------

Role3::Role3()
{
	HP = 200;
	Rage = 200;
	speed = 10;
	jumpSpeed  = 10;
	moveRight = true;
	strcpy(roleName, "Role3");
}

Role3* Role3::create()
{
	Role3* role3 = new Role3();

	char plistFileName[100];
	
	sprintf(plistFileName,"character/%s.plist", role3->roleName);  

	role3->cache = SpriteFrameCache::sharedSpriteFrameCache();
	role3->cache->addSpriteFramesWithFile(plistFileName);

	if(role3 && role3->initWithSpriteFrame(role3->cache->spriteFrameByName("Normal1.png")))
	{
		role3->setAction(role3->cache);
		role3->autorelease();
		return role3;
	}

	return NULL;
}