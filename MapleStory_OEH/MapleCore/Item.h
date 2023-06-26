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

	void SetItemInfo(std::shared_ptr<struct ItemInfo> _ItemName, int _ItemType);

	void SetParentItemList(std::shared_ptr<class ItemList> _ParentItemList)
	{
		ParentItemList = _ParentItemList;
	}

	void Clicked();
	void EquipThis();

protected:
	void Start();
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;
private:
	
	std::string ItemName = "";

	bool isEmptyItem = false;
	bool isClicked = false;
	bool isEquip = false;

	int ItemType = 0;
	//int EquipLevel = 0;
	//int NumOfItem = 0;
	//int EquipType = -1;
	
	std::shared_ptr<struct ItemInfo> MyInfo = nullptr;

	int ItemIndex = 0;

	std::shared_ptr<class ItemList> ParentItemList = nullptr;

	std::shared_ptr<GameEngineUIRenderer> ItemRender = nullptr;
	std::shared_ptr<GameEngineCollision> ItemCollision = nullptr;
};

