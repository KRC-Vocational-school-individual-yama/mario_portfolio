#pragma once
#include"libs/object.h"

class BreakBlock :public Object {
public:
	BreakBlock(Scene* sc);
	~BreakBlock();
	void Init();
	void Update();
	void Draw();

	void Reset();
	void Collision(Vec2<int> _pos,bool blockBreak=false);
	void Collision(int x, int y, bool blockBreak=false) { Collision(Vec2<int>{x,y},blockBreak); }
private:
	void BlockBreak();
	int hImage;
};