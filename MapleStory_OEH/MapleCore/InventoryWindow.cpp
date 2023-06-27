#include "PrecompileHeader.h"
#include "InventoryWindow.h"
#include "ItemList.h"
#include "Item.h"

#include <GameEngineCore/GameEngineLevel.h>
#include <GameEnginePlatform/GameEngineInput.h>

InventoryWindow::InventoryWindow()
{
}

InventoryWindow::~InventoryWindow()
{
}

void InventoryWindow::Start()
{
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
	Inventory->GetTransform()->SetParent(GetTransform());
	
	GetTransform()->SetLocalPosition({ 200, 50 , 0 });
	
	Inventory->LoadAllItem();

	Inventory->SortItemListToType(static_cast<int>(ItemType::Equip));

	SetInventoryType(static_cast<int>(ItemType::Equip));
	Inventory->ChangeRenderItem(static_cast<int>(ItemType::Equip), static_cast<int>(ItemType::Equip));
}

void InventoryWindow::Update(float _DeltaTime)
{
	ColPosUpdate();
	ChangeInventory();
	InventoryUpdate();
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
			if (InventoryType == static_cast<int>(ItemType::Equip))
			{
				return;
			}

			Inventory->ChangeRenderItem(InventoryType, static_cast<int>(ItemType::Equip));
			InventoryRender->SetScaleToTexture("EquipInventory.png");
			InventoryType = static_cast<int>(ItemType::Equip);
		}

		Collision = Use->Collision(static_cast<int>(CollisionOrder::Mouse), ColType::AABBBOX2D, ColType::AABBBOX2D);

		if (Collision != nullptr)
		{
			if (InventoryType == static_cast<int>(ItemType::Use))
			{
				return;
			}

			Inventory->ChangeRenderItem(InventoryType, static_cast<int>(ItemType::Use));
			InventoryRender->SetScaleToTexture("UseInventory.png");
			InventoryType = static_cast<int>(ItemType::Use);
		}

		Collision = Etc->Collision(static_cast<int>(CollisionOrder::Mouse), ColType::AABBBOX2D, ColType::AABBBOX2D);

		if (Collision != nullptr)
		{
			if (InventoryType == static_cast<int>(ItemType::Etc))
			{
				return;
			}

			Inventory->ChangeRenderItem(InventoryType, static_cast<int>(ItemType::Etc));
			InventoryRender->SetScaleToTexture("EtcInventory.png");
			InventoryType = static_cast<int>(ItemType::Etc);
		}

		Collision = Setup->Collision(static_cast<int>(CollisionOrder::Mouse), ColType::AABBBOX2D, ColType::AABBBOX2D);

		if (Collision != nullptr)
		{
			if (InventoryType == static_cast<int>(ItemType::Setup))
			{
				return;
			}

			Inventory->ChangeRenderItem(InventoryType, static_cast<int>(ItemType::Setup));
			InventoryRender->SetScaleToTexture("SetupInventory.png");
			InventoryType = static_cast<int>(ItemType::Setup);
		}

		Collision = Cash->Collision(static_cast<int>(CollisionOrder::Mouse), ColType::AABBBOX2D, ColType::AABBBOX2D);

		if (Collision != nullptr)
		{
			if (InventoryType == static_cast<int>(ItemType::Cash))
			{
				return;
			}

			Inventory->ChangeRenderItem(InventoryType, static_cast<int>(ItemType::Cash));
			InventoryRender->SetScaleToTexture("CashInventory.png");
			InventoryType = static_cast<int>(ItemType::Cash);
		}
	}
}

void InventoryWindow::InventoryUpdate()
{
	Inventory->InventoryItemOn(InventoryType);
	Inventory->SortItemListToType(InventoryType);
}

void InventoryWindow::ClearInventory()
{
	Inventory->ClearItem();
}

void InventoryWindow::ColPosUpdate()
{
	float4 CamPos = GetLevel()->GetMainCamera()->GetTransform()->GetLocalPosition();

	Equip->GetTransform()->SetLocalPosition(CamPos + float4{ -65, 110 });
	Use->GetTransform()->SetLocalPosition(CamPos + float4{ -30, 110 });
	Etc->GetTransform()->SetLocalPosition(CamPos + float4{ 3, 110 });
	Setup->GetTransform()->SetLocalPosition(CamPos + float4{ 36 , 110 });
	Cash->GetTransform()->SetLocalPosition(CamPos + float4{ 69, 110 });
}