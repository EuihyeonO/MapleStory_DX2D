#pragma once
#include <GameEngineCore/GameEngineLevel.h>

class Level_ZakumRoad2 : public GameEngineLevel
{

public:

	Level_ZakumRoad2();
	~Level_ZakumRoad2();

	Level_ZakumRoad2(const Level_ZakumRoad2& _Other) = delete;
	Level_ZakumRoad2(Level_ZakumRoad2&& _Other) noexcept = delete;
	Level_ZakumRoad2& operator=(const Level_ZakumRoad2& _Other) = delete;
	Level_ZakumRoad2& operator=(Level_ZakumRoad2&& _Other) noexcept = delete;

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
	std::shared_ptr<class ZakumRoad2> Map = nullptr;
	std::shared_ptr<class Mouse> MyMouse = nullptr;
	std::shared_ptr<class UIWindowManager> MyUIWindowManager = nullptr;
};

