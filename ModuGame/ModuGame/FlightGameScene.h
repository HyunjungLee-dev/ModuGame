#pragma once
#include "GlobalDefine.h"
#include"LoadingScene.h"
#include "JEngine.h"
#include"Label.h"
#include<list>
#include"Bullet.h"
#include"Star.h"
#include"GameBase.h"
#include"UserManager.h"

struct Flight
{
	JEngine::BitMap*	FlightBit;
	JEngine::POINT		FlightPoint;
	RECT		Rect;
};

class FlightGameScene : public JEngine::Scene
{
private:
	GameBase*			m_pGameBase;

	JEngine::BitMap*	m_pSky[2];
	JEngine::BitMap*	m_pRule;

	Flight				m_Flight;
	list<Bullet*>		m_pBulletList;
	list<Star*>			m_pStarList;


	float				m_fExplosionTime;
	float				m_fSkyX, m_fSkyY[2];

	bool				m_bExplosion;
public:
	virtual void Init(HWND hWnd);
	virtual bool Input(float fETime);
	virtual void Update(float fETime);
	virtual void Draw(HDC hdc);
	virtual void Release();

	void BulletUpdate(float fETime);
	void BulletCollision(float fETime);
	void BulletListClear();

	void StarUpdate(float fETime);
	void StarCollision();
	void StarListClear();

	bool OnSelectCheck();

	FlightGameScene();
	~FlightGameScene();
};

