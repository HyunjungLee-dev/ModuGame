#pragma once
#include "JEngine.h"
#include"Label.h"
#include"defines.h"
#include"ResoucesManager.h"

enum ANIMALTYPE
{
	MOLE,
	OCTOPUS
};


class Animal  //메모리풀 클래스 상속 | 오퍼레이터 new,del
{
protected:
	ANIMALTYPE m_eAnimalType;
	JEngine::POINT m_Point;
	JEngine::RECT m_Rect;
	int m_iMotionNum;
public:
	virtual void Init(DIRECTION  Holedirct) = 0;
	void PointSet(DIRECTION  Holedirct);
	virtual void Draw() = 0;
	Animal() {};
	virtual ~Animal() {};
};

class  Mole : public Animal
{
private:
	bool	m_bHaveBomb; // 랜덤확률 이용
	JEngine::BitMap*	m_pMole[6];
public:
	virtual void Init(DIRECTION  Holedirct) override;
	virtual void Draw() override;
	Mole() {};
	virtual ~Mole() {};

private:

};

class  Octopus  : public Animal
{
private:
	JEngine::BitMap*	m_pOctopus[2];
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