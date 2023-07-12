#include "PrecompileHeader.h"
#include "EquipItemList.h"
#include "Item.h"
#include "UIController.h"

#include <GameEngineBase/GameEngineString.h>
#include <GameEngineCore/GameEngineLevel.h>

EquipItemList::EquipItemList()
{
}

EquipItemList::~EquipItemList()
{
}

void EquipItemList::Start()
{
	MyEquipItems[static_cast<int>(EquipType::Cap)] = nullptr;
	MyEquipItems[static_cast<int>(EquipType::Weapon)] = nullptr;
	MyEquipItems[static_cast<int>(EquipType::Coat)] = nullptr;
	MyEquipItems[static_cast<int>(EquipType::Pants)] = nullptr;
	MyEquipItems[static_cast<int>(EquipType::Shoes)] = nullptr;

	LoadAllEquipItem();
	SortItem();

	//std::shared_ptr<GameEngineUIRenderer> Test = CreateComponent<GameEngineUIRenderer>();
	//Test->SetTexture("MouseTest.png");
	//Test->GetTransform()->SetLocalScale({ 32, 32 });
	
}

void EquipItemList::Update(float _DeltaTime) 
{
	if (MyEquipItems[static_cast<int>(EquipType::Coat)] != nullptr)
	{
		float4 Pos = MyEquipItems[static_cast<int>(EquipType::Coat)]->GetTransform()->GetLocalPosition();
		float4 Pos1 = MyEquipItems[static_cast<int>(EquipType::Coat)]->GetTransform()->GetLocalPosition();
	}

	if (MyEquipItems[static_cast<int>(EquipType::Pants)] != nullptr)
	{
		float4 Pos = MyEquipItems[static_cast<int>(EquipType::Pants)]->GetTransform()->GetLocalPosition();
		float4 Pos2 = MyEquipItems[static_cast<int>(EquipType::Pants)]->GetTransform()->GetLocalPosition();
	}
}

void EquipItemList::Render(float _DeltaTime) 
{
}

void EquipItemList::LoadAllEquipItem()
{
	std::shared_ptr<ItemInfo> LoadedItem = UIController::GetUIController()->GetEquipItem(static_cast<int>(EquipType::Cap));

	if(LoadedItem != nullptr)
	{
		std::shared_ptr<Item> NewItem = GetLevel()->CreateActor<Item>();
		NewItem->SetItemInfo(LoadedItem, static_cast<int>(ItemType::Equip));
		NewItem->ItemRender->On();
		NewItem->isEquip = true;

		MyEquipItems[static_cast<int>(EquipType::Cap)] = NewItem;
	}

	LoadedItem = UIController::GetUIController()->GetEquipItem(static_cast<int>(EquipType::Weapon));

	if (LoadedItem != nullptr)
	{
		std::shared_ptr<Item> NewItem = GetLevel()->CreateActor<Item>();
		NewItem->SetItemInfo(LoadedItem, static_cast<int>(ItemType::Equip));
		NewItem->ItemRender->On();
		NewItem->isEquip = true;

		MyEquipItems[static_cast<int>(EquipType::Weapon)] = NewItem;
	}

	LoadedItem = UIController::GetUIController()->GetEquipItem(static_cast<int>(EquipType::Shoes));

	if (LoadedItem != nullptr)
	{
		std::shared_ptr<Item> NewItem = GetLevel()->CreateActor<Item>();
		NewItem->SetItemInfo(LoadedItem, static_cast<int>(ItemType::Equip));
		NewItem->ItemRender->On();
		NewItem->isEquip = true;

		MyEquipItems[static_cast<int>(EquipType::Shoes)] = NewItem;
	}

	LoadedItem = UIController::GetUIController()->GetEquipItem(static_cast<int>(EquipType::Coat));

	if (LoadedItem != nullptr)
	{
		std::shared_ptr<Item> NewItem = GetLevel()->CreateActor<Item>();
		NewItem->SetItemInfo(LoadedItem, static_cast<int>(ItemType::Equip));
		NewItem->ItemRender->On();
		NewItem->isEquip = true;

		MyEquipItems[static_cast<int>(EquipType::Coat)] = NewItem;
	}

	LoadedItem = UIController::GetUIController()->GetEquipItem(static_cast<int>(EquipType::Pants));

	if (LoadedItem != nullptr)
	{
		std::shared_ptr<Item> NewItem = GetLevel()->CreateActor<Item>();
		NewItem->SetItemInfo(LoadedItem, static_cast<int>(ItemType::Equip));
		NewItem->ItemRender->On();
		NewItem->isEquip = true;

		MyEquipItems[static_cast<int>(EquipType::Pants)] = NewItem;
	}
}

void EquipItemList::ClearEquipItem()
{
	std::map<int, std::shared_ptr<class Item>>::iterator Start = MyEquipItems.begin();
	std::map<int, std::shared_ptr<class Item>>::iterator End = MyEquipItems.end();

	for (; Start != End;)
	{
		if(Start->second != nullptr)
		{
			Start->second->Death();
		}

		Start = MyEquipItems.erase(Start);
	}
}

void EquipItemList::LoadEquipItem(int _ItemType)
{
	std::shared_ptr<ItemInfo> LoadedItem = UIController::GetUIController()->GetEquipItem(_ItemType);

	if (LoadedItem != nullptr)
	{
		if (MyEquipItems[_ItemType] != nullptr)
		{
			MyEquipItems[_ItemType]->Death();
			MyEquipItems[_ItemType] = nullptr;
		}

		std::shared_ptr<Item> NewItem = GetLevel()->CreateActor<Item>();
		NewItem->SetItemInfo(LoadedItem, _ItemType);
		NewItem->GetItemRender()->On();
		NewItem->GetItemCollision()->On();
		NewItem->isEquip = true;

		MyEquipItems[_ItemType] = NewItem;
	}

	SortItem();
}

void EquipItemList::SortItem()
{

	if (MyEquipItems[static_cast<int>(EquipType::Cap)] != nullptr)
	{
		MyEquipItems[static_cast<int>(EquipType::Cap)]->GetTransform()->SetLocalPosition({ -200 , 193, -1 });
	}

	if (MyEquipItems[static_cast<int>(EquipType::Coat)] != nullptr)
	{
		MyEquipItems[static_cast<int>(EquipType::Coat)]->GetTransform()->SetLocalPosition({ -233, 94, -1 });
		MyEquipItems[static_cast<int>(EquipType::Coat)]->GetItemRender()->On();
		MyEquipItems[static_cast<int>(EquipType::Coat)]->GetItemCollision()->On();
	}

	if (MyEquipItems[static_cast<int>(EquipType::Pants)] != nullptr)
	{
		MyEquipItems[static_cast<int>(EquipType::Pants)]->GetTransform()->SetLocalPosition({ -233, 61, -1 });
	}

	if (MyEquipItems[static_cast<int>(EquipType::Weapon)] != nullptr)
	{
		MyEquipItems[static_cast<int>(EquipType::Weapon)]->GetTransform()->SetLocalPosition({ -167 , 94, -1 });
	}

	if (MyEquipItems[static_cast<int>(EquipType::Shoes)] != nullptr)
	{
		MyEquipItems[static_cast<int>(EquipType::Shoes)]->GetTransform()->SetLocalPosition({ -200 , 28, -1 });
	}
}