#ifndef __ROLE__H__
#define __ROLE__H__

#include "Person.h"

class Role1 : public Person
{
public:
	Role1();
	
	static Role1* create();

};


class Role2: public Person
{
public:
	Role2();

	static Role2* create();

};


class Role3: public Person
{
public:
	Role3();
	static Role3* create();
};


#endif __ROLE__H__