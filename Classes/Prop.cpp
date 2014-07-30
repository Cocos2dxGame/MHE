#include "Prop.h"


Prop::Prop(void)
{
}


Prop::~Prop(void)
{
}

Prop* Prop::createProp(GameSceneType sceneType, PropType propType)
{
	Prop* newProp = Prop::create();
	int type = sceneType*5+propType;
	switch (type)
	{
	default:
		newProp->initWithFile("prop/pp_000.png");
		break;
	}
	return newProp;
}