#pragma once
#include"libs/object.h"

class Coin :public Object {
public :
	Coin(Scene* sc);
	~Coin()			override;
	void Init()		override;
	void Update()	override;
	void Draw()		override;

	void SetPos(Vec2<float>_p) { pos = _p; }
private:


	bool disp;
	bool keystop;
	int hImage;
	int updownCount;
	int animCount;
	float upDownY;
	Vec2<float>pos;
	Vec2<int>anim;

	void UpDownMove();
};