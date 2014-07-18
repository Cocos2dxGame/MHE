#include"NPC.h"
USING_NS_CC;

NPC::NPC()
{
	strcpy(roleName, "Role1");

	char plistFileName[100];
	sprintf(plistFileName,"character/%s.plist", roleName);  
	cache = SpriteFrameCache::sharedSpriteFrameCache();
	cache->addSpriteFramesWithFile(plistFileName);
}

NPC::~NPC()
{
}


//��һ��npc
NPC1::NPC1()
{
	strcpy(roleName, "Role2");

	char plistFileName[100];
	sprintf(plistFileName,"character/%s.plist", roleName);  
	cache = SpriteFrameCache::sharedSpriteFrameCache();
	cache->addSpriteFramesWithFile(plistFileName);
}

NPC1::~NPC1()
{
}

bool NPC1::init()
{
	do 
	{
		CC_BREAK_IF(!Person::initWithSpriteFrameName("Role2Normal1.png"));

		CallFunc *callbackNormal = CallFunc::create(std::bind(&NPC1::normalAction, this));
		CallFunc *callbackJumpEnd = CallFunc::create(std::bind(&NPC1::jumpActionEnd, this));

		Size visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleOrigin();

		//����״̬�¶���
		const char* normalPng = String::createWithFormat("%s%s", roleName, "Normal")->getCString();
		Animation* normalAnimation = createAnimation(normalPng,6,12);
		setNormalAction(RepeatForever::create(Animate::create(normalAnimation)));

		//�ƶ�״̬��
		//const char* movePng = String::createWithFormat(roleName,"Move")->getCString();
		//Animation* moveAnimation = createAnimation(movePng,6,12);
		setMoveAction(RepeatForever::create(Animate::create(normalAnimation)));

		//����״̬�¶���
		const char* firePng = String::createWithFormat("%s%s", roleName, "Fire")->getCString();
		Animation* fireAnimation = createAnimation(firePng,2,10);
		setFireAction(Sequence::create(Animate::create(fireAnimation), callbackNormal, NULL));

		//�ܵ�����״̬�¶���
		const char* attackedPng = String::createWithFormat("%s%s", roleName, "Attacked")->getCString();
		Animation* attackedAnimation = createAnimation(attackedPng,3,12);
		setAttackedAction(Sequence::create(Animate::create(attackedAnimation), callbackNormal, NULL));

		//��Ծ״̬�¶���
		auto actionBy = JumpBy::create(2, Vec2(0,0), visibleSize.height/4, 1);
		//auto actionByBack = actionBy->reverse();
		setJumpAction(Sequence::create(actionBy, callbackNormal, NULL));
		
		setTotalHP(100);
		setTotalSP(100);

		setHP(100);
		setSP(0);

		return true;
	}while(0);

	return false;
}

//�ڶ���npc
NPC2::NPC2()
{
	strcpy(roleName, "Role3");

	char plistFileName[100];
	sprintf(plistFileName,"character/%s.plist", roleName);  
	cache = SpriteFrameCache::sharedSpriteFrameCache();
	cache->addSpriteFramesWithFile(plistFileName);
}

NPC2::~NPC2()
{
}

bool NPC2::init()
{
	do 
	{
		CC_BREAK_IF(!Person::initWithSpriteFrameName("Role3Normal1.png"));

		CallFunc *callbackNormal = CallFunc::create(std::bind(&NPC2::normalAction, this));
		CallFunc *callbackJumpEnd = CallFunc::create(std::bind(&NPC2::jumpActionEnd, this));

		Size visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleOrigin();

		//����״̬�¶���
		const char* normalPng = String::createWithFormat("%s%s", roleName, "Normal")->getCString();
		Animation* normalAnimation = createAnimation(normalPng,6,12);
		setNormalAction(RepeatForever::create(Animate::create(normalAnimation)));

		//�ƶ�״̬��
		//const char* movePng = String::createWithFormat(roleName,"Move")->getCString();
		//Animation* moveAnimation = createAnimation(movePng,6,12);
		setMoveAction(RepeatForever::create(Animate::create(normalAnimation)));

		//����״̬�¶���
		const char* firePng = String::createWithFormat("%s%s", roleName, "Fire")->getCString();
		Animation* fireAnimation = createAnimation(firePng,2,10);
		setFireAction(Sequence::create(Animate::create(fireAnimation), callbackNormal, NULL));

		//�ܵ�����״̬�¶���
		const char* attackedPng = String::createWithFormat("%s%s", roleName, "Attacked")->getCString();
		Animation* attackedAnimation = createAnimation(attackedPng,3,12);
		setAttackedAction(Sequence::create(Animate::create(attackedAnimation), callbackNormal, NULL));

		//��Ծ״̬�¶���
		auto actionBy = JumpBy::create(2, Vec2(0,0), visibleSize.height/4, 1);
		//auto actionByBack = actionBy->reverse();
		setJumpAction(Sequence::create(actionBy, callbackNormal, NULL));
		
		setTotalHP(100);
		setTotalSP(100);

		setHP(100);
		setSP(0);

		return true;
	}while(0);

	return false;
}

//������
NPC3::NPC3()
{
	strcpy(roleName, "Role4");

	char plistFileName[100];
	sprintf(plistFileName,"character/%s.plist", roleName);  
	cache = SpriteFrameCache::sharedSpriteFrameCache();
	cache->addSpriteFramesWithFile(plistFileName);
}

NPC3::~NPC3()
{
}

bool NPC3::init()
{
	do 
	{
		CC_BREAK_IF(!Person::initWithSpriteFrameName("Role4Normal1.png"));

		CallFunc *callbackNormal = CallFunc::create(std::bind(&NPC3::normalAction, this));
		CallFunc *callbackJumpEnd = CallFunc::create(std::bind(&NPC3::jumpActionEnd, this));

		Size visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleOrigin();

		//����״̬�¶���
		const char* normalPng = String::createWithFormat("%s%s", roleName, "Normal")->getCString();
		Animation* normalAnimation = createAnimation(normalPng,6,12);
		setNormalAction(RepeatForever::create(Animate::create(normalAnimation)));

		//�ƶ�״̬��
		//const char* movePng = String::createWithFormat(roleName,"Move")->getCString();
		//Animation* moveAnimation = createAnimation(movePng,6,12);
		setMoveAction(RepeatForever::create(Animate::create(normalAnimation)));

		//����״̬�¶���
		const char* firePng = String::createWithFormat("%s%s", roleName, "Fire")->getCString();
		Animation* fireAnimation = createAnimation(firePng,2,10);
		setFireAction(Sequence::create(Animate::create(fireAnimation), callbackNormal, NULL));

		//�ܵ�����״̬�¶���
		const char* attackedPng = String::createWithFormat("%s%s", roleName, "Attacked")->getCString();
		Animation* attackedAnimation = createAnimation(attackedPng,3,12);
		setAttackedAction(Sequence::create(Animate::create(attackedAnimation), callbackNormal, NULL));

		//��Ծ״̬�¶���
		auto actionBy = JumpBy::create(2, Vec2(0,0), visibleSize.height/4, 1);
		//auto actionByBack = actionBy->reverse();
		setJumpAction(Sequence::create(actionBy, callbackNormal, NULL));
		
		setTotalHP(100);
		setTotalSP(100);

		setHP(100);
		setSP(0);

		return true;
	}while(0);

	return false;
}