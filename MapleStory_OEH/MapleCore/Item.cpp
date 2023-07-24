#include "PrecompileHeader.h"
#include "Item.h"
#include "Mouse.h"
#include "ItemList.h"
#include "InventoryWindow.h"
#include "UIController.h"
#include "ContentFontRenderer.h"
#include "DropItem.h"
#include "ContentUIRenderer.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineLevel.h>


Item::Item()
{
}

Item::~Item()
{
}

void Item::Start()
{
	ItemRender = CreateComponent<GameEngineUIRenderer>();

	NumRender.reserve(4);

	for (int i = 0; i < 4; i++)
	{
		NumRender.push_back(CreateComponent<GameEngineUIRenderer>());
		NumRender[i]->Off();
	}
}

void Item::Update(float _DeltaTime)
{
	Clicked();

	float4 CamPos = GetLevel()->GetMainCamera()->GetTransform()->GetLocalPosition();
	ItemCollision->GetTransform()->SetLocalPosition(CamPos);

	EquipThis();

	InfoBoxUpdate();

	UseItem();
}

void Item::Render(float _DeltaTime)
{
}

void Item::SetItemInfo(std::shared_ptr<ItemInfo> _ItemInfo, int _ItemType)
{
	MyInfo = _ItemInfo;

	ItemType = static_cast<int>(_ItemType);

	ItemRender->SetScaleToTexture(MyInfo->ItemName + "Icon.png");
	ItemRender->Off();

	ItemCollision = CreateComponent<GameEngineCollision>();
	ItemCollision->GetTransform()->SetLocalScale({ 30, 30 });

	if (UIController::GetUIController()->GetCurInventoryWindow() != nullptr)
	{
		if (UIController::GetUIController()->GetCurInventoryWindow()->GetInventoryType() != ItemType)
		{
			ItemCollision->Off();
		}
	}

	SetMyInfoBox();
}

void Item::Clicked()
{
	if (isClicked == true && GameEngineInput::IsDown("LClick") == true)
	{
		if (ItemCollision->Collision(static_cast<int>(CollisionOrder::Inventory), ColType::AABBBOX2D, ColType::AABBBOX2D) == nullptr && isEquip == false)
		{
			std::shared_ptr<DropItem> NewItem = GetLevel()->CreateActor<DropItem>();
			NewItem->SetQuadraticFunction(1.0f, Player::GetCurPlayer()->GetTransform()->GetWorldPosition() + float4{ 0, 5 });
			NewItem->SetDropItemInfo(MyInfo->ItemName, ItemType);

			UIController::GetUIController()->GetCurItemList()->DeleteItem(DynamicThis<Item>());

			isClicked = false;

			ItemRender->GetTransform()->SetParent(GetTransform());
			ItemCollision->GetTransform()->SetParent(GetTransform());
			Death();
			return;
		}

		ItemRender->GetTransform()->SetParent(GetTransform());
		ItemCollision->GetTransform()->SetParent(GetTransform());

		ItemRender->GetTransform()->SetLocalPosition({ 0, 0 });
		ItemCollision->GetTransform()->SetLocalPosition({ 0, 0 });

		NumRenderOn();

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

			NumRenderOff();

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
			UIController::GetUIController()->GetCurItemList()->EquipItem(DynamicThis<Item>());
		}	
	}
}

void Item::NumRenderUpdate()
{
	int CopyNum = MyInfo->Num;
	Digit = 0;

	for (int i = 0; CopyNum > 0; i++)
	{
		CopyNum /= 10;
		Digit++;
	}

	CopyNum = MyInfo->Num;
	
	for (int i = 0; i < Digit; i++)
	{
		int Num = CopyNum % 10;
		CopyNum /= 10;

		NumRender[Digit - i - 1]->SetScaleToTexture("ItemNumber" + std::to_string(Num) + ".png");
	}

	for (int i = 0; i < 4; i++)
	{
		NumRender[i]->GetTransform()->SetLocalPosition(ItemRender->GetTransform()->GetLocalPosition() + float4{ -12, -8 } + float4{ i * 7.0f, 0 });
	}
}

void Item::NumRenderOn()
{
	for (int i = 0; i < Digit; i++)
	{
		if (NumRender[i] != nullptr)
		{
			NumRender[i]->On();
		}
	}
}

void Item::NumRenderOff()
{
	for (int i = 0; i < Digit; i++)
	{
		if (NumRender[i] != nullptr)
		{
			NumRender[i]->Off();
		}
	}
}

void Item::UseItem()
{
	if (ItemType != static_cast<int>(ItemType::Use))
	{
		return;
	}
	
	if (Mouse::GetMouse()->IsDoubleClick() != true)
	{
		return;
	}

	std::shared_ptr<GameEngineCollision> Col = ItemCollision->Collision(static_cast<int>(CollisionOrder::Mouse), ColType::AABBBOX2D, ColType::AABBBOX2D);

	if (Col == nullptr)
	{
		return;
	}

	if (MyInfo->ItemName == "APPLEOFROZAR")
	{
		PlayerValue::GetValue()->AddHp(50);
		UIController::GetUIController()->DeleteToItemList("APPLEOFROZAR", static_cast<int>(ItemType::Use));
		UIController::GetUIController()->GetCurItemList()->DeleteItem(DynamicThis<Item>());
	}
}