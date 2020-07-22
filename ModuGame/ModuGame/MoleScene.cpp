#include "MoleScene.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "UIManager.h"
#include "ResoucesManager.h"
#include <Windows.h>
#include "defines.h"

MoleScene::MoleScene()
{
}

MoleScene::~MoleScene()
{
}



void MoleScene::Init(HWND hWnd)
{
	m_bExplosion = false;

	m_pGameBase = new GameBase;
	m_pGameBase->Init(hWnd);

	JEngine::InputManager::GetInstance()->Clear();
	JEngine::InputManager::GetInstance()->RegistKeyCode(VK_LBUTTON);

	
	m_pBack = JEngine::ResoucesManager::GetInstance()->GetBitmap("res\\whack_a_moleMap.bmp");
	m_pRule = JEngine::ResoucesManager::GetInstance()->GetBitmap("res\\Whack_a_MoleRule.bmp");

	m_pAnimalManager = new AnimalManager;
	m_pAnimalManager->Init();

	JEngine::UIManager::GetInstance()->AddButton(CLIENT_SIZE_WIDTH * 0.212, CLIENT_SIZE_HEIGHT * 0.845, "res\\check00.bmp", std::bind(&MoleScene::OnSelectCheck, this));

}

bool MoleScene::Input(float fETime)
{
	if (m_pGameBase->GetGamePlay())
	{
		if (JEngine::InputManager::GetInstance()->isKeyDown(VK_LBUTTON))
		{
			m_MousePoint = JEngine::InputManager::GetInstance()->GetMousePoint();
			CollisionAnimal();
		}
	}
	return false;
}

void MoleScene::CollisionAnimal()
{
	m_pGameBase->SetFeverDown(false);

	ANIMALTYPE CollisionType = m_pAnimalManager->CollisionUpdate(m_MousePoint);
	
	if (CollisionType == MOLE)
	{
		if (m_pGameBase->GetFeverTime())
		{
			m_pGameBase->AddScore();
			m_pGameBase->SetFeverGauge(20,ADD);
			m_pGameBase->SetBonusPoint(100,ADD);
		}
		else
		{
			m_pGameBase->AddScore(9);
			m_pGameBase->SetFeverGauge(10,ADD);
		}
	}
	else if (CollisionType == OCTOPUS)
	{
		m_pGameBase->SetFeverDown(true);
		m_pGameBase->SetBonusPoint(100,SET);
	}
	else if (CollisionType == BOMBMOLE)
	{
		int BombNum = m_pAnimalManager->BombMole();
		for (int i = 0; i < BombNum; i++)
		{
			if (m_pGameBase->GetFeverTime())
			{
				m_pGameBase->AddScore();
				m_pGameBase->SetFeverGauge(20,ADD);
				m_pGameBase->SetBonusPoint(100,ADD);
			}
			else
			{
				m_pGameBase->AddScore(9);
				m_pGameBase->SetFeverGauge(10,ADD);
			}
		}
	}
	else
		return;
}

void MoleScene::AnimalUpdate(float fETime)
{
	RandAnimalUpdate(fETime);
	m_pAnimalManager->ExplosionDraw(fETime);
	m_pAnimalManager->Update();

}

void MoleScene::RandAnimalUpdate(float fETime)
{
	static float AnimalUpTime = 0.0f;
	static float UpdateTime = 0.0f;

	AnimalUpTime += fETime;
	UpdateTime += fETime;

	if (AnimalUpTime > 0.1f)
	{
		int randDirect = rand() % (NONDIRECTION + 1);
		m_pAnimalManager->MotionSet(randDirect);
		AnimalUpTime = 0.0f;
	}

	if (UpdateTime > 0.13f)
	{
		m_pAnimalManager->MotionUpdate();
		UpdateTime = 0.0f;
	}

}



void MoleScene::Update(float fETime)
{
	if (m_pGameBase->GetGamePlay())
	{
		m_pGameBase->GameEnd(MOLEGAME, fETime);
		if (m_pGameBase->GetTimeover())
			return;

		AnimalUpdate(fETime);

		m_pGameBase->FeverStateCheck(fETime);

	}
	m_pGameBase->GameStart(fETime);
}


void MoleScene::Draw(HDC hdc)
{
	char ch[128];

	//GamePlay
	if (m_pGameBase->GetGamePlay())
	{
	

		m_pBack->DrawBitblt(0, 90);


		m_pAnimalManager->Draw();
		if(m_pGameBase->GetFeverTime())
			m_pAnimalManager->StarDraw(m_pGameBase->GetBonusPoint());


		//Frame
		m_pGameBase->DisplayDraw(hdc);
		return;
	}


		//Rule & Loading
		if (m_pGameBase->GetStart())
		{
			m_pRule->DrawBitblt(0, 0);
			m_pGameBase->LoadingDraw(hdc);
		}
		else
		{
			m_pRule->DrawBitblt(0, 0);
			JEngine::UIManager::GetInstance()->Draw();
		}
}



bool MoleScene::OnSelectCheck()
{
	m_pGameBase->SetStart(true);
	return true;
}


void MoleScene::Release()
{

}
