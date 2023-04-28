#pragma once

//ÉNÉäÉ{Å[
#include"enemyBase.h"

class Goomba :public EnemyBase{
public:
	Goomba(Scene* sc);
	~Goomba()		override;
	void Init()		override;
	void Update()	override;
	void Draw()		override;

	bool Collision(Vec2<float>p,Vec2<float>s,Vec2<float>v)override;
	void CollisionToOther(EnemyBase* enemy);
private:
	void Move(bool leftMove);
	
	void CollisionToField();

	int hImage;
	int animCount;
	bool moveLeft;

	Vec2<float>	dispPos;
	Vec2<float>velocity;
	Vec2<int>	gridPos;
	Vec2<int> anim;
};

// Goomba : 18  nokonoko : 1
