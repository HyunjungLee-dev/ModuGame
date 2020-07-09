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
	//엔진 객체를 생성하고 타이틀과 윈도우 사이즈를 넣어준다.
	srand(time(NULL));
	JEngine::EngineMain engine("모두의 게임", CLIENT_SIZE_WIDTH, CLIENT_SIZE_HEIGHT);
	//씬을 등록한다. 첫번째 등록하는 씬이 초기화면이 된다.
	JEngine::SceneManager::GetInstance()->RegistScene(new TitleScene);
	JEngine::SceneManager::GetInstance()->RegistScene(new SelectScence);
	JEngine::SceneManager::GetInstance()->RegistScene(new PaperGameScene);
	JEngine::SceneManager::GetInstance()->RegistScene(new PlaneGameScence);


	//엔진 시작
	return engine.StartEngine(hInstance);
}