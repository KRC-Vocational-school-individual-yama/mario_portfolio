#include "backimage.h"

#include"libs/scene.h"
#include"field.h"
#include"player.h"

#include <string_view>
#include<typeinfo>

BackImage::BackImage(Scene* sc)
	:Object(sc)
	, hImage(-1)
	, pos()
	, vec()
{}

BackImage::~BackImage() {
	if (hImage > 0)
		DeleteGraph(hImage);
}
void BackImage::Init() {
	hImage = LoadGraph("data/texture/mario_backImage.png");
	assert(hImage > 0);

	pos = { 0,0 };
	vec = { 0,0 };
}
void BackImage::Update() {

	//プレイヤーの移動に合わせて動く
	Scroll();

	//適用
	Player* player = GetScene()->Invoke<Player>();
	if (player != nullptr) {
		Vec2<float>playerPos = player->GetDispPos();

#ifdef _DEBUG

#else
		if (playerPos.x > SCREEN_WIDTH / 2.f-FieldConfig::GraphSize*1.5f)
#endif // _DEBUG
			pos += vec;
	}
}

void BackImage::Draw(){
	Vec2<float> moves = {0,0};
	Movement(&moves);
#ifdef _DEBUG
	//printfDx("moves.x= %.0f\n",moves.x);
	//printfDx("moves.y= %.0f\n",moves.y);
#endif
	float justY = -128;
	Vec2<float> changePos = moves;
	changePos.y += justY;
	//基本の描画
	DrawGraph(static_cast<int>(changePos.x)%3072,changePos.y,hImage,true);
	//右側描画
	DrawGraph(static_cast<int>(changePos.x)%3072+3072,changePos.y,hImage,true);

}

void BackImage::Movement(Vec2<float>* _moves){
	if(_moves == nullptr)return;
	Vec2<float> reverse = {-1,-1};
	reverse *= pos;

	*_moves = reverse;
}

void BackImage::MoveVec(Vec2<float>* _mVec){
	*_mVec = vec;
}

void BackImage::Scroll(){
	bool upKey = CheckHitKey(KEY_INPUT_UP)		;//||CheckHitKey(KEY_INPUT_W);
	bool downKey = CheckHitKey(KEY_INPUT_DOWN)	;//||CheckHitKey(KEY_INPUT_S);
	bool leftKey = CheckHitKey(KEY_INPUT_LEFT)	||CheckHitKey(KEY_INPUT_A);
	bool rightKey = CheckHitKey(KEY_INPUT_RIGHT)||CheckHitKey(KEY_INPUT_D);

	//移動量Y

	if (upKey) {
		vec.y-=10;
	}
	if (downKey) {
		vec.y+=10;
	}
	//if (leftKey) {
	//	vec.x-=10;
	//}
	//if (rightKey) {
	//	vec.x+=10;
	//}
	//vecを戻す
	if (!upKey && !downKey) {
		vec.y = 0;
	}
	//if (!leftKey && !rightKey) {
	//	vec.x = 0;
	//}
	//vecの上下限
	//if (vec.x > 10) vec.x = 10;
	//if (vec.x < -10) vec.x = -10;
	if (vec.y > 10) vec.y = 10;
	if (vec.y < -10)vec.y = -10;




	//移動量X


	Player* player = GetScene()->Invoke<Player>();
	if (player != nullptr) {
	//{
	//	int num = player->GetVelocity().x;
	//	vec.x = num > 0 ? num : 0;
	//}
			vec.x = player->GetVelocity().x;

	}
}
