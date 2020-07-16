#include "UserManager.h"
#include<algorithm>


	UserManager::UserManager()
	{
	}



	void UserManager::RankSort()
	{
		sort(m_pUserList.begin(), m_pUserList.end(), [](User* user1, User* user2) { return user1->AllScore > user2->AllScore; });

		for (int i = 0; i < m_pUserList.size(); i++)
		{
			m_pUserList[i]->Rank = i + 1;
		}
	}

	void UserManager::Save()
	{
		HANDLE hFile = CreateFile(TEXT("UserList"), GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
		for (int i = 0; i < m_pUserList.size(); i++)
		{
			DWORD writeB;
			WriteFile(hFile, &m_pUserList[i]->Name, sizeof(string), &writeB, NULL);
			WriteFile(hFile, &m_pUserList[i]->AllScore, sizeof(int), &writeB, NULL);
			WriteFile(hFile, &m_pUserList[i]->PaperScore, sizeof(int), &writeB, NULL);
			WriteFile(hFile, &m_pUserList[i]->FlightScore, sizeof(int), &writeB, NULL);
		}
		CloseHandle(hFile);
	}


	void UserManager::SetUserList()
	{
		m_pUserList.push_back(new User);


		m_pUserList.back()->m_pUser = JEngine::ResoucesManager::GetInstance()->GetBitmap("res\\User.bmp");

		m_pUserList.back()->m_pLabelName = new JEngine::Label();
		m_pUserList.back()->m_pLabelAllScore = new JEngine::Label();
		m_pUserList.back()->m_pLabelRank = new JEngine::Label();

		m_pUserList.back()->Rank = 0;
	}

	void UserManager::Load()
	{
		HANDLE hFile = CreateFile(TEXT("UserList"), GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

		DWORD readB;
		if (hFile != INVALID_HANDLE_VALUE) // 파일의 존재 여부 확인
		{
			while (1)
			{
				SetUserList();
				ReadFile(hFile, &m_pUserList.back()->Name, sizeof(string), &readB, NULL);
				if (readB != sizeof(string))
				{
					delete m_pUserList.back();
					m_pUserList.pop_back();
					break;
				}
				ReadFile(hFile, &m_pUserList.back()->AllScore, sizeof(int), &readB, NULL);
				ReadFile(hFile, &m_pUserList.back()->PaperScore, sizeof(int), &readB, NULL);
				ReadFile(hFile, &m_pUserList.back()->FlightScore, sizeof(int), &readB, NULL);
			}
		}

		CloseHandle(hFile);
	}

	void UserManager::SetUser(string name)
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

		m_pUserList.push_back(m_NowPlayingUser);
	}

	void UserManager::Release()
	{
		for (vector<User*>::iterator iter = m_pUserList.begin(); iter != m_pUserList.end(); iter++)
		{
			delete (*iter);
		}
		m_pUserList.clear();
	}

	void UserManager::Draw(int x, int y)
	{
		int DrawY = y;

		for (vector<User*>::iterator iter = m_pUserList.begin(); iter != m_pUserList.end(); iter++)
		{
				(*iter)->Draw(x, DrawY);

			DrawY += 80;
		}
	}

	UserManager::~UserManager()
	{
	}
