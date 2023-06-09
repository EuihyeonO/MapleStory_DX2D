#pragma once
#include "BasicFunction.h"

class MonsterBasicFunction : public BasicFunction
{
public:
	MonsterBasicFunction();
	~MonsterBasicFunction();

	MonsterBasicFunction(const MonsterBasicFunction& _Other) = delete;
	MonsterBasicFunction(MonsterBasicFunction&& _Other) noexcept = delete;
	MonsterBasicFunction& operator=(const MonsterBasicFunction& _Other) = delete;
	MonsterBasicFunction& operator=(MonsterBasicFunction&& _Other) noexcept = delete;

	void GravityUpdate(float _DeltaTime);
	void Move(float _DeltaTime);
	void SetColMap(const std::string_view& _MapName);

	void SetLeft();
	void SetRight();

	void DirUpdate();
	void TimeCounting();

	void SetMoveSpeed(float _MoveSpeed)
	{
		MoveSpeed = _MoveSpeed;
	}
	
	bool IsGround()
	{
		return isGround;
	}

	void SetMyZone(class MonsterSpawnZone* _Zone, std::function<void(MonsterSpawnZone&, int)> _StartFunc)
	{
		if (_Zone == nullptr)
		{
			MsgAssert("Nullptr인 함수포인터를 사용했습니다. , 함수 MonsterBasicFunction::SetMyZone ");
		}

		MyZone = _Zone;
		_StartFunc(*MyZone, MyName);
	}

	virtual void Hit(int _Damage, bool _isRealAttack) = 0;

protected:
	bool isAbleJump = false;

	int AniIndex = 0;
	float AnimationCount = 0.0f;

	int MyName = 0;

	std::string MoveType = "Stand";
	
	MonsterSpawnZone* GetMyZone()
	{
		return MyZone;
	}

	virtual void Spawn(float _DeltaTime) = 0;
	virtual void MonsterDeath(float _DeltaTime) = 0;
private:

	bool isGround = false;
	bool isFight = false;

	std::string LeftRightDir = "Left";

	std::shared_ptr<class GameEngineTexture> ColMap = nullptr;

	float MoveSpeed = 0.0f;
	float MoveDistance = 0.0f;
	float StandTime = 0.0f;

	float Gravity = 200.0f;
	float GravityAccel = 1000.0f;

	class MonsterSpawnZone* MyZone = nullptr;
};

