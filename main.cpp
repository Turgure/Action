#include "DxLib.h"
#include "Graphic.h"
#include "Scenes.h"
using namespace std;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow){
	ChangeWindowMode(true);
	if(DxLib_Init() == -1) return -1;
	SetDrawScreen(DX_SCREEN_BACK);

	SetGraphMode(640, 480, 32);
	SetMainWindowText("SpriteManager test");

	SceneManager::run(std::make_shared<SceneA>());

	DxLib_End();
	return 0;
}