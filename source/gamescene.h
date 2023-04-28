#pragma once
#include"libs/scene.h"

class GameScene :public Scene{
public:
	GameScene();
	~GameScene()override;
	void Update()override;
	void Draw()override;
private:

};
