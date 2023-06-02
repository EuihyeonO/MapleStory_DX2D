#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <list>

class GameEngineSpriteRenderer;
class UIWindowManager : public GameEngineActor
{
public:

	UIWindowManager();
	~UIWindowManager();

	UIWindowManager(const UIWindowManager& _Other) = delete;
	UIWindowManager(UIWindowManager&& _Other) noexcept = delete;
	UIWindowManager& operator=(const UIWindowManager& _Other) = delete;
	UIWindowManager& operator=(UIWindowManager&& _Other) noexcept = delete;

	void AllWindowDeath();
	
protected:
	void Start();
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;
private:

	void CreateUIKey();
	void UIOnOff();

	std::shared_ptr<class StatusWindow> MyStatusWindow = nullptr;
	std::shared_ptr<class SkillWindow> MySKillWindow = nullptr;
	std::shared_ptr<class InventoryWindow> MyInventoryWindow = nullptr;
	std::shared_ptr<class EquipWindow> MyEquipWindow = nullptr;

};

