#pragma once
#include "MonsterBasicFunction.h"

class Boogie : public MonsterBasicFunction
{

public:

	Boogie();
	~Boogie();

	Boogie(const Boogie& _Other) = delete;
	Boogie(Boogie&& _Other) noexcept = delete;
	Boogie& operator=(const Boogie& _Other) = delete;
	Boogie& operator=(Boogie&& _Other) noexcept = delete;

	void Hit(int _Damage, bool _isRealAttack) override;

protected:
	void Start();
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

	void Spawn(float _DeltaTime) override;
	void MonsterDeath(float _DeltaTime) override;
private:

	void SetAnimation();

	int Hp = 250;

	std::vector<std::pair<std::string, /*0이상 100이하의 정수*/int>> DropItemList;
};

