#include "MoleScene.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "UIManager.h"
#include "ResoucesManager.h"
#include <Windows.h>
#include "defines.h"

MoleScene::MoleScene()
{
}

MoleScene::~MoleScene()
{
}

void MoleScene::SetMember()
{
	m_fNextSceTime = 0.0f;
	m_bLoading = false;


	m_bStart = false;
	m_bGamePlay = false;
	m_bTimeOver = false;
	m_bExplosion = false;
	m_bFeverTime = false;
	m_bFeverDown = false;


	m_eFeverState = BASIC;
	m_eUltraTime = ULTRA;

	m_fNextSceTime = 0.0f;
	m_fExplosionTime = 0.0f;
	m_iScore = 0;
	m_iFeverGauge = 0;
	m_iBonusPoint = 100;
}

void MoleScene::Init(HWND hWnd)
{
	SetMember();


	m_LoadingSc.Init(hWnd);


	JEngine::InputManager::GetInstance()->Clear();
	JEngine::InputManager::GetInstance()->RegistKeyCode(VK_SPACE);
	JEngine::InputManager::GetInstance()->RegistKeyCode(VK_ESCAPE);
	JEngine::InputManager::GetInstance()->RegistKeyCode(VK_LEFT);
	JEngine::InputManager::GetInstance()->RegistKeyCode(VK_RIGHT);
	JEngine::InputManager::GetInstance()->RegistKeyCode(VK_UP);
	JEngine::InputManager::GetInstance()->RegistKeyCode(VK_DOWN);
	JEngine::InputManager::GetInstance()->RegistKeyCode(VK_LBUTTON);

	m_pFrame = JEngine::ResoucesManager::GetInstance()->GetBitmap("res\\FlightGameBackTra.bmp");
	m_pBack = JEngine::ResoucesManager::GetInstance()->GetBitmap("res\\whack_a_moleMap.bmp");
	m_pRule = JEngine::ResoucesManager::GetInstance()->GetBitmap("res\\Whack_a_MoleRule.bmp");


	m_pTimeBar = JEngine::ResoucesManager::GetInstance()->GetBitmap("res\\ColoredPaperTimeBar.bmp");
	m_pTimeOver = JEngine::ResoucesManager::GetInstance()->GetBitmap("res\\TimeOver.bmp");
	m_pExplosion[0] = JEngine::ResoucesManager::GetInstance()->GetBitmap("res\\explosion1.bmp");
	m_pExplosion[1] = JEngine::ResoucesManager::GetInstance()->GetBitmap("res\\explosion2.bmp");
	m_pExplosion[2] = JEngine::ResoucesManager::GetInstance()->GetBitmap("res\\explosion3.bmp");
	m_pFever[0] = JEngine::ResoucesManager::GetInstance()->GetBitmap("res\\Fever1.bmp");
	m_pFever[1] = JEngine::ResoucesManager::GetInstance()->GetBitmap("res\\Fever2.bmp");
	m_pFever[2] = JEngine::ResoucesManager::GetInstance()->GetBitmap("res\\Fever3.bmp");
	m_pFeverEffect = JEngine::ResoucesManager::GetInstance()->GetBitmap("res\\FeverEffect3.bmp");
	m_pTimeOver = JEngine::ResoucesManager::GetInstance()->GetBitmap("res\\TimeOver.bmp");


	m_pGameTime = new JEngine::Label();
	m_pScore = new JEngine::Label();
	m_pCursor = new JEngine::Label();

	m_pAnimalList = new AnimalList;
	m_pAnimalList->Init();

	JEngine::UIManager::GetInstance()->AddButton(CLIENT_SIZE_WIDTH * 0.212, CLIENT_SIZE_HEIGHT * 0.845, "res\\check00.bmp", std::bind(&MoleScene::OnSelectCheck, this));

	m_LoadingSc.Init(hWnd);
}

bool MoleScene::Input(float fETime)
{
	return false;
}



void MoleScene::Update(float fETime)
{
	static float m_fScoreTime = 0.0f;

	if (m_bGamePlay)
	{
		m_MousePoint = JEngine::InputManager::GetInstance()->GetMousePoint();
		
		if (m_fGameTime <= GetTickCount())
		{
			DownFeverGauge();
			m_bTimeOver = true;
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
					if (m_iScore >= UserManager::GetInstance()->GetUser()->MoleScore)
						UserManager::GetInstance()->GetUser()->SetUser(MOLEGAME, m_iScore);
					UserManager::GetInstance()->RankSort();
					UserManager::GetInstance()->Save();
					JEngine::SceneManager::GetInstance()->LoadScene(SCENE_INDEX_RANK);
					SetMember();
				}
			}
			return;
		}

		

		//Fever
		/*if (m_bFeverDown)
			DownFeverGauge();
		else
			FeverUpdate(fETime);

		m_fScoreTime += fETime;

		if (m_fScoreTime > 1.0f && !m_bExplosion)
		{
			m_iScore += 3;
			if (m_eFeverState != ULTRA)
				m_iFeverGauge += 5;
			m_fScoreTime = 0.0f;

		}*/


	}



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

void MoleScene::DownFeverGauge()
{
	m_iFeverGauge -= 1;
	if (m_iFeverGauge <= 0)
	{
		m_iFeverGauge = 0;
		m_eFeverState = BASIC;
		m_bFeverTime = false;
		m_fUltraTime = 0.0f;
		m_bFeverDown = false;
	}
}

void MoleScene::FeverUpdate(float fETime)
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
				DownFeverGauge();
			}
		}
	}
	else
		m_fEffectTime = 0.0f;
}

void MoleScene::ScoreDraw()
{
	m_pScore->Init(to_string(m_iScore), CLIENT_SIZE_WIDTH * 0.48, CLIENT_SIZE_HEIGHT * 0.03, DT_CENTER | DT_WORDBREAK);
	m_pScore->Draw();
}

void MoleScene::GameTimeDraw()
{
	char ch[128];

	float time = (m_fGameTime - GetTickCount()) / 1000.0f;
	int sec = (int)(m_fGameTime - GetTickCount()) / 1000.0f;
	int sec2 = (int)((time - sec) * 100);

	if (sec < 10)
		sprintf(ch, "0%d : %d ", sec, sec2);
	else
		sprintf(ch, "%d : %d ", sec, sec2);
	string str(ch);
	m_pGameTime->Init(str, 40, 620, DT_CENTER | DT_WORDBREAK);
	m_pTimeBar->StretchDraw(25, 620, ((m_fGameTime - GetTickCount()) / 1000.0f) / 45, 1);

	m_pGameTime->Draw();
}

void MoleScene::FeverTimeDraw()
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

void MoleScene::Draw(HDC hdc)
{
	char ch[128];

	//GamePlay
	if (m_bGamePlay)
	{
	

		m_pBack->DrawBitblt(0, 90);


		m_pAnimalList->Draw();

		sprintf(ch, "%d , %d ", m_MousePoint.x, m_MousePoint.y);
		string str(ch);
		m_pCursor->Init(str, m_MousePoint.x + 10, m_MousePoint.y, DT_CENTER | DT_WORDBREAK);
		m_pCursor->Draw();


		//Frame
		m_pFrame->Draw(0, 0);

		ScoreDraw();

		if (m_bTimeOver && m_iFeverGauge == 0)
		{
			m_pTimeOver->Draw(CLIENT_SIZE_WIDTH * 0.2, CLIENT_SIZE_HEIGHT * 0.4);
			if (m_bStart)
			{
				m_LoadingSc.Draw(hdc);
			}
			return;

		}

	//	GameTimeDraw();
		FeverTimeDraw();
		return;
	}



	//Rule & Loading
	if (m_bStart)
	{

		m_pRule->DrawBitblt(0, 0);
		m_LoadingSc.Draw(hdc);
	}
	else
	{
		m_pRule->DrawBitblt(0, 0);
		JEngine::UIManager::GetInstance()->Draw();
	}
}



bool MoleScene::OnSelectCheck()
{
	m_bStart = true;
	return true;
}


void MoleScene::Release()
{
	delete m_pAnimalList;
}
