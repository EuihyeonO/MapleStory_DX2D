#pragma once
#include "BasicFunction.h"
#include <functional>

class GameEngineSpriteRenderer;
class SkillActor : public BasicFunction
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

	void SetSkillActor(const std::string_view& _SkillName, bool isRePlay = true);
	void SetSkillAnimation();
	void SetUpdateFunc();

	void Haste();
	void Avenger();
	void LuckySeven();
	void JavelinBooster();
	void ShadowPartner();

	std::string SkillName;

	std::shared_ptr<GameEngineSpriteRenderer> AnimationRender;

	std::map<std::string, std::vector<float4>> SkillOriginPosVector;
	std::map <std::string, std::vector<float>> AniFrameList;

	std::function<void(SkillActor&)> UpdateFunc =  nullptr;

	bool isRePlay = false;

	int AnimationIndex = 0;
	int LastIndex = 0;
	float AnimationCount = 0.0f;
};

