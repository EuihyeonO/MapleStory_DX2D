#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <functional>

class GameEngineSpriteRenderer;
class StarHitEffect : public GameEngineActor
{

public:

	StarHitEffect();
	~StarHitEffect();

	StarHitEffect(const StarHitEffect& _Other) = delete;
	StarHitEffect(StarHitEffect&& _Other) noexcept = delete;
	StarHitEffect& operator=(const StarHitEffect& _Other) = delete;
	StarHitEffect& operator=(StarHitEffect&& _Other) noexcept = delete;

	void SetSkillType(const std::string_view& _SkillType)
	{
		SkillType = _SkillType;
	}

	void SetFrame();

protected:
	void Start();
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;
private:

	void HitAnimationUpdate();
	void TimeCounting();
	float CurTime = 0.0f;
	float PrevTime = 0.0f;
	float TimeCount = 0.0f;

	int AniIndex = 0;
	float AnimationCount = 0.0f;

	std::string SkillType = "";

	std::shared_ptr<GameEngineSpriteRenderer> EffectRender = nullptr;
	std::vector<float> FrameList;
};

