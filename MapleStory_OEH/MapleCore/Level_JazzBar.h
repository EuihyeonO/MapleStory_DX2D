#pragma once
#include <GameEngineCore/GameEngineLevel.h>

class Level_JazzBar : public GameEngineLevel
{

public:

	Level_JazzBar();
	~Level_JazzBar();

	Level_JazzBar(const Level_JazzBar& _Other) = delete;
	Level_JazzBar(Level_JazzBar&& _Other) noexcept = delete;
	Level_JazzBar& operator=(const Level_JazzBar& _Other) = delete;
	Level_JazzBar& operator=(Level_JazzBar&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void LevelChangeStart() override;
	void LevelChangeEnd() override;
private:

	void ActorCreate();
	void ActorDeath();

	void LoadResources();
	void UnLoadResources();

	std::shared_ptr<class QuickSlot> MyQuickSlot = nullptr;
	std::shared_ptr<class BottomBar> MyBottomBar = nullptr;
	std::shared_ptr<class Player> MyPlayer = nullptr;
	std::shared_ptr<class JazzBar> Map = nullptr;
	std::shared_ptr<class Mouse> MyMouse = nullptr;
	std::shared_ptr<class UIWindowManager> MyUIWindowManager = nullptr;
};

