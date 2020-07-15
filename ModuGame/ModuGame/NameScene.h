#pragma once
#include "GlobalDefine.h"
#include"LoadingScene.h"
#include<string>
#include<Label.h>
#include "JEngine.h"

class NameScene : public JEngine::Scene
{
private:
	JEngine::BitMap*	m_pTitle;
	JEngine::BitMap*	m_pName;
	JEngine::BitMap*	m_pBack;
	LoadingScene		m_LoadingSc;

	string				m_strName;
	JEngine::Label*		m_pLabelName;

	float				m_fNextSceTime;
	bool				m_bLoading;				

public:
	virtual void Init(HWND hWnd);
	virtual bool Input(float fETime);
	virtual void Update(float fETime);
	virtual void Draw(HDC hdc);
	virtual void Release();
	bool OnClick();

	void NameTyping();

	NameScene();
	virtual ~NameScene();
};

