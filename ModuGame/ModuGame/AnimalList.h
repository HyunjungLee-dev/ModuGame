#pragma once
#include"Animal.h"
#include<list>


class AnimalList  : public	Animal
{
public:
	AnimalList();
	virtual ~AnimalList();

	virtual void Init(DIRECTION  Holedirct) final {};
	void Init();
	virtual void Draw() override;
	void Update(POINT mpoint);
	void Release();

private:
	list<Animal*> m_pAnimalList;



};

