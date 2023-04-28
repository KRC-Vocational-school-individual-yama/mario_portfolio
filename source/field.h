#pragma once
#include"libs/object.h"
namespace FieldConfig {
	static const int GraphSize = 64;
	static const int FieldHeigth = 16;

	static const int OffsetX = 0;
	static const int OffsetY =  -64 * 2 - 32;

	static const int OffsetHalf =  32;
	const Vec2<float>offsets = {OffsetX,OffsetY};
}
struct Chip {
	int mapNum;
	Vec2<int>gridPos;
	Vec2<float>mainPos;
	Vec2<float>dispPos;

	Chip() 
		:mapNum(-1)
		, gridPos({ 0,0 })
		, mainPos({ 0,0 })
		, dispPos({ 0,0 }) 
	{}
};
class Field :public Object {
public:
	enum class GNumber {
		empty ,
		Cstart_stick,
		Cstart_circle,
		breakBlock_normal,
		breakBlock_bule,
		groundBlock_normal,
		groundBlock_normal_half,
		groundBlock_bule,
		groundBlock_bule_half,
		earhenPipe_lu,
		earhenPipe_ru,
		earhenPipe_ld,
		earhenPipe_rd,
		rockBlock,
		emptyBox,
		questionBox_inCoin,
		questionBox_inMushroom,
		questionBox_inStar,
		questionBox_inOneUp,

		Pstart,
		EnemyGoomba,
		fortress,

		max
	};
	Field(Scene* sc);
	~Field()		override;
	void Init()		override;
	void Update()	override;
	void Draw()		override;

	void SetFieldInside(int _x,int _y,int _num);
	void SetFieldInside(Vec2<int>_pos, int _num) { SetFieldInside(_pos.x, _pos.y, _num); }
	void SetFieldInside(Vec2<int>_pos, GNumber _num) { SetFieldInside(_pos.x, _pos.y, static_cast<int>(_num)); }
	GNumber GetFieldInside(int x, int y) { return GetFieldInside(Vec2<int>{x,y}); }
	GNumber GetFieldInside(Vec2<int> _pos);
	//ç°ÇÃÇ∆Ç±ÇÎç≈èâÇÃÇÕÇƒÇ»ÇµÇ©ï‘Ç≥Ç»Ç¢
	std::vector<Vec2<int>> GetFieldInsidePos(GNumber _num);
	//bool isFieldCollision(Vec2<float>* _pos);
	int fieldCollisionDown(Vec2<float> _pos);
	int fieldCollisionUp(Vec2<float> _pos);
	int fieldCollisionLeft(Vec2<float> _pos);
	int fieldCollisionRight(Vec2<float> _pos);

	int IndexChange(int _i, int _j);
private:
	void FieldLoad();
	void FieldSave();
	int IndexChange(Vec2<int>_pos) { return IndexChange(_pos.x,_pos.y); }
	Vec2<int>GraphChangeVec2(GNumber _Num);

	std::vector<Chip>maps;
	bool keystop;
	int hImage;
	int fieldWidth;
};