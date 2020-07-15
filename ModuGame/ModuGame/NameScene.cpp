#include "NameScene.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "UIManager.h"
#include "ResoucesManager.h"
#include "Data.h"
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
	JEngine::InputManager::GetInstance()->Clear();

	for (int i = 'A'; i <= 'Z'; i++)
	{
		JEngine::InputManager::GetInstance()->RegistKeyCode(i);
	}

	JEngine::InputManager::GetInstance()->RegistKeyCode(VK_BACK);
	JEngine::InputManager::GetInstance()->RegistKeyCode(VK_LBUTTON);

	m_pTitle = JEngine::ResoucesManager::GetInstance()->GetBitmap("res\\Title.bmp");
	m_pBack = JEngine::ResoucesManager::GetInstance()->GetBitmap("res\\LoadingBack.bmp");
	m_pName = JEngine::ResoucesManager::GetInstance()->GetBitmap("res\\Name.bmp");

	m_pLabelName = new JEngine::Label();

	JEngine::UIManager::GetInstance()->AddButton(CLIENT_SIZE_WIDTH * 0.25, CLIENT_SIZE_HEIGHT * 0.846, "res\\StartButton.bmp", std::bind(&NameScene::OnClick, this));


	m_LoadingSc.Init(hWnd);
}

bool NameScene::Input(float fETime)
{
	if (JEngine::InputManager::GetInstance()->isKeyDown(VK_BACK))
	{
		m_strName = m_strName.substr(0, m_strName.length() - 1);
	}

	if (m_strName.size() == 10)
		return false;

	for (int i = 'A'; i <= 'Z'; i++)
	{
		if (JEngine::InputManager::GetInstance()->isKeyDown(i))
		{
				m_strName += (char)i;
		}
	}
	return false;
}

void NameScene::Update(float fETime)
{
	if (m_bLoading)
	{
		m_fNextSceTime += fETime;
		m_LoadingSc.Update(fETime);
		if (m_fNextSceTime > 2.0f)
		{
			Data::GetInstance()->SetUser(m_strName);
			JEngine::SceneManager::GetInstance()->LoadScene(SCENE_INDEX_RANK);
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

	m_pLabelName->Init(m_strName, CLIENT_SIZE_WIDTH * 0.53, CLIENT_SIZE_HEIGHT * 0.5, DT_CENTER | DT_WORDBREAK);
	m_pLabelName->Draw();

	JEngine::UIManager::GetInstance()->Draw();

	if (m_bLoading)
	{
		m_LoadingSc.Draw(hdc);
	}
}

void NameScene::NameTyping()
{

}

void NameScene::Release()
{

}

bool NameScene::OnClick()
{
	if(m_strName.size() == 0)
		m_bLoading = false;
	else
		m_bLoading = true;

	return true;
}