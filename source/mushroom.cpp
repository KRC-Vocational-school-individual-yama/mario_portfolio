#include "mushroom.h"
#include"libs/scene.h"
#include"backimage.h"
#include"player.h"

Mushroom::Mushroom(Scene* sc)
	:ItemBase(sc)
	,hImage(-1)
	,pos()
{}
Mushroom::~Mushroom(){
	if (hImage > 0)
		DeleteGraph(hImage);
}

void Mushroom::Init() {
	hImage = LoadGraph("data/texture/kinoko.png");
	assert(hImage > 0);
	pos = {FieldConfig::GraphSize*6,FieldConfig::GraphSize*6};
}

void Mushroom::Update(){
	//“–‚½‚è”»’è‚ðƒvƒŒƒCƒ„[‚Æ‚Æ‚é
	
	Player* p = GetScene()->Invoke<Player>();
	if (p == nullptr)return;
	
	Square<float>player = {p->GetPos(),p->GetSize()};
	if (CheckSquareCollision(player, { pos,{64,64} })) {
		MyDestroy();
	}

}

void Mushroom::Draw(){

	Vec2<float>backMove = {};
	GetScene()->Invoke<BackImage>()->Movement(&backMove);
	Vec2<float>dispPos = pos;
	dispPos += backMove;
	Vec2<int>size = {128/2,64};

	int distance = FieldConfig::GraphSize * 3 + FieldConfig::OffsetHalf;
	DrawRectGraph(dispPos.x, dispPos.y-(distance)
		, size.x * 0,size.y*0,size.x,size.y,hImage,true);
}
