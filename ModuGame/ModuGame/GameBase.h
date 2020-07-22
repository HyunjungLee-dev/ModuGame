#pragma once
#include "GlobalDefine.h"
#include "Label.h"
#include "JEngine.h"
#include"defines.h"
#include"LoadingScene.h"
#include"UserManager.h"
#include"SceneManager.h"
#include"Object.h"

enum SETTER
{
	SET,
	ADD
};

class GameBase : public Object
{
private:
	LoadingScene		m_LoadingSc;

	FEVERSTATE			m_eFeverState;
	FEVERSTATE			m_eUltraTime;

	float				m_fNextSceTime;
	float				m_fGameTime;
	float				m_fEffectTime;
	float				m_fUltraTime;

	bool				m_bLoading;
	bool				m_bStart;
	bool				m_bGamePlay;
	bool				m_bFeverTime;
	bool				m_bTimeOver;
	bool				m_bFeverDown;

	bool				m_bGameEnd;

	int					m_iBonusPoint;
	int					m_iScore;
	int					m_iFeverGauge;



public:
	void Init(HWND hWnd);
	void FeverTimeDraw();
	void FeverUpdate(float fETime);
	void DownFeverGauge();
	void GameEnd(GAME type, float fETime);
	void FeverStateCheck(float fETime);
	void GameStart(float fETime);
	void DisplayDraw(HDC hdc);
	void LoadingDraw(HDC hdc);
	void StarDraw(int textx, int texty, int starX, int starY);


	void SetFeverState(FEVERSTATE state) { m_eFeverState = state; }
	void SetFeverDown(bool b) { m_bFeverDown = b; }
	void SetTimeOver(bool b) { m_bTimeOver = b; }
	void SetStart(bool b) { m_bStart = b; }

	void SetFeverGauge(int gauge, SETTER type);
	void SetBonusPoint(int point, SETTER type);
	void SetNextTime(int time, SETTER type);


	void AddScore(int Score) { m_iScore += Score; }
	void AddScore() { m_iScore += m_iBonusPoint; }


	bool GetFeverTime() { return m_bFeverTime; }
	bool GetGamePlay() { return m_bGamePlay; }
	bool GetTimeover() { return m_bTimeOver; }
	int  GetBonusPoint() { return m_iBonusPoint; }
	float GetGameTime() { return m_fGameTime; }
	bool GetStart() { return m_bStart; }
	float GetNextTime() { return m_fNextSceTime; }
	bool GetFeverGauge() { return m_iFeverGauge; }
	FEVERSTATE GetFeverState() { return m_eFeverState; }
	bool GetGameEnd() { return m_bGameEnd; }


	GameBase();
	~GameBase();
};


