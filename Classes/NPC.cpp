#include"NPC.h"
USING_NS_CC;

NPC::NPC()
{
	strcpy(roleName, "Role1");
	strcpy(attackedSound, "npcAttacked.wav");

	char plistFileName[100];
	sprintf(plistFileName,"character/%s.plist", roleName);  
	cache = SpriteFrameCache::sharedSpriteFrameCache();
	cache->addSpriteFramesWithFile(plistFileName);

	_faceRight = false;
}

NPC::~NPC()
{
}


//��һ��npc
NPC1::NPC1()
{
	strcpy(roleName, "Role2");
	strcpy(attackedSound, "npcAttacked.wav");

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

		//����ס״̬��
		const char* frozenPng = String::createWithFormat("%s%s", roleName, "Frozen")->getCString();
		Animation* frozenAnimation = createAnimation(frozenPng,2,10);
		setFrozenAction(Sequence::create(Animate::create(frozenAnimation), DelayTime::create(5), callbackNormal, NULL));

		//���ڶ���ס״̬��
		const char* holePng = String::createWithFormat("%s%s", roleName, "Hole")->getCString();
		Animation* holeAnimation = createAnimation(holePng,2,10);
		setHoleAction(Sequence::create(Animate::create(holeAnimation), DelayTime::create(5), callbackNormal, NULL));

		//����ס״̬��
		const char* netPng = String::createWithFormat("%s%s", roleName, "Net")->getCString();
		Animation* netAnimation = createAnimation(netPng,2,10);
		setNetAction(Sequence::create(Animate::create(netAnimation), DelayTime::create(5), callbackNormal, NULL));

		//��Ծ״̬�¶���
		auto actionBy = JumpBy::create(1, Vec2(0,0), visibleSize.height/4, 1);
		//auto actionByBack = actionBy->reverse();
		setJumpAction(Sequence::create(actionBy, callbackJumpEnd, NULL));

		//ʤ��״̬��
		const char* victoryPng = String::createWithFormat("%s%s", roleName, "Victory")->getCString();
		Animation* victoryAnimation = createAnimation(victoryPng,2,10);
		setVictoryAction(Sequence::create(Animate::create(victoryAnimation), DelayTime::create(5), NULL));

		//ʧ��״̬��
		const char* failPng = String::createWithFormat("%s%s", roleName, "Failure")->getCString();
		Animation* failAnimation = createAnimation(failPng,2,10);
		setFailAction(Sequence::create(Animate::create(failAnimation), DelayTime::create(5), NULL));

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
	strcpy(attackedSound, "npcAttacked.wav");

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

		//����ס״̬��
		const char* frozenPng = String::createWithFormat("%s%s", roleName, "Frozen")->getCString();
		Animation* frozenAnimation = createAnimation(frozenPng,2,10);
		setFrozenAction(Sequence::create(Animate::create(frozenAnimation), DelayTime::create(5), callbackNormal, NULL));

		//���ڶ���ס״̬��
		const char* holePng = String::createWithFormat("%s%s", roleName, "Hole")->getCString();
		Animation* holeAnimation = createAnimation(holePng,2,10);
		setHoleAction(Sequence::create(Animate::create(holeAnimation), DelayTime::create(5), callbackNormal, NULL));

		//����ס״̬��
		const char* netPng = String::createWithFormat("%s%s", roleName, "Net")->getCString();
		Animation* netAnimation = createAnimation(netPng,2,10);
		setNetAction(Sequence::create(Animate::create(netAnimation), DelayTime::create(5), callbackNormal, NULL));

		//��Ծ״̬�¶���
		auto actionBy = JumpBy::create(1, Vec2(0,0), visibleSize.height/4, 1);
		//auto actionByBack = actionBy->reverse();
		setJumpAction(Sequence::create(actionBy, callbackJumpEnd, NULL));

		//ʤ��״̬��
		const char* victoryPng = String::createWithFormat("%s%s", roleName, "Victory")->getCString();
		Animation* victoryAnimation = createAnimation(victoryPng,2,10);
		setVictoryAction(Sequence::create(Animate::create(victoryAnimation), DelayTime::create(5), NULL));

		//ʧ��״̬��
		const char* failPng = String::createWithFormat("%s%s", roleName, "Failure")->getCString();
		Animation* failAnimation = createAnimation(failPng,2,10);
		setFailAction(Sequence::create(Animate::create(failAnimation), DelayTime::create(5), NULL));
		
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
	strcpy(attackedSound, "npcAttacked.wav");

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

		//����ס״̬��
		const char* frozenPng = String::createWithFormat("%s%s", roleName, "Frozen")->getCString();
		Animation* frozenAnimation = createAnimation(frozenPng,2,10);
		setFrozenAction(Sequence::create(Animate::create(frozenAnimation), DelayTime::create(5), callbackNormal, NULL));

		//���ڶ���ס״̬��
		const char* holePng = String::createWithFormat("%s%s", roleName, "Hole")->getCString();
		Animation* holeAnimation = createAnimation(holePng,2,10);
		setHoleAction(Sequence::create(Animate::create(holeAnimation), DelayTime::create(5), callbackNormal, NULL));

		//����ס״̬��
		const char* netPng = String::createWithFormat("%s%s", roleName, "Net")->getCString();
		Animation* netAnimation = createAnimation(netPng,2,10);
		setNetAction(Sequence::create(Animate::create(netAnimation), DelayTime::create(5), callbackNormal, NULL));

		//��Ծ״̬�¶���
		auto actionBy = JumpBy::create(1, Vec2(0,0), visibleSize.height/4, 1);
		//auto actionByBack = actionBy->reverse();
		setJumpAction(Sequence::create(actionBy, callbackJumpEnd, NULL));

		//ʤ��״̬��
		const char* victoryPng = String::createWithFormat("%s%s", roleName, "Victory")->getCString();
		Animation* victoryAnimation = createAnimation(victoryPng,2,10);
		setVictoryAction(Sequence::create(Animate::create(victoryAnimation), DelayTime::create(5), NULL));

		//ʧ��״̬��
		const char* failPng = String::createWithFormat("%s%s", roleName, "Failure")->getCString();
		Animation* failAnimation = createAnimation(failPng,2,10);
		setFailAction(Sequence::create(Animate::create(failAnimation), DelayTime::create(5), NULL));
		
		setTotalHP(100);
		setTotalSP(100);

		setHP(100);
		setSP(0);

		return true;
	}while(0);

	return false;
}