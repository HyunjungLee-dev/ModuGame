#pragma once
#include"JEngine.h"
#include"ResoucesManager.h"
#include"JEngine.h"
#include"Label.h"
#include"defines.h"
#include"SingleTon.h"
#include<algorithm>

	struct User
	{
		string Name;
		int Rank;
		int AllScore;
		int PaperScore;
		int FlightScore;
		int MoleScore;

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
			else if (type == MOLE)
				MoleScore = num;
			AllScore = PaperScore + FlightScore;
		}

		void Draw(int x, int y)
		{
			m_pUser->Draw(x, y);

			m_pLabelName->Init(Name, x + 120, y + 10, DT_LEFT | DT_WORDBREAK);
			m_pLabelName->Draw();

			m_pLabelAllScore->Init(to_string(AllScore), x + 120, y + 40, DT_LEFT | DT_WORDBREAK);
			m_pLabelAllScore->Draw();

			m_pLabelRank->Init(to_string(Rank), x + 20, y + 28, DT_LEFT | DT_WORDBREAK);
			m_pLabelRank->Draw();
		}


	};


	class UserManager : public SingleTon < UserManager>
	{
	private:
		User* m_NowPlayingUser;
		vector<User*> m_pUserList;
	public:
		UserManager();
		~UserManager();


		void Release();
		void SetUserList();
		void Save();
		void Load();
		void Draw(int x, int y);
		void SetUser(string name);
		void RankSort();
		



		User* GetUser()
		{
			return m_NowPlayingUser;
		}
		
		int ListSize()
		{
			return m_pUserList.size();
		}

	};



