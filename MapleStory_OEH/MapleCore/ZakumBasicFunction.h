#pragma once
#include "MonsterBasicFunction.h"

class ZakumBasicFunction : public MonsterBasicFunction
{
	friend class Zakum;
public:

	ZakumBasicFunction();
	~ZakumBasicFunction();

	ZakumBasicFunction(const ZakumBasicFunction& _Other) = delete;
	ZakumBasicFunction(ZakumBasicFunction&& _Other) noexcept = delete;
	ZakumBasicFunction& operator=(const ZakumBasicFunction& _Other) = delete;
	ZakumBasicFunction& operator=(ZakumBasicFunction&& _Other) noexcept = delete;

	void Hit(int _Damage, bool _isRealAttack);


protected:
	int ArmIndex = 0;
	bool isLeft = true;

	std::shared_ptr<class GameEngineSpriteRenderer> ArmRender = nullptr;
	std::shared_ptr<class GameEngineCollision> ArmCollision = nullptr;

	virtual void Attack(){}

private:
	
	int Hp = 200;

	void Spawn(float _DeltaTime) {}
	void MonsterDeath(float _DeltaTime) {}
};

