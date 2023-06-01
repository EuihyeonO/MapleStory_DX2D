#include "PrecompileHeader.h"
#include "EquipItemList.h"
#include "Item.h"
#include "UIController.h"

#include <GameEngineBase/GameEngineString.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineUIRenderer.h>

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

	LoadEquipItem();

	std::shared_ptr<GameEngineUIRenderer> Test = CreateComponent<GameEngineUIRenderer>();
	Test->SetTexture("MouseTest.png");
	Test->GetTransform()->SetLocalScale({ 32, 32 });
	Test->GetTransform()->SetLocalPosition({ 0, 0 });

}

void EquipItemList::Update(float _DeltaTime) 
{
}

void EquipItemList::Render(float _DeltaTime) 
{
}

void EquipItemList::LoadEquipItem()
{
	std::string ItemName;
	
	ItemName = UIController::GetUIController()->GetEquipItem(static_cast<int>(EquipType::Cap)).data();

	if(ItemName != "")
	{
		std::shared_ptr<Item> NewItem = GetLevel()->CreateActor<Item>();
		NewItem->SetItemInfo(ItemName, static_cast<int>(EquipType::Cap));

		MyEquipItems[static_cast<int>(EquipType::Cap)] = NewItem;
	}

	ItemName = UIController::GetUIController()->GetEquipItem(static_cast<int>(EquipType::Weapon)).data();

	if (ItemName != "")
	{
		std::shared_ptr<Item> NewItem = GetLevel()->CreateActor<Item>();
		NewItem->SetItemInfo(ItemName, static_cast<int>(EquipType::Weapon));

		MyEquipItems[static_cast<int>(EquipType::Weapon)] = NewItem;
	}

	ItemName = UIController::GetUIController()->GetEquipItem(static_cast<int>(EquipType::Shoes)).data();

	if (ItemName != "")
	{
		std::shared_ptr<Item> NewItem = GetLevel()->CreateActor<Item>();
		NewItem->SetItemInfo(ItemName, static_cast<int>(EquipType::Shoes));

		MyEquipItems[static_cast<int>(EquipType::Shoes)] = NewItem;
	}

	ItemName = UIController::GetUIController()->GetEquipItem(static_cast<int>(EquipType::Coat)).data();

	if (ItemName != "")
	{
		std::shared_ptr<Item> NewItem = GetLevel()->CreateActor<Item>();
		NewItem->SetItemInfo(ItemName, static_cast<int>(EquipType::Coat));

		MyEquipItems[static_cast<int>(EquipType::Coat)] = NewItem;
	}

	ItemName = UIController::GetUIController()->GetEquipItem(static_cast<int>(EquipType::Pants)).data();

	if (ItemName != "")
	{
		std::shared_ptr<Item> NewItem = GetLevel()->CreateActor<Item>();
		NewItem->SetItemInfo(ItemName, static_cast<int>(EquipType::Pants));

		MyEquipItems[static_cast<int>(EquipType::Pants)] = NewItem;
	}
}