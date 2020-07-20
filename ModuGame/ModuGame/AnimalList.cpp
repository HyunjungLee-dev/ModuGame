#include "AnimalList.h"



AnimalList::AnimalList()
{
}

void AnimalList::Init()
{
	//9개 초기할당
	//랜덤(문어 두더지)

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
	// 리스트 전체 드로우
	//폭발 확인

	for (list<Animal*>::iterator iter = m_pAnimalList.begin(); iter != m_pAnimalList.end(); iter++)
	{
		(*iter)->Draw();
	}
	
 }

void AnimalList::Update(POINT mpoint)
{
	// 속도  , 동작	  (모션 ++)
	// 마우스 포인터 충돌 체크

}

void AnimalList::Release()
{
	// 리스트 동적할당 해제
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
