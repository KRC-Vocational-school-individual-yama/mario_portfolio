#pragma once
#include"object.h"

class TestPlayer :public Object {
public:
	TestPlayer(Scene* sc);
	~TestPlayer()		override;
	void Init()		override;
	void Update()	override;
	void Draw()		override;

private:
	void Trash();

	Circle<float> en;
	int speed;
};