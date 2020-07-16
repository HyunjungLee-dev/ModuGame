#include "PaperGameScene.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "UIManager.h"
#include "ResoucesManager.h"
#include <Windows.h>
#include"UserManager.h"
#include "defines.h"

PaperGameScene::PaperGameScene()
{

	
}

PaperGameScene::~PaperGameScene()
{
}

void PaperGameScene::SetMember()
{
	m_bLoading = false;
	m_bStart = false;
	m_bMoveing = false;
	m_bGamePlay = false;
	m_bSame = true;
	m_bFeverTime = false;
	m_bTimeOver = false;
	m_bFeverDown = false;


	m_fNextSceTime = 0.0f;
	m_fUltraTime = 0.0f;


	m_eFeverState = BASIC;
	m_eUltraTime = ULTRA;

	m_iBonusPoint = 100;
	m_iScore = 0;
	m_iComboCount = 0;
	m_iPaperPoint = 90;
	m_fMoveSpeed = 1000;
	m_iFeverGauge = 0;
}

void PaperGameScene::Init(HWND hWnd)
{
	SetMember();

	JEngine::InputManager::GetInstance()->Clear();
	JEngine::InputManager::GetInstance()->RegistKeyCode(VK_SPACE);
	JEngine::InputManager::GetInstance()->RegistKeyCode(VK_ESCAPE);
	JEngine::InputManager::GetInstance()->RegistKeyCode(VK_LEFT);
	JEngine::InputManager::GetInstance()->RegistKeyCode(VK_RIGHT);
	JEngine::InputManager::GetInstance()->RegistKeyCode(VK_UP);
	JEngine::InputManager::GetInstance()->RegistKeyCode(VK_DOWN);
	JEngine::InputManager::GetInstance()->RegistKeyCode(VK_LBUTTON);

	m_pBack = JEngine::ResoucesManager::GetInstance()->GetBitmap("res\\ColoredPaperBack.bmp");
	m_pRule = JEngine::ResoucesManager::GetInstance()->GetBitmap("res\\ColoredPaperRule.bmp");


	m_pColor[BLUE] = JEngine::ResoucesManager::GetInstance()->GetBitmap("res\\ColoredPaperBlue.bmp");
	m_pColor[GREEN] = JEngine::ResoucesManager::GetInstance()->GetBitmap("res\\ColoredPaperGreen.bmp");
	m_pColor[RED] = JEngine::ResoucesManager::GetInstance()->GetBitmap("res\\ColoredPaperRed.bmp");
	m_pColor[YELLOW] = JEngine::ResoucesManager::GetInstance()->GetBitmap("res\\ColoredPaperYellow.bmp");

	m_pFever[0] = JEngine::ResoucesManager::GetInstance()->GetBitmap("res\\Fever1.bmp");
	m_pFever[1] = JEngine::ResoucesManager::GetInstance()->GetBitmap("res\\Fever2.bmp");
	m_pFever[2] = JEngine::ResoucesManager::GetInstance()->GetBitmap("res\\Fever3.bmp");

	m_pBonusStar[0] = JEngine::ResoucesManager::GetInstance()->GetBitmap("res\\FlightGameStar1.bmp");
	m_pBonusStar[1] = JEngine::ResoucesManager::GetInstance()->GetBitmap("res\\FlightGameStar2.bmp");
	m_pBonusStar[2] = JEngine::ResoucesManager::GetInstance()->GetBitmap("res\\FlightGameStar3.bmp");

	m_pFeverEffect = JEngine::ResoucesManager::GetInstance()->GetBitmap("res\\FeverEffect3.bmp");
	m_pTimeBar = JEngine::ResoucesManager::GetInstance()->GetBitmap("res\\ColoredPaperTimeBar.bmp");
	m_pTimeOver = JEngine::ResoucesManager::GetInstance()->GetBitmap("res\\TimeOver.bmp");


	m_pScore = new JEngine::Label();
	m_pPaperPoint = new JEngine::Label();
	m_pGameTime = new JEngine::Label();

	JEngine::UIManager::GetInstance()->AddButton(CLIENT_SIZE_WIDTH * 0.212, CLIENT_SIZE_HEIGHT * 0.846, "res\\check00.bmp", std::bind(&PaperGameScene::OnSelectCheck, this));

	m_LoadingSc.Init(hWnd);
	SetColorPaper();
	SetTurnPaper();
}

bool PaperGameScene::Input(float fETime)
{
	if (!m_bMoveing)
	{
		if (JEngine::InputManager::GetInstance()->isKeyDown(VK_UP))
		{
			m_pTurnPaper[NOW]->m_eDirection = UP;
			m_bMoveing = true;

		}
		else if (JEngine::InputManager::GetInstance()->isKeyDown(VK_DOWN))
		{
			m_pTurnPaper[NOW]->m_eDirection = DOWN;
			m_bMoveing = true;
		}
		else if (JEngine::InputManager::GetInstance()->isKeyDown(VK_LEFT))
		{
			m_pTurnPaper[NOW]->m_eDirection = LEFT;
			m_bMoveing = true;
		}
		else if (JEngine::InputManager::GetInstance()->isKeyDown(VK_RIGHT))
		{
			m_pTurnPaper[NOW]->m_eDirection = RIGHT;
			m_bMoveing = true;
		}
	}
	return false;
}



void PaperGameScene::Update(float fETime)
{
	static int MovableCount = 0;
	
	TCHAR str[128];


	if (m_bGamePlay)
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
					if (m_iScore >= UserManager::GetInstance()->GetUser()->PaperScore)
						UserManager::GetInstance()->GetUser()->SetUser(PAPER, m_iScore);
					UserManager::GetInstance()->RankSort();
					UserManager::GetInstance()->Save();
					JEngine::SceneManager::GetInstance()->LoadScene(SCENE_INDEX_RANK);
					SetMember();
				}
			}
			return;
		}

		if (m_bFeverDown)
			DownFeverGauge();
		else
			FeverUpdate(fETime);

		if (m_bMoveing)
		{
				SlidePaper(fETime);
		}
		else
		{

			if (!m_bSame)
			{
				m_fNextSceTime += fETime;
				NotSameMotion(fETime);
				if (m_fNextSceTime > 0.5f)
				{
					m_fNextSceTime = 0.0f;
					m_bSame = true;
					m_pTurnPaper[NOW]->m_fPaperX = 150.0f;
					m_pTurnPaper[NOW]->m_fPaperY = 300.0f;
				}
			}
		}
	}

	if (m_bStart)
	{
		m_fNextSceTime += fETime;
		m_LoadingSc.Update(fETime);
		if (m_fNextSceTime > 3.0f)
		{
			m_fNextSceTime = 0.0f;
			m_bStart = false;
			m_bGamePlay = true;
			m_fGameTime = GetTickCount() + 45000;
		}
	}


}

void PaperGameScene::FeverUpdate(float fETime)
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
				m_bFeverDown = true;
			}
		}
	}
	else
		m_fEffectTime = 0.0f;
}

void PaperGameScene::DownFeverGauge()
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

void PaperGameScene::GameTimeDraw()
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

void PaperGameScene::ScoreDraw()
{
	m_pScore->Init(to_string(m_iScore), CLIENT_SIZE_WIDTH * 0.48, CLIENT_SIZE_HEIGHT * 0.03, DT_CENTER | DT_WORDBREAK);
	m_pScore->Draw();
}


void PaperGameScene::FeverTimeDraw()
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

void PaperGameScene::Draw(HDC hdc)
{


	if (m_bGamePlay)
	{

		m_pBack->DrawBitblt(0, 0);



		m_pColor[m_pTurnPaper[NEXT]->m_eColor]->Draw(m_pTurnPaper[NEXT]->m_fPaperX, m_pTurnPaper[NEXT]->m_fPaperY);
		m_pColor[m_pTurnPaper[NOW]->m_eColor]->Draw(m_pTurnPaper[NOW]->m_fPaperX, m_pTurnPaper[NOW]->m_fPaperY);

		if ((m_iComboCount > 0 && m_iComboCount % 5 == 0)|| m_bFeverTime)
		{
			float CenterX = m_pTurnPaper[NOW]->m_fPaperX + m_pColor[m_pTurnPaper[NOW]->m_eColor]->GetWidth()*0.4;
			float CenterY = m_pTurnPaper[NOW]->m_fPaperY + m_pColor[m_pTurnPaper[NOW]->m_eColor]->GetHeight()*0.4;

			if (m_iBonusPoint >= 3000)
				m_pBonusStar[STAR_BLUE]->Draw((int)CenterX - 15,(int)CenterY - 20);
			else if(m_iBonusPoint >= 1000)
				m_pBonusStar[STAR_GREEN]->Draw((int)CenterX - 15, (int)CenterY - 20);
			else
				m_pBonusStar[STAR_YELLOW]->Draw((int)CenterX - 15, (int)CenterY - 20);
			m_pPaperPoint->Init(to_string(m_iBonusPoint),(int) CenterX,(int)CenterY, DT_CENTER | DT_WORDBREAK);
			m_pPaperPoint->Draw();
		}

		ScoreDraw();
		FeverTimeDraw();

		if (m_bTimeOver && m_iFeverGauge == 0)
		{
			m_pTimeOver->Draw(CLIENT_SIZE_WIDTH * 0.2, CLIENT_SIZE_HEIGHT * 0.4);
			if (m_bStart)
			{
				m_LoadingSc.Draw(hdc);
			}
			return;

		}

		GameTimeDraw();
		return;
	}

	if (m_bStart )
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

void PaperGameScene::SetColorPaper()
{

	m_pColorPaper[LEFT] = new Paper;
	m_pColorPaper[LEFT]->m_eColor = BLUE;
	m_pColorPaper[LEFT]->m_eDirection = LEFT;
	m_pColorPaper[LEFT]->m_fPaperX = 10.0f;
	m_pColorPaper[LEFT]->m_fPaperY = 300.0f;


	m_pColorPaper[UP] = new Paper;
	m_pColorPaper[UP]->m_eColor = GREEN;
	m_pColorPaper[UP]->m_eDirection = UP;
	m_pColorPaper[UP]->m_fPaperX = 150.0f;
	m_pColorPaper[UP]->m_fPaperY = 120.0f;


	m_pColorPaper[DOWN] = new Paper;
	m_pColorPaper[DOWN]->m_eColor = YELLOW;
	m_pColorPaper[DOWN]->m_eDirection = DOWN;
	m_pColorPaper[DOWN]->m_fPaperX = 150.0f;
	m_pColorPaper[DOWN]->m_fPaperY = 480.0f;

	m_pColorPaper[RIGHT] = new Paper;
	m_pColorPaper[RIGHT]->m_eColor = RED;
	m_pColorPaper[RIGHT]->m_eDirection = RIGHT;
	m_pColorPaper[RIGHT]->m_fPaperX = 290.0f;
	m_pColorPaper[RIGHT]->m_fPaperY = 300.0f;
}

void PaperGameScene::SetTurnPaper()
{
	m_pTurnPaper[NOW] = new Paper;
	m_pTurnPaper[NOW]->m_eColor = ((PAPER_COLOR)(rand() % 4));
	m_pTurnPaper[NOW]->m_eDirection = NONE;
	m_pTurnPaper[NOW]->m_fPaperX = 150.0f;
	m_pTurnPaper[NOW]->m_fPaperY = 300.0f;


	m_pTurnPaper[NEXT] = new Paper;
	m_pTurnPaper[NEXT]->m_eColor = ((PAPER_COLOR)(rand() % 4));
	m_pTurnPaper[NEXT]->m_eDirection = NONE;
	m_pTurnPaper[NEXT]->m_fPaperX = 160.0f;
	m_pTurnPaper[NEXT]->m_fPaperY = 310.0f;
}

void PaperGameScene::SlidePaper(float fETime)
{
	Paper* Now = m_pTurnPaper[NOW];

		switch (m_pTurnPaper[NOW]->m_eDirection)
		{
		case UP:
			if (Now->m_eColor != m_pColorPaper[UP]->m_eColor)
			{
				IsSameColor(false);
			}
			else
			{
				m_pTurnPaper[NOW]->m_fPaperY -= fETime * m_fMoveSpeed;
				if (m_pTurnPaper[NOW]->m_fPaperY <= m_pColorPaper[UP]->m_fPaperY)
				{
					IsSameColor(true);
				}
			}
			break;
		case DOWN:
			if (Now->m_eColor != m_pColorPaper[DOWN]->m_eColor)
			{
				IsSameColor(false);
			}
			else
			{
				m_pTurnPaper[NOW]->m_fPaperY += fETime * m_fMoveSpeed;
				if (m_pTurnPaper[NOW]->m_fPaperY >= m_pColorPaper[DOWN]->m_fPaperY)
				{
					IsSameColor(true);
				}
			}
			break;
		case RIGHT:
			if (Now->m_eColor != m_pColorPaper[RIGHT]->m_eColor)
			{
				IsSameColor(false);
			}
			else
			{
				m_pTurnPaper[NOW]->m_fPaperX += fETime * m_fMoveSpeed;
				if (m_pTurnPaper[NOW]->m_fPaperX >= m_pColorPaper[RIGHT]->m_fPaperX)
				{
					IsSameColor(true);
				}
			}
			break;
		case LEFT:
			if (Now->m_eColor != m_pColorPaper[LEFT]->m_eColor)
			{
				IsSameColor(false);
			}
			else
			{
				m_pTurnPaper[NOW]->m_fPaperX -= fETime * m_fMoveSpeed;
				if (m_pTurnPaper[NOW]->m_fPaperX <= m_pColorPaper[LEFT]->m_fPaperX)
				{
					IsSameColor(true);

				}
			}
			break;
		default:
			break;
		}
}

void PaperGameScene::IsSameColor(bool bSame)
{
	if (bSame)
	{
		//페이퍼 바꾸기
		delete m_pTurnPaper[NOW];
		m_pTurnPaper[NOW] = new Paper;
		m_pTurnPaper[NOW]->m_fPaperX = 150.0f;
		m_pTurnPaper[NOW]->m_fPaperY = 300.0f;
		m_pTurnPaper[NOW]->m_eColor = m_pTurnPaper[NEXT]->m_eColor;
		m_pTurnPaper[NEXT]->m_eColor = ((PAPER_COLOR)(rand() % 4));
		//콤보일 경우 피버 추가로 더 올리고 아닐 경우는 그냥
		//5번 콤보 마다 보너스 -> 피버는 계속
		if ((m_iComboCount > 0 && m_iComboCount % 5 == 0 ) || m_bFeverTime)
		{
			if(m_eFeverState != ULTRA)
				m_iFeverGauge += 20;
			m_iScore += m_iBonusPoint;
			m_iBonusPoint += 100;
			if (m_iBonusPoint > 5000)
				m_iBonusPoint = 5000;
		}
		else
		{

			m_iFeverGauge += 10;
			//스코어 추가
			m_iScore += m_iPaperPoint;
		}
		//콤보 올리기
		m_iComboCount++;
		m_bMoveing = false;
		m_bSame = true;
	}
	else
	{
		
		if (m_eFeverState != ULTRA)
		{
			//피버 감소
			m_iFeverGauge -= 30;
			if (m_iFeverGauge < 0)
				m_iFeverGauge = 0;
		}
		//콤보0
		m_iComboCount = 0;
		m_iBonusPoint = 100;
		//리턴 진동
		m_bSame = false;

		m_bMoveing = false;
		
	}
}

void PaperGameScene::NotSameMotion(float fETime)
{
		static bool bDirect = true;
		if (m_pTurnPaper[NOW]->m_eDirection == UP || m_pTurnPaper[NOW]->m_eDirection == DOWN || m_pTurnPaper[NOW]->m_eDirection == NONE)
		{
			if (m_pTurnPaper[NOW]->m_fPaperY > 290.0f & bDirect)
			{
				m_pTurnPaper[NOW]->m_fPaperY -= fETime * 100;
			}
			else
			{
				bDirect = false;
				if (m_pTurnPaper[NOW]->m_fPaperY > 310.f & !bDirect)
				{
					bDirect = true;
				}
				m_pTurnPaper[NOW]->m_fPaperY += fETime * 100;

			}
		}
		else
		{
			if (m_pTurnPaper[NOW]->m_fPaperX > 140.0f & bDirect)
			{
				m_pTurnPaper[NOW]->m_fPaperX -= fETime * 100;
			}
			else
			{
				bDirect = false;
				if (m_pTurnPaper[NOW]->m_fPaperX > 160.f & !bDirect)
				{
					bDirect = true;
				}
				m_pTurnPaper[NOW]->m_fPaperX += fETime * 100;

			}
		}

}

bool PaperGameScene::OnSelectCheck()
{
	m_bStart = true;
	return true;
}

void PaperGameScene::Release()
{
}
