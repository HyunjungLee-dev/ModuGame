#pragma once
#include "JEngine.h"
#include"Label.h"
#include"defines.h"
#include"ResoucesManager.h"

enum ANIMALTYPE
{
	MOLE,
	OCTOPUS,
	BOMBMOLE,
	NONETYPE,
};

struct EffectObj
{
	JEngine::BitMap*	m_pFever[3];
	JEngine::BitMap*    m_pExplosion[3];
	JEngine::BitMap*	m_pBonusStar[3];
	JEngine::Label*		m_pBonusPoint;

	void Init()
	{
		m_pExplosion[0] = JEngine::ResoucesManager::GetInstance()->GetBitmap("res\\explosion1.bmp");
		m_pExplosion[1] = JEngine::ResoucesManager::GetInstance()->GetBitmap("res\\explosion2.bmp");
		m_pExplosion[2] = JEngine::ResoucesManager::GetInstance()->GetBitmap("res\\explosion3.bmp");

		m_pFever[0] = JEngine::ResoucesManager::GetInstance()->GetBitmap("res\\Fever1.bmp");
		m_pFever[1] = JEngine::ResoucesManager::GetInstance()->GetBitmap("res\\Fever2.bmp");
		m_pFever[2] = JEngine::ResoucesManager::GetInstance()->GetBitmap("res\\Fever3.bmp");

		m_pBonusStar[0] = JEngine::ResoucesManager::GetInstance()->GetBitmap("res\\FlightGameStar1.bmp");
		m_pBonusStar[1] = JEngine::ResoucesManager::GetInstance()->GetBitmap("res\\FlightGameStar2.bmp");
		m_pBonusStar[2] = JEngine::ResoucesManager::GetInstance()->GetBitmap("res\\FlightGameStar3.bmp");

		m_pBonusPoint = new JEngine::Label();
	}
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
	EffectObj* m_Effect;
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
		m_Effect =  new EffectObj;
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

private:

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

private:

};



//1. 총 6마리
// 게임씬에서 list : 메모리풀...일단 리스트로
//
//2. 랜덤 동물
//- 초기 설정 한번(init)
//- 죽으면 다시 할당(동물,위치...)
//
//3. 랜덤 위치
//- 업데이트
//->나왔다가 들어가면 위치 랜덤으로 다시 설정함
//
//4. 피버 일때만 스타 등장
//
//5. 충돌(마우스로 동물 rect)
//- 폭탄 두더지 : 모든 두더지 터짐(점수 두더지 나와있는 마리수만큼)
//- 문어 : 먹물
//- 일단 두더지 : 점수(9점)