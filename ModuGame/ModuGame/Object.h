#pragma once
#include "GlobalDefine.h"
#include "Label.h"
#include "JEngine.h"
#include"ResoucesManager.h"
#include"defines.h"

class Object
{
protected:
	JEngine::BitMap*	m_pFrame;
	JEngine::BitMap*	m_pTimeBar;
	JEngine::BitMap*	m_pTimeOver;
	JEngine::BitMap*	m_pFever[3];
	JEngine::BitMap*	m_pBonusStar[3];
	JEngine::BitMap*    m_pExplosion[3];
	JEngine::BitMap*	m_pFeverEffect;

	JEngine::Label*		m_pScore;
	JEngine::Label*		m_pBonusPoint;
	JEngine::Label*		m_pGameTime;
public:
	Object();
	~Object();

	void Init();
	void ScoreDraw(int score);
	void GameTimeDraw(float gameTime);
	void StarDraw(int BonusPoint, int textx, int texty ,int starX, int starY);
	void ExplosionDraw(int motionNum,int x, int y);
};

