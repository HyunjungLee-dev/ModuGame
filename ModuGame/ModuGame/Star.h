#pragma once
#include "GlobalDefine.h"
#include "JEngine.h"
#include"Label.h"
#include<string>
#include"defines.h"
#include "ResoucesManager.h"

class Star
{
private:
	float m_fx, m_fy;
	float m_fMoveX, m_fMoveY;
	int m_iPoint;
	RECT m_rect;
	JEngine::BitMap*    m_pStar[3];
	JEngine::Label*		m_pPoint;


public:
	Star() {};
	~Star() {};

	void InitStar(float fx, float fy, float FlightX, float FlightY)
	{
		m_fx = fx;
		m_fy = fy;
		m_fMoveX = (FlightX - m_fx) * 0.003f;
		m_fMoveY = (FlightY - m_fy)  * 0.003f;


		m_pStar[0] = JEngine::ResoucesManager::GetInstance()->GetBitmap("res\\FlightGameStar1.bmp");
		m_pStar[1] = JEngine::ResoucesManager::GetInstance()->GetBitmap("res\\FlightGameStar2.bmp");
		m_pStar[2] = JEngine::ResoucesManager::GetInstance()->GetBitmap("res\\FlightGameStar3.bmp");

		m_rect = {(long) m_fx ,(long)m_fy,(long)m_fx + m_pStar[0]->GetWidth(),(long)m_fy + m_pStar[0]->GetHeight() };

		m_pPoint = new JEngine::Label();
		m_iPoint = 100;
	}

	void SetPoint(int point)
	{
		m_iPoint = point;
	}

	void Draw()
	{
		int StarType;

		if (m_iPoint >= 3000)
			StarType = STAR_BLUE;
		else if (m_iPoint >= 1000)
			StarType = STAR_GREEN;
		else
			StarType = STAR_YELLOW;

		float CenterX = m_fx + m_pStar[StarType]->GetWidth()*0.4;
		float CenterY = m_fy + m_pStar[StarType]->GetHeight()*0.4;

		m_pStar[StarType]->Draw((int)CenterX - 15, (int)CenterY - 20);

		m_pPoint->Init(to_string(m_iPoint), (int)CenterX, (int)CenterY, DT_CENTER | DT_WORDBREAK);
		m_pPoint->Draw();
	}

	void Move(float fETime)
	{
		m_fx += m_fMoveX;
		m_fy += m_fMoveY;
		m_rect = { (long)m_fx ,(long)m_fy,(long)m_fx + m_pStar[0]->GetWidth(),(long)m_fy + m_pStar[0]->GetHeight() };
	}

	bool OutRange()
	{
		if (m_fx < 0 - 17 || m_fy < 90 - 18 || m_fx > CLIENT_SIZE_WIDTH || m_fy > 600)
			return true;
		return false;
	}

	bool IsIntersect(RECT rect)
	{
		RECT tmp;
		if (IntersectRect(&tmp, &m_rect, &rect))
			return true;
		else
			return false;
	}

	int GetPoint()
	{
		return m_iPoint;
	}



};
