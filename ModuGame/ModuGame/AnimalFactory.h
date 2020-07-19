#pragma once
#include"Animal.h"
class AnimalFactory
{
public:
	virtual Animal* CreateAnimal(string Name) = 0;
	AnimalFactory() {};
	~AnimalFactory() {};
};


class MoleFactory : public AnimalFactory
{
public:
	virtual Animal* CreateAnimal(string Name) override
	{
		return new Mole();
	}
};
