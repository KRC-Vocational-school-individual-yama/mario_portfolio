#pragma once
#include"libs/object.h"

class Character :public Object {
public:
	Character(Scene* sc) :Object(sc){}

	virtual void CollisionToField() {}

private:

};