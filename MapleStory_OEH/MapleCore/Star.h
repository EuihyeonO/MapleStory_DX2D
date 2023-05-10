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

	void SetUpdateFuction(std::function<bool(float)> _Fuction)
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

	float CurTime = 0.0f;
	float PrevTime = 0.0f;
	float TimeCount = 0.0f;

	float AnimationCount = 0.0f;

	float MoveDistance = 0.0f;

	int AniIndex = 0;

	std::shared_ptr<GameEngineSpriteRenderer> StarRender = nullptr;
	
	std::function<bool(float)> UpdateFuction = nullptr;
};

