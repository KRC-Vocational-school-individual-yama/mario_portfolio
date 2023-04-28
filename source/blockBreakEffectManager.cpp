#include "blockBreakEffectManager.h"
#include"blockBreakEffect.h"


BlockBreakEffectManager::BlockBreakEffectManager(Scene* sc)
	:Object(sc)
	,effectList()
	,hImage(-1)
{
	effectList.clear();
}
BlockBreakEffectManager::~BlockBreakEffectManager(){
	if (hImage != -1)
		DeleteGraph(hImage);

}
void BlockBreakEffectManager::Init(){
	hImage = LoadGraph("data/texture/”j•Ð.png");
	assert(hImage!=-1);





	//Create();

	//for (auto it = effectList.begin(); it != effectList.end(); it++) {
	//	Emitter*& object = (*it);
	//
	//	object->Init();
	//}
}
void BlockBreakEffectManager::Update(){
	/*if (CheckHitKey(KEY_INPUT_B)) {
		Create();
	}*/

	if (effectList.empty())
		return;

	for (auto it = effectList.begin(); it != effectList.end();) {
		Emitter*& object = (*it);
		object->Update();



		////Á‚·
		//if (object->active) {
		//	object->Destroy();
		//	--count;
		//}
		//
		//if (object == nullptr) {
		//
		//	it = effectList.erase(it);
		//}
		//else {
		//	it++;
		//}

		//Á‚·
		if (!object->active) {
			delete object;
			object = nullptr;
			--count;

			it = effectList.erase(it);
		}
		else {
			it++;
		}
	}

}
void BlockBreakEffectManager::Draw() {
	for (auto*& aEffect : effectList) {
		aEffect->Draw();
	}
	//printfDx("effectNum =%d",count);
}

void BlockBreakEffectManager::Create(){
	count++;
	Emitter* emi = new Emitter;


	emi->Create(hImage,GetScene());

	effectList.emplace_back(emi);

	//for (auto it = effectList.begin(); it != effectList.end(); it++) {
	//	Emitter*& object = (*it);
	//
	//	if(object->initialize)
	//		object->Init();
	//}
}

void BlockBreakEffectManager::SetPos(Vec2<float> position)
{
	for (Emitter* emit : effectList) {
		emit->SetPos(position);
	}
}



void Emitter::Init(){
	for (BlockBreakEffect*& effect : effectList) {
		effect->Init();
	}
}

void Emitter::Update(){
	if (effectList.empty())
		active = false;

	for (auto it = effectList.begin(); it != effectList.end();) {
		BlockBreakEffect*& effect = (*it);
		effect->Update();


		if (!effect->GetActive()) {
			delete effect;
			effect = nullptr;

			it=effectList.erase(it);
		}
		else {
			it++;
		}
		
	}
}

void Emitter::Draw(){
	for (BlockBreakEffect*& effect : effectList) {
		effect->Draw();
	}
}

void Emitter::Destroy() {
	for (auto& it = effectList.begin(); it != effectList.end(); it++) {
		BlockBreakEffect*& obj = (*it);

		delete obj;
		obj = nullptr;

	}
	effectList.clear();
}

void Emitter::Create(int hImage, Scene* sc)
{
	std::vector<Vec2<float>>pos;
	std::vector<Vec2<float>>vec;
	pos.resize(4, Vec2<float>{500.f, 500.f});
	vec.resize(4, Vec2<float>{0, 0});
	vec[0] = Vec2<float>{ 10.f,-25.f };
	vec[1] = Vec2<float>{ -10.f,-25.f };
	vec[2] = Vec2<float>{ 10.f,-45.f };
	vec[3] = Vec2<float>{ -10.f,-45.f };

	for (int i = 0; i < 4; i++) {
		BlockBreakEffect* blockEffect = new BlockBreakEffect(sc);
		blockEffect->SethImage(hImage);
		blockEffect->SetPosAndVec(pos.at(i), vec.at(i));

		effectList.emplace_back(blockEffect);
	}

}

void Emitter::SetPos(Vec2<float> position) {
	for (BlockBreakEffect* effect : effectList) {
		effect->SetPos(position);
	}
}
