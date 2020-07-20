#include "AnimalList.h"



AnimalList::AnimalList()
{
}

void AnimalList::Init()
{
	//9�� �ʱ��Ҵ�
	//����(���� �δ���)

	int Direction = EAST;

	for (int i = 0; i < 9; i++)
	{
		int RandNum = rand() % 1;
		switch ((ANIMALTYPE)RandNum)
		{
		case MOLE:
			m_pAnimalList.push_back(new Mole);
			break;
		case OCTOPUS:
			m_pAnimalList.push_back(new Octopus);
			break;
		default:
			break;
		}

		m_pAnimalList.back()->Init((DIRECTION)Direction);
		Direction++;
	}
}

	 
void AnimalList:: Draw()
 {
	// ����Ʈ ��ü ��ο�
	//���� Ȯ��

	for (list<Animal*>::iterator iter = m_pAnimalList.begin(); iter != m_pAnimalList.end(); iter++)
	{
		(*iter)->Draw();
	}
	
 }

void AnimalList::Update(POINT mpoint)
{
	// �ӵ�  , ����	  (��� ++)
	// ���콺 ������ �浹 üũ

}

void AnimalList::Release()
{
	// ����Ʈ �����Ҵ� ����
	for (list<Animal*>::iterator iter = m_pAnimalList.begin(); iter != m_pAnimalList.end(); iter++)
	{
		delete (*iter);
	}
	m_pAnimalList.clear();
}


AnimalList::~AnimalList()
{
	Release();
}
