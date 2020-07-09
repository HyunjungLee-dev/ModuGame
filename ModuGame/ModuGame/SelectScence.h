#pragma once
#include "GlobalDefine.h"
#include"LoadingScence.h"
#include "JEngine.h"
#include"defines.h"

class SelectScence : public JEngine::Scene
{
private:
	JEngine::BitMap*	m_pGameSelect;
	LoadingScence		m_LoadingSc;

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

	SelectScence();
	~SelectScence();
};

