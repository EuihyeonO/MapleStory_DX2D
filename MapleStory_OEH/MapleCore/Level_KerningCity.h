#pragma once
#include <GameEngineCore/GameEngineLevel.h>

class Level_KerningCity : public GameEngineLevel
{

public:

	Level_KerningCity();
	~Level_KerningCity();

	Level_KerningCity(const Level_KerningCity& _Other) = delete;
	Level_KerningCity(Level_KerningCity&& _Other) noexcept = delete;
	Level_KerningCity& operator=(const Level_KerningCity& _Other) = delete;
	Level_KerningCity& operator=(Level_KerningCity&& _Other) noexcept = delete;

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
	std::shared_ptr<class KerningCity> Map = nullptr;
	std::shared_ptr<class Mouse> MyMouse = nullptr;
	std::shared_ptr<class UIWindowManager> MyUIWindowManager = nullptr;
};

