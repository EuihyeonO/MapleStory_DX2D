#include "PrecompileHeader.h"
#include "Item.h"
#include "Mouse.h"
#include "ItemList.h"

#include <GameEnginePlatform/GameEngineInput.h>


Item::Item()
{
}

Item::~Item()
{
}

void Item::Start()
{
	ItemRender = CreateComponent<GameEngineUIRenderer>();
}

void Item::Update(float _DeltaTime) 
{
	Clicked();
	EquipThis();
}

void Item::Render(float _DeltaTime) 
{
}

void Item::SetItemInfo(const std::string_view& _ItemName, int _ItemType, int _EquipLevel, int _EquipType)
{
	ItemName = _ItemName;
	ItemType = static_cast<int>(_ItemType);

	EquipLevel = _EquipLevel;

	if(_ItemType == static_cast<int>(ItemType::Equip))
	{
		EquipType = _EquipType;
	}

	ItemRender->SetScaleToTexture(ItemName + "Icon.png");
	ItemRender->Off();

	ItemCollision = CreateComponent<GameEngineCollision>();
	ItemCollision->GetTransform()->SetLocalScale({30, 30});
}

void Item::SetEmptyItem()
{
	isEmptyItem = true;

	ItemRender->Off();
	ItemCollision = CreateComponent<GameEngineCollision>();
	ItemCollision->Off();
}

void Item::Clicked()
{
	if (isClicked == true && GameEngineInput::IsDown("LClick") == true)
	{
		ItemRender->GetTransform()->SetParent(GetTransform());
		ItemCollision->GetTransform()->SetParent(GetTransform());

		ItemRender->GetTransform()->SetLocalPosition({ 0, 0 });
		ItemCollision->GetTransform()->SetLocalPosition({ 0, 0 });

		isClicked = false;
	}

	else if (ItemCollision->Collision(static_cast<int>(CollisionOrder::Mouse), ColType::AABBBOX2D, ColType::AABBBOX2D) != nullptr)
	{
		if (isClicked == false && GameEngineInput::IsDown("LClick") == true)
		{
			ItemRender->GetTransform()->SetParent(Mouse::GetMouse()->GetTransform());
			ItemCollision->GetTransform()->SetParent(Mouse::GetMouse()->GetTransform());

			ItemRender->GetTransform()->SetLocalPosition({ -10, 15 });
			ItemCollision->GetTransform()->SetLocalPosition({ -10, 15 });

			isClicked = true;
		}
	}
}

void Item::EquipThis()
{
	if (ItemType != static_cast<int>(ItemType::Equip))
	{
		return;
	}

	if (isEquip == true)
	{
		return;
	}

	if (Mouse::GetMouse()->IsDoubleClick() == true)
	{
		std::shared_ptr<GameEngineCollision> MyCollision = ItemCollision->Collision(static_cast<int>(CollisionOrder::Mouse), ColType::AABBBOX2D, ColType::AABBBOX2D);
		if (MyCollision != nullptr)
		{
			ParentItemList->EquipItem(DynamicThis<Item>());
		}	
	}
}