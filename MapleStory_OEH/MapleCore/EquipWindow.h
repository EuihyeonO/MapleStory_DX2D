#pragma once
#include <GameEngineCore/GameEngineActor.h>

class GameEngineUIRenderer;
class EquipWindow : public GameEngineActor
{

public:

	EquipWindow();
	~EquipWindow();

	EquipWindow(const EquipWindow& _Other) = delete;
	EquipWindow(EquipWindow&& _Other) noexcept = delete;
	EquipWindow& operator=(const EquipWindow& _Other) = delete;
	EquipWindow& operator=(EquipWindow&& _Other) noexcept = delete;

	std::shared_ptr<class EquipItemList> GetEquipItemList()
	{
		return MyEquipItemList;
	}

protected:
	void Start();
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;
private:
	std::shared_ptr<GameEngineUIRenderer> EquipWindowRender = nullptr;

	std::shared_ptr<class EquipItemList> MyEquipItemList = nullptr;
};

