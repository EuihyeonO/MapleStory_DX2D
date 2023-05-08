#pragma once
#include <GameEngineCore/GameEngineActor.h>

class GameEngineSpriteRenderer;
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
	std::shared_ptr<GameEngineSpriteRenderer> BottomBarBackGround = nullptr;
	std::shared_ptr<GameEngineSpriteRenderer> BottomBarLayer = nullptr;
	std::shared_ptr<GameEngineSpriteRenderer> StatusBar = nullptr;
};

