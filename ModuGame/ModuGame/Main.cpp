#include <Windows.h>
#include "EngineMain.h"
#include "SceneManager.h"
#include "TitleScene.h"
#include"SelectScence.h"
#include"PlaneGameScence.h"
#include"PaperGameScene.h"
#include <crtdbg.h> 
#include <time.h>
#include"defines.h"




int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	//���� ��ü�� �����ϰ� Ÿ��Ʋ�� ������ ����� �־��ش�.
	srand(time(NULL));
	JEngine::EngineMain engine("����� ����", CLIENT_SIZE_WIDTH, CLIENT_SIZE_HEIGHT);
	//���� ����Ѵ�. ù��° ����ϴ� ���� �ʱ�ȭ���� �ȴ�.
	JEngine::SceneManager::GetInstance()->RegistScene(new TitleScene);
	JEngine::SceneManager::GetInstance()->RegistScene(new SelectScence);
	JEngine::SceneManager::GetInstance()->RegistScene(new PaperGameScene);
	JEngine::SceneManager::GetInstance()->RegistScene(new PlaneGameScence);


	//���� ����
	return engine.StartEngine(hInstance);
}