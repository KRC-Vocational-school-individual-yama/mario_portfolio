#pragma once
#include"character.h"

class EnemyBase :public Character{
public:
	EnemyBase(Scene* sc) :Character(sc)
		,pos()
		,size()
		,active(true)
	{}
	virtual ~EnemyBase()	=default;
	virtual void Init()		=0;
	virtual void Update()	=0;
	virtual void Draw()		=0;


	virtual bool Collision(Vec2<float>,Vec2<float>,Vec2<float>) { return false; }
	virtual void SetPos(Vec2<float>_p) { pos = _p; }
	virtual void SetSize(Vec2<float>_s) { size = _s; }
	Square<float> GetCollider() { return { pos,size }; }
	virtual void CollisionToField() {}
	virtual void CollisionToOther(EnemyBase* enemy) {}

protected:
	Vec2<float>pos;
	Vec2<float>size;
	bool active;
};