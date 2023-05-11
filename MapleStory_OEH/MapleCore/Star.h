#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <functional>

class GameEngineSpriteRenderer;
class Star : public GameEngineActor
{
	friend class Player;
public:

	Star();
	~Star();

	void SetUpdateFuction(std::function<bool(Star&, float)> _Fuction)
	{
		UpdateFuction = _Fuction;
	}
	
	void SetStarName(const std::string_view& _Name)
	{
		StarName = _Name;
	}

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

	void TimeCounting();
	void AnimationUpdate();
	void Move(float _DeltaTime);
	void StartTimingCheck(float _DeltaTime);
	void SetStartPos();

	float CurTime = 0.0f;
	float PrevTime = 0.0f;
	float TimeCount = 0.0f;

	float4 StartPos = { 0,0 };

	float AnimationCount = 0.0f;

	float4 MoveDistance = { 0, 0 };

	int AniIndex = 0;
	bool isSet = false;

	std::shared_ptr<GameEngineSpriteRenderer> StarRender = nullptr;
	
	std::function<void(Star&, float)> UpdateFuction = nullptr;
};

