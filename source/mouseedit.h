#pragma once
#include"libs/object.h"

class MouseEdit :public Object {
public:
	MouseEdit(Scene* sc);
	~MouseEdit();
	void Init()		override;
	void Update()	override;
	void Draw()		override;
private:
	template<class C>
	bool CheckClass();
	void MouseWhoweel();
	void GameScene();
	

	Vec2<int> mousePos;
	std::vector<int>hImages;
	int hImage_item;
	int nowNum;
	bool keystop;
};

template<class C>
bool MouseEdit::CheckClass()
{
	if (GetScene()->Invoke<C>() != nullptr)
		return true;

	return false;
};
