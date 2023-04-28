#include "title.h"

#include"libs/myDxLib.h"
#include"libs/scenemanager.h"

Title::Title(){

}
Title::~Title(){

}
void Title::Update() {
	
	bool flag = CheckHitKey(KEY_INPUT_SPACE);
	if (flag) {
		SceneManager::ChangeScene("Game");
	}
	flag = CheckHitKey(KEY_INPUT_R);
	if (flag) {
		SceneManager::ChangeScene("Unown");
	}
}
void Title::Draw() {
	Vec2<int> poss = { 100,100 };
	DrawFormatString(poss.x, poss.y * 1, 0xffffff, "_現在_　　　　TitleScene　（仮");
	DrawFormatString(poss.x, poss.y * 2, 0xffffff, "Spaceキー　　 GameScene　 （仮");
	DrawFormatString(poss.x, poss.y * 3, 0xffffff, "Rキー　　　　 UnownScene　 （未作成");
}