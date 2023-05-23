#pragma once
#include <GameEngineCore/GameEngineActor.h>

class GameEngineSpriteRenderer;
class GameEngineUIRenderer;
class BottomBar : public GameEngineActor
{

public:

	BottomBar();
	~BottomBar();

	BottomBar(const BottomBar& _Other) = delete;
	BottomBar(BottomBar&& _Other) noexcept = delete;
	BottomBar& operator=(const BottomBar& _Other) = delete;
	BottomBar& operator=(BottomBar&& _Other) noexcept = delete;

protected:
	void Start();
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;
private:

	void BottomBarPosUpdate();
	void GradationUpdate();

	void LevelUpdate();

	std::shared_ptr<GameEngineUIRenderer> BottomBarBackGround = nullptr;
	std::shared_ptr<GameEngineUIRenderer> BottomBarLayer = nullptr;
	std::shared_ptr<GameEngineUIRenderer> StatusBar = nullptr;
	std::shared_ptr<GameEngineUIRenderer> StatusBarLayer = nullptr;

	std::shared_ptr<GameEngineUIRenderer> HpGradation = nullptr;
	std::shared_ptr<GameEngineUIRenderer> MpGradation = nullptr;
	std::shared_ptr<GameEngineUIRenderer> ExpGradation = nullptr;

	std::vector<std::shared_ptr<GameEngineUIRenderer>> LevelRenderer;
	float4 ExpBarRightPos = { 0, 0 };
	float4 HpBarRightPos = { 0, 0 };
	float4 MpBarRightPos = { 0, 0 };

	bool Test = false;

};

