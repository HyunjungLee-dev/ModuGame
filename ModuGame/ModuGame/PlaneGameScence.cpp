#include "PlaneGameScence.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "UIManager.h"
#include "ResoucesManager.h"
#include <Windows.h>
#include "defines.h"

PlaneGameScence::PlaneGameScence()
{
	m_fNextSceTime = 0.0f;
	m_bLoading = false;
}

PlaneGameScence::~PlaneGameScence()
{
}

void PlaneGameScence::Init(HWND hWnd)
{
	m_pBack = JEngine::ResoucesManager::GetInstance()->GetBitmap("res\\FlightGameBack.bmp");
	m_LoadingSc.Init(hWnd);
}

bool PlaneGameScence::Input(float fETime)
{
	return false;
}


void PlaneGameScence::Update(float fETime)
{

}

void PlaneGameScence::Draw(HDC hdc)
{
	m_pBack->DrawBitblt(0, 0);
}

void PlaneGameScence::Release()
{

}
