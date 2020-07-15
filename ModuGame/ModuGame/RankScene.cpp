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

	m_pBack = JEngine::ResoucesManager::GetInstance()->GetBitmap("res\\WBack.bmp");
	m_pFrame = JEngine::ResoucesManager::GetInstance()->GetBitmap("res\\Rank.bmp");
	m_LoadingSc.Init(hWnd);

	JEngine::UIManager::GetInstance()->AddButton(CLIENT_SIZE_WIDTH * 0.22, CLIENT_SIZE_HEIGHT * 0.79, "res\\StartButton.bmp", std::bind(&RankScene::OnClick, this));

}

bool RankScene::Input(float fETime)
{
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
	m_pFrame->Draw(0, 0);
	Data::GetInstance()->GetUser()->Draw(40, 150);


	JEngine::UIManager::GetInstance()->Draw();

	if (m_bLoading)
	{
		m_LoadingSc.Draw(hdc);
	}
}

void RankScene::Release()
{

}

bool RankScene::OnClick()
{
	m_bLoading = true;
	return true;
}