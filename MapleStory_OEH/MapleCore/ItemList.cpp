#include "PrecompileHeader.h"
#include "ItemList.h"
#include "Item.h"
#include "UIController.h"
#include "Mouse.h"
#include "PlayerValue.h"

#include <GameEngineCore/GameEngineLevel.h>
#include <GameEnginePlatform/GameEngineInput.h>

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
	
	if (_ItemName == "EMPTY")
	{
		NewItem->SetEmptyItem();
		NewItem->GetTransform()->SetParent(GetTransform());
		NewItem->SetParentItemList(DynamicThis<ItemList>());
		MyItemList[static_cast<int>(_ItemType)].push_back(NewItem);
		return NewItem;
	}
	else
	{
		NewItem->SetItemInfo(_ItemName, _ItemType);
	}

	NewItem->GetTransform()->SetParent(GetTransform());
	NewItem->SetParentItemList(DynamicThis<ItemList>());

	std::list<std::shared_ptr<class Item>>::iterator Start = MyItemList[static_cast<int>(_ItemType)].begin();
	std::list<std::shared_ptr<class Item>>::iterator End = MyItemList[static_cast<int>(_ItemType)].end();

	for (; Start != End; Start++)
	{
		if (Start->get()->isEmptyItem == true)
		{
			Start->get()->Death();
			*Start = NewItem;
			return NewItem;
		}
	}

	MyItemList[static_cast<int>(_ItemType)].push_back(NewItem);
	return NewItem;
}

void ItemList::LoadItem(const std::string_view& _ItemName, int _ItemType)
{
	std::shared_ptr<Item> NewItem = GetLevel()->CreateActor<Item>();

	if (_ItemName == "EMPTY")
	{
		NewItem->SetEmptyItem();
		NewItem->GetTransform()->SetParent(GetTransform());
		NewItem->SetParentItemList(DynamicThis<ItemList>());
		MyItemList[static_cast<int>(_ItemType)].push_back(NewItem);
		return;
	}
	else
	{
		NewItem->SetItemInfo(_ItemName, _ItemType);
		NewItem->GetTransform()->SetParent(GetTransform());
		NewItem->SetParentItemList(DynamicThis<ItemList>());
		MyItemList[static_cast<int>(_ItemType)].push_back(NewItem);
		return;
	}
}

void ItemList::LoadAllItem()
{
	std::map<int, std::list<std::string>> CopyMap = UIController::GetUIController()->GetItemList();
	
	std::list<std::string>::iterator Start;
	std::list<std::string>::iterator End;

	size_t EquipSize = CopyMap[static_cast<int>(ItemType::Equip)].size();
	
	Start = CopyMap[static_cast<int>(ItemType::Equip)].begin();
	End = CopyMap[static_cast<int>(ItemType::Equip)].end();

	for (; Start != End; Start++)
	{
		std::string _ItemName = *Start;
		LoadItem(_ItemName, static_cast<int>(ItemType::Equip));
	}

	size_t UseSize = CopyMap[static_cast<int>(ItemType::Use)].size();

	Start = CopyMap[static_cast<int>(ItemType::Use)].begin();
	End = CopyMap[static_cast<int>(ItemType::Use)].end();

	for (; Start != End; Start++)
	{
		std::string _ItemName = *Start;
		LoadItem(_ItemName, static_cast<int>(ItemType::Use));
	}

	size_t EtcSize = CopyMap[static_cast<int>(ItemType::Etc)].size();

	Start = CopyMap[static_cast<int>(ItemType::Etc)].begin();
	End = CopyMap[static_cast<int>(ItemType::Etc)].end();

	for (; Start != End; Start++)
	{
		std::string _ItemName = *Start;
		LoadItem(_ItemName, static_cast<int>(ItemType::Etc));
	}

	size_t SetupSize = CopyMap[static_cast<int>(ItemType::Setup)].size();
	
	Start = CopyMap[static_cast<int>(ItemType::Setup)].begin();
	End = CopyMap[static_cast<int>(ItemType::Setup)].end();

	for (; Start != End; Start++)
	{
		std::string _ItemName = *Start;
		LoadItem(_ItemName, static_cast<int>(ItemType::Setup));
	}

	size_t CashSize = CopyMap[static_cast<int>(ItemType::Cash)].size();
	
	Start = CopyMap[static_cast<int>(ItemType::Cash)].begin();
	End = CopyMap[static_cast<int>(ItemType::Cash)].end();
	
	for (; Start != End; Start++)
	{
		std::string _ItemName = *Start;
		LoadItem(_ItemName, static_cast<int>(ItemType::Cash));
	}
}

void ItemList::SortItemListToType(int _ItemType)
{
	std::list<std::shared_ptr<class Item>>::iterator Start = MyItemList[_ItemType].begin();
	std::list<std::shared_ptr<class Item>>::iterator End = MyItemList[_ItemType].end();

	int count = 0;

	for (;Start != End; Start++)
	{
		if (Start->get()->isClicked == true)
		{
			count++;
			continue;
		}

		int Yindex = count / 4;
		int Xindex = count % 4;

		Start->get()->GetTransform()->SetLocalPosition(StartPos + float4{Xinterval * Xindex, Yinterval * Yindex });
		Start->get()->ItemIndex = count;

		count++;
	}
}

void ItemList::ClearItem()
{
	std::list<std::shared_ptr<class Item>>::iterator Start = MyItemList[static_cast<int>(ItemType::Equip)].begin();
	std::list<std::shared_ptr<class Item>>::iterator End = MyItemList[static_cast<int>(ItemType::Equip)].end();

	for (;Start != End;)
	{
		if (Start->get()->isClicked == true)
		{
			Start->get()->ItemRender->GetTransform()->SetParent(Start->get()->GetTransform());
			Start->get()->ItemCollision->GetTransform()->SetParent(Start->get()->GetTransform());
		}

		Start->get()->Death();
		Start = MyItemList[static_cast<int>(ItemType::Equip)].erase(Start);
	}

	Start = MyItemList[static_cast<int>(ItemType::Use)].begin();
	End = MyItemList[static_cast<int>(ItemType::Use)].end();

	for (; Start != End;)
	{
		Start->get()->Death();
		Start = MyItemList[static_cast<int>(ItemType::Use)].erase(Start);
	}

	Start = MyItemList[static_cast<int>(ItemType::Etc)].begin();
	End = MyItemList[static_cast<int>(ItemType::Etc)].end();

	for (; Start != End;)
	{
		Start->get()->Death();
		Start = MyItemList[static_cast<int>(ItemType::Etc)].erase(Start);
	}

	Start = MyItemList[static_cast<int>(ItemType::Setup)].begin();
	End = MyItemList[static_cast<int>(ItemType::Setup)].end();

	for (; Start != End;)
	{
		Start->get()->Death();
		Start = MyItemList[static_cast<int>(ItemType::Setup)].erase(Start);
	}

	Start = MyItemList[static_cast<int>(ItemType::Cash)].begin();
	End = MyItemList[static_cast<int>(ItemType::Cash)].end();

	for (; Start != End;)
	{
		Start->get()->Death();
		Start = MyItemList[static_cast<int>(ItemType::Cash)].erase(Start);
	}
}


void ItemList::ChangeRenderItem(int _CurItemType, int _NextItemType)
{
	InventoryItemOff(_CurItemType);
	InventoryItemOn(_NextItemType);
}

void ItemList::InventoryItemOn(int _CurItemType)
{
	std::list<std::shared_ptr<class Item>>::iterator Start = MyItemList[_CurItemType].begin();
	std::list<std::shared_ptr<class Item>>::iterator End = MyItemList[_CurItemType].end();

	for (; Start != End; Start++)
	{
		if(Start->get()->isEmptyItem == false)
		{
			Start->get()->GetItemRender()->On();
			Start->get()->GetItemCollision()->On();
		}
	}
}

void ItemList::InventoryItemOff(int _CurItemType)
{
	std::list<std::shared_ptr<class Item>>::iterator Start = MyItemList[_CurItemType].begin();
	std::list<std::shared_ptr<class Item>>::iterator End = MyItemList[_CurItemType].end();

	for (; Start != End; Start++)
	{
		Start->get()->GetItemRender()->Off();
		Start->get()->GetItemCollision()->Off();
	}
}


int ItemList::GetRealSizeOfItemList(int _ItemType)
{
	int count = 0;
	std::list<std::shared_ptr<class Item>>::iterator Start = MyItemList[static_cast<int>(_ItemType)].begin();
	std::list<std::shared_ptr<class Item>>::iterator End = MyItemList[static_cast<int>(_ItemType)].end();

	for (;Start != End; Start++)
	{
		count++;	
	}

	return count;
}

void ItemList::EquipItem(std::shared_ptr<class Item> _Item)
{
	if (_Item->EquipLevel > PlayerValue::GetValue()->GetLevel())
	{
		return;
	}

	std::string ItemName = GameEngineString::ToUpper(_Item->ItemName);
	int ItemType = _Item->ItemType;

	DeleteItem(_Item);

	UIController::GetUIController()->AddToEquipItemList(ItemName, ItemType);
}

void ItemList::DeleteItem(std::shared_ptr<Item> _Item)
{
	int ItemType = _Item->ItemType;

	UIController::GetUIController()->DeleteToItemList(_Item->ItemIndex, ItemType);

	std::list<std::shared_ptr<class Item>>::iterator Start = MyItemList[ItemType].begin();
	std::list<std::shared_ptr<class Item>>::iterator End = MyItemList[ItemType].end();
	std::list<std::shared_ptr<class Item>>::iterator EndCopy = MyItemList[ItemType].end();
	
	for (; Start != End;)
	{
		if (Start->get()->DynamicThis<Item>() == _Item)
		{
			Start->get()->Death();

			if (Start == EndCopy--)
			{
				Start = MyItemList[ItemType].erase(Start);
				return;
			}

			std::shared_ptr<Item> NewItem = GetLevel()->CreateActor<Item>();
			NewItem->SetEmptyItem();
			*Start = NewItem;
			return;
		}
		Start++;
	}
}