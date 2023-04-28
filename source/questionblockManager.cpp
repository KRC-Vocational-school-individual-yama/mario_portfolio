#include "questionblockManager.h"

#include"libs/scene.h"
#include"field.h"
#include"backimage.h"
#include"questionblock.h"
#include"coin.h"

namespace {
	static const char HANDLE_GRAPHIC[] = "data/texture/ハテナブロック.png";
	static const char HANDLE_GRAPHIC_ITEM[] = "data/texture/items.png";

}

QuestionBlockManager::QuestionBlockManager(Scene* sc)
	:Object(sc)
	,hImage(-1)
	,hImage_Item(-1)
	,emptyhImage(-1)
{}

QuestionBlockManager::~QuestionBlockManager(){
	if (hImage != -1)
		DeleteGraph(hImage);
	if (hImage_Item != -1)
		DeleteGraph(hImage_Item);
	if (emptyhImage != -1)
		DeleteGraph(emptyhImage);
}

void QuestionBlockManager::Init(){
	hImage = LoadGraph(HANDLE_GRAPHIC);
	assert(hImage > 0);
	hImage_Item = LoadGraph(HANDLE_GRAPHIC_ITEM);
	assert(hImage_Item > 0);

	const int maxIndex = (640/64)*(128/64);
	int temphImage[maxIndex] = {};//640 128
	
	LoadDivGraph("data/texture/marioBlocks__.png",maxIndex,640/64,128/64,64,64,temphImage);
	
	emptyhImage = temphImage[0];
	assert(emptyhImage > 0);
	
	for (int i = 1; i < maxIndex; i++) {
		DeleteGraph(temphImage[i]);
	}

	Reset();

	//Field* field = GetScene()->Invoke<Field>();
	//if (field == nullptr) 
	//	return;
	////pos= field->GetFieldInsidePos(Field::GNumber::questionBox)[0].Cast<float>();
	//
	//std::vector<Vec2<int>>questions= field->GetFieldInsidePos//(Field::GNumber::questionBox);
	//for (Vec2<int> aquestion : questions) {
	//	QuestionBlock aq;
	//	aq.SetPos(aquestion.Cast<float>());
	//	aq.SetHandle(hImage);
	//
	//	questionList.emplace_back(aq);
	//}
}

void QuestionBlockManager::Update(){
	for (QuestionBlock*& obj : questionList) {
	//frameCount++;
		obj->Update();
	}
#ifdef _DEBUG
	if (CheckHitKey(KEY_INPUT_B)) {
		auto it= questionList.begin();
		QuestionBlock*& block = (*it);
		block->KnockOn();
	}
#endif
}

void QuestionBlockManager::Draw(){

	Vec2<float>backMove = {0,0};
	BackImage* bi = GetScene()->Invoke<BackImage>();
	if (bi != nullptr) 
		bi->Movement(&backMove);
	for (QuestionBlock*& obj : questionList) {
		obj->Draw(backMove);
	}

	//const int gSize = FieldConfig::GraphSize;
	//backMove += pos * Vec2<float>{gSize, gSize};
	//backMove.x += FieldConfig::OffsetX;
	//backMove.y += FieldConfig::OffsetY;
	//
	//
	//Vec2<float>gAllSize = {320/5,64};
	//DrawRectGraphF(backMove.x, backMove.y,gAllSize.x*(frameCount/5%5),gAllSize.y*0,gSize,gSize,hImage,true);

}

void QuestionBlockManager::Reset(){
	questionList.clear();



	Field* field = GetScene()->Invoke<Field>();
	if (field == nullptr)
		return;

	auto FieldGnumtoBlockItem = [](Field::GNumber num) -> BlockItem {
		BlockItem ans= BlockItem::Coin;
		switch (num){
		case Field::GNumber::questionBox_inCoin		:	ans= BlockItem::Coin;			break;
		case Field::GNumber::questionBox_inMushroom	:	ans= BlockItem::Mushroom;		break;
		case Field::GNumber::questionBox_inStar		:	ans= BlockItem::Star;			break;
		case Field::GNumber::questionBox_inOneUp	:	ans= BlockItem::OneUp;			break;
		default										:	ans= BlockItem::Coin;			break;
		}


		return ans;
	};

	std::vector<std::vector<Vec2<int>>>qboxs;

	qboxs.emplace_back(field->GetFieldInsidePos(Field::GNumber::questionBox_inCoin));
qboxs.emplace_back(field->GetFieldInsidePos(Field::GNumber::questionBox_inMushroom));
qboxs.emplace_back(field->GetFieldInsidePos(Field::GNumber::questionBox_inStar));
qboxs.emplace_back(field->GetFieldInsidePos(Field::GNumber::questionBox_inOneUp));

for (std::vector<Vec2<int>>box : qboxs) {
	for (Vec2<int> aquestion : box) {
		QuestionBlock* aq = new QuestionBlock(GetScene());

		aq->SetPos(aquestion.Cast<float>());
		Field::GNumber gNum = field->GetFieldInside(aquestion * Vec2<int>{FieldConfig::GraphSize, FieldConfig::GraphSize});
		aq->SetMyItem(FieldGnumtoBlockItem(gNum));
		aq->SetHandle(hImage);
		aq->SetHandle_item(hImage_Item);
		aq->SetHandle_bBlock(emptyhImage);

		questionList.emplace_back(aq);
	}
}

//
////コイン ハテナブロック
//std::vector<Vec2<int>>questions = field->GetFieldInsidePos(Field::GNumber::questionBox_inCoin);
//for (Vec2<int> aquestion : questions) {
//	QuestionBlock aq;
//	aq.SetPos(aquestion.Cast<float>());
//	aq.SetMyItem(BlockItem::Coin);
//	aq.SetHandle(hImage);
//	aq.SetHandle_item(hImage_Item);
//	aq.SetHandle_bBlock(emptyhImage);
//
//	questionList.emplace_back(aq);
//}
//questions.clear();
//
////キノコ ハテナブロック
//questions = field->GetFieldInsidePos(Field::GNumber::questionBox_inMushroom);
//for (Vec2<int> aquestion : questions) {
//	QuestionBlock aq;
//	aq.SetPos(aquestion.Cast<float>());
//	aq.SetMyItem(BlockItem::Mushroom);
//	aq.SetHandle(hImage);
//	aq.SetHandle_item(hImage_Item);
//	aq.SetHandle_bBlock(emptyhImage);
//
//	questionList.emplace_back(aq);
//}
//questions.clear();
//
////ファイヤ ハテナブロック
//questions = field->GetFieldInsidePos(Field::GNumber::questionBox_inFire);
//for (Vec2<int> aquestion : questions) {
//	QuestionBlock aq;
//	aq.SetPos(aquestion.Cast<float>());
//	aq.SetMyItem(BlockItem::Fire);
//	aq.SetHandle(hImage);
//	aq.SetHandle_item(hImage_Item);
//	aq.SetHandle_bBlock(emptyhImage);
//
//	questionList.emplace_back(aq);
//}
//questions.clear();
//
////スター ハテナブロック
//questions = field->GetFieldInsidePos(Field::GNumber::questionBox_inStar);
//for (Vec2<int> aquestion : questions) {
//	QuestionBlock aq;
//	aq.SetPos(aquestion.Cast<float>());
//	aq.SetMyItem(BlockItem::Star);
//	aq.SetHandle(hImage);
//	aq.SetHandle_item(hImage_Item);
//	aq.SetHandle_bBlock(emptyhImage);
//
//	questionList.emplace_back(aq);
//}
//questions.clear();
//
////ワンナップ ハテナブロック
//questions = field->GetFieldInsidePos(Field::GNumber::questionBox_inOneUp);
//for (Vec2<int> aquestion : questions) {
//	QuestionBlock aq;
//	aq.SetPos(aquestion.Cast<float>());
//	aq.SetMyItem(BlockItem::OneUp);
//	aq.SetHandle(hImage);
//	aq.SetHandle_item(hImage_Item);
//	aq.SetHandle_bBlock(emptyhImage);
//
//	questionList.emplace_back(aq);
//}
}

void QuestionBlockManager::Collision(Vec2<int> _pos) {

	for (QuestionBlock*& block : questionList) {
		Vec2<int> bPos = block->GetChip().mainPos.Cast<int>();
		bool just = bPos == _pos;

		if (!just)
			continue;


		if (block->GetKnock())continue;
		
		Vec2<float> setPositionValue = block->GetChip().mainPos * Vec2<float>{FieldConfig::GraphSize, FieldConfig::GraphSize};
		Object* item=nullptr;
		switch (block->GetItem()) {
		case BlockItem::Coin:
			item= GetScene()->Create<Coin>();
			assert(item != nullptr);
			dynamic_cast<Coin*>(item)->SetPos(setPositionValue);
			break;
		case BlockItem::Fire:
			break;
		case BlockItem::Star:
			break;
		case BlockItem::OneUp:
			break;
		case BlockItem::Mushroom:
			break;
		default:
			break;
		}
		
		block->KnockOn();
	}

}
