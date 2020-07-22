#include "Object.h"



Object::Object()
{
}


Object::~Object()
{
}


void Object::Init()
{
	m_pFrame = JEngine::ResoucesManager::GetInstance()->GetBitmap("res\\FlightGameBackTra.bmp");
	m_pTimeBar = JEngine::ResoucesManager::GetInstance()->GetBitmap("res\\ColoredPaperTimeBar.bmp");
	m_pTimeOver = JEngine::ResoucesManager::GetInstance()->GetBitmap("res\\TimeOver.bmp");

	m_pFever[0] = JEngine::ResoucesManager::GetInstance()->GetBitmap("res\\Fever1.bmp");
	m_pFever[1] = JEngine::ResoucesManager::GetInstance()->GetBitmap("res\\Fever2.bmp");
	m_pFever[2] = JEngine::ResoucesManager::GetInstance()->GetBitmap("res\\Fever3.bmp");
	m_pFeverEffect = JEngine::ResoucesManager::GetInstance()->GetBitmap("res\\FeverEffect3.bmp");
	m_pTimeOver = JEngine::ResoucesManager::GetInstance()->GetBitmap("res\\TimeOver.bmp");

	m_pBonusStar[0] = JEngine::ResoucesManager::GetInstance()->GetBitmap("res\\FlightGameStar1.bmp");
	m_pBonusStar[1] = JEngine::ResoucesManager::GetInstance()->GetBitmap("res\\FlightGameStar2.bmp");
	m_pBonusStar[2] = JEngine::ResoucesManager::GetInstance()->GetBitmap("res\\FlightGameStar3.bmp");

	m_pExplosion[0] = JEngine::ResoucesManager::GetInstance()->GetBitmap("res\\explosion1.bmp");
	m_pExplosion[1] = JEngine::ResoucesManager::GetInstance()->GetBitmap("res\\explosion2.bmp");
	m_pExplosion[2] = JEngine::ResoucesManager::GetInstance()->GetBitmap("res\\explosion3.bmp");


	m_pGameTime = new JEngine::Label();
	m_pScore = new JEngine::Label();
	m_pBonusPoint = new JEngine::Label();
}


void Object::ScoreDraw(int score)
{
	m_pScore->Init(to_string(score), CLIENT_SIZE_WIDTH * 0.48, CLIENT_SIZE_HEIGHT * 0.03, DT_CENTER | DT_WORDBREAK);
	m_pScore->Draw();
}

void Object::GameTimeDraw(float gameTime)
{
	char ch[128];

	float time = (gameTime - GetTickCount()) / 1000.0f;
	int sec = (int)(gameTime - GetTickCount()) / 1000.0f;
	int sec2 = (int)((time - sec) * 100);

	if (sec < 10)
		sprintf(ch, "0%d : %d ", sec, sec2);
	else
		sprintf(ch, "%d : %d ", sec, sec2);
	string str(ch);
	m_pGameTime->Init(str, 40, 620, DT_CENTER | DT_WORDBREAK);
	m_pTimeBar->StretchDraw(25, 620, ((gameTime - GetTickCount()) / 1000.0f) / 45, 1);

	m_pGameTime->Draw();
}

void Object::StarDraw(int BonusPoint, int textx, int texty, int starX, int starY)
{
	if (BonusPoint >= 3000)
		m_pBonusStar[STAR_BLUE]->Draw(starX, starY);
	else if (BonusPoint >= 1000)
		m_pBonusStar[STAR_GREEN]->Draw(starX, starY);
	else
		m_pBonusStar[STAR_YELLOW]->Draw(starX, starY);
	m_pBonusPoint->Init(to_string(BonusPoint), textx, texty, DT_CENTER | DT_WORDBREAK);
	m_pBonusPoint->Draw();
}

void Object::ExplosionDraw(int MotionNum,int x, int y)
{
	m_pExplosion[MotionNum]->Draw(x, y);
}

