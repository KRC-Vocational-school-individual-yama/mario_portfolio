#pragma once
#include"itemBase.h"


class Mushroom :public ItemBase {
public:
	Mushroom(Scene* sc)		;
	~Mushroom()		override;
	void Init()		override;
	void Update()	override;
	void Draw()		override;

private:
	int hImage;
	Vec2<float>pos;
};

