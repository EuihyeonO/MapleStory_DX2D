#pragma once

#include <GameEngineBase/GameEngineTimeEvent.h>
#include <GameEngineCore\GameEngineLevel.h>

class Level_AlterOfZakum : public GameEngineLevel
{

public:

	Level_AlterOfZakum();
	~Level_AlterOfZakum();

	Level_AlterOfZakum(const Level_AlterOfZakum& _Other) = delete;
	Level_AlterOfZakum(Level_AlterOfZakum&& _Other) noexcept = delete;
	Level_AlterOfZakum& operator=(const Level_AlterOfZakum& _Other) = delete;
	Level_AlterOfZakum& operator=(Level_AlterOfZakum&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void LevelChangeStart() override;
	void LevelChangeEnd() override;
private:
	void LoadSprite();
	void LoadResources();

	void ReLoadSprite();
	
	void UnLoadSprite();
	void UnLoadResources();

	void ActorCreate();
	void ActorDeath();


	std::shared_ptr<class Player> MyPlayer = nullptr;
	std::shared_ptr<class AlterOfZakum> Map = nullptr;
	std::shared_ptr<class Mouse> MyMouse = nullptr;
	std::shared_ptr<class UIWindowManager> MyUIWindowManager = nullptr;
	std::shared_ptr<class QuickSlot> MyQuickSlot = nullptr;
	std::shared_ptr<class BottomBar> MyBottomBar = nullptr;
};

