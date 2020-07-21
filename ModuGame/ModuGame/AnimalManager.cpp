#include "AnimalManager.h"




AnimalManager::AnimalManager()
{
}

void AnimalManager::Init()
{
	int Direction = EAST;

	for (int i = 0; i < 9; i++)
	{
		int RandNum = rand() % 2;
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

void AnimalManager::Reset(DIRECTION dirct)
{

	vector<Animal*>::iterator it;
	it = m_pAnimalList.begin() + dirct + 1;


	int RandNum = rand() % 2;
	switch ((ANIMALTYPE)RandNum)
	{
	case MOLE:
		m_pAnimalList.insert(it , new Mole);
		break;
	case OCTOPUS:
		m_pAnimalList.insert(it , new Octopus);
		break;
	default:
		break;
	}

	delete m_pAnimalList[dirct];
	m_pAnimalList.erase(m_pAnimalList.begin() + dirct);

	m_pAnimalList[dirct]->Init(dirct);
}

bool AnimalManager::CollisionUpdate(JEngine::POINT mpoint)
{
	for (vector<Animal*>::iterator iter = m_pAnimalList.begin(); iter != m_pAnimalList.end(); iter++)
	{
		JEngine::RECT AnimalRect;
		AnimalRect = (*iter)->GetRect();

		if ((*iter)->GetMotionNum() >= 2 && AnimalRect.isPtin(mpoint))
		{
			(*iter)->SetExplosion();
			return true;
		}
	}
	return false;
}

	 
void AnimalManager:: Draw()
 {
	for (vector<Animal*>::iterator iter = m_pAnimalList.begin(); iter != m_pAnimalList.end(); iter++)
	{
		(*iter)->Draw();
	}
 }

void AnimalManager::ExplosionDraw(float *fETime)
{
	for (vector<Animal*>::iterator iter = m_pAnimalList.begin(); iter != m_pAnimalList.end(); iter++)
	{
		if ((*iter)->GetExplosion() >= 0)
		{
			if ((*iter)->GetType() == OCTOPUS && (*iter)->GetExplosion() == 2)
			{
				if(*fETime > 0.4f)
				{
					(*iter)->SetExplosion();
					*fETime = 0.0f;
				}
			}
			else
			{
				if (*fETime > 0.1f)
				{
					(*iter)->SetExplosion();
					*fETime = 0.0f;
				}
			}
		}
	}
}

void AnimalManager::MotionUpdate()
{
	for (vector<Animal*>::iterator iter = m_pAnimalList.begin(); iter != m_pAnimalList.end(); iter++)
	{
		if ((*iter)->GetState() != ANIMALNONE)
			(*iter)->Motion();
	}
}

void AnimalManager::MotionSet(int Direction)
{
		if (m_pAnimalList[Direction]->GetState() == ANIMALNONE)
			m_pAnimalList[Direction]->SetState(ANIMALUP);
}

void AnimalManager::Update()
{
	//폭발한 동물 초기화
	for (int i = 0; i < m_pAnimalList.size(); i++)
	{
		if (m_pAnimalList[i]->GetState() == EXPLOSION || 
			(m_pAnimalList[i]->GetMotionNum() == -1 && m_pAnimalList[i]->GetState() == ANIMALDOWN))
		{
			Reset((DIRECTION)i);
		}
	}

	//랜덤 위치


}

void AnimalManager::Release()
{
	// 리스트 동적할당 해제
	for (vector<Animal*>::iterator iter = m_pAnimalList.begin(); iter != m_pAnimalList.end(); iter++)
	{
		delete (*iter);
	}
	m_pAnimalList.clear();
}


AnimalManager::~AnimalManager()
{
	Release();
}
