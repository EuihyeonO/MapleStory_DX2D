#pragma once
#include <GameEngineCore/GameEngineLevel.h>

class Level_AlterOfZakumEnt : public GameEngineLevel
{

public:

	Level_AlterOfZakumEnt();
	~Level_AlterOfZakumEnt();

	Level_AlterOfZakumEnt(const Level_AlterOfZakumEnt& _Other) = delete;
	Level_AlterOfZakumEnt(Level_AlterOfZakumEnt&& _Other) noexcept = delete;
	Level_AlterOfZakumEnt& operator=(const Level_AlterOfZakumEnt& _Other) = delete;
	Level_AlterOfZakumEnt& operator=(Level_AlterOfZakumEnt&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void LevelChangeStart() override;
	void LevelChangeEnd() override;
private:
	void LoadResources();
	void UnLoadResources();

	void ActorCreate();
	void ActorDeath();

	std::shared_ptr<class QuickSlot> MyQuickSlot = nullptr;
	std::shared_ptr<class BottomBar> MyBottomBar = nullptr;
	std::shared_ptr<class Player> MyPlayer = nullptr;
	std::shared_ptr<class AlterOfZakumEnt> Map = nullptr;
	std::shared_ptr<class Mouse> MyMouse = nullptr;
	std::shared_ptr<class UIWindowManager> MyUIWindowManager = nullptr;
};

