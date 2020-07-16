#include"RankScene.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "UIManager.h"
#include "ResoucesManager.h"
#include "defines.h"


RankScene::RankScene()
{
	m_fNextSceTime = 0.0f;
	m_bLoading = false;
}

RankScene::~RankScene()
{
}

void RankScene::Init(HWND hWnd)
{
	JEngine::InputManager::GetInstance()->Clear();
	JEngine::InputManager::GetInstance()->RegistKeyCode(VK_LBUTTON);
	JEngine::InputManager::GetInstance()->RegistKeyCode(VK_UP);
	JEngine::InputManager::GetInstance()->RegistKeyCode(VK_DOWN);


	m_pBack = JEngine::ResoucesManager::GetInstance()->GetBitmap("res\\WBack.bmp");
	m_pFrame = JEngine::ResoucesManager::GetInstance()->GetBitmap("res\\Rank.bmp");
	m_LoadingSc.Init(hWnd);

	m_RankX = 40;
	m_RankY = 150;

	if (UserManager::GetInstance()->GetUser()->Rank != 1 && UserManager::GetInstance()->ListSize() >= 4)
		m_RankY = m_RankY - 80 * (UserManager::GetInstance()->GetUser()->Rank - 4);
	if(UserManager::GetInstance()->GetUser()->Rank >= 1 && UserManager::GetInstance()->GetUser()->Rank <= 4)
		m_RankY = 150;
	

	JEngine::UIManager::GetInstance()->AddButton(CLIENT_SIZE_WIDTH * 0.22, CLIENT_SIZE_HEIGHT * 0.79, "res\\StartButton.bmp", std::bind(&RankScene::OnClick, this));

}

bool RankScene::Input(float fETime)
{
	if (JEngine::InputManager::GetInstance()->isKeyDown(VK_UP))
	{
		if (m_RankY < 150)
			m_RankY += 80;

	}
	else if (JEngine::InputManager::GetInstance()->isKeyDown(VK_DOWN))
	{
		if (m_RankY > 150 - (UserManager::GetInstance()->ListSize() - 4) * 80)
			m_RankY -= 80;
	}

	return false;
}

void RankScene::Update(float fETime)
{


	if (m_bLoading)
	{
		m_fNextSceTime += fETime;
		m_LoadingSc.Update(fETime);
		if (m_fNextSceTime > 2.0f)
		{
			JEngine::SceneManager::GetInstance()->LoadScene(SCENE_INDEX_SELECT);
			m_fNextSceTime = 0.0f;
			m_bLoading = false;
		}
	}
}

void RankScene::Draw(HDC hdc)
{
	m_pBack->DrawBitblt(0, 0);
	UserManager::GetInstance()->Draw(m_RankX, m_RankY);
	m_pFrame->Draw(0, 0);


	JEngine::UIManager::GetInstance()->Draw();

	if (m_bLoading)
	{
		m_LoadingSc.Draw(hdc);
	}
}

void RankScene::Release()
{
	UserManager::GetInstance()->Save();
}

bool RankScene::OnClick()
{
	m_bLoading = true;
	return true;
}