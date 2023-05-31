#include "PrecompileHeader.h"
#include "InventoryWindow.h"
#include "ItemList.h"
#include "Item.h"

#include <GameEngineCore/GameEngineUIRenderer.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEnginePlatform/GameEngineInput.h>

InventoryWindow::InventoryWindow()
{
}

InventoryWindow::~InventoryWindow()
{
}

void InventoryWindow::Start()
{
	GetTransform()->SetLocalPosition({ 200, 50 , 0 });

	InventoryRender = CreateComponent<GameEngineUIRenderer>();
	InventoryRender->SetScaleToTexture("EquipInventory.png");

	Equip = CreateComponent<GameEngineCollision>();
	Equip->GetTransform()->SetLocalPosition({ -65, 110 });
	Equip->GetTransform()->SetLocalScale({ 31, 18 });

	Use = CreateComponent<GameEngineCollision>();
	Use->GetTransform()->SetLocalPosition({ -30, 110 });
	Use->GetTransform()->SetLocalScale({ 31, 18 });

	Etc = CreateComponent<GameEngineCollision>();
	Etc->GetTransform()->SetLocalPosition({ 3, 110 });
	Etc->GetTransform()->SetLocalScale({ 31, 18 });

	Setup = CreateComponent<GameEngineCollision>();
	Setup->GetTransform()->SetLocalPosition({ 36, 110 });
	Setup->GetTransform()->SetLocalScale({ 31, 18 });

	Cash = CreateComponent<GameEngineCollision>();
	Cash->GetTransform()->SetLocalPosition({ 69, 110 });
	Cash->GetTransform()->SetLocalScale({ 31, 18 });

	Inventory = GetLevel()->CreateActor<ItemList>();
	Inventory->CreateItem("WhiteTshirt", static_cast<int>(ItemType::Equip));

	Inventory->GetTransform()->SetParent(GetTransform());
	
	Inventory->SortItemListToType(static_cast<int>(ItemType::Equip));
	SetInventoryType("EQUIP");
}

void InventoryWindow::Update(float _DeltaTime)
{
	ChangeInventory();
}

void InventoryWindow::Render(float _DeltaTime)
{
}

void InventoryWindow::ChangeInventory()
{
	if (GameEngineInput::IsDown("LClick") == true)
	{
		std::shared_ptr<GameEngineCollision> Collision = Equip->Collision(static_cast<int>(CollisionOrder::Mouse), ColType::AABBBOX2D, ColType::AABBBOX2D);

		if (Collision != nullptr)
		{
			if (InventoryType == "EQUIP")
			{
				return;
			}

			InventoryRender->SetScaleToTexture("EquipInventory.png");
			InventoryType = "EQUIP";
		}

		Collision = Use->Collision(static_cast<int>(CollisionOrder::Mouse), ColType::AABBBOX2D, ColType::AABBBOX2D);

		if (Collision != nullptr)
		{
			if (InventoryType == "USE")
			{
				return;
			}

			InventoryRender->SetScaleToTexture("UseInventory.png");
			InventoryType = "USE";
		}

		Collision = Etc->Collision(static_cast<int>(CollisionOrder::Mouse), ColType::AABBBOX2D, ColType::AABBBOX2D);

		if (Collision != nullptr)
		{
			if (InventoryType == "ETC")
			{
				return;
			}

			InventoryRender->SetScaleToTexture("EtcInventory.png");
			InventoryType = "ETC";
		}

		Collision = Setup->Collision(static_cast<int>(CollisionOrder::Mouse), ColType::AABBBOX2D, ColType::AABBBOX2D);

		if (Collision != nullptr)
		{
			if (InventoryType == "SETUP")
			{
				return;
			}

			InventoryRender->SetScaleToTexture("SetupInventory.png");
			InventoryType = "SETUP";
		}

		Collision = Cash->Collision(static_cast<int>(CollisionOrder::Mouse), ColType::AABBBOX2D, ColType::AABBBOX2D);

		if (Collision != nullptr)
		{
			if (InventoryType == "CASH")
			{
				return;
			}

			InventoryRender->SetScaleToTexture("CashInventory.png");
			InventoryType = "CASH";
		}
	}
}