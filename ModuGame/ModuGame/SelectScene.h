#pragma once
#include "GlobalDefine.h"
#include"LoadingScene.h"
#include "JEngine.h"
#include"defines.h"
#include"Label.h"
#include"UserManager.h"

class SelectScene : public JEngine::Scene
{
private:
	JEngine::BitMap*	m_pGameSelect;
	LoadingScene		m_LoadingSc;
	JEngine::Label*		m_pPaperScore;
	JEngine::Label*		m_pFlightScore;

	SCENE_INDEX			m_eSelectIndex;
	float				m_fNextSceTime;
	bool				m_bSelect;

public:
	virtual void Init(HWND hWnd);
	virtual bool Input(float fETime);
	virtual void Update(float fETime);
	virtual void Draw(HDC hdc);
	virtual void Release();
	bool OnSelectPaper();
	bool OnSelectPlane();

	SelectScene();
	~SelectScene();
};

