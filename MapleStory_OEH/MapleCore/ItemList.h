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
protected:
	void Start();
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;
private:

	std::map<int, std::list<std::shared_ptr<class Item>>> MyItemList;
};

