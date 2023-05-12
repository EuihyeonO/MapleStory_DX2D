#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <functional>

class GameEngineSpriteRenderer;
class SkillActor : public GameEngineActor
{
	friend class Player;
public:

	SkillActor();
	~SkillActor();

	SkillActor(const SkillActor& _Other) = delete;
	SkillActor(SkillActor&& _Other) noexcept = delete;
	SkillActor& operator=(const SkillActor& _Other) = delete;
	SkillActor& operator=(SkillActor&& _Other) noexcept = delete;


protected:
	void Start();
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;
private:

	void TimeCounting();

	float CurTime = 0.0f;
	float PrevTime = 0.0f;
	float TimeCount = 0.0f;

	void SetSkillActor(const std::string_view& _SkillName);
	void SetSkillAnimation();
	void SetUpdateFunc();

	void Haste();

	std::string SkillName;

	std::shared_ptr<GameEngineSpriteRenderer> AnimationRender;
	std::shared_ptr<GameEngineSpriteRenderer> IconRender;

	std::map<std::string, std::vector<float4>> SkillOriginPosVector;
	std::map <std::string, std::vector<float>> AniFrameList;

	std::function<void(SkillActor&)> UpdateFunc =  nullptr;

	int AnimationIndex = 0;
	float AnimationCount = 0.0f;
};

