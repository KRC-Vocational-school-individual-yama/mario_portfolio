#include "mouseedit.h"

#include"libs/scene.h"
#include"field.h"
#include"player.h"
#include"backimage.h"
#include"questionblockManager.h"
#include"breakBlock.h"

namespace {
	static const char* HANDLE_FIELD = "data/texture/marioBlocks__.png";

}

MouseEdit::MouseEdit(Scene* sc)
	:Object(sc)
	,nowNum(0)
	,mousePos()
	,keystop(true)
	,hImages()
	,hImage_item(-1)
{}
MouseEdit::~MouseEdit(){
	for (int& aGraph : hImages) {
		if(aGraph != -1)
			DeleteGraph(aGraph);
	}
	hImages.clear();
	if (hImage_item !=-1)
		DeleteGraph(hImage_item);
}
void MouseEdit::Init(){
	mousePos = {100,100};
	
	Vec2<int>graphSize = {640,128};
	const int graphAllNum = (640 / 64) * (128 / 64);
	int handle[graphAllNum] = {};

	DxLib::LoadDivGraph(HANDLE_FIELD,graphAllNum,graphSize.x/64,graphSize.y/64,64,64,handle);

	auto indexChange = [=] (Vec2<int>pos) ->int {
		int ans = pos.y * (graphSize.x / 64) +pos.x;

		return ans;
	};

	std::vector<Vec2<int>>gPos;
	gPos.reserve(graphAllNum);
	gPos.emplace_back(Vec2<int>{1,1});
	gPos.emplace_back(Vec2<int>{0,1});
	gPos.emplace_back(Vec2<int>{2,0});
	gPos.emplace_back(Vec2<int>{3,0});
	gPos.emplace_back(Vec2<int>{4,0});
	gPos.emplace_back(Vec2<int>{4,1});
	gPos.emplace_back(Vec2<int>{5,0});
	gPos.emplace_back(Vec2<int>{5,1});
	gPos.emplace_back(Vec2<int>{6,0});
	gPos.emplace_back(Vec2<int>{7,0});
	gPos.emplace_back(Vec2<int>{8,0});
	gPos.emplace_back(Vec2<int>{9,0});
	gPos.emplace_back(Vec2<int>{1,0});
	gPos.emplace_back(Vec2<int>{0,0});
	gPos.shrink_to_fit();
	for (int i = 0; i < gPos.size(); i++) {
		hImages.emplace_back(handle[indexChange(gPos[i])]);
	}



	const int questionGAll = (320 / 64) * (64 / 64);
	int ghandle[questionGAll] = {};
	LoadDivGraph("data/texture/ハテナブロック.png" , questionGAll,320/64,64/64,64,64,ghandle);
	hImages.emplace_back(ghandle[0]);
	for (int i = 1; i < (questionGAll); i++) {
		DeleteGraph(ghandle[i]);
	}


	hImage_item= LoadGraph("data/texture/items.png");
	assert(hImage_item != -1);
}
void MouseEdit::Update() {
	MouseWhoweel();
	GetMousePoint(&mousePos.x, &mousePos.y);



	GameScene();
}
void MouseEdit::Draw(){
#ifdef _DEBUG
	printfDx("\n");
	printfDx("LCtrol+Skey  で保存\n");
	printfDx("左クリックで　入れ替え\n");
	printfDx("マウスホイールで　変更\n");
	printfDx("\n");
	//printfDx("mousePos .x= %d\n",mousePos.x);
	//printfDx("mousePos .y= %d\n",mousePos.y);
#endif
	Vec2<float>backMove = {0,0};
	GetScene()->Invoke<BackImage>()->Movement(&backMove);
	Vec2<int> pos = { 0,0 };
	Vec2<int> offsets = {FieldConfig::OffsetX,FieldConfig::OffsetY};
	Vec2<int>fGraphSize = {FieldConfig::GraphSize,FieldConfig::GraphSize};
	pos = mousePos - offsets;
	pos += backMove.Cast<int>();
	pos /= fGraphSize;

#ifdef _DEBUG
	//printfDx("posNums .x= %d\n", pos.x);
	//printfDx("posNums .y= %d\n", pos.y);

	//printfDx("%d\n",nowNum);
	//printfDx("\n");
#endif
	if (nowNum >= static_cast<int>(Field::GNumber::Pstart))
		return;
	if (nowNum <= static_cast<int>(Field::GNumber::empty))
		return;
	int index = nowNum-1;
	if (index < 0)index = 0;
	if (nowNum > static_cast<int>(Field::GNumber::questionBox_inCoin))
		index = static_cast<int>(Field::GNumber::questionBox_inCoin)-1;
	DrawGraph(mousePos.x,mousePos.y, hImages[index],true);



	//ここから下はハテナブロックの処理
	if (nowNum <= static_cast<int>(Field::GNumber::emptyBox))
		return;

	Vec2<int>dispItem = {0,0};
	switch (nowNum) {
	case static_cast<int>(Field::GNumber::questionBox_inCoin)		:	dispItem = {1,1};	break;
	case static_cast<int>(Field::GNumber::questionBox_inMushroom)	:	dispItem = {0,0};	break;
	//case static_cast<int>(Field::GNumber::questionBox_inFire)		:	dispItem = {2,0};	break;
	case static_cast<int>(Field::GNumber::questionBox_inStar)		:	dispItem = {0,1};	break;
	case static_cast<int>(Field::GNumber::questionBox_inOneUp)		:	dispItem = {1,0};	break;
	default															:	dispItem = {1,1};	break;
	}
	DrawRectGraph(mousePos.x,mousePos.y, 64 *dispItem.x, 64 *dispItem.y,64,64,hImage_item,true);
}

void MouseEdit::MouseWhoweel() {
	nowNum -= GetMouseWheelRotVol();
	if (nowNum < 0)nowNum = 0;
	int maxSize = static_cast<int>(Field::GNumber::max);
	if (nowNum > maxSize - 1)nowNum = maxSize - 1;

}

void MouseEdit::GameScene(){
if (!CheckClass<Field>())return;

	bool change = (GetMouseInput() & MOUSE_INPUT_LEFT);
	if (change /*&& !keystop*/) {

		Vec2<float>backMove = { 0,0 };
		GetScene()->Invoke<BackImage>()->Movement(&backMove);
		Vec2<int> pos = { 0,0 };
		Vec2<int> offsets = { FieldConfig::OffsetX,FieldConfig::OffsetY };
		Vec2<int>fGraphSize = { FieldConfig::GraphSize,FieldConfig::GraphSize };
		pos = mousePos-offsets;
		pos -= backMove.Cast<int>();
		pos /= fGraphSize;




		GetScene()->Invoke<Field>()->SetFieldInside(pos, nowNum);

	}

	//ハテナブロックの更新
	if (change && !keystop) {
		QuestionBlockManager* qb = GetScene()->Invoke<QuestionBlockManager>();
		if (qb != nullptr) {
			qb->Reset();
		}
		BreakBlock* bp = GetScene()->Invoke<BreakBlock>();
		if (bp != nullptr) {
			bp->Reset();
		}
	}
	if (!change && keystop) {
		QuestionBlockManager* qb = GetScene()->Invoke<QuestionBlockManager>();
		if (qb != nullptr) {
			qb->Reset();
		}
		BreakBlock* bp = GetScene()->Invoke<BreakBlock>();
		if (bp != nullptr) {
			bp->Reset();
		}
	}
	
	keystop = change;
}
