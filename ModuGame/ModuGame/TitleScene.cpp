#include "TitleScene.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "UIManager.h"
#include "ResoucesManager.h"
#include "defines.h"


TitleScene::TitleScene()
{
	m_fNextSceTime = 0.0f;
	m_bLoading = false;
}

TitleScene::~TitleScene()
{
}

void TitleScene::Init(HWND hWnd)
{
	m_pTitle = JEngine::ResoucesManager::GetInstance()->GetBitmap("res\\Title.bmp");
	m_LoadingSc.Init(hWnd);
}

bool TitleScene::Input(float fETime)
{
	return false;
}

void TitleScene::Update(float fETime)
{
	m_fNextSceTime += fETime;

	if (!m_bLoading && m_fNextSceTime > 0.5f)
	{
		m_bLoading = true;
		m_fNextSceTime = 0.0f;
	}

	if (m_bLoading)
	{
		m_LoadingSc.Update(fETime);
		if (m_fNextSceTime > 2.0f)
		{

			JEngine::SceneManager::GetInstance()->LoadScene(SCENE_INDEX_NAME);
			m_fNextSceTime = 0.0f;
			m_bLoading = false;
		}
	}
}

void TitleScene::Draw(HDC hdc)
{
	m_pTitle->DrawBitblt(0, 0);
	if (m_bLoading)
	{
		m_LoadingSc.Draw(hdc);
	}
}

void TitleScene::Release()
{

}

bool TitleScene::OnClick()
{
	return true;
}