#include "NameScene.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "UIManager.h"
#include "ResoucesManager.h"
#include "defines.h"


NameScene::NameScene()
{
	m_fNextSceTime = 0.0f;
	m_bLoading = false;
}

NameScene::~NameScene()
{
}

void NameScene::Init(HWND hWnd)
{
	m_pTitle = JEngine::ResoucesManager::GetInstance()->GetBitmap("res\\Title.bmp");
	m_pBack = JEngine::ResoucesManager::GetInstance()->GetBitmap("res\\LoadingBack.bmp");
	m_pName = JEngine::ResoucesManager::GetInstance()->GetBitmap("res\\Name.bmp");
	m_LoadingSc.Init(hWnd);
}

bool NameScene::Input(float fETime)
{
	return false;
}

void NameScene::Update(float fETime)
{
	m_fNextSceTime += fETime;


	if (m_bLoading)
	{
		m_LoadingSc.Update(fETime);
		if (m_fNextSceTime > 2.0f)
		{
			//JEngine::SceneManager::GetInstance()->LoadScene(SCENE_INDEX_SELECT);
			m_fNextSceTime = 0.0f;
			m_bLoading = false;
		}
	}
}

void NameScene::Draw(HDC hdc)
{
	m_pTitle->DrawBitblt(0, 0);
	m_pBack->DrawAlpha(0, 0);
	m_pName->Draw(CLIENT_SIZE_WIDTH * 0.25, CLIENT_SIZE_HEIGHT * 0.45);
	if (m_bLoading)
	{
		m_LoadingSc.Draw(hdc);
	}
}

void NameScene::Release()
{

}

bool NameScene::OnClick()
{
	return true;
}