#pragma once
#include "GlobalDefine.h"
#include"LoadingScene.h"
#include "JEngine.h"

class NameScene : public JEngine::Scene
{
private:
	JEngine::BitMap*	m_pTitle;
	JEngine::BitMap*	m_pName;
	JEngine::BitMap*	m_pBack;
	LoadingScene		m_LoadingSc;

	float				m_fNextSceTime;
	bool				m_bLoading;

public:
	virtual void Init(HWND hWnd);
	virtual bool Input(float fETime);
	virtual void Update(float fETime);
	virtual void Draw(HDC hdc);
	virtual void Release();
	bool OnClick();

	NameScene();
	virtual ~NameScene();
};
