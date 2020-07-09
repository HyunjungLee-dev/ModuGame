#include "SelectScence.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "UIManager.h"
#include "ResoucesManager.h"
#include <Windows.h>
#include "defines.h"

SelectScence::SelectScence()
{
	m_fNextSceTime = 0.0f;
	m_bSelect = false;
}

SelectScence::~SelectScence()
{
}

void SelectScence::Init(HWND hWnd)
{
	JEngine::InputManager::GetInstance()->Clear();
	JEngine::InputManager::GetInstance()->RegistKeyCode(VK_LBUTTON);

	m_pGameSelect = JEngine::ResoucesManager::GetInstance()->GetBitmap("res\\GameSelect.bmp");
	m_LoadingSc.Init(hWnd);

	JEngine::UIManager::GetInstance()->AddButton(CLIENT_SIZE_WIDTH * 0.77, CLIENT_SIZE_HEIGHT * 0.26, "res\\OnSelect.bmp", std::bind(&SelectScence::OnSelectPaper, this));
	JEngine::UIManager::GetInstance()->AddButton(CLIENT_SIZE_WIDTH * 0.77, CLIENT_SIZE_HEIGHT * 0.39, "res\\OnSelect.bmp", std::bind(&SelectScence::OnSelectPlane, this));
}

bool SelectScence::Input(float fETime)
{
	return false;
}



void SelectScence::Update(float fETime)
{
	m_fNextSceTime += fETime;

	if (m_bSelect)
	{
		m_LoadingSc.Update(fETime);
		if (m_fNextSceTime > 3.0f)
		{
			JEngine::SceneManager::GetInstance()->LoadScene(m_eSelectIndex);
			m_fNextSceTime = 0.0f;
			m_bSelect = false;
		}
	}
}

void SelectScence::Draw(HDC hdc)
{
	m_pGameSelect->DrawBitblt(0, 0);
	JEngine::UIManager::GetInstance()->Draw();
	if (m_bSelect)
	{
		m_LoadingSc.Draw(hdc);
	}
}

bool SelectScence::OnSelectPaper()
{
	m_eSelectIndex = SCENE_INDEX_PAPER;
	m_bSelect = true;
	return true;
}

bool SelectScence::OnSelectPlane()
{
	m_eSelectIndex = SCENE_INDEX_PLANE;
	m_bSelect = true;
	return true;
}

void SelectScence::Release()
{

}
