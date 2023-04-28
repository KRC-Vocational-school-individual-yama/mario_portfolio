#pragma once
#include"libs/object.h"
class QuestionBlock;


class QuestionBlockManager :public Object {
public:
	QuestionBlockManager(Scene* sc);
	~QuestionBlockManager()override;
	void Init()		override;
	void Update()	override;
	void Draw()		override;
	void Reset();

	void Collision(Vec2<int> _pos);
	void Collision(int x, int y) { Collision(Vec2<int>{x, y}); }

private:
	int hImage;
	int hImage_Item;
	int emptyhImage;
	std::list<QuestionBlock*>questionList;

};

// ブロック関連
//https://xn--qcka9i7azcwa9bz223dvr6c.jp/2019/10/04/%E3%83%97%E3%83%AD%E3%82%B0%E3%83%A9%E3%83%A0%E3%81%A7%E3%83%9E%E3%83%AA%E3%82%AA%E3%82%92%E4%BD%9C%E3%82%8B%E7%AC%AC37%E5%9B%9E%E3%83%96%E3%83%AD%E3%83%83%E3%82%AF%E3%83%9E%E3%83%83%E3%83%97/
