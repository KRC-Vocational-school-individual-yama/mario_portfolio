#include "gamescene.h"

#include"libs/scenemanager.h"
#include<DxLib.h>
#include"player.h"
#include"field.h"
#include"mouseedit.h"
#include"backimage.h"
#include"questionblockManager.h"
#include"blockBreakEffectManager.h"
#include"breakBlock.h"
#include"goomba.h"
#include"enemyManager.h"
#include"fortress.h"
#include"mushroom.h"
#include"coin.h"

GameScene::GameScene(){
	ChangeDispRank(Create<BackImage>(),-3);
	ChangeDispRank(Create<Field>(),-2);
	Create<QuestionBlockManager>();
	Create<BreakBlock>();
	Create<Fortress>();
	Create<Player>();
	Create<BlockBreakEffectManager>();
	Create<EnemyManager>();
	Create<Mushroom>();
	Create<Coin>();
#ifdef _DEBUG
	Create<MouseEdit>();
#endif
}
GameScene::~GameScene(){

}

void GameScene::Update(){
	Scene::Update();
	if (CheckHitKey(KEY_INPUT_RETURN)) {
		SceneManager::ChangeScene("Title");
	}
}

void GameScene::Draw(){
	Scene::Draw();
	printfDx("エンターキーで\nタイトルに戻る\n");
}

