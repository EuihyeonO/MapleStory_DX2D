#include "PrecompileHeader.h"
#include "ItemList.h"
#include "Item.h"

#include <GameEngineCore/GameEngineLevel.h>

ItemList::ItemList()
{
}

ItemList::~ItemList()
{
}

void ItemList::Start()
{	
}

void ItemList::Update(float _DeltaTime) 
{
}

void ItemList::Render(float _DeltaTime) 
{
}

std::shared_ptr<Item> ItemList::CreateItem(const std::string_view& _ItemName, int _ItemType)
{
	std::shared_ptr<Item> NewItem = GetLevel()->CreateActor<Item>();
	NewItem->SetItemInfo(_ItemName, _ItemType);

	MyItemList[static_cast<int>(_ItemType)].push_back(NewItem);
	
	NewItem->GetTransform()->SetParent(GetTransform());

	return NewItem;
}

void ItemList::SortItemListToType(int _ItemType)
{
	std::list<std::shared_ptr<class Item>>::iterator Start = MyItemList[_ItemType].begin();
	std::list<std::shared_ptr<class Item>>::iterator End = MyItemList[_ItemType].end();

	for (; Start != End; Start++)
	{
		Start->get()->GetTransform()->SetLocalPosition({ -30, 100 });
	}
}