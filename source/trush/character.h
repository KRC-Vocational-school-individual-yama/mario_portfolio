#pragma once
#include"libs/object.h"

class Character :public Object {
public:
	Character(Scene* sc)
		:Object(sc)
	{};
	~Character()			override=default;
	virtual void Init()		override=0;
	virtual void Update()	override=0;
	virtual void Draw()		override=0;

private:

};