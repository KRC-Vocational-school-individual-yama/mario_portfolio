#include "blockBreakEffect.h"
#include"player.h"
#include"mains/config.h"
#include"backimage.h"
#include"libs/scene.h"

BlockBreakEffect::BlockBreakEffect(Scene* sc)
	:Object		(sc)
	,hImage		(-1)
	,pos		(Vec2<float>::zero())
	,velocity	(Vec2<float>::zero())
	,angle		(0)
	,animCount	(0)
	,active		(true)
{}
BlockBreakEffect::~BlockBreakEffect(){
}
void BlockBreakEffect::Init(){
	pos.x		= 500.f;
	pos.y		= 500.f;
	velocity.x	= 10.f;
	velocity.y	= -25.f;
}
void BlockBreakEffect::Update(){
	++animCount; //ブロック破片の動き


	//重力と摩擦等
	velocity.y	+= PlayerConfig::GRAVITY;
	velocity	*= Vec2<float>{0.98f,0.98f};
	
	//positionに適用
	pos			+= velocity;
	
	if (pos.y > SCREEN_HEIGHT + 64)
		active = false;
}
void BlockBreakEffect::Draw(){
	//64 32
	Vec2<int> gSize = {64,32};
	Vec2<int> gNum = {2,1};
	BackImage* bp=GetScene()->Invoke<BackImage>();
	Vec2<float> backMove{};
	if(bp!=nullptr)
		bp->Movement(&backMove);
	
	
	Vec2<int> sprit = gSize/gNum;
	int anim = AnimPattern(animCount);

	DrawRectGraph(pos.x+backMove.x,pos.y+backMove.y
		,sprit.x*anim	,sprit.y*0
		,sprit.x		,sprit.y,hImage,true);


}

void BlockBreakEffect::SetPosAndVec(Vec2<float> position, Vec2<float> vec){
	SetPos(position);
	velocity = vec;
}
