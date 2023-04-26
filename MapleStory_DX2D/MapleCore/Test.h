#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class Test : public GameEngineActor
{
public:
	// constrcuter destructer
	Test();
	~Test();

	// delete Function
	Test(const Test& _Other) = delete;
	Test(Test&& _Other) noexcept = delete;
	Test& operator=(const Test& _Other) = delete;
	Test& operator=(Test&& _Other) noexcept = delete;

protected:
	void Start();
	void Update(float _Delta) override;
	void Render(float _Delta) override;

private:

	void TimeCount();

	float PrevTime = 0.0f;
	float CurTime = 0.0f;
	float CountTime = 0.0f;

	float RenderTime = 0.0f;

	int RenderIndex = 0;

	float Angle = 0.0f;

	float4 Color;
	float4 Color2;

	std::shared_ptr<class GameEngineSpriteRenderer> Render0;
	std::shared_ptr<class GameEngineSpriteRenderer> Render1;
	std::shared_ptr<class GameEngineSpriteRenderer> Render2;
};

