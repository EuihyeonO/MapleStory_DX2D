#pragma once
#include <GameEngineCore/GameEngineActor.h>

class GameEngineUIRenderer;
class InventoryWindow : public GameEngineActor
{
public:

	InventoryWindow();
	~InventoryWindow();

	InventoryWindow(const InventoryWindow& _Other) = delete;
	InventoryWindow(InventoryWindow&& _Other) noexcept = delete;
	InventoryWindow& operator=(const InventoryWindow& _Other) = delete;
	InventoryWindow& operator=(InventoryWindow&& _Other) noexcept = delete;

	void SetInventoryType(int _InvenType)
	{
		InventoryType = _InvenType;
	}
	
	std::shared_ptr<class ItemList> GetInventory()
	{
		return Inventory;
	}

	void InventoryUpdate();

	void ChangeInventory();
	void ClearInventory();

protected:
	void Start();
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;
private:
	std::shared_ptr<GameEngineUIRenderer> InventoryRender = nullptr;

	std::shared_ptr<class ItemList> Inventory = nullptr;

	std::shared_ptr<GameEngineCollision> Equip = nullptr;
	std::shared_ptr<GameEngineCollision> Use = nullptr;
	std::shared_ptr<GameEngineCollision> Setup = nullptr;
	std::shared_ptr<GameEngineCollision> Etc = nullptr;
	std::shared_ptr<GameEngineCollision> Cash = nullptr;

	int InventoryType = 0;
};

