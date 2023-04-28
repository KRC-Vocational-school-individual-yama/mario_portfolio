#pragma once
#include"libs/object.h"
#include"field.h"

enum class BlockItem {
	Coin
	, Mushroom
	, Fire
	, Star
	, OneUp
};

class QuestionBlock:public Object {
public:
	QuestionBlock(Scene* sc);
	~QuestionBlock()	override;
	void Init()			override;
	void Update()		override;
	void Draw()			override {}
	void Draw(Vec2<float>_backMove);

	void SetPos(Vec2<float>_pos)		{ myChip.mainPos = _pos; }
	void SetMyItem(BlockItem _item)		{ myItem = _item; }
	void SetHandle(int _handle)			{ hImage = _handle; }
	void SetHandle_bBlock(int _handle)	{ breakhImage = _handle; }
	void SetHandle_item(int _handle)	{ hImage_item = _handle; }

	Chip GetChip() {return myChip;}
	BlockItem GetItem() { return myItem; }
	bool GetKnock() { return isBreak; }
	void KnockOn()						{ isBreak = true; }
	void Knock();

private:
	int hImage;
	int hImage_item;
	int breakhImage;
	int count;
	int knockCount;
	bool isBreak;
	float sinPosY;
	Chip myChip;
	BlockItem myItem;
};
