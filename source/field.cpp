#include "field.h"
#include"save.h"
#include"backimage.h"
#include"libs/scene.h"
#include<math.h>

namespace {
	//static const int FieldWidth = ;
}

Field::Field(Scene* sc)
	:Object(sc)
	,maps()
	,keystop(true)
	,hImage(-1)
	,fieldWidth(0)
{}
Field::~Field(){
	if(hImage!=-1)
		DeleteGraph(hImage);
	
}
void Field::Init(){
	hImage= LoadGraph("data/texture/marioBlocks__.png");
	assert(hImage>0);
	FieldLoad();
	fieldWidth = maps.size() / FieldConfig::FieldHeigth;


	//for (int i = 0; i < fieldWidth; i++) {
	//	for (int j = 0; j < FieldConfig::FieldHeigth; j++) {
	//		const int index = IndexChange(i,j);
	//		Vec2<int>grid = {i,j};
	//		maps[index].gridPos = grid;
	//		maps[index].mainPos = grid.Cast<float>() * Vec2<float>{FieldConfig::GraphSize,FieldConfig::GraphSize};
	//	}
	//}
}
void Field::Update(){
	bool saveKey = CheckHitKey(KEY_INPUT_S)&&CheckHitKey(KEY_INPUT_LCONTROL);
	bool reloadKey = CheckHitKey(KEY_INPUT_R);
	bool allKey = saveKey || reloadKey;
	if (reloadKey && !keystop) {
		FieldLoad();
	}
	if (saveKey && !keystop) {
		FieldSave();
	}

	keystop = allKey;
}
void Field::Draw(){
	Vec2<float>backMove = {0,0};
	BackImage* bi= GetScene()->Invoke<BackImage>();
	if (bi != nullptr) 
		bi->Movement(&backMove);

	

//	for (int i = 0; i < fieldWidth; i++) {
//		for (int j = 0; j < FieldConfig::FieldHeigth; j++) {
//
//			int index = IndexChange(i,j);
//			int graphIndex = map[index];
//			if (map[index] == -1)continue;
//
//			
//			Vec2<int> mPos = { FieldConfig::OffsetX,FieldConfig::OffsetY};
//			int size = FieldConfig::GraphSize;
//			mPos.Add({i* size,j* size });
//			mPos.Add(backMove);
//
//
//	Vec2<int>graphSize = {640/10,128/2};
//	GNumber graphNum = static_cast<GNumber>(graphIndex);
//	Vec2<int>graphPos = GraphChangeVec2(graphNum);
//	//DrawBox(mPos.x,mPos.y,mPos.x+ size -1,mPos.y+ size -1,0xffffff,true);
//	DrawRectExtendGraph(mPos.x, mPos.y, mPos.x + size , mPos.y + size 
//	,graphSize.x*graphPos.x,graphSize.y* graphPos.y,graphSize.x,graphSize.y
//		,hImage,true);
//#ifdef _DEBUG
//			std::string str = std::to_string(graphIndex);
//	DrawFormatString(mPos.x,mPos.y,0xffffff,str.c_str());
//#endif
//	
//		}
//	}

	int count=0;
	for (int i = 0; i < 17; i++) {
		for (int j = 0; j < FieldConfig::FieldHeigth; j++) {
			count++;
			const int nowLeftBackMovePos = static_cast<int>(backMove.x) / 64;
			//int widthToiIndex = (i- nowLeftBackMovePos)%fieldWidth;
			int widthToiIndex = i- nowLeftBackMovePos;
			int index = IndexChange(widthToiIndex, j);
			const int graphIndex = maps[index].mapNum;
			if (graphIndex == -1)continue;


			maps[index].dispPos  = maps[index].mainPos;
			maps[index].dispPos += backMove;
			maps[index].dispPos += FieldConfig::offsets;

			const Vec2<int>graphSize = { 640 / 10,128 / 2 };
			const GNumber graphNum = static_cast<GNumber>(graphIndex);
			if (graphNum == GNumber::breakBlock_normal		)continue;
			if (graphNum == GNumber::questionBox_inCoin		)continue;
			if (graphNum == GNumber::questionBox_inMushroom	)continue;
			if (graphNum == GNumber::questionBox_inStar		)continue;
			if (graphNum == GNumber::questionBox_inOneUp	)continue;
			const Vec2<int>graphPos = GraphChangeVec2(graphNum);
			const int size = FieldConfig::GraphSize;

			DrawRectExtendGraph(maps[index].dispPos.x, maps[index].dispPos.y
				, maps[index].dispPos.x + size, maps[index].dispPos.y + size
				, graphSize.x * graphPos.x, graphSize.y * graphPos.y, graphSize.x, graphSize.y
				, hImage, true);
#ifdef _DEBUG
			std::string str = std::to_string(graphIndex);
			DrawFormatString(maps[index].dispPos.x, maps[index].dispPos.y
				, 0xffffff, str.c_str());
#endif

		}
	}
}

void Field::SetFieldInside(int _i, int _j, int _num){
	int index = IndexChange(_i,_j);
	maps[index].mapNum=_num;
}

Field::GNumber Field::GetFieldInside(Vec2<int> _pos){
	BackImage* bi = GetScene()->Invoke<BackImage>();
	Vec2<float>backMove = { 0,0 };
	if (bi != nullptr) 
		bi->Movement(&backMove);
	
	int gSize = FieldConfig::GraphSize;
	int index = IndexChange(_pos.x/gSize, _pos.y/gSize);
	int inMap = maps[index].mapNum;

	return static_cast<GNumber>(inMap);
}

std::vector<Vec2<int>> Field::GetFieldInsidePos(GNumber _num){
	std::vector<Vec2<int>> mapNums;
	for (int i = 0; i < fieldWidth; i++) {
		for (int j = 0; j < FieldConfig::FieldHeigth; j++) {
			const int index = IndexChange(i, j);

			if (_num != static_cast<GNumber>(maps.at(index).mapNum))
				continue;
			mapNums.emplace_back(Vec2<int>{i,j});
			
		}
	}
	
	return mapNums;
}



//bool Field::isFieldCollision(Vec2<float> *_pos){
//	BackImage* bi = GetScene()->Invoke<BackImage>();
//	Vec2<float>backMove = { 0,0 };
//	if (bi != nullptr)
//		bi->Movement(&backMove);
//	int gSize = FieldConfig::GraphSize;
//	Vec2<int>index = {static_cast<int>(_pos->x/gSize),static_cast<int>(_pos->y/gSize)};
//	if (map[IndexChange(index)] == static_cast<int>(GNumber::groundBlock_normal)
//		) {
//
//		Vec2<int> mPos = { FieldConfig::OffsetX,FieldConfig::OffsetY };
//		Vec2<int> nowPos = { index.x * gSize,index.y * gSize - 64 };
//		Vec2<int>backs = backMove.Cast<int>();
//		backs.x %= 64;
//		mPos += nowPos;
//		mPos += backs;
//		//mPos.Add({ index.x * gSize,index.y * gSize -64});
//		//mPos.Add({ static_cast<int>(backMove.x) % 64,static_cast<int>(backMove.y) });
//		*_pos = mPos.Cast<float>();
//
//		return true;
//	}
//
//	return false;
//}

int Field::fieldCollisionDown(const Vec2<float> _pos){
	float gSize = FieldConfig::GraphSize;
	Vec2<float>gsizes = {gSize,gSize};
	Vec2<float>_p = _pos;
	Vec2<int>index = _p.Cast<int>()/ gsizes.Cast<int>();
	float heightY = static_cast<int>(_pos.y);
	GNumber chip = static_cast<GNumber>(maps[IndexChange(index)].mapNum);
	switch (chip){
												/*	faoooooooooooool	down	*/
	case Field::GNumber::breakBlock_normal:
	case Field::GNumber::breakBlock_bule:
	case Field::GNumber::groundBlock_normal:
	case Field::GNumber::groundBlock_normal_half:
	case Field::GNumber::groundBlock_bule:
	case Field::GNumber::groundBlock_bule_half:
	case Field::GNumber::earhenPipe_lu:
	case Field::GNumber::earhenPipe_ru:
	case Field::GNumber::earhenPipe_ld:
	case Field::GNumber::earhenPipe_rd:
	case Field::GNumber::rockBlock:
	case Field::GNumber::questionBox_inCoin:
	case Field::GNumber::questionBox_inMushroom :
	case Field::GNumber::questionBox_inStar :
	case Field::GNumber::questionBox_inOneUp:
	case Field::GNumber::emptyBox:
	//default:
		return fmod(heightY, gSize);
		//return heightY% gSize+1;
		break;
	}

	return 0;
}

int Field::fieldCollisionUp(Vec2<float> _pos){
	float gSize = FieldConfig::GraphSize;
	Vec2<float>gsizes = { gSize,gSize };
	Vec2<float>_p = _pos;
	Vec2<int>index = _p.Cast<int>() / gsizes.Cast<int>();
	float heightY = static_cast<int>(_pos.y);
	GNumber chip = static_cast<GNumber>(maps[IndexChange(index)].mapNum);
	switch (chip) {
		/*	faoooooooooooool	down	*/
	case Field::GNumber::breakBlock_normal:
	case Field::GNumber::breakBlock_bule:
	case Field::GNumber::groundBlock_normal:
	case Field::GNumber::groundBlock_normal_half:
	case Field::GNumber::groundBlock_bule:
	case Field::GNumber::groundBlock_bule_half:
	case Field::GNumber::earhenPipe_lu:
	case Field::GNumber::earhenPipe_ru:
	case Field::GNumber::earhenPipe_ld:
	case Field::GNumber::earhenPipe_rd:
	case Field::GNumber::rockBlock:
	case Field::GNumber::questionBox_inCoin:
	case Field::GNumber::questionBox_inMushroom:
	case Field::GNumber::questionBox_inStar:
	case Field::GNumber::questionBox_inOneUp:
	case Field::GNumber::emptyBox:
		//default:
		return  gSize- fmod(heightY , gSize);
		//return gSize-heightY % gSize;
		break;
	}

	return 0;
}

int Field::fieldCollisionRight(Vec2<float> _pos){
	float gSize = FieldConfig::GraphSize;
	Vec2<float>gsizes = { gSize,gSize };
	Vec2<float>_p = _pos;
	Vec2<int>index = _p.Cast<int>() / gsizes.Cast<int>();
	float heightX = static_cast<int>(_pos.x);
	GNumber chip = static_cast<GNumber>(maps[IndexChange(index)].mapNum);
	switch (chip) {
		/*	faoooooooooooool	down	*/
	case Field::GNumber::breakBlock_normal:
	case Field::GNumber::breakBlock_bule:
	case Field::GNumber::groundBlock_normal:
	case Field::GNumber::groundBlock_normal_half:
	case Field::GNumber::groundBlock_bule:
	case Field::GNumber::groundBlock_bule_half:
	case Field::GNumber::earhenPipe_lu:
	case Field::GNumber::earhenPipe_ru:
	case Field::GNumber::earhenPipe_ld:
	case Field::GNumber::earhenPipe_rd:
	case Field::GNumber::rockBlock:
	case Field::GNumber::questionBox_inCoin:
	case Field::GNumber::questionBox_inMushroom:
	case Field::GNumber::questionBox_inStar:
	case Field::GNumber::questionBox_inOneUp:
	case Field::GNumber::emptyBox:
		//default:
		return fmod(heightX , gSize);
		//return heightX % gSize+1;
		break;
	}

	return 0;
}

int Field::fieldCollisionLeft(Vec2<float> _pos){
	float gSize = FieldConfig::GraphSize;
	Vec2<float>gsizes = { gSize,gSize };
	Vec2<float>_p = _pos;
	Vec2<int>index = _p.Cast<int>() / gsizes.Cast<int>();
	float heightX = static_cast<int>(_pos.x);
	GNumber chip = static_cast<GNumber>(maps[IndexChange(index)].mapNum);
	switch (chip) {
		/*	faoooooooooooool	down	*/
	case GNumber::breakBlock_normal:
	case GNumber::breakBlock_bule:
	case GNumber::groundBlock_normal:
	case GNumber::groundBlock_normal_half:
	case GNumber::groundBlock_bule:
	case GNumber::groundBlock_bule_half:
	case GNumber::earhenPipe_lu:
	case GNumber::earhenPipe_ru:
	case GNumber::earhenPipe_ld:
	case GNumber::earhenPipe_rd:
	case GNumber::rockBlock:
	case Field::GNumber::questionBox_inCoin:
	case Field::GNumber::questionBox_inMushroom:
	case Field::GNumber::questionBox_inStar:
	case Field::GNumber::questionBox_inOneUp:
	case GNumber::emptyBox:
		//default:
		return gSize-fmod( heightX , gSize);
		//return gSize- heightX % gSize;
		break;
	}

	return 0;
}



void Field::FieldLoad() {
	//map.clear();
	maps.clear();
	std::vector<std::string>mapString;
	mapString = CsvSave::Load("data/stagedata/field1-1.csv");
	//CsvSave::Load("data/stagedata/field1-1.csv",&map);
	if (!mapString.empty()) {
		for (int i = 0; static_cast<unsigned int>(i) < mapString.size(); i++) {
			Chip aChip;
			if (mapString[i].c_str() == "-") {
				i++;
				//map.emplace_back(-1);
				aChip.mapNum = -1;
				maps.emplace_back(aChip);
				continue;
			}
			int stageNumber = stoi(mapString[i]);// atoi(mapString[i].c_str());
			//int stageNumber = atoi(mapString[i].c_str());
			//map.emplace_back(stageNumber);
			aChip.mapNum = stageNumber;
			maps.emplace_back(aChip);
		}
	}
	const int width = maps.size() / FieldConfig::FieldHeigth;
	fieldWidth = width;

	for (int i = 0; i < fieldWidth; i++) {
		for (int j = 0; j < FieldConfig::FieldHeigth; j++) {
			const int index = IndexChange(i, j);
			Vec2<int>grid = { i,j };
			maps[index].gridPos = grid;
			maps[index].mainPos = grid.Cast<float>() * Vec2<float>{FieldConfig::GraphSize, FieldConfig::GraphSize};
		}
	}
}

void Field::FieldSave(){
	std::vector<std::string>mapSave;
	mapSave.clear();
	//for (auto& intejar : map) {
	//	std::string str = "";
	//	str = std::to_string(intejar);
	//	mapSave.emplace_back(str);
	//}

	for (int i = 0; i < fieldWidth; i++) {
		for (int j = 0; j < FieldConfig::FieldHeigth; j++) {
			std::string str = "";
			int index = i *FieldConfig::FieldHeigth+ j; //IndexChange(i,j);
			str = std::to_string(maps[index].mapNum);
			mapSave.emplace_back(str);
		}
	}
	CsvSave::Save("data/stagedata/field1-1.csv",mapSave, fieldWidth);
}

int Field::IndexChange(int _i, int _j){
	int index =_i  + _j* fieldWidth ;
	if (index < 0)index = 0;
	if (static_cast<unsigned int>(index)>= maps.size())
		index = maps.size()-1;
	return index;
}


Vec2<int> Field::GraphChangeVec2(GNumber _Num){

	const Vec2<int>emptyPos = {9,1};

	switch (_Num){
	case Field::GNumber::empty					:		return emptyPos;			break;
	case Field::GNumber::Pstart					:		return emptyPos;			break;
	case Field::GNumber::Cstart_stick			:		return Vec2<int>{1, 1};		break;
	case Field::GNumber::Cstart_circle			:		return Vec2<int>{0, 1};		break;
	case Field::GNumber::breakBlock_normal		:		return Vec2<int>{2, 0};		break;
	case Field::GNumber::breakBlock_bule		:		return Vec2<int>{3, 0};		break;
	case Field::GNumber::groundBlock_normal		:		return Vec2<int>{4, 0};		break;
	case Field::GNumber::groundBlock_normal_half:		return Vec2<int>{4, 1};		break;
	case Field::GNumber::groundBlock_bule		:		return Vec2<int>{5, 0};		break;
	case Field::GNumber::groundBlock_bule_half	:		return Vec2<int>{5, 1};		break;
	case Field::GNumber::earhenPipe_lu			:		return Vec2<int>{6, 0};		break;
	case Field::GNumber::earhenPipe_ru			:		return Vec2<int>{7, 0};		break;
	case Field::GNumber::earhenPipe_ld			:		return Vec2<int>{8, 0};		break;
	case Field::GNumber::earhenPipe_rd			:		return Vec2<int>{9, 0};		break;
	case Field::GNumber::rockBlock				:		return Vec2<int>{1, 0};		break;
	case Field::GNumber::questionBox_inCoin		:		return Vec2<int>{0, 0};		break;
	case Field::GNumber::questionBox_inMushroom	:		return Vec2<int>{0, 0};		break;
	case Field::GNumber::questionBox_inStar		:		return Vec2<int>{0, 0};		break;
	case Field::GNumber::questionBox_inOneUp	:		return Vec2<int>{0, 0};		break;
	case Field::GNumber::emptyBox				:		return Vec2<int>{0, 0};		break;
	case Field::GNumber::max					:		return emptyPos;			break;
	default										:		return emptyPos;			break;
	}
	return emptyPos;
}
