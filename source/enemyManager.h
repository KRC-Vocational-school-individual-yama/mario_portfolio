#pragma once
#include"libs/object.h"
class EnemyBase;
class Player;

class EnemyManager :public Object {
public:
	EnemyManager(Scene* sc);
	~EnemyManager()	override;
	void Init()		override;
	void Update()	override;
	void Draw()		override;

	bool Collisions(Player* player);
private:
	std::list<EnemyBase*>enemies;
	int count;
};