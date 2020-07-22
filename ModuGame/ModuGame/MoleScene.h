#pragma once
#include "GlobalDefine.h"
#include"LoadingScene.h"
#include "JEngine.h"
#include"Label.h"
#include"UserManager.h"
#include"GameBase.h"
#include"AnimalManager.h"




class MoleScene : public JEngine::Scene
{
private:
	GameBase*			m_pGameBase;

	JEngine::BitMap*	m_pBack;
	JEngine::BitMap*	m_pRule;

	JEngine::POINT      m_MousePoint; 

	AnimalManager*		m_pAnimalManager;

	float				m_fExplosionTime;
	bool				m_bExplosion;

public:
	virtual void Init(HWND hWnd);
	virtual bool Input(float fETime);
	virtual void Update(float fETime);
	virtual void Draw(HDC hdc);
	virtual void Release();

	void AnimalUpdate(float fETime);
	void RandAnimalUpdate(float fETime);
	void CollisionAnimal();

	bool OnSelectCheck();



	MoleScene();
	~MoleScene();
};

