#pragma once
#include "ZakumBasicFunction.h"
#include <GameEngineCore/GameEngineActor.h>

class Zakum : public ZakumBasicFunction
{

public:

	Zakum();
	~Zakum();

	Zakum(const Zakum& _Other) = delete;
	Zakum(Zakum&& _Other) noexcept = delete;
	Zakum& operator=(const Zakum& _Other) = delete;
	Zakum& operator=(Zakum&& _Other) noexcept = delete;
	
	void Hit(int _Damage, bool _isRealAttack) override {}
	
	static std::shared_ptr<Zakum> GetZakum()
	{
		return GlobalZakum;
	}

	void ArmDeath(bool _isLeft, int _ArmIndex);

protected:
	void Start();
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;
private:
	void Spawn(float _DeltaTime) {}
	void MonsterDeath(float _DeltaTime) {}
	void CreateArm(bool _isLeft, int _ArmIndex);

	void SetAnimation();
	void ArmAttack();

	static std::shared_ptr<Zakum> GlobalZakum;

	std::shared_ptr<class GameEngineSpriteRenderer> BodyRender = nullptr;
	std::string AnimationName = "";

	std::shared_ptr<class ZakumRArm_0> RArm_0 = nullptr;
	std::shared_ptr<class ZakumRArm_1> RArm_1 = nullptr;
	std::shared_ptr<class ZakumRArm_2> RArm_2 = nullptr;
	std::shared_ptr<class ZakumRArm_3> RArm_3 = nullptr;

	std::shared_ptr<class ZakumLArm_0> LArm_0 = nullptr;
	std::shared_ptr<class ZakumLArm_1> LArm_1 = nullptr;
	std::shared_ptr<class ZakumLArm_2> LArm_2 = nullptr;
	std::shared_ptr<class ZakumLArm_3> LArm_3 = nullptr;

	bool isArmAtCoolTime = false;
	int AniIndex = 0;
	float AniCount = 0;
};

