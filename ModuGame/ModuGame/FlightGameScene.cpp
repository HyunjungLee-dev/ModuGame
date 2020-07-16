#include "FlightGameScene.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "UIManager.h"
#include "ResoucesManager.h"
#include <Windows.h>
#include "defines.h"

FlightGameScene::FlightGameScene()
{
}

FlightGameScene::~FlightGameScene()
{
}

void FlightGameScene::SetMember()
{
	m_fNextSceTime = 0.0f;
	m_bLoading = false;


	m_bStart = false;
	m_bGamePlay = false;
	m_bTimeOver = false;
	m_bExplosion = false;
	m_bFeverTime = false;
	m_bFeverDown = false;


	m_eFeverState = BASIC;
	m_eUltraTime = ULTRA;

	m_fNextSceTime = 0.0f;
	m_fExplosionTime = 0.0f;
	m_iScore = 0;
	m_iFeverGauge = 0;
	m_iBonusPoint = 100;
}

void FlightGameScene::Init(HWND hWnd)
{
	SetMember();

	m_pSky[0] = JEngine::ResoucesManager::GetInstance()->GetBitmap("res\\Sky00.bmp");
	m_pSky[1] = JEngine::ResoucesManager::GetInstance()->GetBitmap("res\\Sky01.bmp");
	m_LoadingSc.Init(hWnd);


	JEngine::InputManager::GetInstance()->Clear();
	JEngine::InputManager::GetInstance()->RegistKeyCode(VK_SPACE);
	JEngine::InputManager::GetInstance()->RegistKeyCode(VK_ESCAPE);
	JEngine::InputManager::GetInstance()->RegistKeyCode(VK_LEFT);
	JEngine::InputManager::GetInstance()->RegistKeyCode(VK_RIGHT);
	JEngine::InputManager::GetInstance()->RegistKeyCode(VK_UP);
	JEngine::InputManager::GetInstance()->RegistKeyCode(VK_DOWN);
	JEngine::InputManager::GetInstance()->RegistKeyCode(VK_LBUTTON);

	m_pFrame = JEngine::ResoucesManager::GetInstance()->GetBitmap("res\\FlightGameBackTra.bmp");
	m_pRule = JEngine::ResoucesManager::GetInstance()->GetBitmap("res\\PlaneRule.bmp");

	m_pTimeBar = JEngine::ResoucesManager::GetInstance()->GetBitmap("res\\ColoredPaperTimeBar.bmp");
	m_pTimeOver = JEngine::ResoucesManager::GetInstance()->GetBitmap("res\\TimeOver.bmp");
	m_pExplosion[0] = JEngine::ResoucesManager::GetInstance()->GetBitmap("res\\explosion1.bmp");
	m_pExplosion[1] = JEngine::ResoucesManager::GetInstance()->GetBitmap("res\\explosion2.bmp");
	m_pExplosion[2] = JEngine::ResoucesManager::GetInstance()->GetBitmap("res\\explosion3.bmp");
	m_pFever[0] = JEngine::ResoucesManager::GetInstance()->GetBitmap("res\\Fever1.bmp");
	m_pFever[1] = JEngine::ResoucesManager::GetInstance()->GetBitmap("res\\Fever2.bmp");
	m_pFever[2] = JEngine::ResoucesManager::GetInstance()->GetBitmap("res\\Fever3.bmp");
	m_pFeverEffect = JEngine::ResoucesManager::GetInstance()->GetBitmap("res\\FeverEffect3.bmp");
	m_pTimeOver = JEngine::ResoucesManager::GetInstance()->GetBitmap("res\\TimeOver.bmp");

	m_Flight.FlightBit = JEngine::ResoucesManager::GetInstance()->GetBitmap("res\\FlightGameFlight.bmp");


	m_pGameTime = new JEngine::Label();
	m_pScore = new JEngine::Label();

	m_Flight.FlightPoint.x = CLIENT_SIZE_WIDTH * 0.2;
	m_Flight.FlightPoint.y = CLIENT_SIZE_HEIGHT * 0.8;

	m_fSkyX = 0;
	m_fSkyY[0] = 0;
	m_fSkyY[1] = 0 - m_pSky[1]->GetHeight();

	
	JEngine::UIManager::GetInstance()->AddButton(CLIENT_SIZE_WIDTH * 0.212, CLIENT_SIZE_HEIGHT * 0.845, "res\\check00.bmp", std::bind(&FlightGameScene::OnSelectCheck, this));

	m_LoadingSc.Init(hWnd);
}

bool FlightGameScene::Input(float fETime)
{
	return false;
}

void FlightGameScene::BulletUpdate(float fETime)
{
	static float BulletTime = 0.0f;
	float CreatTime = 0.8f;

	//생성 시간
	BulletTime += fETime;

	//생성->오른쪽,왼쪽, 위
	if (BulletTime >= CreatTime)
	{
		int randDirect = rand() % SOUTH;

		float fX, fY;

		switch ((DIRECTION)randDirect)
		{
		case EAST:
			//y가 100 ~600  , x는 CLIENT_SIZE_WIDTH
			fX = CLIENT_SIZE_WIDTH - 17;
			fY = rand() % 501 + 100;
			break;
		case WEST:
			//y가 100 ~600  , x는 0
			fX = 0;
			fY = rand() % 501 + 100;
			break;
		case NORTH:
			//y는 100  , x가 0~ CLIENT_SIZE_WIDTH 
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

	//움직임
	for (list<Bullet*>::iterator iter = m_pBulletList.begin(); iter != m_pBulletList.end(); iter++)
	{
		(*iter)->Move(fETime);
	}

	//범위 벗어났을경우 리스트에서 삭제
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
				//별과 총알 전부 없애기
				StarListClear();
				BulletListClear();

				//폭발
				m_bExplosion = true;

				//피버 0으로 감소 내려가기,피버 레벨 베이직,별보너스 초기화
				m_eFeverState = BASIC;
				m_iBonusPoint = 100;
				break;
			}

		}
	}
	else
	{
		m_bFeverDown = true;
		m_fExplosionTime += fETime;
	}
}

void FlightGameScene::StarUpdate(float fETime)
{
	static float StarTime = 0.0f;
	float CreatTime;

	if(m_bFeverTime)
		 CreatTime = 0.5f;
	else
		 CreatTime = 1.3f;

	//생성 시간
	StarTime += fETime;

	//생성->오른쪽,왼쪽, 위
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

	//포인트 갱신
	for (list<Star*>::iterator iter = m_pStarList.begin(); iter != m_pStarList.end(); iter++)
	{
		(*iter)->SetPoint(m_iBonusPoint);
	}

	//움직임
	for (list<Star*>::iterator iter = m_pStarList.begin(); iter != m_pStarList.end(); iter++)
	{
		(*iter)->Move(fETime);
	}

	//범위 벗어났을경우 리스트에서 삭제
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
			if(m_eFeverState != ULTRA)
				m_iFeverGauge += 20;
			m_iBonusPoint += 100;
			if (m_iBonusPoint > 5000)
				m_iBonusPoint = 5000;
			m_iScore += (*iter)->GetPoint();

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

	if (m_bGamePlay)
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


		if (m_fGameTime <= GetTickCount())
		{
			DownFeverGauge();
			m_bTimeOver = true;
			m_fNextSceTime += fETime;
			if (m_fNextSceTime > 1.0f)
			{
				m_bStart = true;
			}
			if(m_bStart)
			{
				m_LoadingSc.Update(fETime);
				if (m_fNextSceTime > 4.0f)
				{
					if(m_iScore >= UserManager::GetInstance()->GetUser()->FlightScore)
						UserManager::GetInstance()->GetUser()->SetUser(FLIGHT, m_iScore);
					UserManager::GetInstance()->RankSort();
					UserManager::GetInstance()->Save();
					JEngine::SceneManager::GetInstance()->LoadScene(SCENE_INDEX_RANK);
					SetMember();
				}
			}
			return;
		}

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
		if (m_bFeverDown)
			DownFeverGauge();
		else
			FeverUpdate(fETime);

		m_fScoreTime += fETime;

		if (m_fScoreTime > 1.0f && !m_bExplosion)
		{
			m_iScore += 3;
			if (m_eFeverState != ULTRA)
				m_iFeverGauge += 5;
			m_fScoreTime = 0.0f;

		}

		StarCollision();
		BulletCollision(fETime);
	}



	if (m_bStart )
	{
		m_fNextSceTime += fETime;
		m_LoadingSc.Update(fETime);
		if (m_fNextSceTime > 3.0f)
		{
			m_bStart = false;
			m_bGamePlay = true;
			m_fGameTime = GetTickCount() + 45000;
			
			m_fNextSceTime = 0.0f;
		}
	}
}

void FlightGameScene::DownFeverGauge()
{
	m_eFeverState = BASIC;
	m_iFeverGauge -= 1;
	if (m_iFeverGauge <= 0)
	{
		m_iFeverGauge = 0;
		m_eFeverState = BASIC;
		m_bFeverTime = false;
		m_fUltraTime = 0.0f;
		m_bFeverDown = false;
	}
}

void FlightGameScene::FeverUpdate(float fETime)
{
	if (m_iFeverGauge > 100 && m_eFeverState != ULTRA)
	{
		int tmp = 100 - m_iFeverGauge;
		if (m_eFeverState == BASIC)
		{
			m_bFeverTime = true;
			m_eFeverState = SUPER;
		}
		else if (m_eFeverState == SUPER)
		{
			m_eFeverState = ULTRA;
			m_iFeverGauge = 99;
			return;
		}
		m_iFeverGauge = abs(tmp);
	}

	if (m_bFeverTime)
	{
		m_fEffectTime += fETime;
		if (m_eFeverState == ULTRA)
		{
			m_fUltraTime += fETime;
			m_fNextSceTime += fETime;
			if (m_fNextSceTime > 0.1f)
			{
				if (m_eUltraTime == ULTRA)
					m_eUltraTime = BASIC;
				else
					m_eUltraTime = ULTRA;
				m_fNextSceTime = 0.0f;
			}

			if (m_fUltraTime > 5.0f)
			{
				m_eUltraTime = BASIC;
				DownFeverGauge();
			}
		}
	}
	else
		m_fEffectTime = 0.0f;
}

void FlightGameScene::ScoreDraw()
{
	m_pScore->Init(to_string(m_iScore), CLIENT_SIZE_WIDTH * 0.48, CLIENT_SIZE_HEIGHT * 0.03, DT_CENTER | DT_WORDBREAK);
	m_pScore->Draw();
}

void FlightGameScene::GameTimeDraw()
{
	char ch[128];

	float time = (m_fGameTime - GetTickCount()) / 1000.0f;
	int sec = (int)(m_fGameTime - GetTickCount()) / 1000.0f;
	int sec2 = (int)((time - sec) * 100);

	if (sec < 10)
		sprintf(ch, "0%d : %d ", sec, sec2);
	else
		sprintf(ch, "%d : %d ", sec, sec2);
	string str(ch);
	m_pGameTime->Init(str, 40, 620, DT_CENTER | DT_WORDBREAK);
	m_pTimeBar->StretchDraw(25, 620, ((m_fGameTime - GetTickCount()) / 1000.0f) / 45, 1);

	m_pGameTime->Draw();
}

void FlightGameScene::FeverTimeDraw()
{
	if (m_bFeverDown)
	{
		m_pFever[BASIC]->StretchDraw(20, 55, m_iFeverGauge / 100.0f, 1);
		return;
	}

	if (m_bFeverTime)
	{
		if (m_fEffectTime > 0.1f)
		{
			m_pFeverEffect->Draw(0, 0);
			m_fEffectTime = 0.0f;
		}
	}

	if (m_eFeverState != ULTRA)
	{
		if (m_eFeverState > BASIC)
			m_pFever[BASIC]->Draw(20, 55);
		m_pFever[m_eFeverState]->StretchDraw(20, 55, m_iFeverGauge / 100.0f, 1);
	}
	else
	{
		if (m_fUltraTime > 10.0f)
		{
			if (m_eUltraTime == BASIC)
				m_pFever[m_eUltraTime]->StretchDraw(20, 55, m_iFeverGauge / 100.0f, 1);
		}
		else
			m_pFever[m_eUltraTime]->Draw(20, 55);
	}
}

void FlightGameScene::Draw(HDC hdc)
{
	//GamePlay
	if (m_bGamePlay)
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
				m_pExplosion[0]->Draw(m_Flight.FlightPoint.x, m_Flight.FlightPoint.y );
			else if (m_fExplosionTime <= 0.4f)
				m_pExplosion[1]->Draw(m_Flight.FlightPoint.x, m_Flight.FlightPoint.y );
			else if (m_fExplosionTime <= 0.6f)
				m_pExplosion[2]->Draw(m_Flight.FlightPoint.x , m_Flight.FlightPoint.y );
			else
				m_bExplosion = false;
		}
		else
			m_Flight.FlightBit->Draw(m_Flight.FlightPoint);

		//Frame
		m_pFrame->Draw(0, 0);

		ScoreDraw();

		if (m_bTimeOver && m_iFeverGauge == 0 )
		{
			m_pTimeOver->Draw(CLIENT_SIZE_WIDTH * 0.2, CLIENT_SIZE_HEIGHT * 0.4);
			if (m_bStart)
			{
				m_LoadingSc.Draw(hdc);
			}
			return;

		}

		GameTimeDraw();
		FeverTimeDraw();
		return;
	}



	//Rule & Loading
	if (m_bStart)
	{
	
		m_pRule->DrawBitblt(0, 0);
		m_LoadingSc.Draw(hdc);
	}
	else
	{
		m_pRule->DrawBitblt(0, 0);
		JEngine::UIManager::GetInstance()->Draw();
	}
}



bool FlightGameScene::OnSelectCheck()
{
	m_bStart = true;
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

}
