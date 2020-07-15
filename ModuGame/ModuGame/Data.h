#pragma once
#include"JEngine.h"
#include"ResoucesManager.h"
#include"JEngine.h"
#include"Label.h"
#include"defines.h"
#include"SingleTon.h"

struct User
{
	string Name;
	int Rank;
	int AllScore;
	int PaperScore;
	int FlightScore;

	JEngine::BitMap*	m_pUser;
	JEngine::Label*		m_pLabelName;
	JEngine::Label*		m_pLabelAllScore;
	JEngine::Label*		m_pLabelRank;


	void SetUser(GAME type, int num)
	{
		if (type == FLIGHT)
			FlightScore = num;
		else if (type == PAPER)
			PaperScore = num;
	}

	void Draw(int x, int y)
	{
		m_pUser->Draw(x,y);

		m_pLabelName->Init(Name, x + 120, y + 10, DT_LEFT | DT_WORDBREAK);
		m_pLabelName->Draw();

		AllScore = PaperScore + FlightScore;
		m_pLabelAllScore->Init(to_string(AllScore), x + 120, y + 40, DT_LEFT | DT_WORDBREAK);
		m_pLabelAllScore->Draw();

		m_pLabelRank->Init(to_string(Rank),x + 20, y + 28, DT_LEFT | DT_WORDBREAK);
		m_pLabelRank->Draw();
	}
};


class Data : public SingleTon < Data>
{
private:
	User* m_NowPlayingUser;
	vector<User*> m_pRank;
public:
	Data();
	~Data();

	//void Init(HWND hWnd) {};
	//bool Input(float fETime) {};
	//void Update(float fETime) {};
	//void Draw(HDC hdc) {};
	//void Release() {};

	void SetUser(string name)
	{
		m_NowPlayingUser = new User;
		m_NowPlayingUser->m_pLabelName = new JEngine::Label();
		m_NowPlayingUser->m_pLabelAllScore = new JEngine::Label();
		m_NowPlayingUser->m_pLabelRank = new JEngine::Label();

		m_NowPlayingUser->Name = name;
		m_NowPlayingUser->FlightScore = 0;
		m_NowPlayingUser->PaperScore = 0;
		m_NowPlayingUser->AllScore = 0;
		m_NowPlayingUser->Rank = 0;

		m_NowPlayingUser->m_pUser = JEngine::ResoucesManager::GetInstance()->GetBitmap("res\\NowUser.bmp");
	}


	User* GetUser()
	{
		return m_NowPlayingUser;
	}

	
};


