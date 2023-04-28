#pragma once
#include"libs/object.h"
class BlockBreakEffect;

struct Emitter{
	std::list<BlockBreakEffect*>effectList;
	bool active=true;
	bool initialize=false;

	void Init();
	void Update();
	void Draw();

	void Destroy();
	void Create(int graph,Scene* sc);
	void SetPos(Vec2<float>position);
};

class BlockBreakEffectManager :public Object {
public:
	BlockBreakEffectManager(Scene* sc);
	~BlockBreakEffectManager()	override;
	void Init()					override;
	void Update()				override;
	void Draw()					override;

	void Create();
	void SetPos(Vec2<float>position);
private:
	std::list<Emitter*>effectList;
	int hImage;
	int count=0;
};



//
// BlokBreakEffectManagerの中身
// BlockBreakEffectを管理
//
// ブロックを叩いた時は関数一つで生成
// 
// BreakEffectをCreateで四つの破片を作る。
// 作るときのデータは　struct or class　でまとめておく＋関数を作る。
// list<>で複数きてもいいようにする
// 
// Update()はそれぞれの更新
// Draw()はそれぞれの描画
//