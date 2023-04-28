#include"app.h"
#include<DxLib.h>
#include"config.h"
#include"../libs/scenemanager.h"
#include"../libs/fpstimer.h"

namespace {
	FpsTimer* fpsManager;
}

namespace App {



	void Init() {
		fpsManager = new FpsTimer;

		SceneManager::Init();
	}
	void Update() {
		fpsManager->Update();
#ifdef _DEBUG
		printfDx("\n");
#endif //_DEBUG

		SceneManager::Update();

	}
	void Draw() {
		SceneManager::Draw();
#ifdef _DEBUG
		fpsManager->Draw();
#endif //_DEBUG
		fpsManager->Wait();
	}
	void Delete() {
		SceneManager::Delete();

		delete fpsManager;
	}
}