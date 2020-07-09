#pragma once
#include "GlobalDefine.h"
#include"LoadingScence.h"
#include "JEngine.h"

class PlaneGameScence : public JEngine::Scene
{
private:
	JEngine::BitMap*	m_pBack;
	LoadingScence		m_LoadingSc;

	float				m_fNextSceTime;
	bool				m_bLoading;


public:
	virtual void Init(HWND hWnd);
	virtual bool Input(float fETime);
	virtual void Update(float fETime);
	virtual void Draw(HDC hdc);
	virtual void Release();

	PlaneGameScence();
	~PlaneGameScence();
};

