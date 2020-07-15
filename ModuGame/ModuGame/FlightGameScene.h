#pragma once
#include "GlobalDefine.h"
#include"LoadingScene.h"
#include "JEngine.h"
#include"Label.h"
#include<list>
#include"Bullet.h"
#include"Star.h"
#include"Data.h"

struct Flight
{
	JEngine::BitMap*	FlightBit;
	JEngine::POINT		FlightPoint;
	RECT				Rect;
};

class FlightGameScene : public JEngine::Scene
{
private:
	JEngine::BitMap*	m_pSky[2];
	JEngine::BitMap*	m_pFrame;
	JEngine::BitMap*	m_pRule;
	JEngine::BitMap*	m_pTimeBar;
	JEngine::BitMap*	m_pTimeOver;
	JEngine::BitMap*	m_pFever[3];
	JEngine::BitMap*	m_pFeverEffect;
	JEngine::BitMap*    m_pExplosion[3];

	JEngine::Label*		m_pGameTime;
	JEngine::Label*		m_pScore;

	FEVERSTATE			m_eFeverState;
	FEVERSTATE			m_eUltraTime;

	LoadingScene		m_LoadingSc;

	Flight				m_Flight;
	
	list<Bullet*> m_pBulletList;
	list<Star*> m_pStarList;

	float				m_fNextSceTime;
	float				m_fGameTime;
	float				m_fExplosionTime;
	float				m_fSkyX, m_fSkyY[2];

	int					m_iScore;
	int					m_iBonusPoint;
	int					m_iFeverGauge;

	bool				m_bLoading;
	bool				m_bStart;
	bool				m_bGamePlay;
	bool				m_bTimeOver;
	bool				m_bExplosion;
	bool				m_bFeverDown;


	float				m_fEffectTime;
	float				m_fUltraTime;


	bool				m_bFeverTime;



	



public:
	virtual void Init(HWND hWnd);
	virtual bool Input(float fETime);
	virtual void Update(float fETime);
	virtual void Draw(HDC hdc);
	virtual void Release();

	void SetMember();
	void ScoreDraw();
	void GameTimeDraw();
	void FeverTimeDraw();

	void BulletUpdate(float fETime);
	void BulletCollision(float fETime);
	void BulletListClear();

	void StarUpdate(float fETime);
	void StarCollision();
	void StarListClear();

	void FeverUpdate(float fETime);
	void DownFeverGauge();
	
	bool OnSelectCheck();



	FlightGameScene();
	~FlightGameScene();
};

