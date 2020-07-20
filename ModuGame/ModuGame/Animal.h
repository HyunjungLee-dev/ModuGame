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


class Animal  //�޸�Ǯ Ŭ���� ��� | ���۷����� new,del
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
	bool	m_bHaveBomb; // ����Ȯ�� �̿�
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



//1. �� 6����
// ���Ӿ����� list : �޸�Ǯ...�ϴ� ����Ʈ��
//
//2. ���� ����
//- �ʱ� ���� �ѹ�(init)
//- ������ �ٽ� �Ҵ�(����,��ġ...)
//
//3. ���� ��ġ
//- ������Ʈ
//->���Դٰ� ���� ��ġ �������� �ٽ� ������
//
//4. �ǹ� �϶��� ��Ÿ ����
//
//5. �浹(���콺�� ���� rect)
//- ��ź �δ��� : ��� �δ��� ����(���� �δ��� �����ִ� ��������ŭ)
//- ���� : �Թ�
//- �ϴ� �δ��� : ����(9��)