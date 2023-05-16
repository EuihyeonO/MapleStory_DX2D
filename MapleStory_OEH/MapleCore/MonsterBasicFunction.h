#pragma once
#include <GameEngineCore/GameEngineActor.h>

class MonsterBasicFunction : public GameEngineActor
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

	virtual void Hit() = 0;

protected:

	float TimeCount = 0.0f;

	bool isAbleJump = false;

	int AniIndex = 0;
	float AnimationCount = 0.0f;
	
	std::string MoveType = "Stand";

	virtual void Spawn(float _DeltaTime) = 0;
	virtual void Death() = 0;


private:

	bool isGround = false;
	bool isFight = false;

	std::string LeftRightDir = "Left";

	std::shared_ptr<class GameEngineTexture> ColMap = nullptr;

	float MoveSpeed = 0.0f;
	float MoveDistance = 0.0f;
	float StandTime = 0.0f;

	float CurTime = 0.0f;
	float PrevTime = 0.0f;

	float Gravity = 200.0f;
	float GravityAccel = 1000.0f;

};

