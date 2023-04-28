#pragma once
#include"character.h"
#include<array>
namespace PlayerConfig {
	static const float MOVE_NORMAL_SPEED = 10;
	static const float MOVE_DASH_SPEED =  20;

	static const float GRAVITY = 3.4f;
};


class PlyaerInAnim {
public:
	enum class AnimNumber {
		 normal =0
		,walk1
		,walk2
		,walk3
		,jump
		,takkuru//反転
		,tuta1
		,tuta2
		,over

		,max
	};
	PlyaerInAnim();

	void SetAnim(AnimNumber _animNum);
	Vec2<int>GetAnim() { return anim; }
private:
	Vec2<int>anim;
};

class Player : public Character{
public:
	Player(Scene* sc);
	~Player()		override;
	void Init()		override;
	void Update()	override;
	void Draw()		override;

	void CollisionToField()override;

	Vec2<float>GetVelocity() { return velocity; }
	Vec2<float>GetDispPos() { return dispPos; }

	Vec2<float>GetPos() { return position; }
	Vec2<float>GetSize() { return size.Cast<float>(); }

private:
	enum KeyState{
		left=0
		,right
		,dash
		,all
		,max
	};
	
	void Jump();
	void VelocityDown();
	void AnimsMoveAndNormal(std::array<bool,KeyState::max>_key);
	void KeyStates(std::array<bool, KeyState::max> _key);

	PlyaerInAnim* playerAnim;
	Vec2<float>	position;
	Vec2<float>	dispPos;
	Vec2<float>velocity;
	Vec2<int>	gridPos;
	Vec2<int>size;
	bool revese;
	bool keystop;
	bool onGround;
	bool isWall;
	std::vector<int>hImages;
	std::array<bool, KeyState::max> key;
	int starCount;
	int hJumpSound;
	int jumpCount;
	int moveAnimCount;
};


//マリオ参考動画
//https://www.youtube.com/watch?v=SqnyfjByae8&t=3s

