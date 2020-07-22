#include "FlightGameScene.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "UIManager.h"
#include "ResoucesManager.h"
#include <Windows.h>
#include "defines.h"

FlightGameScene::FlightGameScene()
{
	m_pGameBase = NULL;
}

FlightGameScene::~FlightGameScene()
{
}

void FlightGameScene::Init(HWND hWnd)
{
	m_pGameBase = new GameBase;
	m_pGameBase->Init(hWnd);

	m_fExplosionTime = 0.0f;
	m_bExplosion = false;

	m_pSky[0] = JEngine::ResoucesManager::GetInstance()->GetBitmap("res\\Sky00.bmp");
	m_pSky[1] = JEngine::ResoucesManager::GetInstance()->GetBitmap("res\\Sky01.bmp");

	JEngine::InputManager::GetInstance()->Clear();
	JEngine::InputManager::GetInstance()->RegistKeyCode(VK_LBUTTON);

	
	m_pRule = JEngine::ResoucesManager::GetInstance()->GetBitmap("res\\PlaneRule.bmp");

	
	m_Flight.FlightBit = JEngine::ResoucesManager::GetInstance()->GetBitmap("res\\FlightGameFlight.bmp");


	m_Flight.FlightPoint.x = CLIENT_SIZE_WIDTH * 0.2;
	m_Flight.FlightPoint.y = CLIENT_SIZE_HEIGHT * 0.8;

	m_fSkyX = 0;
	m_fSkyY[0] = 0;
	m_fSkyY[1] = 0 - m_pSky[1]->GetHeight();

	
	JEngine::UIManager::GetInstance()->AddButton(CLIENT_SIZE_WIDTH * 0.212, CLIENT_SIZE_HEIGHT * 0.845, "res\\check00.bmp", std::bind(&FlightGameScene::OnSelectCheck, this));

}

bool FlightGameScene::Input(float fETime)
{
	return false;
}

void FlightGameScene::BulletUpdate(float fETime)
{
	static float BulletTime = 0.0f;
	float CreatTime = 0.8f;

	//���� �ð�
	BulletTime += fETime;

	//����->������,����, ��
	if (BulletTime >= CreatTime)
	{
		int randDirect = rand() % SOUTH;

		float fX, fY;

		switch ((DIRECTION)randDirect)
		{
		case EAST:
			//y�� 100 ~600  , x�� CLIENT_SIZE_WIDTH
			fX = CLIENT_SIZE_WIDTH - 17;
			fY = rand() % 501 + 100;
			break;
		case WEST:
			//y�� 100 ~600  , x�� 0
			fX = 0;
			fY = rand() % 501 + 100;
			break;
		case NORTH:
			//y�� 100  , x�� 0~ CLIENT_SIZE_WIDTH 
			fX = rand() % CLIENT_SIZE_WIDTH;
			fY = 90;
			break;
		default:
			break;
		}

		m_pBulletList.push_back(new Bullet);
		m_pBulletList.back()->InitBullet(fX, fY, m_Flight.FlightPoint.x , m_Flight.FlightPoint.y);
		BulletTime = 0.0f;
	}

	//������
	for (list<Bullet*>::iterator iter = m_pBulletList.begin(); iter != m_pBulletList.end(); iter++)
	{
		(*iter)->Move(fETime);
	}

	//���� �������� ����Ʈ���� ����
	for (list<Bullet*>::iterator iter = m_pBulletList.begin(); iter != m_pBulletList.end();)
	{
		if ((*iter)->OutRange())
		{
			list<Bullet*>::iterator it = iter;
			iter++;
			delete (*it);
			m_pBulletList.erase(it);
		}
		else
			iter++;

	}
}

void FlightGameScene::BulletCollision(float fETime)
{
	if (!m_bExplosion)
	{

		m_fExplosionTime = 0.0f;

		for (list<Bullet*>::iterator iter = m_pBulletList.begin(); iter != m_pBulletList.end(); iter++)
		{
			if ((*iter)->IsPointInRect(m_Flight.Rect))
			{
				//���� �Ѿ� ���� ���ֱ�
				StarListClear();
				BulletListClear();

				//����
				m_bExplosion = true;

				//�ǹ� 0���� ���� ��������,�ǹ� ���� ������,�����ʽ� �ʱ�ȭ
				m_pGameBase->SetFeverState(BASIC);
				m_pGameBase->SetBonusPoint(100,SET);
				break;
			}

		}
	}
	else
	{
		m_pGameBase->SetFeverDown(true);
		m_fExplosionTime += fETime;
	}
}

void FlightGameScene::StarUpdate(float fETime)
{
	static float StarTime = 0.0f;
	float CreatTime;

	if(m_pGameBase->GetFeverTime())
		 CreatTime = 0.5f;
	else
		 CreatTime = 1.3f;

	//���� �ð�
	StarTime += fETime;

	//����->������,����, ��
	if (StarTime >= CreatTime)
	{
		int randDirect = rand() % SOUTH;

		float fX, fY;

		switch ((DIRECTION)randDirect)
		{
		case EAST:
			fX = CLIENT_SIZE_WIDTH - 17;
			fY = rand() % 501 + 100;
			break;
		case WEST:
			fX = 0;
			fY = rand() % 501 + 100;
			break;
		case NORTH:
			fX = rand() % CLIENT_SIZE_WIDTH;
			fY = 90;
			break;
		default:
			break;
		}

		m_pStarList.push_back(new Star);
		m_pStarList.back()->InitStar(fX, fY, m_Flight.FlightPoint.x, m_Flight.FlightPoint.y);
		StarTime = 0.0f;
	}

	//����Ʈ ����
	for (list<Star*>::iterator iter = m_pStarList.begin(); iter != m_pStarList.end(); iter++)
	{
		(*iter)->SetPoint(m_pGameBase->GetBonusPoint());
	}

	//������
	for (list<Star*>::iterator iter = m_pStarList.begin(); iter != m_pStarList.end(); iter++)
	{
		(*iter)->Move(fETime);
	}

	//���� �������� ����Ʈ���� ����
	for (list<Star*>::iterator iter = m_pStarList.begin(); iter != m_pStarList.end();)
	{
		if ((*iter)->OutRange())
		{
			list<Star*>::iterator it = iter;
			iter++;
			delete (*it);
			m_pStarList.erase(it);
		}
		else
			iter++;

	}
}

void FlightGameScene::StarCollision()
{

	for (list<Star*>::iterator iter = m_pStarList.begin(); iter != m_pStarList.end();)
	{
		if ((*iter)->IsIntersect(m_Flight.Rect))
		{
			if (m_pGameBase->GetFeverState() != ULTRA)
				m_pGameBase->SetFeverGauge(20,ADD);
			m_pGameBase->SetBonusPoint(100,ADD);
			if (m_pGameBase->GetBonusPoint() > 5000)
				m_pGameBase->SetBonusPoint(5000,SET);
			m_pGameBase->AddScore((*iter)->GetPoint());

			list<Star*>::iterator it = iter;
			iter++;
			delete (*it);
			m_pStarList.erase(it);

		}
		else
			iter++;
	}
	

}


void FlightGameScene::Update(float fETime)
{
	static float m_fScoreTime = 0.0f;

	if (m_pGameBase->GetGamePlay())
	{ 
	
		//sky
		m_fSkyY[0] += 100 * fETime;
		m_fSkyY[1] += 100 * fETime;

		if (m_fSkyY[0] >= CLIENT_SIZE_HEIGHT)
		{
			m_fSkyY[0] = 0 - m_pSky[1]->GetHeight();
		}
		if(m_fSkyY[1] >= CLIENT_SIZE_HEIGHT)
		{
			m_fSkyY[1] = 0 - m_pSky[1]->GetHeight();
		}


		StarUpdate(fETime);
		BulletUpdate(fETime);

		m_pGameBase->GameEnd(FLIGHTGAME, fETime);
		if (m_pGameBase->GetTimeover())
			return;

 	  //Flight
		int mousepointX = JEngine::InputManager::GetInstance()->GetMousePoint().x;
		 int mousepointY = JEngine::InputManager::GetInstance()->GetMousePoint().y;

			if ((mousepointX > 20 && mousepointX < CLIENT_SIZE_WIDTH - 20)
				&& (mousepointY > 100 && mousepointY < CLIENT_SIZE_HEIGHT - 60))
			{
				m_Flight.FlightPoint = JEngine::InputManager::GetInstance()->GetMousePoint();
				m_Flight.FlightPoint.x = m_Flight.FlightPoint.x - m_Flight.FlightBit->GetWidth() * 0.5;
				m_Flight.FlightPoint.y = m_Flight.FlightPoint.y - m_Flight.FlightBit->GetHeight() * 0.5;
				m_Flight.Rect = { m_Flight.FlightPoint.x ,m_Flight.FlightPoint.y ,
				m_Flight.FlightPoint.x + m_Flight.FlightBit->GetWidth(),m_Flight.FlightPoint.y + m_Flight.FlightBit->GetHeight() };
			}

		//Fever
		m_pGameBase->FeverStateCheck(fETime);

		m_fScoreTime += fETime;

		if (m_fScoreTime > 1.0f && !m_bExplosion)
		{
			m_pGameBase->AddScore(3);
			if (m_pGameBase->GetFeverState() != ULTRA)
				m_pGameBase->SetFeverGauge(5,ADD);
			m_fScoreTime = 0.0f;

		}

		StarCollision();
		BulletCollision(fETime);


	}

	m_pGameBase->GameStart(fETime);
}


void FlightGameScene::Draw(HDC hdc)
{
	//GamePlay
	if (m_pGameBase->GetGamePlay())
	{
		//BackSky
		m_pSky[0]->DrawBitblt(m_fSkyX, m_fSkyY[0]);
		m_pSky[1]->DrawBitblt(m_fSkyX, m_fSkyY[1]);

		//Bullet
		for (list<Bullet*>::iterator iter = m_pBulletList.begin(); iter != m_pBulletList.end(); iter++)
		{
			(*iter)->Draw();
		}

		//Star
		for (list<Star*>::iterator iter = m_pStarList.begin(); iter != m_pStarList.end(); iter++)
		{
			(*iter)->Draw();
		}


		//Flight
		if (m_bExplosion)
		{
			if (m_fExplosionTime <= 0.2f)
				m_pGameBase->ExplosionDraw(0, m_Flight.FlightPoint.x, m_Flight.FlightPoint.y);
			else if (m_fExplosionTime <= 0.4f)
				m_pGameBase->ExplosionDraw(1, m_Flight.FlightPoint.x, m_Flight.FlightPoint.y);
			else if (m_fExplosionTime <= 0.6f)
				m_pGameBase->ExplosionDraw(2, m_Flight.FlightPoint.x, m_Flight.FlightPoint.y);
			else
				m_bExplosion = false;
		}
		else
			m_Flight.FlightBit->Draw(m_Flight.FlightPoint);

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



bool FlightGameScene::OnSelectCheck()
{
	m_pGameBase->SetStart(true);
	return true;
}

void FlightGameScene::BulletListClear()
{
	for (list<Bullet*>::iterator iter = m_pBulletList.begin(); iter != m_pBulletList.end();iter++)
	{
		delete (*iter);
	}
	m_pBulletList.clear();
}

void FlightGameScene::StarListClear()
{
	for (list<Star*>::iterator iter = m_pStarList.begin(); iter != m_pStarList.end(); iter++)
	{
		delete (*iter);
	}
	m_pStarList.clear();
}

void FlightGameScene::Release()
{

	//bullet
	BulletListClear();

	//star
	StarListClear();

	if (m_pGameBase != NULL)
	{
		delete m_pGameBase;
		m_pGameBase = NULL;
	}

}
