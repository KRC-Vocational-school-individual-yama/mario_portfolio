#include "enemyManager.h"
#include"enemyBase.h"
#include"goomba.h"
#include"player.h"
#include"field.h"
#include"libs/scene.h"

EnemyManager::EnemyManager(Scene* sc)
	:Object(sc)
	,enemies()
	,count(0)
{}
EnemyManager::~EnemyManager(){
	for (auto it = enemies.begin(); it != enemies.end();) {
		EnemyBase* enemy = dynamic_cast<EnemyBase*>(*it);

		delete enemy;
		enemy = nullptr;

		it= enemies.erase(it);
	}
}
void EnemyManager::Init(){
	enemies.clear();

	Field* fp= GetScene()->Invoke<Field>();
	if (fp == nullptr) return;
	
	std::vector<Vec2<int>>enePoss= fp->GetFieldInsidePos(Field::GNumber::EnemyGoomba);
	Vec2<float>tileSize={FieldConfig::GraphSize, FieldConfig::GraphSize};

	for (auto& aPos : enePoss) {
		EnemyBase* ene = new Goomba(GetScene());

		ene->SetPos(aPos.Cast<float>()*tileSize);
		ene->SetSize({64,64});
		count++;
		enemies.emplace_back(ene);
	}


	for (auto& enemy : enemies)
		enemy->Init();
}
void EnemyManager::Update(){


	for (auto enemy : enemies) {
		for (auto ene : enemies) {
			enemy->CollisionToOther(ene);
		}
	}


	for (auto it = enemies.begin(); it != enemies.end(); ) {
		EnemyBase* ene = (*it);
		

		ene->Update();
		
		if (ene->GetDestroy()) {
			count--;
			delete ene;
			ene = nullptr;

			it= enemies.erase(it);
		}
		else {
			it++;
		}
	}


}
void EnemyManager::Draw(){
	for (auto& enemy : enemies) {
		enemy->Draw();
	}
#ifdef _DEBUG
	printfDx("count= %d\n",count);
#endif
}

bool EnemyManager::Collisions(Player* player){
	bool ans=false;
	if (player == nullptr)return false;
	Vec2<float> pos		=player->GetPos();
	Vec2<float> size	=player->GetSize();
	Vec2<float>vec		=player->GetVelocity();
	pos.x -= size.x/2;

	for (auto& enemy : enemies) {
		ans= ans || enemy->Collision(pos,size,vec);
		//ans|= enemy->Collision(pos,size,vec);
	}

	return ans;
}
