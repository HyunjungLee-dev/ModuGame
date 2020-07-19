#pragma once
#include "JEngine.h"
#include"Label.h"
#include"defines.h"
#include"ResoucesManager.h"
class Animal
{
protected:
	string m_strName;
	JEngine::POINT m_Point;
	JEngine::RECT m_Rect;
public:
	virtual void Init(DIRECTION  Holedirct) {};
	void PointSet(DIRECTION  Holedirct);
	virtual void Draw(int motionNum) {};
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
	virtual void Draw(int motionNum) override;
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
	virtual void Draw(int motionNum) override;
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