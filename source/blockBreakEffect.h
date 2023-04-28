#pragma once
#include"libs/object.h"

class BlockBreakEffect :public Object {
public:
	BlockBreakEffect(Scene* sc);
	~BlockBreakEffect()	override;
	void Init()			override;
	void Update()		override;
	void Draw()			override;

	void SethImage(int _img) { hImage = _img; }
	void SetPos(Vec2<float> position) { pos = position; }
	void SetPosAndVec(Vec2<float> position,Vec2<float> vec);
	bool GetActive() { return active; }
private:
	int AnimPattern(const int& count) { return (count/10)%2; }


	int hImage;
	int animCount;
	float angle;
	bool active;
	Vec2<float> pos;
	Vec2<float> velocity;


};