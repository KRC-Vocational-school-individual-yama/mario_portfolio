#pragma once
#include"libs/object.h"
class ItemBase;

class ItemManager :public Object {
public:
	ItemManager(Scene* sc);
	~ItemManager()	override;
	void Init()		override;
	void Update()	override;
	void Draw()		override;

private:
	std::list<ItemBase*>itemList;
};