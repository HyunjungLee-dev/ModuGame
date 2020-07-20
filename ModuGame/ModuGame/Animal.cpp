#include "Animal.h"





void Animal::PointSet(DIRECTION  Holedirct)
{
	switch (Holedirct)
	{
	case EAST:
		break;
	case WEST:
		break;
	case NORTH:
		m_Point.x = 16 * 9;
		m_Point.y = 120;
		break;
	case SOUTH:
		break;
	case NORTHWEST:
		break;
	case NORTHEAST:
		break;
	case SOUTHWEST:
		break;
	case SOUTHEAST:
		break;
	case NONDIRECTION:
		break;
	default:
		break;
	}
}

void Mole::Init(DIRECTION  Holedirct)
{
	char ch[128];
	
	m_eAnimalType = MOLE;
	m_iMotionNum = 0;

	for (int i = 0; i < 6; i++)
	{
		int randNum = rand() % 100;

		sprintf(ch, "res\\moleMotion0%d.bmp", i);
		string str(ch);
		m_pMole[i] = JEngine::ResoucesManager::GetInstance()->GetBitmap(str);

		if (randNum < 10)
			m_bHaveBomb = true;
		else
			m_bHaveBomb = false;

		PointSet(Holedirct);
	}
}

void Mole::Draw()
{

	switch (m_iMotionNum)
	{
	case 0:
		m_pMole[m_iMotionNum]->Draw(m_Point.x, m_Point.y * 1.6);
		break;
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
		m_pMole[m_iMotionNum]->Draw(m_Point.x, m_Point.y);
		break;
	default:
		break;
	}
}

void Octopus::Init(DIRECTION  Holedirct)
{
	m_eAnimalType = OCTOPUS;
	m_iMotionNum = 0;

	char ch[128];

	for (int i = 0; i < 2; i++)
	{
		int randNum = rand() % 100;

		sprintf(ch, "res\\octopusMotion%d.bmp", i);
		string str(ch);
		m_pOctopus[i] = JEngine::ResoucesManager::GetInstance()->GetBitmap(str);
	}

	PointSet(Holedirct);
}

void Octopus::Draw()
{
	switch (m_iMotionNum)
	{
	case 0:
	case 1:
		m_pOctopus[m_iMotionNum]->Draw(m_Point.x, m_Point.y);
		break;
	default:
		break;
	}
}

