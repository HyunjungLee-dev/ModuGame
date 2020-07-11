#include "PaperGameScene.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "UIManager.h"
#include "ResoucesManager.h"
#include <Windows.h>
#include <string>
#include "defines.h"

PaperGameScene::PaperGameScene()
{
	m_fNextSceTime = 0.0f;
	m_bLoading = false;
	m_bStart = false;
	m_bMoveing = false;
	m_bGamePlay = false;
	m_bSame = true;
	m_iScore = 0;
	m_iPaperPoint = 90;
	m_fMoveSpeed = 500;
	m_iFeverGauge = 0;
}

PaperGameScene::~PaperGameScene()
{
}

void PaperGameScene::Init(HWND hWnd)
{
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


	m_pScore = new JEngine::Label();
	m_pPaperPoint = new JEngine::Label();

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

	if (m_bStart)
	{
		m_fNextSceTime += fETime;
		m_LoadingSc.Update(fETime);
		if (m_fNextSceTime > 3.0f)
		{
			m_fNextSceTime = 0.0f;
			m_bStart = false;
			m_bGamePlay = true;
		}
	}

	if (m_bGamePlay)
	{
		
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

}

void PaperGameScene::Draw(HDC hdc)
{

	if (m_bGamePlay)
	{
		m_pBack->DrawBitblt(0, 0);

		m_pScore->Init(to_string(m_iScore), CLIENT_SIZE_WIDTH * 0.48, CLIENT_SIZE_HEIGHT * 0.03, DT_CENTER | DT_WORDBREAK);
		m_pScore->Draw();

		m_pColor[m_pTurnPaper[NEXT]->m_eColor]->Draw(m_pTurnPaper[NEXT]->m_fPaperX, m_pTurnPaper[NEXT]->m_fPaperY);
		m_pColor[m_pTurnPaper[NOW]->m_eColor]->Draw(m_pTurnPaper[NOW]->m_fPaperX, m_pTurnPaper[NOW]->m_fPaperY);
		return;
	}

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
		//스코어 추가
		m_iScore += m_iPaperPoint;
		//페이퍼 바꾸기
		delete m_pTurnPaper[NOW];
		m_pTurnPaper[NOW] = new Paper;
		m_pTurnPaper[NOW]->m_fPaperX = 150.0f;
		m_pTurnPaper[NOW]->m_fPaperY = 300.0f;
		m_pTurnPaper[NOW]->m_eColor = m_pTurnPaper[NEXT]->m_eColor;
		m_pTurnPaper[NEXT]->m_eColor = ((PAPER_COLOR)(rand() % 4));
		//콤보일 경우 피버 추가로 더 올리고 아닐 경우는 그냥
		//5번 콤보 마다 보너스 -> 피버는 계속
		if(m_iComboCount > 0 && m_iComboCount % 5 == 0)
			m_iFeverGauge += 20;
		else
			m_iFeverGauge += 10;
		//콤보 올리기
		m_iComboCount++;
		m_bMoveing = false;
		m_bSame = true;
	}
	else
	{
		//피버 감소
		m_iFeverGauge -= 10;
		if (m_iFeverGauge < 0)
			m_iFeverGauge = 0;
		//콤보0
		m_iComboCount = 0;
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
