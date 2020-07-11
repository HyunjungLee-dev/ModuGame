#pragma once
#include "GlobalDefine.h"
#include"LoadingScence.h"
#include "Label.h"
#include "JEngine.h"
#include"defines.h"


struct Paper
{
	PAPER_DIRECTION m_eDirection;
	PAPER_COLOR			m_eColor;
	float				m_fPaperX;
	float				m_fPaperY;

};

class PaperGameScene : public JEngine::Scene
{
private:
	JEngine::BitMap*	m_pBack;
	JEngine::BitMap*	m_pRule;
	JEngine::BitMap*	m_pColor[4];
	JEngine::Label*		m_pScore;
	JEngine::Label*		m_pPaperPoint;
	LoadingScence		m_LoadingSc;

	Paper*				m_pColorPaper[4];
	Paper*				m_pTurnPaper[2];

	float				m_fNextSceTime;
	float				m_fMoveSpeed;
	float				m_fGameTime;

	bool				m_bLoading;
	bool				m_bStart;
	bool				m_bGamePlay;
	bool				m_bMoveing;
	bool				m_bSame;


	int					m_iComboCount;
	int					m_iScore;
	int					m_iPaperPoint;
	int					m_iFeverGauge;



public:
	virtual void Init(HWND hWnd);
	virtual bool Input(float fETime);
	virtual void Update(float fETime);
	virtual void Draw(HDC hdc);
	virtual void Release();

	void SetColorPaper();
	void SetTurnPaper();
	void SlidePaper(float fETime);
	void NotSameMotion(float fETime);
	void IsSameColor(bool bSame);
	bool OnSelectCheck();

	PaperGameScene();
	~PaperGameScene();
};

