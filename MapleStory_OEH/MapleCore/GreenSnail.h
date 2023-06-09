#pragma once
#include "MonsterBasicFunction.h"

class GreenSnail : public MonsterBasicFunction
{

public:

	GreenSnail();
	~GreenSnail();

	GreenSnail(const GreenSnail& _Other) = delete;
	GreenSnail(GreenSnail&& _Other) noexcept = delete;
	GreenSnail& operator=(const GreenSnail& _Other) = delete;
	GreenSnail& operator=(GreenSnail&& _Other) noexcept = delete;

	void Hit(int _Damage, bool _isRealAttack) override;

protected:
	void Start();
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

	void Spawn(float _DeltaTime) override;
	void MonsterDeath(float _DeltaTime) override;
private:

	void TextureUpdate();
	void SetAnimationList();	
	void SetDropItemList();

	float RenderAlpha = 0.0f;

	int Hp = 50;

	bool isSpawnAnimationEnd = false;
	bool isDeathStart = false;

	std::map<std::string, std::vector<float>> FrameList;
	std::vector<std::pair<std::string, /*0�̻� 100������ ����*/int>> DropItemList;

	//std::shared_ptr<class DamageRender> Re;
	std::shared_ptr<class ContentRenderer> BasicRender;
	std::shared_ptr<class GameEngineCollision> BasicCollision;
};

