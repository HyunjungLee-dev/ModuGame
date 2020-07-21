#include "Animal.h"

#define DEFAULTX	10
#define DEFAULTY	105 
#define	SIZEY		140
#define SIZEX		140

void Animal::PointSet(DIRECTION  Holedirct)
{
	switch (Holedirct)
	{
	case EAST:
		m_Point.x =	 SIZEX * 2;
		m_Point.y =  SIZEY;
		break;
	case WEST:
		m_Point.x = 0;
		m_Point.y =  SIZEY;
		break;
	case NORTH:
		m_Point.x = SIZEX;
		m_Point.y = 0;
		break;
	case SOUTH:
		m_Point.x = SIZEX;
		m_Point.y = SIZEY *2;
		break;
	case NORTHWEST:
		m_Point.x = 0;
		m_Point.y = 0;
		break;
	case NORTHEAST:
		m_Point.x = SIZEX * 2;
		m_Point.y = 0;
		break;
	case SOUTHWEST:
		m_Point.x = 0;
		m_Point.y = SIZEY * 2;
		break;
	case SOUTHEAST:
		m_Point.x = SIZEX * 2;
		m_Point.y = SIZEY * 2;
		break;
	case NONDIRECTION:
		m_Point.x = SIZEX;
		m_Point.y = SIZEY;
		break;
	default:
		break;
	}

	m_Rect = { DEFAULTX + m_Point.x ,DEFAULTY + m_Point.y,DEFAULTX + m_Point.x + 120,DEFAULTY + m_Point.y + 140 };
}

void Animal::Motion()
{
	if (m_iExplosion < 0)
	{
		if (m_eState == ANIMALUP)
		{
			m_iMotionNum++;
			if (m_iMotionNum > 3)
			{
				m_eState = ANIMALDOWN;
				m_iMotionNum = 3;
			}
		}
		else if (m_eState == ANIMALDOWN || m_eState == EXPLOSION)
		{
			m_iMotionNum--;
			if (m_iMotionNum < -1)
			{
				m_iMotionNum = -1;
			}
		}
	}
}

void Mole::Init(DIRECTION  Holedirct)
{
	char ch[128];
	
	m_eAnimalType = MOLE;
	m_iMotionNum = -1;
	m_eState = ANIMALNONE;
	m_iExplosion = -1;


	int randNum = rand() % 100;

	if (randNum < 10)
		m_bHaveBomb = true;
	else
		m_bHaveBomb = false;

	for (int i = 0; i < 5; i++)
	{
		sprintf(ch, "res\\moleMotion0%d.bmp", i);
		string str(ch);
		m_pMole[i] = JEngine::ResoucesManager::GetInstance()->GetBitmap(str);
	}	
	PointSet(Holedirct);
}

void Mole::Draw()
{
	if (m_iMotionNum != -1)
	{
		if(m_iMotionNum == 3 && m_bHaveBomb == true)
			m_pMole[4]->Draw(DEFAULTX + m_Point.x, DEFAULTY + m_Point.y);
		else
			m_pMole[m_iMotionNum]->Draw(DEFAULTX + m_Point.x, DEFAULTY + m_Point.y);

		if (m_iExplosion > 2)
		{
			m_iExplosion = -1;
			m_eState = EXPLOSION;
		}
		else if (m_iExplosion != -1)
		{
			m_Effect->m_pExplosion[m_iExplosion]->Draw(DEFAULTX + m_Point.x, DEFAULTY + m_Point.y);
		}
	}

}

void Octopus::Init(DIRECTION  Holedirct)
{
	m_eAnimalType = OCTOPUS;
	m_iMotionNum = -1;
	m_eState = ANIMALNONE;
	m_iExplosion = -1;


	char ch[128];

	for (int i = 0; i < 4; i++)
	{
		if (i < 2)
		{
			sprintf(ch, "res\\ink0%d.bmp", i);
			string str(ch);
			m_pInk[i] = JEngine::ResoucesManager::GetInstance()->GetBitmap(str);
		}
		sprintf(ch, "res\\octopusMotion0%d.bmp", i);
		string str(ch);
		m_pOctopus[i] = JEngine::ResoucesManager::GetInstance()->GetBitmap(str);
	}

	PointSet(Holedirct);
}

void Octopus::Draw()
{
	if (m_iMotionNum != -1)
	{
		m_pOctopus[m_iMotionNum]->Draw(DEFAULTX + m_Point.x, DEFAULTY + m_Point.y);
		if (m_iExplosion > 2)
		{
			m_iExplosion = -1;
			m_eState = EXPLOSION;
		}
		else if (m_iExplosion != -1)
		{
			if(m_iExplosion == 0)
				m_Effect->m_pExplosion[m_iExplosion]->Draw(DEFAULTX + m_Point.x, DEFAULTY + m_Point.y);
			else
				m_pInk[m_iExplosion-1]->Draw( m_Point.x,  m_Point.y);
		}
	}

}

