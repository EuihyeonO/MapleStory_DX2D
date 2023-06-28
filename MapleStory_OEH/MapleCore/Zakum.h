#pragma once
#include "ZakumBasicFunction.h"
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineLevel.h>
//#include <GameEngineCore/GameEngineCollision.h>

class Zakum : public ZakumBasicFunction
{
	friend class ZakumLArm_0;
	friend class ZakumLArm_1;
	friend class ZakumLArm_2;
	friend class ZakumLArm_3;
	friend class ZakumRArm_0;
	friend class ZakumRArm_1;
	friend class ZakumRArm_2;
	friend class ZakumRArm_3;

public:

	Zakum();
	~Zakum();

	Zakum(const Zakum& _Other) = delete;
	Zakum(Zakum&& _Other) noexcept = delete;
	Zakum& operator=(const Zakum& _Other) = delete;
	Zakum& operator=(Zakum&& _Other) noexcept = delete;
	
	void Hit(int _Damage, bool _isRealAttack) override;
	
	bool GetIsAtPowerUp()
	{
		return isAtPowerUp;
	}

	bool GetIsDefUp()
	{
		return isDefUp;
	}

	void SetIsAtPowerUp(bool _Bool)
	{
		isAtPowerUp = _Bool;
	}

	void SetIsDefUp(bool _Bool)
	{
		isDefUp = _Bool;
	}

	int GetAtt()
	{
		return Att;
	}

	static std::shared_ptr<Zakum> GetZakum()
	{
		return GlobalZakum;
	}

	void SubHp(int _Damage)
	{
		Hp -= _Damage;
	}

	void SubArmCount()
	{
		ArmCount--;
	}

	void BodyStart()
	{
		if (ArmCount <= 0)
		{
			GetLevel()->TimeEvent.AddEvent(3.0f, [this](GameEngineTimeEvent::TimeEvent&, GameEngineTimeEvent*) {BodyAttackStart = true;});
			BodyCollision->On();
		}
	}

	void AtPowerUp();
	void DefUp();

protected:
	void Start();
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;
private:

	void ArmDeath(bool _isLeft, int _ArmIndex);
	

	void Spawn(float _DeltaTime) {}
	void MonsterDeath(float _DeltaTime) {}
	void CreateArm(bool _isLeft, int _ArmIndex);

	void SetPhase1Attack();
	void SetPhase2Attack();
	void SetPhase3Attack();

	void SetAnimation();
	void ArmAttack();
	void BodyAttack();
	
	void Attack() override;
	void BlackOut();

	static std::shared_ptr<Zakum> GlobalZakum;

	std::shared_ptr<class GameEngineSpriteRenderer> BodyRender = nullptr;
	std::shared_ptr<GameEngineCollision> BodyCollision = nullptr;
	std::string AnimationName = "";

	std::shared_ptr<class ZakumRArm_0> RArm_0 = nullptr;
	std::shared_ptr<class ZakumRArm_1> RArm_1 = nullptr;
	std::shared_ptr<class ZakumRArm_2> RArm_2 = nullptr;
	std::shared_ptr<class ZakumRArm_3> RArm_3 = nullptr;

	std::shared_ptr<class ZakumLArm_0> LArm_0 = nullptr;
	std::shared_ptr<class ZakumLArm_1> LArm_1 = nullptr;
	std::shared_ptr<class ZakumLArm_2> LArm_2 = nullptr;
	std::shared_ptr<class ZakumLArm_3> LArm_3 = nullptr;

	bool isArmAttCoolTime = false;
	bool isBodyAttCoolTime = false;

	bool isHit = false;

	int AniIndex = 0;
	float AniCount = 0;
	
	int CurPhase = 1;

	bool isAtPowerUp = false;
	bool isDefUp = false;

	bool BodyAttackStart = false;
	bool isBodyDefUp = false;
	bool isBlackOut = false;

	int ArmCount = 8;

	bool isArm = false;

	int Hp = 4600;

	void FunctionUpdate();
	std::list<std::function<bool()>> UpdateFuncList;


	//UnLoad
	void LArm_0_UnLoad();
	void LArm_1_UnLoad();
	void LArm_2_UnLoad();
	void LArm_3_UnLoad();
	void RArm_0_UnLoad();
	void RArm_1_UnLoad();
	void RArm_2_UnLoad();
	void RArm_3_UnLoad();

};

