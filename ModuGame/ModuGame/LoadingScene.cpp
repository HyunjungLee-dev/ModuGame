#include "LoadingScene.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "UIManager.h"
#include "ResoucesManager.h"
#include <Windows.h>
#include "defines.h"

LoadingScene::LoadingScene()
{

	m_fLoadingX = CLIENT_SIZE_WIDTH * 0.3;
	m_fLoadingY = CLIENT_SIZE_HEIGHT * 0.35;


	m_fSpeedY = 80;
	m_iAlpha = 250;

}

LoadingScene::~LoadingScene()
{
}

void LoadingScene::Init(HWND hWnd)
{
	m_pBack = JEngine::ResoucesManager::GetInstance()->GetBitmap("res\\LoadingBack.bmp");
	m_pLoading = JEngine::ResoucesManager::GetInstance()->GetBitmap("res\\Loading.bmp");
}

void LoadingScene::Update(float fETime)
{
		static bool bUp = true;

		if (m_fLoadingY > CLIENT_SIZE_HEIGHT* 0.3 && bUp)
		{
			m_fLoadingY -= fETime * m_fSpeedY;
		}
		else
			bUp = false;

		if (!bUp)
		{
			m_fLoadingY += fETime * m_fSpeedY;
			if (m_fLoadingY > CLIENT_SIZE_HEIGHT * 0.35)
			{
				m_fLoadingY = CLIENT_SIZE_HEIGHT * 0.35;
				bUp = true;
			}
		}

}

void LoadingScene::Draw(HDC hdc)
{

		m_pBack->DrawAlpha(0, 0);
		m_pLoading->Draw((int)m_fLoadingX, (int)m_fLoadingY);

}

void LoadingScene::Release()
{

}
