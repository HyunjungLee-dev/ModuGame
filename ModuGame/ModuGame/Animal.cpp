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
		break;
	case SOUTH:
		break;
	case NORTHWEST:
		m_Point.x = 20;
		m_Point.y = 112;
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
	
	m_strName = "Mole";

	for (int i = 0; i < 6; i++)
	{
		int randNum = rand() % 100;

		sprintf(ch, "res\\moleMotion0%d", i);
		string str(ch);
		m_pMole[i] = JEngine::ResoucesManager::GetInstance()->GetBitmap(str);

		if (randNum < 10)
			m_bHaveBomb = true;
		else
			m_bHaveBomb = false;

		PointSet(Holedirct);
	}
}

void Mole::Draw(int motionNum)
{

	m_strName = "Octopus";

	switch (motionNum)
	{
	case 0:
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
		m_pMole[motionNum]->Draw(m_Point.x, m_Point.y);
		break;
	default:
		break;
	}
}

void Octopus::Init(DIRECTION  Holedirct)
{
	char ch[128];

	for (int i = 0; i < 2; i++)
	{
		int randNum = rand() % 100;

		sprintf(ch, "res\\octopusMotion%d", i);
		string str(ch);
		m_pOctopus[i] = JEngine::ResoucesManager::GetInstance()->GetBitmap(str);
	}

	PointSet(Holedirct);
}

void Octopus::Draw(int motionNum)
{
	switch (motionNum)
	{
	case 0:
	case 1:
		m_pOctopus[motionNum]->Draw(m_Point.x, m_Point.y);
		break;
	default:
		break;
	}
}

