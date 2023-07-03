#pragma once
#include <GameEngineCore/GameEngineLevel.h>

class Level_SouthFerry : public GameEngineLevel
{

public:

	Level_SouthFerry();
	~Level_SouthFerry();

	Level_SouthFerry(const Level_SouthFerry& _Other) = delete;
	Level_SouthFerry(Level_SouthFerry&& _Other) noexcept = delete;
	Level_SouthFerry& operator=(const Level_SouthFerry& _Other) = delete;
	Level_SouthFerry& operator=(Level_SouthFerry&& _Other) noexcept = delete;

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
	std::shared_ptr<class SouthFerry> Map = nullptr;
	std::shared_ptr<class Mouse> MyMouse = nullptr;
	std::shared_ptr<class UIWindowManager> MyUIWindowManager = nullptr;
};

