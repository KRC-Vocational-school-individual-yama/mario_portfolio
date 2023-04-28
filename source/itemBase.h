#pragma once
#include"libs/object.h"
#include"field.h"

class ItemBase :public Object{
public:
	ItemBase(Scene* sc) 
		:Object(sc)
		,pos()
		,size(Vec2<float>{FieldConfig::GraphSize,FieldConfig::GraphSize})
		,active(true)
	{}
	virtual ~ItemBase() =default;
	virtual void Init()		override{}
	virtual void Update()	override{}
	virtual void Draw()		override{}

	virtual bool Collision(Vec2<float>p, Vec2<float>s, Vec2<float>v) { return false; }
	
protected:
	Vec2<float>pos;
	Vec2<float>size;
	bool active;
};
//
//template<typename T>
//inline bool ItemBase::Collision(Vec2<T> _pos, Vec2<T>_size){
//	Square<T> enemy = {_pos,_size};
//	Square<T> myS = {pos.Cast<T>() ,size.Cast<T>() };
//	bool ans=false;
//
//	if (CheckSquareCollision<T>(myS, enemy))
//		ans = true;
//
//
//	return ans;
//}
