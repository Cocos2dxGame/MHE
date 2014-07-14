#include "Role.h"
USING_NS_CC;

//Role1
//--------------------------------------------------------------------------
//--------------------------------------------------------------------------

Role1::Role1()
{
	totalHP = 200;
	HP = 200;
	SP = 0;
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

	char keyname[100];
	sprintf(keyname,"%sNormal1.png", role1->roleName);

	if(role1 && role1->initWithSpriteFrame(role1->cache->spriteFrameByName(keyname)))
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
	totalHP = 200;
	HP = 200;
	SP = 200;
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
	
	char keyname[100];
	sprintf(keyname,"%sNormal1.png", role2->roleName);

	if(role2 && role2->initWithSpriteFrame(role2->cache->spriteFrameByName(keyname)))
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
	totalHP = 200;
	HP = 200;
	SP = 200;
	speed = 10;
	jumpSpeed  = 10;
	moveRight = true;
	strcpy(roleName, "Role3");

	char plistFileName[100];
	
	sprintf(plistFileName,"character/%s.plist", roleName);

	cache = SpriteFrameCache::sharedSpriteFrameCache();
	cache->addSpriteFramesWithFile(plistFileName);
}

Role3* Role3::create()
{
	Role3* role3 = new Role3();

	char keyname[100];
	sprintf(keyname,"%sNormal1.png", role3->roleName);

	if(role3 && role3->initWithSpriteFrame(role3->cache->spriteFrameByName(keyname)))
	{
		role3->setAction(role3->cache);
		role3->autorelease();
		return role3;
	}

	return NULL;
}



//Role4
//--------------------------------------------------------------------------
//--------------------------------------------------------------------------

Role4::Role4()
{
	totalHP = 200;
	HP = 200;
	SP = 200;
	speed = 10;
	jumpSpeed  = 10;
	moveRight = true;
	strcpy(roleName, "Role4");

	char plistFileName[100];
	
	sprintf(plistFileName,"character/%s.plist", roleName);

	cache = SpriteFrameCache::sharedSpriteFrameCache();
	cache->addSpriteFramesWithFile(plistFileName);
}

Role4* Role4::create()
{
	Role4* role4 = new Role4();

	char keyname[100];
	sprintf(keyname,"%sNormal1.png", role4->roleName);

	if(role4 && role4->initWithSpriteFrame(role4->cache->spriteFrameByName(keyname)))
	{
		role4->setAction(role4->cache);
		role4->autorelease();
		return role4;
	}

	return NULL;
}