#pragma once
#include"libs/object.h"
class BackImage :public Object {
public:
	BackImage(Scene* sc);
	~BackImage()	override;
	void Init()		override;
	void Update()	override;
	void Draw()		override;

	void Movement(Vec2<float> *_moves);
	void MoveVec(Vec2<float>* _mVec);

	void SetBackMove(Vec2<float> _p) { pos=_p; }
private:
	void Scroll();

	int hImage;
	Vec2<float>pos;
	Vec2<float>vec;
};