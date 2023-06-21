#pragma once
#include "MonsterBasicFunction.h"

class SmallZakum0 : public MonsterBasicFunction
{

public:

	SmallZakum0();
	~SmallZakum0();

	SmallZakum0(const SmallZakum0& _Other) = delete;
	SmallZakum0(SmallZakum0&& _Other) noexcept = delete;
	SmallZakum0& operator=(const SmallZakum0& _Other) = delete;
	SmallZakum0& operator=(SmallZakum0&& _Other) noexcept = delete;

	void Hit(int _Damage, bool _isRealAttack) override;

protected:
	void Start();
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

	void Spawn(float _DeltaTime) override;
	void MonsterDeath(float _DeltaTime) override;
	
	void Fly(float _DeltaTime) override;
private:

	void SetStatus();
	void SetAnimation();
	void Hit();

	int Hp = 250;

	float MaxMoveDistance = 0.0f;

	void SetMoveDir();
	float4 MoveDir = { 0, 0 };

	std::vector<std::pair<std::string, /*0이상 100이하의 정수*/int>> DropItemList;
};

