#include "SelectScene.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "UIManager.h"
#include "ResoucesManager.h"
#include <Windows.h>
#include "defines.h"


SelectScene::SelectScene()
{
	m_fNextSceTime = 0.0f;
	m_bSelect = false;
}

SelectScene::~SelectScene()
{
}

void SelectScene::Init(HWND hWnd)
{
	JEngine::InputManager::GetInstance()->Clear();
	JEngine::InputManager::GetInstance()->RegistKeyCode(VK_LBUTTON);

	m_pGameSelect = JEngine::ResoucesManager::GetInstance()->GetBitmap("res\\GameSelect.bmp");
	m_LoadingSc.Init(hWnd);

	m_pFlightScore = new JEngine::Label();
	m_pPaperScore = new JEngine::Label();
	m_pMoleScore = new JEngine::Label();

	JEngine::UIManager::GetInstance()->AddButton(CLIENT_SIZE_WIDTH * 0.77, CLIENT_SIZE_HEIGHT * 0.26, "res\\OnSelect.bmp", std::bind(&SelectScene::OnSelectPaper, this));
	JEngine::UIManager::GetInstance()->AddButton(CLIENT_SIZE_WIDTH * 0.77, CLIENT_SIZE_HEIGHT * 0.39, "res\\OnSelect.bmp", std::bind(&SelectScene::OnSelectPlane, this));
	JEngine::UIManager::GetInstance()->AddButton(CLIENT_SIZE_WIDTH * 0.77, CLIENT_SIZE_HEIGHT * 0.52, "res\\OnSelect.bmp", std::bind(&SelectScene::OnSelectMole, this));

}

bool SelectScene::Input(float fETime)
{
	return false;
}



void SelectScene::Update(float fETime)
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

void SelectScene::Draw(HDC hdc)
{
	m_pGameSelect->DrawBitblt(0, 0);
	JEngine::UIManager::GetInstance()->Draw();

	m_pFlightScore->Init(to_string(UserManager::GetInstance()->GetUser()->FlightScore), CLIENT_SIZE_WIDTH * 0.27, CLIENT_SIZE_HEIGHT * 0.44, DT_LEFT | DT_WORDBREAK);
	m_pFlightScore->Draw();
	
	m_pPaperScore->Init(to_string(UserManager::GetInstance()->GetUser()->PaperScore), CLIENT_SIZE_WIDTH * 0.27, CLIENT_SIZE_HEIGHT * 0.31, DT_LEFT | DT_WORDBREAK);
	m_pPaperScore->Draw();

	m_pMoleScore->Init(to_string(UserManager::GetInstance()->GetUser()->MoleScore), CLIENT_SIZE_WIDTH * 0.27, CLIENT_SIZE_HEIGHT * 0.57, DT_LEFT | DT_WORDBREAK);
	m_pMoleScore->Draw();

	if (m_bSelect)
	{
		m_LoadingSc.Draw(hdc);
	}
}

bool SelectScene::OnSelectPaper()
{
	m_eSelectIndex = SCENE_INDEX_PAPER;
	m_bSelect = true;
	return true;
}

bool SelectScene::OnSelectPlane()
{
	m_eSelectIndex = SCENE_INDEX_FLIGHT;
	m_bSelect = true;
	return true;
}

bool SelectScene::OnSelectMole()
{
	m_eSelectIndex = SCENE_INDEX_MOLE;
	m_bSelect = true;
	return true;
}

void SelectScene::Release()
{

}
