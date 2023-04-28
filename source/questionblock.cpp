#include "questionblock.h"

QuestionBlock::QuestionBlock(Scene* sc)
	:Object(sc)
	,count(0)
	, knockCount(0)
	, hImage(-1)
	, hImage_item(-1)
	, breakhImage(-1)
	, myItem(BlockItem::Coin)
	, isBreak(false)
	, myChip()
	, sinPosY(0.f)
{}
QuestionBlock::~QuestionBlock(){

}
void QuestionBlock::Init(){

}
void QuestionBlock::Update(){
	myChip.gridPos = myChip.mainPos.Cast<int>() / Vec2<int>{FieldConfig::GraphSize, FieldConfig::GraphSize};

	count++;
	Knock();
}
void QuestionBlock::Draw(Vec2<float>_backMove) {
	const int gSize = FieldConfig::GraphSize;

	myChip.dispPos = myChip.mainPos * Vec2<float>{gSize, gSize};
	myChip.dispPos += _backMove;
	myChip.dispPos += FieldConfig::offsets;
	myChip.dispPos.y += sinPosY;


	if (!isBreak) {
		Vec2<float>gAllSize = { 320 / 5,64 };
		DrawRectGraphF(myChip.dispPos.x, myChip.dispPos.y, gAllSize.x * (count / 5 % 5), gAllSize.y * 0, gSize, gSize, hImage, true);

#ifdef _DEBUG
		Vec2<int>item_gridPos = { 0,0 };
		switch (myItem) {
		case BlockItem::Coin:	item_gridPos = { 1,1 };		break;
		case BlockItem::Mushroom:	item_gridPos = { 0,0 };		break;
		case BlockItem::Fire:	item_gridPos = { 2,0 };		break;
		case BlockItem::Star:	item_gridPos = { 0,1 };		break;
		case BlockItem::OneUp:	item_gridPos = { 1,0 };		break;
		default:	item_gridPos = { 1,1 };		break;
		}
		Vec2<float>gItemSize = { 192 / 3,128 / 2 };
		DrawRectGraph(myChip.dispPos.x, myChip.dispPos.y, gItemSize.x * item_gridPos.x, gItemSize.y * item_gridPos.y, gSize, gSize, hImage_item, true);
#endif
	}
	else {
		Vec2<float> gAllSize = { 640 / 64,128 / 64 };
		//DrawRectGraphF(_backMove.x,_backMove.y,gSize*0,gSize*0,gSize,gSize,breakhImage,true);
		DrawGraphF(myChip.dispPos.x, myChip.dispPos.y, breakhImage, true);
	}

}



void QuestionBlock::Knock() {
	if (!isBreak)return;
	//		isBreak=true;

	if (knockCount < DX_PI * 180 / DX_PI)
		knockCount += 13.5f;

	const float speed = 13.f;//radius
	sinPosY = -(sin(DX_PI / 180 * knockCount) * speed);

	//ここでアイテム出現
	//	   ||
	//	　＼／
	// program~~


}