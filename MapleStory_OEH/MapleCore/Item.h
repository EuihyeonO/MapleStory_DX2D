#pragma once
#include <GameEngineCore/GameEngineActor.h>

class GameEngineUIRenderer;
class GameEngineCollision;
class Item : public GameEngineActor
{
	friend class ItemList;
	friend class InventoryWindow;
	friend class EquipItemList;

public:

	Item();
	~Item();

	Item(const Item& _Other) = delete;
	Item(Item&& _Other) noexcept = delete;
	Item& operator=(const Item& _Other) = delete;
	Item& operator=(Item&& _Other) noexcept = delete;

	std::shared_ptr<GameEngineUIRenderer> GetItemRender()
	{
		return ItemRender;
	}

	std::shared_ptr<GameEngineCollision> GetItemCollision()
	{
		return ItemCollision;
	}

	void SetItemInfo(const std::string_view& _ItemName, int _ItemType, int _EquipLevel = 0, int EquipType = 0);
	void SetEmptyItem();

	void SetParentItemList(std::shared_ptr<class ItemList> _ParentItemList)
	{
		ParentItemList = _ParentItemList;
	}

protected:
	void Start();
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;
private:
	
	std::string ItemName = "";

	bool isEmptyItem = false;
	bool isClicked = false;

	int ItemType = 0;
	int EquipLevel = 0;

	int EquipType = -1;
	
	int ItemIndex = 0;

	std::shared_ptr<class ItemList> ParentItemList = nullptr;

	std::shared_ptr<GameEngineUIRenderer> ItemRender = nullptr;
	std::shared_ptr<GameEngineCollision> ItemCollision = nullptr;
};

