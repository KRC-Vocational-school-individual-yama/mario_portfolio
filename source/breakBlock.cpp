#include "breakBlock.h"

#include"libs/scene.h"
#include"backimage.h"
#include"field.h"
#include"blockBreakEffectManager.h"


namespace {

	class BreakOneBlock {
	public:

		void Update();
		void Draw(Vec2<float>_backMove);
		void Knock();

		void SetPos(Vec2<float>pos);
		Vec2<float> GetPos() { return myChip.mainPos; }
		Vec2<int> GetGridPos() { return myChip.gridPos; }
		Vec2<float> GetDispPos() { return myChip.dispPos; }
		void SetImage(int img) { hImage = img; }
		void Break() { active = false; }
		void IsKnock() { onKnock = true; }
		float Debug() { return sinPosY; }
	private:
		Chip myChip;
		int hImage=-1;
		int knockCount=0;
		float sinPosY = 0.f;
		bool active=true;
		bool onKnock = false;
	};

	void BreakOneBlock::Update() {
		myChip.gridPos = myChip.mainPos.Cast<int>() / Vec2<int>{FieldConfig::GraphSize, FieldConfig::GraphSize};
		Knock();
	}
	void BreakOneBlock::Draw(Vec2<float>_backMove) {
		if (!active)return;
		const int gSize = FieldConfig::GraphSize;

		myChip.dispPos = myChip.mainPos ;
		myChip.dispPos += _backMove;
		myChip.dispPos += FieldConfig::offsets;
		myChip.dispPos.y += sinPosY;

		Vec2<float>gAllSize = { 640/10 ,128/2 };
		DrawRectGraphF(myChip.dispPos.x, myChip.dispPos.y
			, gAllSize.x * 2, gAllSize.y * 0, gSize, gSize, hImage, true);

	}
	void BreakOneBlock::Knock(){
		if (!onKnock) 
			return;
		

		if (knockCount < DX_PI * 180 / DX_PI)
			knockCount += 25.f;// 13.5f;
		else {
			sinPosY = 0.f;
			knockCount = 0;
			onKnock = false;
		}

		const float speed = 13.f;//radius
		sinPosY = -(sin(DX_PI / 180 * knockCount) * speed);

	}
	void BreakOneBlock::SetPos(Vec2<float>pos) {
		myChip.mainPos = pos;
		myChip.gridPos = myChip.mainPos.Cast<int>() / Vec2<int>{FieldConfig::GraphSize, FieldConfig::GraphSize};
		myChip.dispPos = myChip.mainPos;
		myChip.dispPos += FieldConfig::offsets;

	}

	std::list<BreakOneBlock>blockList;
}
BreakBlock::BreakBlock(Scene* sc)
	:Object(sc)
	,hImage(-1)
{}
BreakBlock::~BreakBlock(){
	if (hImage != -1)
		DeleteGraph(hImage);
}
void BreakBlock::Init(){
	hImage = LoadGraph("data/texture/marioBlocks__.png");
	assert(hImage != -1);


	Reset();

}
void BreakBlock::Update(){
	for (BreakOneBlock& obj : blockList) {
		//frameCount++;
		obj.Update();
	}
#ifdef _DEBUG
	//ÉuÉçÉbÉNÇÃèàóù
	//if (CheckHitKey(KEY_INPUT_B)) {
	//	BlockBreak();
	//}
	if (CheckHitKey(KEY_INPUT_V)) {
		blockList.front().IsKnock();
	}
#endif
}



void BreakBlock::Draw(){
	Vec2<float>backMove = { 0,0 };
	BackImage* bi = GetScene()->Invoke<BackImage>();
	if (bi != nullptr)
		bi->Movement(&backMove);
	for (BreakOneBlock& obj : blockList) {
		obj.Draw(backMove);
	}
}

void BreakBlock::Reset() {
	blockList.clear();



	Field* field = GetScene()->Invoke<Field>();
	if (field == nullptr)
		return;

	std::vector<Vec2<int>>box = field->GetFieldInsidePos(Field::GNumber::breakBlock_normal);


	for (Vec2<int>& aquestion : box) {
		BreakOneBlock aq;

		aq.SetPos(aquestion.Cast<float>() * Vec2<float>{FieldConfig::GraphSize,FieldConfig::GraphSize});
		aq.SetImage(hImage);

		blockList.emplace_back(aq);
	}
}

void BreakBlock::Collision(Vec2<int> _pos, bool blockBreak) {

	for (auto it = blockList.begin(); it != blockList.end();) {
		BreakOneBlock& block = (*it);

		bool just = block.GetGridPos().Cast<int>() == _pos;
		if (!just) {
			it++;
			continue;
		}
		if (blockBreak) {


			auto* bp = GetScene()->Invoke<BlockBreakEffectManager>();
			if (bp != nullptr) {
				bp->Create();
				Vec2<float>gsizes = { FieldConfig::GraphSize ,FieldConfig::GraphSize };
				Vec2<float> two = { 4 , 0.5f };
				Vec2<float>tyousei = { 1,-1 };

				Vec2<float> blockEPos = block.GetPos() + (gsizes / two * tyousei);
				bp->SetPos(blockEPos);
				block.Break();
				it = blockList.erase(it);
			}
			return;
		}
		else {
			block.IsKnock();
			it++;
		}
	}

}

void BreakBlock::BlockBreak(){
	auto it = blockList.begin();
	BreakOneBlock& block = (*it);
	block.Break();

	auto* bp = GetScene()->Invoke<BlockBreakEffectManager>();
	if (bp != nullptr) {
		bp->Create();

		bp->SetPos(block.GetDispPos() + Vec2<float>{FieldConfig::GraphSize / 2, FieldConfig::GraphSize / 2});
	}
}
