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
	object�N���X�ɕK�v�Ȃ��Ƃ�
	�E���O�A
	�E�����V�[���A
	�E�A�N�e�B�u
	�E��L���ꂼ��� get set �֐�
	�E��b�̃R���X�g���N�^�A�f�X�g���N�^�i�R ���̂܂� �f virtual�j
	�E��b��Start,Updae,Draw �֐��ivirtual =0�j
*/