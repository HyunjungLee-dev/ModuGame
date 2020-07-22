#pragma once
#include "JEngine.h"
#include"Label.h"
#include"defines.h"
#include"ResoucesManager.h"
#include"Object.h"

enum ANIMALTYPE
{
	MOLE,
	OCTOPUS,
	BOMBMOLE,
	NONETYPE,
};




class Animal  
{
protected:
	ANIMALSTATE m_eState;
	ANIMALTYPE m_eAnimalType;
	JEngine::POINT m_Point;
	JEngine::RECT m_Rect;
	int m_iMotionNum;
	int m_iExplosion;
	Object* m_Effect;
public:
	virtual void Init(DIRECTION  Holedirct) = 0;
	virtual void Draw() = 0;

	void PointSet(DIRECTION  Holedirct);
	void Motion();

	JEngine::RECT GetRect() { return m_Rect; }
	ANIMALSTATE GetState() { return m_eState; }
	int GetExplosion() { return m_iExplosion; }
	ANIMALTYPE GetType() { return m_eAnimalType; }

	void SetState(ANIMALSTATE state) { m_eState = state; }
	void SetExplosion() { m_iExplosion ++; }

	int GetMotionNum() { return m_iMotionNum; }

	Animal() { 
		m_Effect =  new Object;
		m_Effect->Init();
	};
	virtual ~Animal() {	delete m_Effect	;};
};

class  Mole : public Animal
{
private:
	bool	m_bHaveBomb; 
	bool	m_bHaveStar;
	JEngine::BitMap*	m_pMole[6];
public:
	virtual void Init(DIRECTION  Holedirct) override;
	virtual void Draw() override;
	void StarDraw(int BonusNum);
	bool GethaveBomb() { return m_bHaveBomb; }
	Mole() {};
	virtual ~Mole() {};


};

class  Octopus  : public Animal
{
private:
	JEngine::BitMap*	m_pOctopus[4];
	JEngine::BitMap*	m_pInk[2];
public:
	virtual void Init(DIRECTION  Holedirct) override;
	virtual void Draw() override;
	Octopus() {};
	virtual ~Octopus() {};


};

