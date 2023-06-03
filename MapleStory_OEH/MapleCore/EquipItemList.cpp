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
	std::map<int, std::shared_ptr<class Item>> MyEqu = MyEquipItems;
}

void EquipItemList::Render(float _DeltaTime) 
{
}

void EquipItemList::LoadAllEquipItem()
{
	std::string ItemName;
	
	ItemName = UIController::GetUIController()->GetEquipItem(static_cast<int>(EquipType::Cap)).data();

	if(ItemName != "")
	{
		std::shared_ptr<Item> NewItem = GetLevel()->CreateActor<Item>();
		NewItem->SetItemInfo(ItemName, static_cast<int>(EquipType::Cap));
		NewItem->isEquip = true;

		MyEquipItems[static_cast<int>(EquipType::Cap)] = NewItem;
	}

	ItemName = UIController::GetUIController()->GetEquipItem(static_cast<int>(EquipType::Weapon)).data();

	if (ItemName != "")
	{
		std::shared_ptr<Item> NewItem = GetLevel()->CreateActor<Item>();
		NewItem->SetItemInfo(ItemName, static_cast<int>(EquipType::Weapon));
		NewItem->isEquip = true;

		MyEquipItems[static_cast<int>(EquipType::Weapon)] = NewItem;
	}

	ItemName = UIController::GetUIController()->GetEquipItem(static_cast<int>(EquipType::Shoes)).data();

	if (ItemName != "")
	{
		std::shared_ptr<Item> NewItem = GetLevel()->CreateActor<Item>();
		NewItem->SetItemInfo(ItemName, static_cast<int>(EquipType::Shoes));
		NewItem->isEquip = true;

		MyEquipItems[static_cast<int>(EquipType::Shoes)] = NewItem;
	}

	ItemName = UIController::GetUIController()->GetEquipItem(static_cast<int>(EquipType::Coat)).data();

	if (ItemName != "")
	{
		std::shared_ptr<Item> NewItem = GetLevel()->CreateActor<Item>();
		NewItem->SetItemInfo(ItemName, static_cast<int>(EquipType::Coat));
		NewItem->isEquip = true;

		MyEquipItems[static_cast<int>(EquipType::Coat)] = NewItem;
	}

	ItemName = UIController::GetUIController()->GetEquipItem(static_cast<int>(EquipType::Pants)).data();

	if (ItemName != "")
	{
		std::shared_ptr<Item> NewItem = GetLevel()->CreateActor<Item>();
		NewItem->SetItemInfo(ItemName, static_cast<int>(EquipType::Pants));
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
	std::string ItemName = UIController::GetUIController()->GetEquipItem(_ItemType).data();

	if (ItemName != "")
	{
		if (MyEquipItems[_ItemType] != nullptr)
		{
			MyEquipItems[_ItemType]->Death();
		}

		std::shared_ptr<Item> NewItem = GetLevel()->CreateActor<Item>();
		NewItem->SetItemInfo(ItemName, _ItemType);
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
		MyEquipItems[static_cast<int>(EquipType::Cap)]->GetTransform()->SetLocalPosition({ -200 , 193 });
	}

	if (MyEquipItems[static_cast<int>(EquipType::Coat)] != nullptr)
	{
		MyEquipItems[static_cast<int>(EquipType::Coat)]->GetTransform()->SetLocalPosition({ -233, 94 });
		MyEquipItems[static_cast<int>(EquipType::Coat)]->GetItemRender()->On();
		MyEquipItems[static_cast<int>(EquipType::Coat)]->GetItemCollision()->On();
	}

	if (MyEquipItems[static_cast<int>(EquipType::Pants)] != nullptr)
	{
		MyEquipItems[static_cast<int>(EquipType::Pants)]->GetTransform()->SetLocalPosition({ -233, 61 });
	}

	if (MyEquipItems[static_cast<int>(EquipType::Weapon)] != nullptr)
	{
		MyEquipItems[static_cast<int>(EquipType::Weapon)]->GetTransform()->SetLocalPosition({ -167 , 94 });
	}

	if (MyEquipItems[static_cast<int>(EquipType::Shoes)] != nullptr)
	{
		MyEquipItems[static_cast<int>(EquipType::Shoes)]->GetTransform()->SetLocalPosition({ -200 , 28 });
	}
}