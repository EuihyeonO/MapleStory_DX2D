#pragma once
#include "MonsterBasicFunction.h"

class SmallZakum2 : public MonsterBasicFunction
{

public:

	SmallZakum2();
	~SmallZakum2();

	SmallZakum2(const SmallZakum2& _Other) = delete;
	SmallZakum2(SmallZakum2&& _Other) noexcept = delete;
	SmallZakum2& operator=(const SmallZakum2& _Other) = delete;
	SmallZakum2& operator=(SmallZakum2&& _Other) noexcept = delete;

	void Hit(int _Damage, bool _isRealAttack) override;

protected:
	void Start();
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

	void Spawn(float _DeltaTime) override;
	void MonsterDeath(float _DeltaTime) override;

	void Fly(float _DeltaTime) override;
	void Attack() override;
private:

	void SetStatus();
	void SetAnimation();
	void Hit();
	void AttackRangeCheck();

	int Hp = 250;

	float MaxMoveDistance = 0.0f;
	bool isAttack = false;
	bool isAttCoolTime = false;

	void SetMoveDir();
	float4 MoveDir = { 0, 0 };

	std::vector<std::pair<std::string, /*0�̻� 100������ ����*/int>> DropItemList;
	std::shared_ptr<GameEngineCollision> AttackCollision = nullptr;
};

