#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <map>
#include <list>

class GameEngineUIRenderer;
class ItemList : public GameEngineActor
{
	friend class InventoryWindow;

public:

	ItemList();
	~ItemList();

	ItemList(const ItemList& _Other) = delete;
	ItemList(ItemList&& _Other) noexcept = delete;
	ItemList& operator=(const ItemList& _Other) = delete;
	ItemList& operator=(ItemList&& _Other) noexcept = delete;
	
	std::shared_ptr<class Item> CreateItem(const std::string_view& _ItemName, int _ItemType);

	void SortItemListToType(int _ItemType);
	void SortItemList();

	void LoadAllItem();
	void LoadItem(const std::string_view& _ItemName, int _ItemType);

	void ClearItem();
	
	void EquipItem(std::shared_ptr<class Item> _Item);
	void DeleteItem(std::shared_ptr<class Item> _Item);

	void ChangeRenderItem(int _CurItemType, int _NextItemType);
	void InventoryItemOn(int _CurItemType);
	void InventoryItemOff(int _CurItemType);

	int GetRealSizeOfItemList(int _ItemType);
protected:
	void Start();
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;
private:

	float4 StartPos = { -63 , 77 };
	float Xinterval = 36.0f;
	float Yinterval = -34.0f;

	std::shared_ptr<Item> _item;
	std::map<int, std::list<std::shared_ptr<class Item>>> MyItemList;
};

