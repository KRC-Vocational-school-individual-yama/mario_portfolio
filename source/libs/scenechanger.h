#pragma once
#include<string>
#include<windows.h>
#include<assert.h>

class Scene;

class SceneChanger {
public:
	Scene* StartScene();

	Scene* Changer(std::string name);
};