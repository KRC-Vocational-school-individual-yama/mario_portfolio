#pragma once
#include<string>
#include<vector>
#include<list>
#include<assert.h>

#include"myDxLib.h"

#include"scenemanager.h"
#include"colorhsv.h"
#include"../mains/config.h"
class Scene;


class Object {
public:
			Object(Scene* sc):scene(sc)
				,name("")
				,myDestroy(false)
			{}
	virtual ~Object()		=default;
	virtual void Init()		=0;
	virtual void Update()	=0;
	virtual void Draw()		=0;

	void SetName(std::string _name) { name = _name; }
	void MyDestroy() { myDestroy = true; }

	Scene* GetScene() { return scene; }
	std::string GetName() { return name; }
	const bool& GetDestroy() { return myDestroy; }
private:
	Scene* scene;
	std::string name;
	bool myDestroy;
};
/*
	objectクラスに必要なことは
	・名前、
	・所属シーン、
	・アクティブ
	・上記それぞれの get set 関数
	・基礎のコンストラクタ、デストラクタ（コ そのまま デ virtual）
	・基礎のStart,Updae,Draw 関数（virtual =0）
*/