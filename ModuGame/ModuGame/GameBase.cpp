#include "GameBase.h"



GameBase::GameBase()
{
}

void GameBase::Init(HWND hWnd)
{
	m_fNextSceTime = 0.0f;
	m_bLoading = false;

	m_bGameEnd = false;
	m_bStart = false;
	m_bGamePlay = false;
	m_bTimeOver = false;
	m_bFeverTime = false;
	m_bFeverDown = false;

	m_eFeverState = BASIC;
	m_eUltraTime = ULTRA;

	m_fNextSceTime = 0.0f;
	m_iScore = 0;
	m_iFeverGauge = 0;
	m_iBonusPoint = 100;
	m_fUltraTime = 0.0f;

	Object::Init();
	m_LoadingSc.Init(hWnd);
}

void GameBase::FeverTimeDraw()
{

	if (m_bFeverDown)
	{
		m_pFever[BASIC]->StretchDraw(20, 55, m_iFeverGauge / 100.0f, 1);
		return;
	}

	if (m_bFeverTime)
	{
		if (m_fEffectTime > 0.1f)
		{
			m_pFeverEffect->Draw(0, 0);
			m_fEffectTime = 0.0f;
		}
	}

	if (m_eFeverState != ULTRA)
	{
		if (m_eFeverState > BASIC)
			m_pFever[BASIC]->Draw(20, 55);
		m_pFever[m_eFeverState]->StretchDraw(20, 55, m_iFeverGauge / 100.0f, 1);
	}
	else
	{
		if (m_fUltraTime > 10.0f)
		{
			if (m_eUltraTime == BASIC)
				m_pFever[m_eUltraTime]->StretchDraw(20, 55, m_iFeverGauge / 100.0f, 1);
		}
		else
			m_pFever[m_eUltraTime]->Draw(20, 55);
	}
}


void GameBase::FeverUpdate(float fETime)
{
	if (m_iFeverGauge > 100 && m_eFeverState != ULTRA)
	{
		int tmp = 100 - m_iFeverGauge;
		if (m_eFeverState == BASIC)
		{
			m_bFeverTime = true;
			m_eFeverState = SUPER;
		}
		else if (m_eFeverState == SUPER)
		{
			m_eFeverState = ULTRA;
			m_iFeverGauge = 99;
			return;
		}
		m_iFeverGauge = abs(tmp);
	}

	if (m_bFeverTime)
	{
		m_fEffectTime += fETime;
		if (m_eFeverState == ULTRA)
		{
			m_fUltraTime += fETime;
			m_fNextSceTime += fETime;
			if (m_fNextSceTime > 0.1f)
			{
				if (m_eUltraTime == ULTRA)
					m_eUltraTime = BASIC;
				else
					m_eUltraTime = ULTRA;
				m_fNextSceTime = 0.0f;
			}

			if (m_fUltraTime > 5.0f)
			{
				m_eUltraTime = BASIC;
				m_iFeverGauge = 99;
				m_bFeverDown = true;
			}
		}
	}
	else
		m_fEffectTime = 0.0f;
}


void GameBase::DownFeverGauge()
{
	m_iFeverGauge -= 3;
	if (m_iFeverGauge <= 0)
	{
		m_iFeverGauge = 0;
		m_eFeverState = BASIC;
		m_bFeverTime = false;
		m_fUltraTime = 0.0f;
		m_bFeverDown = false;
	}
}

void GameBase::GameEnd(GAME type,float fETime)
{
	if (m_fGameTime <= GetTickCount())
	{
		DownFeverGauge();
		m_bTimeOver = true;
		m_bFeverDown = true;
		m_fNextSceTime += fETime;
		if (m_fNextSceTime > 1.0f)
		{
			m_bStart = true;
		}
		if (m_bStart)
		{
			m_LoadingSc.Update(fETime);
			if (m_fNextSceTime > 4.0f)
			{
				if (m_fNextSceTime > 4.0f)
				{
					if (type == FLIGHTGAME)
					{
						if (m_iScore >= UserManager::GetInstance()->GetUser()->FlightScore)
							UserManager::GetInstance()->GetUser()->SetUser(type, m_iScore);
					}
					else if (type == PAPERGAME)
					{
						if (m_iScore >= UserManager::GetInstance()->GetUser()->PaperScore)
							UserManager::GetInstance()->GetUser()->SetUser(type, m_iScore);
					}
					else if (type == MOLEGAME)
					{
						if (m_iScore >= UserManager::GetInstance()->GetUser()->MoleScore)
							UserManager::GetInstance()->GetUser()->SetUser(MOLEGAME, m_iScore);
					}
					UserManager::GetInstance()->RankSort();
					UserManager::GetInstance()->Save();
					JEngine::SceneManager::GetInstance()->LoadScene(SCENE_INDEX_RANK);
				}
			}
			return;
		}
	}
}

void GameBase::FeverStateCheck(float fETime)
{
	if (m_bFeverDown)
		DownFeverGauge();
	else
		FeverUpdate(fETime);
}

void GameBase::GameStart(float fETime)
{
	if (m_bStart)
	{
		m_fNextSceTime += fETime;
		m_LoadingSc.Update(fETime);
		if (m_fNextSceTime > 3.0f)
		{
			m_bStart = false;
			m_bGamePlay = true;
			m_fGameTime = GetTickCount() + 45000;

			m_fNextSceTime = 0.0f;
		}
	}
}

void GameBase::DisplayDraw(HDC hdc)
{
	m_pFrame->Draw(0, 0);

	ScoreDraw(m_iScore);

	if (m_bTimeOver && m_iFeverGauge == 0)
	{
		m_pTimeOver->Draw(CLIENT_SIZE_WIDTH * 0.2, CLIENT_SIZE_HEIGHT * 0.4);
		if (m_bStart)
		{
			m_LoadingSc.Draw(hdc);
		}
		return;

	}

	GameTimeDraw(m_fGameTime);
	FeverTimeDraw();
}

void GameBase::LoadingDraw(HDC hdc)
{
	m_LoadingSc.Draw(hdc);
}

void GameBase::StarDraw(int textx, int texty, int starX, int starY)
{
	Object::StarDraw(m_iBonusPoint, textx, texty, starX, starY);
}


void GameBase::SetFeverGauge(int gauge, SETTER type)
{
	if (type == SET)
	{
		m_iFeverGauge = gauge;
	}
	else
		m_iFeverGauge += gauge;
}

void GameBase::SetBonusPoint(int point, SETTER type)
{
	if (type == SET)
	{
		m_iBonusPoint = point;
	}
	else
		m_iBonusPoint += point;
}

void GameBase::SetNextTime(int time, SETTER type)
{
	if (type == SET)
	{
		m_fNextSceTime = time;
	}
	else
		m_fNextSceTime += time;
}



GameBase::~GameBase()
{
}
