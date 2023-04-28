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
// BlokBreakEffectManager�̒��g
// BlockBreakEffect���Ǘ�
//
// �u���b�N��@�������͊֐���Ő���
// 
// BreakEffect��Create�Ŏl�̔j�Ђ����B
// ���Ƃ��̃f�[�^�́@struct or class�@�ł܂Ƃ߂Ă����{�֐������B
// list<>�ŕ������Ă������悤�ɂ���
// 
// Update()�͂��ꂼ��̍X�V
// Draw()�͂��ꂼ��̕`��
//