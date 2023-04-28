#include "fortress.h"
#include"backimage.h"
#include"libs/scene.h"
#include"field.h"

Fortress::Fortress(Scene* sc)
	:Object(sc)
	,hImage{-1}
	,graphSize{0,0}
	,position{0,0}
	,dispPosition{0,0}
{}
Fortress::~Fortress(){
	if (hImage > 0)
		DeleteGraph(hImage);
}
void Fortress::Init(){
	hImage= LoadGraph("data/texture/fortress.png");
	assert(hImage > 0);

	//GetGraphSize(hImage,&graphSize.x,&graphSize.y);
	Vec2<int>fieldTileSize = { FieldConfig::GraphSize,FieldConfig::GraphSize };
	graphSize = fieldTileSize * Vec2<int>{5,5};
	graphSize /= Vec2<int>{2,1};

	GetFastPos();

}
void Fortress::Update(){
#ifdef _DEBUG
	if (CheckHitKey(KEY_INPUT_LSHIFT)) {
		if (CheckHitKey(KEY_INPUT_SPACE)) {
			myDisp = false;
		}
	}
	else
		myDisp = true;
#endif

	auto* bp= GetScene()->Invoke<BackImage>();
	if (bp == nullptr)return;
	Vec2<float> backMove = {};
	bp->Movement(&backMove);

	dispPosition = position + backMove;
	dispPosition += FieldConfig::offsets;
	dispPosition.x += FieldConfig::OffsetHalf;
	dispPosition.y += FieldConfig::GraphSize;
}
void Fortress::Draw(){
#ifdef _DEBUG
	//DrawGraph(dispPosition.x, dispPosition.y,hImage,true);
	//printfDx("fortress>x%f\n",dispPosition.x);
	//printfDx("fortress>y%f\n",dispPosition.y);
	if ( !myDisp)return;
#endif
	DrawExtendGraph(dispPosition.x-graphSize.x,dispPosition.y-graphSize.y
	,dispPosition.x+graphSize.x,dispPosition.y
	,hImage,true);
	
}

void Fortress::GetFastPos(){

	Field* field = GetScene()->Invoke<Field>();
	if (field == nullptr)
		return;

	std::vector<Vec2<int>>aFortress = field->GetFieldInsidePos(Field::GNumber::fortress);
	if (aFortress.size() < 1)return;
	auto it = aFortress.begin();
	Vec2<float>fortressPos= (*it).Cast<float>();
	fortressPos;

	Vec2<float> fieldTileSize = {FieldConfig::GraphSize,FieldConfig::GraphSize};
	position = fortressPos*fieldTileSize;

}
