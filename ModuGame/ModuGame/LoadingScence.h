#pragma once
#include "GlobalDefine.h"
#include "JEngine.h"

class LoadingScence 
{
private:
	JEngine::BitMap*	m_pBack;
	JEngine::BitMap*	m_pLoading;

	float				m_fLoadingX;
	float				m_fLoadingY;

	float				m_fSpeedY;

	float				m_fNextSceTime;

public:
	void Init(HWND hWnd);
	bool Input(float fETime);
	void Update(float fETime);
	void Draw(HDC hdc);
	void Release();

	LoadingScence();
	~LoadingScence();
};

