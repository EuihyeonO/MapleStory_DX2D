#include "PrecompileHeader.h"
#include "Item.h"
#include "Mouse.h"
#include "ItemList.h"
#include "UIController.h"
#include "ContentFontRenderer.h"

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
	EquipThis();

	float4 CamPos = GetLevel()->GetMainCamera()->GetTransform()->GetLocalPosition();
	ItemCollision->GetTransform()->SetLocalPosition(CamPos);

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
	ItemCollision->GetTransform()->SetLocalScale({30, 30});

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

void Item::NumRenderUpdate()
{
	int CopyNum = MyInfo->Num;
	int Digit = 0;

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
	for (int i = 0; i < 4; i++)
	{
		if (NumRender[i] != nullptr)
		{
			NumRender[i]->On();
		}
	}
}

void Item::NumRenderOff()
{
	for (int i = 0; i < 4; i++)
	{
		if (NumRender[i] != nullptr)
		{
			NumRender[i]->Off();
		}
	}
}