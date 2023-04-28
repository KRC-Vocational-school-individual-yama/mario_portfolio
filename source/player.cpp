#include "player.h"

#include"libs/scene.h"
#include"backimage.h"
#include"field.h"
#include"breakBlock.h"
#include"enemyManager.h"
#include"questionblockManager.h"

namespace {
	static const int JUMP_POWER = -35;// -25;
	static const unsigned short HIMAGE_MAX_NUM = 4;
	static const std::string HIMAGEALL[HIMAGE_MAX_NUM] = {
		{"data/texture/MarioChips/tibiMari_s_0.png"},
		{"data/texture/MarioChips/tibiMari_s_1.png"},
		{"data/texture/MarioChips/tibiMari_s_2.png"},
		{"data/texture/MarioChips/tibiMari_s_3.png"},
	};

	
}

Player::Player(Scene* sc)
	:Character(sc)
	,hJumpSound(-1)
	,position()
	,velocity()
	,dispPos()
	,gridPos()
	,revese(false)
	,keystop(true)
	,onGround(false)
	,isWall(false)
	,jumpCount(0)
	,starCount(0)
	,moveAnimCount(0)
	,playerAnim(nullptr)
	,size({64,64})
	,key()
{}
Player::~Player() {
	if (hJumpSound > 0)
		DeleteSoundMem(hJumpSound);

	for (int i = 0; static_cast<unsigned int>(i) < hImages.size(); i++) {
		DeleteGraph(hImages[i]);
		hImages[i] = -1;
	}

	if (playerAnim != nullptr)
		delete playerAnim;
}
void Player::Init(){
	GetScene()->ChangeDispRank(this, 3);
	playerAnim = new PlyaerInAnim;
	size = {64,64};

	int img = -1;
	for (int i = 0; i < HIMAGE_MAX_NUM; i++) {
		img = LoadGraph(HIMAGEALL[i].c_str());
		assert(img > 0);
		hImages.emplace_back(img);
	}

	hJumpSound = LoadSoundMem("data/sound/12 Super Mario Bros. - マリオジャンプ.mp3");
	assert(hJumpSound>0);
	ChangeVolumeSoundMem(255*35/100,hJumpSound);


	//マリオ初期位置を　fieldから貰う
	Field* fp = GetScene()->Invoke<Field>();
	assert(fp != nullptr);
	std::vector<Vec2<int>>playerPos = fp->GetFieldInsidePos(Field::GNumber::Pstart);
	if (playerPos.empty()) {
		position = { 400,500 };
	}
	else {
		Vec2<float>tileSize = { FieldConfig::GraphSize, FieldConfig::GraphSize };
		position = playerPos.at(0).Cast<float>() *tileSize;
	}


	//位置が左じゃなければ　背景をずらす
	if (position.x != 400) {
		auto bp= GetScene()->Invoke<BackImage>();
		Vec2<float>offset = {};
		offset.x = position.x - 400;
		bp->SetBackMove(offset);
	}

	dispPos= {};
	gridPos = position.Cast<int>()/ Vec2<int>{FieldConfig::GraphSize, FieldConfig::GraphSize};

	velocity = { 0,0 };
	//anim = {0,1};
	playerAnim->SetAnim(PlyaerInAnim::AnimNumber::normal);
}
void Player::Update(){
	jumpCount++;
	moveAnimCount++;
	

	key.at(KeyState::left	)		= CheckHitKey(KEY_INPUT_A)		;
	key.at(KeyState::right	)		= CheckHitKey(KEY_INPUT_D)		;
	key.at(KeyState::dash	)		= CheckHitKey(KEY_INPUT_LSHIFT)	;
	key.at(KeyState::all	)		= key.at(KeyState::left) && key.at(KeyState::right);
	onGround = velocity.y == 0;

	 //移動入力
	 KeyStates(key);


	//ジャンプ
	Jump();


	//横 移動量 減衰
	VelocityDown();

	//クリボー
	auto* gp = GetScene()->Invoke<EnemyManager>();
	if (gp != nullptr) {
		//if (gp->Collisions(position, size.Cast<float>(), velocity)) {
		if (gp->Collisions(this)) {
			if (CheckHitKey(KEY_INPUT_SPACE)) {
				velocity.y = -40;
			}
			else {
				velocity.y = -30;
			}
		}
	}
	
	//歩行、待機アニメーション
	AnimsMoveAndNormal(key);


	velocity.y += PlayerConfig::GRAVITY;//重力
	position += velocity;//移動量適用



	//左に戻れないようにしたい
	BackImage* bp = GetScene()->Invoke<BackImage>();
	if (bp != nullptr) {
		Vec2<float>backMove = {};
		bp->Movement(&backMove);
		dispPos = position;
		dispPos += backMove;
		dispPos += FieldConfig::offsets;
	
	
		if (dispPos.x < 0) {
			position.x = -backMove.x;
			velocity.x = 0.f;
	
		}

	}

	gridPos = position.Cast<int>() / Vec2<int>{FieldConfig::GraphSize, FieldConfig::GraphSize};

	//床の当たり判定＋位置の補正
	CollisionToField();
	

	__func__;
	

#ifdef _DEBUG
	if (CheckHitKey(KEY_INPUT_T)) {

		starCount++;
	}
	else {
		starCount = 0;
	}

	

#endif // _DEBUG

}
void Player::Draw(){
	Vec2<float>backMove = { 0,0 };
	GetScene()->Invoke<BackImage>()->Movement(&backMove);
	Vec2<int>texture = {192/3,256/4};
	dispPos  = position;
	dispPos += backMove;
	dispPos += FieldConfig::offsets;

	Vec2<int> anim = playerAnim->GetAnim();
	DrawRectGraphF(dispPos.x, dispPos.y
		, texture.x * anim.x, texture.y * anim.y
		, texture.x			, texture.y
		, hImages[starCount / 5 % HIMAGE_MAX_NUM], true, revese);

#ifdef _DEBUG
	//printfDx("pos.x= %f\n", disp.x);
	//printfDx("pos.y= %f\n", disp.y);
	//printfDx("velocity.x= %f\n",velocity.x);
	//printfDx("velocity.y= %f\n",velocity.y);
	//
	//if (onGround) {
	//	printfDx("onGround= True\n");
	//}
	//else {
	//	printfDx("onGround= False\n");
	//}
	//if (jumpCount < 60 * 0.18f) {
	//	printfDx("jumpCount= True\n");
	//}
	//else {
	//	printfDx("jumpCount= False\n");
	//}
	//if (keystop) {
	//	printfDx("keystop = True\n");
	//}
	//else {
	//	printfDx("keystop = False\n");
	//}

#endif 


}


void Player::Jump() {
	bool jumpKey = GetMouseInput()&MOUSE_INPUT_LEFT ||
		CheckHitKey(KEY_INPUT_SPACE) || CheckHitKey(KEY_INPUT_W) || CheckHitKey(KEY_INPUT_UP);

	if (jumpKey && !keystop&& onGround) {
		jumpCount = 0;
		PlaySoundMem(hJumpSound, DX_PLAYTYPE_BACK);
		playerAnim->SetAnim(PlyaerInAnim::AnimNumber::jump);
		onGround = false;
	}

	keystop = jumpKey;

	if (jumpKey  && jumpCount < 60 * 0.08f) {
		velocity.y = JUMP_POWER;
		playerAnim->SetAnim(PlyaerInAnim::AnimNumber::jump);
		
	}
}
void Player::CollisionToField() {

	isWall = false;


	Field* fp = GetScene()->Invoke<Field>();
	if (fp != nullptr) {
		//地面の当たり判定　めり込んだら押し返す

		if (velocity.y > 0) {//落下
			int col = 15;
			if (key.at(KeyState::dash))col = 7;

			Vec2<float>collider = { position.x + col	  	,position.y + 63.f + 1.f };//常にめり込まないと地面判定じゃなくなる
			Vec2<float>collider2 = { position.x - col + 64.f	,position.y + 63.f + 1.f };
			float push = fp->fieldCollisionDown(collider);
			float push2 = fp->fieldCollisionDown(collider2);

			if (max(push, push2) > 0.0f) {
				//position.y = (gridPos.y) * FieldConfig::GraphSize;
				position.y -= max(push, push2) - 1.f;
				velocity.y = 0.0f;
				onGround = true;
			}
		}

		if (velocity.y < 0) {//上昇
			Vec2<float>collider = { position.x + 3.f	,position.y };
			Vec2<float>collider2 = { position.x + 63.f - 3.f	,position.y };
			float push = fp->fieldCollisionUp(collider);
			float push2 = fp->fieldCollisionUp(collider2);
			if (max(push, push2) > 0.0f) {



				//上が壊れるブロックだったら
				{
					Field::GNumber blockNum = fp->GetFieldInside(position.Cast<int>());
					if (blockNum == Field::GNumber::breakBlock_normal) {
						jumpCount = 60 / 0.08f;
						auto* bp = GetScene()->Invoke<BreakBlock>();
						if (bp != nullptr) {

							//仮
							bool BigMario = CheckHitKey(KEY_INPUT_I);

							bp->Collision(gridPos, BigMario);


							if (BigMario) {//大マリオ
								fp->SetFieldInside(gridPos, Field::GNumber::empty);
							}
							else {
								//小マリオ状態
							}
						}
					}
				}
				//＿＿＿壊れるブロック終わり

				//上がハテナブロックだったら
				{
					Field::GNumber blockNum = fp->GetFieldInside(position.Cast<int>());

					auto* qmp = GetScene()->Invoke<QuestionBlockManager>();
					switch (blockNum) {
					case Field::GNumber::questionBox_inCoin:
					case Field::GNumber::questionBox_inMushroom:
					case Field::GNumber::questionBox_inStar:
					case Field::GNumber::questionBox_inOneUp:
						jumpCount = 60 / 0.08f;
						if (qmp != nullptr) {
							qmp->Collision(gridPos);

						}
						break;
					default:
						break;
					}

				}
				//＿＿＿ハテナブロック終わり

				//position.y = (gridPos.y+1) * FieldConfig::GraphSize;
				position.y += max(push, push2);
				velocity.y = 0.0f;


			}
		}

		if (key.at(KeyState::right)
			|| velocity.x > 0) {//右移動時
			Vec2<float>collider = { position.x + 64.f,position.y };
			Vec2<float>collider2 = { position.x + 64.f,position.y + 63.f - 1.f };
			float push = fp->fieldCollisionRight(collider);
			float push2 = fp->fieldCollisionRight(collider2);

			if (max(push, push2) > 0.0f) {
				//position.x = (gridPos.x) * FieldConfig::GraphSize-1;
				position.x -= max(push, push2);
				velocity.x = 0.0f;
				onGround = true;
				isWall = true;
			}
		}

		if (velocity.x < 0) {//左移動時
			Vec2<float>collider = { position.x	,position.y };
			Vec2<float>collider2 = { position.x ,position.y + 63 - 1.f };
			float push = fp->fieldCollisionLeft(collider);
			float push2 = fp->fieldCollisionLeft(collider2);
			if (max(push, push2) > 0.0f) {
				//position.x = (gridPos.x+1) * FieldConfig::GraphSize+2;
				position.x += max(push, push2);
				velocity.x = 0.0f;
				onGround = true;
				isWall = true;
			}
		}


	}
	//Field* fp=GetScene()->Invoke<Field>();
	//if (fp != nullptr) {
	//
	//	Vec2<float>_pos = position;
	//	if (fp->isFieldCollision(&_pos)) {
	//		velocity.y = 0;
	//		onGround = true;
	//		position.y = _pos.y;
	//		printfDx("_pos.y= %f\n",_pos.y);
	//	}
	//}

	//if (position.y > 608) {
	//	position.y = 608;
	//	velocity.y = 0.0f;
	//	onGround = true;
	//}
}

void Player::VelocityDown(){
//横 移動量 減衰
	velocity.x *= 0.89f;

	//小さい値を消し飛ばす　横　velocity
	if (static_cast<int>(velocity.x) == 0) {
		velocity.x = 0;
		if (onGround)
			playerAnim->SetAnim(PlyaerInAnim::AnimNumber::normal);
	}
}

void Player::AnimsMoveAndNormal(std::array<bool,KeyState::max>_key){
//待機
	if (onGround && !_key.at(KeyState::left )&& !_key.at(KeyState::right)) 
		playerAnim->SetAnim(PlyaerInAnim::AnimNumber::normal);
	
	//歩行
	if (static_cast<int>(velocity.x) != 0) {
		bool move = _key.at(KeyState::left) || _key.at(KeyState::right);
		int anim = position.x;
		int downSpeed = 30;

		if (move && isWall) {
			anim += moveAnimCount;
			downSpeed = 8;
		}


		if (move&&dispPos.x-1<0) {
			anim += moveAnimCount;
			downSpeed = 8;
		}



		int moveAnimInteger = (static_cast<int>(anim) / downSpeed% 3)+1;
		auto moveAnim = static_cast<PlyaerInAnim::AnimNumber>(moveAnimInteger);
		if (onGround) 
			playerAnim->SetAnim(moveAnim);
		

		//タックル状態
		if (velocity.x > 0) {
			if (velocity.x > 2) {
				if (_key.at(KeyState::left))
					playerAnim->SetAnim(PlyaerInAnim::AnimNumber::takkuru);
			}
		}
		else if (velocity.x < 0) {
			if (velocity.x < -2) {
				if (_key.at(KeyState::right))
					playerAnim->SetAnim(PlyaerInAnim::AnimNumber::takkuru);
			}
		}
	}
}

void Player::KeyStates(std::array<bool,KeyState::max> _key){
	if (_key.at(KeyState::left) && _key.at(KeyState::right))
		return;

	//左移動
	if (_key.at(KeyState::left)) {
		const float move = _key.at(KeyState::dash) ? PlayerConfig::MOVE_DASH_SPEED:PlayerConfig::MOVE_NORMAL_SPEED;

		float num = velocity.x > 0 ? 8.f : 4.f;

		if (velocity.x > -move)//上限ではない時に動く
			velocity.x -= PlayerConfig::MOVE_NORMAL_SPEED /num;
			//velocity.x = -move;

		if(onGround)
			revese = true;
	}

	//右移動
	if (_key.at(KeyState::right)) {

		const float move = _key.at(KeyState::dash) ? PlayerConfig::MOVE_DASH_SPEED : PlayerConfig::MOVE_NORMAL_SPEED;

		float num = velocity.x < 0 ? 8.f : 4.f;

		if(velocity.x<move)//上限ではない時に動く
			velocity.x += PlayerConfig::MOVE_NORMAL_SPEED /num;
			//velocity.x = move;

		if (onGround)
			revese = false;
	}

}

PlyaerInAnim::PlyaerInAnim()
	:anim()
{}

void PlyaerInAnim::SetAnim(AnimNumber animNum){
	using aNum = AnimNumber;
	//aNum number = static_cast<aNum>(animNum);
	//Vec2<int>anim;
	switch (animNum){
	case aNum::normal	:		anim = {0,1};	break;
	case aNum::walk1	:		anim = {0,0};	break;
	case aNum::walk2	:		anim = {1,0};	break;
	case aNum::walk3	:		anim = {2,0};	break;
	case aNum::jump		:		anim = {1,1};	break;
	case aNum::takkuru	:		anim = {2,1};	break;
	case aNum::tuta1	:		anim = {0,2};	break;
	case aNum::tuta2	:		anim = {1,2};	break;
	case aNum::over		:		anim = {2,3};	break;
	case aNum::max		:	//fall downnnnnnn  and  Through 
	default				:		anim = {0,1};	break;
	}

}
