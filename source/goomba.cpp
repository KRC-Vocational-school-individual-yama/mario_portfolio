#include "goomba.h"

#include"player.h"
#include"field.h"
#include"libs/scene.h"
#include"backimage.h"

Goomba::Goomba(Scene* sc)
	:EnemyBase(sc)
	,hImage(-1)
	,animCount(0)
	,dispPos()
	,gridPos()
	,velocity()
	,moveLeft(true)
	,anim()
{}

Goomba::~Goomba(){
	if(hImage!=-1)
		DeleteGraph(hImage);
}

void Goomba::Init(){
	//pos={ 500,500 };

	hImage = LoadGraph("data/texture/kurobo.png");
	assert(hImage!=-1);
}

void Goomba::Update() {
	animCount++;
	Move(moveLeft);//�Ƃ肠����


	if (active) {
		velocity.y += PlayerConfig::GRAVITY;
		pos += velocity;

		gridPos = pos.Cast<int>() / Vec2<int>{FieldConfig::GraphSize, FieldConfig::GraphSize};


		CollisionToField();


		anim = { animCount / 5 % 2,0 };
	}
	else {
		anim.x = 2;

		if (animCount++ > 60)
			MyDestroy();
	}
	if (dispPos.y > SCREEN_HEIGHT + size.y)
		MyDestroy();

}

void Goomba::Draw(){
	//if (!active)return;

	Vec2<float>gSize = { FieldConfig::GraphSize,FieldConfig::GraphSize};

	Vec2<float> backMove = {};
	GetScene()->Invoke<BackImage>()->Movement(&backMove);
	dispPos = pos;
	dispPos += backMove;
	dispPos += FieldConfig::offsets;

	//DrawGraph(400,500,hImage,true);

	DrawRectGraph(dispPos.x,dispPos.y
		,gSize.x*anim.x,gSize.y*anim.y
		,gSize.x,gSize.y,hImage,true);
#ifdef _DEBUG
	DrawBox( dispPos.x,dispPos.y
			,dispPos.x+size.x,dispPos.y+size.y,0xffffff,false);
#endif
}
bool Goomba::Collision(Vec2<float>p, Vec2<float>s, Vec2<float>v){

	Square<float> enemy = { pos,size };
	Square<float> player = {p,s };
	if ( !active)return false;

	if ( !CheckSquareCollision<float>(player, enemy))
		return false;

	//������
	if (v.y < 0)return false;



	active = false;
	animCount = 0;

	return true;


}
void Goomba::CollisionToOther(EnemyBase* enemy){
	Square<float> eSquare = enemy->GetCollider();

	if(eSquare.pos == pos)
		return;

	if (!CheckSquareCollision<float>(eSquare, GetCollider()))
		return;

	// eSquare.pos + eSquare.size;

	if (moveLeft)
		moveLeft = false;
	else
		moveLeft = true;

}
void Goomba::Move(bool leftMove) {
	const float move = 1;
	const float MoveSpeed = PlayerConfig::MOVE_NORMAL_SPEED/4;


	//���ړ�
	if (leftMove) {

		if (velocity.x > -move)//����ł͂Ȃ����ɓ���
			velocity.x -=  MoveSpeed;
		//velocity.x = -move;

	}

	//�E�ړ�
	if (!leftMove) {


		if (velocity.x < move)//����ł͂Ȃ����ɓ���
			velocity.x += MoveSpeed;
		//velocity.x = move;

	}

}


//�����蔻��@
//�߂荞�񂾕��������Ԃ������������̂��A				�����_�ɑΉ��ł��Ȃ�
//�}�X��ŊǗ����A�m���ȍ��W����ꂽ�����ǂ��̂��A�@

void Goomba::CollisionToField() {
	Field* fp = GetScene()->Invoke<Field>();
	if (fp == nullptr) return;
	//�n�ʂ̓����蔻��@�߂荞�񂾂牟���Ԃ�

	if (velocity.y > 0) {//����

		Vec2<float>collider		= { pos.x			,pos.y + 63.f +1.f	};
		Vec2<float>collider2	= { pos.x  + 64.f	,pos.y + 63.f +1.f	};
		float push	= fp->fieldCollisionDown(collider );
		float push2 = fp->fieldCollisionDown(collider2);

		if (max(push, push2) > 0.0f) {
			//pos.y = (gridPos.y - 0) * FieldConfig::GraphSize;
			pos.y -= max(push,push2)-1.f;
			velocity.y = 0.0f;
		}
	}

	if (velocity.x > 0) {//�E�ړ���

		Vec2<float>collider		= { pos.x + 64.f,pos.y };
		Vec2<float>collider2	= { pos.x + 64.f,pos.y + 63.f -1.f };
		float push	= fp->fieldCollisionRight(collider );
		float push2 = fp->fieldCollisionRight(collider2);

		if (max(push, push2) > 0.0f) {
			//pos.x = (gridPos.x) * FieldConfig::GraphSize - 1;
			pos.x -= max(push,push2);
			velocity.x = 0.0f;
			moveLeft = true;
		}
	}

	if (velocity.x < 0) {//���ړ���
		Vec2<float>collider		= { pos.x	,pos.y };
		Vec2<float>collider2	= { pos.x	,pos.y + 63 -1.f};
		float push	= fp->fieldCollisionLeft(collider );
		float push2 = fp->fieldCollisionLeft(collider2);
		if (max(push, push2) > 0.0f) {
			//pos.x = (gridPos.x + 1) * FieldConfig::GraphSize + 2;
			pos.x += max(push, push2);
			velocity.x = 0.0f;
			moveLeft = false;
		}
	}

}
