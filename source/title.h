#pragma once
#include"libs/scene.h"

class Title :public Scene {
public:
	Title()			;
	~Title()		override;
	void Update()	override;
	void Draw()		override;

private:

};