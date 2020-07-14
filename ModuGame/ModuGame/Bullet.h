#pragma once
#include "GlobalDefine.h"
#include"LoadingScene.h"
#include "JEngine.h"
#include"Label.h"
#include "ResoucesManager.h"

class Bullet
{
private:
	float m_fx, m_fy;
	float m_fMoveX,m_fMoveY;
	JEngine::BitMap*    m_pBullet;

public:
	Bullet() {};
	~Bullet() {};

	void InitBullet(float fx, float fy,float FlightX, float FlightY)
	{
		m_fx = fx;
		m_fy = fy;
		m_fMoveX = (FlightX - m_fx) * 0.003f;
		m_fMoveY = (FlightY - m_fy)  * 0.003f;
		m_pBullet = JEngine::ResoucesManager::GetInstance()->GetBitmap("res\\FlightGameBullet.bmp");
	}

	void Draw()
	{
		m_pBullet->Draw(m_fx, m_fy);
	}

	void Move(float fETime)
	{
		m_fx += m_fMoveX;
		m_fy += m_fMoveY;
	}

	bool OutRange()
	{
		if (m_fx < 0 - 17 || m_fy < 90 -18 || m_fx > CLIENT_SIZE_WIDTH || m_fy > 600)
			return true;
		return false;
	}

	bool IsPointInRect(RECT rect)
	{
		if ((rect.left <= m_fx && m_fx <= rect.right) && (rect.top <= m_fy && m_fy <= rect.bottom))
			return true;
		else
			return false;
	}


};
