#pragma once
#include "BasicFunction.h"
#include <functional>

class GameEngineSpriteRenderer;
class Star : public BasicFunction
{
	friend class Player;
	friend class SkillActor;
public:

	Star();
	~Star();

	void SetUpdateFuction(std::function<void(Star&, float)> _Fuction)
	{
		UpdateFuction = _Fuction;
	}
	
	void SetStarName(const std::string_view& _Name)
	{
		StarName = _Name;
	}

	void SetDir(float4 _Dir)
	{
		Dir = _Dir;
	}

	void SetTargetMonster(std::vector<std::shared_ptr<class GameEngineCollision>>& _TargetMonsterVector, float4 _PlayerPos)
	{
		std::shared_ptr<GameEngineCollision> nearlestMonster = nullptr;
		float PrevDistance = 0.0f;

		for (int i = 0; i < _TargetMonsterVector.size(); i++)
		{
			float4 MonsterPos = _TargetMonsterVector[i]->GetTransform()->GetWorldPosition();
			float Distance = (MonsterPos.x - _PlayerPos.x) * (MonsterPos.x - _PlayerPos.x) + (MonsterPos.y - _PlayerPos.y) * (MonsterPos.y - _PlayerPos.y);
						
			if (i == 0)
			{
				PrevDistance = Distance;
				nearlestMonster = _TargetMonsterVector[0];
				continue;
			}
			else
			{
				if (Distance < PrevDistance)
				{
					nearlestMonster = _TargetMonsterVector[i];
				}

				PrevDistance = Distance;
			}
		}
		Target = nearlestMonster;
	}

	void SetTargetMonster(std::shared_ptr<class GameEngineCollision> _TargetMonsterVector)
	{
		Target = _TargetMonsterVector;
	}

	void SetTimingTime(float _Time)
	{
		TimingTime = _Time;
	}
	
	void SetType(const std::string_view& _Type)
	{
		Type = _Type;
	}

	void Damage();
	void AvengerDamage();

	Star(const Star& _Other) = delete;
	Star(Star&& _Other) noexcept = delete;
	Star& operator=(const Star& _Other) = delete;
	Star& operator=(Star&& _Other) noexcept = delete;

protected:
	void Start();
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;
private:

	std::string StarName;
	std::string Type;

	void BasicAnimationUpdate();

	void Move(float _DeltaTime);
	void AvengerMove(float _DeltaTime);

	void StartTimingCheck(float _DeltaTime);
	void SetStartPos();

	float4 StartPos = { 0,0 };
	float AnimationCount = 0.0f;
	float AttackDistance = 0.0f;

	int AniIndex = 0;

	float TimingTime = 0.0f;
	float TimingTimeCount = 0.0f;

	bool isSet = false;

	float4 Dir = { 0,0 };

	std::shared_ptr<GameEngineSpriteRenderer> StarRender = nullptr;
	std::shared_ptr<GameEngineSpriteRenderer> HitRender = nullptr;
	std::shared_ptr<class GameEngineCollision> StarCollision = nullptr;
	std::shared_ptr<class GameEngineCollision> Target = nullptr;
	
	std::function<void(Star&, float)> UpdateFuction = nullptr;
};

