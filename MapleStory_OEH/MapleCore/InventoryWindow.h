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

	int GetInventoryType()
	{
		return InventoryType;
	}

	void InventoryUpdate();

	void ChangeInventory();
	void ClearInventory();

protected:
	void Start();
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;
private:

	void ColPosUpdate();

	std::shared_ptr<GameEngineUIRenderer> InventoryRender = nullptr;

	std::shared_ptr<class ItemList> Inventory = nullptr;

	std::shared_ptr<class GameEngineCollision> Equip = nullptr;
	std::shared_ptr<class GameEngineCollision> Use = nullptr;
	std::shared_ptr<class GameEngineCollision> Setup = nullptr;
	std::shared_ptr<class GameEngineCollision> Etc = nullptr;
	std::shared_ptr<class GameEngineCollision> Cash = nullptr;

	std::shared_ptr<class GameEngineCollision> InventoryBoxCollision = nullptr;

	int InventoryType = 0;
};

