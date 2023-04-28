#include "coin.h"

#include"libs/scene.h"
#include"backimage.h"
#include"field.h"

#include"player.h"

Coin::Coin(Scene* sc)
	:Object(sc)
	,hImage(-1)
	,pos()
	,disp(true)
	,anim()
	,keystop(false)
	,updownCount(180)
	,animCount(0)
{}
Coin::~Coin(){
	if(hImage>0)
		DeleteGraph(hImage);
}
void Coin::Init(){

	hImage = LoadGraph("data/texture/ブロックコイン.png");
	assert(hImage != -1);
	//pos = {FieldConfig::GraphSize*5,FieldConfig::GraphSize * 8 };
	pos -= {0,FieldConfig::GraphSize  };
	anim = {0,0};
}
void Coin::Update(){
	if (!disp)MyDestroy();

	animCount++;
	bool key = CheckHitKey(KEY_INPUT_M);
	if (key && !keystop) {
		updownCount = 180;
	}
	keystop = key;
	UpDownMove();
}
void Coin::Draw() {
	if ( !disp)return;

	//128 56
	Vec2<int>size = {128/4,56};

	Vec2<float>backMove = {0,0};
	GetScene()->Invoke<BackImage>()->Movement(&backMove);

	Vec2<float>dispPos = {};
	dispPos = pos;
	dispPos += backMove;
	dispPos += FieldConfig::offsets;

	//真ん中に持ってくる計算
	dispPos -= {size.x/2.f,size.y/2.f};
	dispPos += {FieldConfig::GraphSize/2,FieldConfig::GraphSize/2};

	//上下動
	dispPos.y -= upDownY;

	//表示
	DrawRectGraph(dispPos.x,dispPos.y
		,size.x*(animCount/4%4),size.y*0
		,size.x,size.y,hImage,true);
#ifdef _DEBUG
	dispPos += {size.x / 2.f, size.y / 2.f};
	DrawCircle(dispPos.x,dispPos.y,5,0xffffff,false);
#endif
}

void Coin::UpDownMove(){
	//if (updownCount < 360+120) {//確認用
	updownCount+=10;
	if (updownCount > 360+120) {
		disp = false;
	}

	float rad = DX_PI_F / 180 * updownCount;
	upDownY = cos(rad)+1;
	upDownY /= 2.f;
	upDownY *= FieldConfig::GraphSize*2.5f;
}
