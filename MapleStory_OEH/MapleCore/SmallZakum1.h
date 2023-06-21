#pragma once
#include "MonsterBasicFunction.h"

class SmallZakum1 : public MonsterBasicFunction
{

public:

	SmallZakum1();
	~SmallZakum1();

	SmallZakum1(const SmallZakum1& _Other) = delete;
	SmallZakum1(SmallZakum1&& _Other) noexcept = delete;
	SmallZakum1& operator=(const SmallZakum1& _Other) = delete;
	SmallZakum1& operator=(SmallZakum1&& _Other) noexcept = delete;

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

	std::vector<std::pair<std::string, /*0이상 100이하의 정수*/int>> DropItemList;
	std::shared_ptr<GameEngineCollision> AttackCollision = nullptr;
};

