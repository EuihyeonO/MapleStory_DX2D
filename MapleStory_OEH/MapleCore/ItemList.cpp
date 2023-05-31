#include "PrecompileHeader.h"
#include "ItemList.h"
#include "Item.h"
#include "UIController.h"

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
	if(GameEngineInput::IsKey("TestKey") == false)
	{
		GameEngineInput::CreateKey("TestKey", 'B');
	}

	if(GameEngineInput::IsDown("TestKey") == true)
	{
		UIController::GetUIController()->AddToItemList("WhiteTshirt", static_cast<int>(ItemType::Equip));
		//ItemList가 켜있으면 이것도 해줘야함.
		//자동화 할 방법 생각해봅시다
		CreateItem("WhiteTshirt", static_cast<int>(ItemType::Equip));
	}
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

void ItemList::LoadItem()
{
	std::map<int, std::vector<std::string>> CopyMap = UIController::GetUIController()->GetItemList();

	size_t EquipSize = CopyMap[static_cast<int>(ItemType::Equip)].size();
	
	for (size_t i = 0; i < EquipSize; i++)
	{
		std::string _ItemName = CopyMap[static_cast<int>(ItemType::Equip)][i];
		CreateItem(_ItemName, static_cast<int>(ItemType::Equip));
	}

	size_t UseSize = CopyMap[static_cast<int>(ItemType::Use)].size();

	for (size_t i = 0; i < UseSize; i++)
	{
		std::string _ItemName = CopyMap[static_cast<int>(ItemType::Use)][i];
		CreateItem(_ItemName, static_cast<int>(ItemType::Use));
	}


	size_t EtcSize = CopyMap[static_cast<int>(ItemType::Use)].size();

	for (size_t i = 0; i < EtcSize; i++)
	{
		std::string _ItemName = CopyMap[static_cast<int>(ItemType::Use)][i];
		CreateItem(_ItemName, static_cast<int>(ItemType::Use));
	}

	size_t SetupSize = CopyMap[static_cast<int>(ItemType::Setup)].size();

	for (size_t i = 0; i < SetupSize; i++)
	{
		std::string _ItemName = CopyMap[static_cast<int>(ItemType::Setup)][i];
		CreateItem(_ItemName, static_cast<int>(ItemType::Setup));
	}

	size_t CashSize = CopyMap[static_cast<int>(ItemType::Cash)].size();

	for (size_t i = 0; i < CashSize; i++)
	{
		std::string _ItemName = CopyMap[static_cast<int>(ItemType::Cash)][i];
		CreateItem(_ItemName, static_cast<int>(ItemType::Cash));
	}
}

void ItemList::SortItemListToType(int _ItemType)
{
	std::list<std::shared_ptr<class Item>>::iterator Start = MyItemList[_ItemType].begin();
	std::list<std::shared_ptr<class Item>>::iterator End = MyItemList[_ItemType].end();

	int count = 0;

	for (; Start != End; Start++)
	{
		int Yindex = count / 4;
		int Xindex = count % 4;

		Start->get()->GetTransform()->SetLocalPosition(StartPos + float4{Xinterval * Xindex, Yinterval * Yindex });
		count++;
	}
}

void ItemList::ClearItem()
{
	std::list<std::shared_ptr<class Item>>::iterator Start = MyItemList[static_cast<int>(ItemType::Equip)].begin();
	std::list<std::shared_ptr<class Item>>::iterator End = MyItemList[static_cast<int>(ItemType::Equip)].end();

	for (;Start != End;)
	{
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
		Start->get()->GetItemRender()->On();
	}
}

void ItemList::InventoryItemOff(int _CurItemType)
{
	std::list<std::shared_ptr<class Item>>::iterator Start = MyItemList[_CurItemType].begin();
	std::list<std::shared_ptr<class Item>>::iterator End = MyItemList[_CurItemType].end();

	for (; Start != End; Start++)
	{
		Start->get()->GetItemRender()->Off();
	}
}