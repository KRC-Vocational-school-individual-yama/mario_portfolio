#pragma once
#include"libs/object.h"

class Fortress :public Object {
public:
	Fortress(Scene* sc);
	~Fortress()		override;
	void Init()		override;
	void Update()	override;
	void Draw()		override;


private:
	void GetFastPos();

	int hImage;
	bool myDisp;
	Vec2<int>graphSize;//5*5
	Vec2<float>position;
	Vec2<float>dispPosition;
};