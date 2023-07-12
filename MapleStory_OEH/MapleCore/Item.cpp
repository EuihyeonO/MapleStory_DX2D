#include "PrecompileHeader.h"
#include "Item.h"
#include "Mouse.h"
#include "ItemList.h"
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

	MyInfoBox = std::make_shared<ItemInfoBox>();

	MyInfoBox->BoxRender = CreateComponent<ContentUIRenderer>();
	MyInfoBox->BoxRender->GetTransform()->SetLocalScale({ 200, 300 });
	MyInfoBox->BoxRender->ColorOptionValue.PlusColor = { 1.0f, 1.0f, 1.0f, 0.0f };
	MyInfoBox->BoxRender->ColorOptionValue.MulColor = { 0.1f, 0.25f, 0.5f, 0.8f };
	MyInfoBox->BoxRender->GetTransform()->SetLocalPosition({ 90, -140, 0 });
	MyInfoBox->BoxRender->Off();

	float4 BoxPos = MyInfoBox->BoxRender->GetTransform()->GetLocalPosition();

	MyInfoBox->ItemBackGround = CreateComponent<ContentUIRenderer>();
	MyInfoBox->ItemBackGround->GetTransform()->SetLocalScale({ 64, 64 });
	MyInfoBox->ItemBackGround->GetTransform()->SetLocalPosition(BoxPos + float4{ -55, 80 });
	MyInfoBox->ItemBackGround->ColorOptionValue.PlusColor = { 1.0f, 1.0f, 1.0f, 0.0f };
	MyInfoBox->ItemBackGround->ColorOptionValue.MulColor = { 0.95f, 0.95f, 0.95f, 0.8f };

	MyInfoBox->ItemRender = CreateComponent<ContentUIRenderer>();
	MyInfoBox->ItemRender->SetScaleToTexture(MyInfo->ItemName + "Icon.png");
	MyInfoBox->ItemRender->GetTransform()->SetLocalScale(MyInfoBox->ItemRender->GetTransform()->GetLocalScale() * 2.0f);
	MyInfoBox->ItemRender->GetTransform()->SetLocalPosition(MyInfoBox->ItemBackGround->GetTransform()->GetLocalPosition());
	MyInfoBox->ItemRender->Off();

	std::string_view KrName = GetItemNameToKr(MyInfo->ItemName);

	MyInfoBox->ItemName = CreateComponent<ContentFontRenderer>();
	MyInfoBox->ItemName->SetFont("±¼¸²");
	MyInfoBox->ItemName->SetColor({1.0f, 1.0f, 1.0f, 1.0f});
	MyInfoBox->ItemName->SetScale(15.0f);
	MyInfoBox->ItemName->GetTransform()->SetLocalPosition(BoxPos + float4{0, 140});
	MyInfoBox->ItemName->SetFontFlag(FW1_TEXT_FLAG::FW1_CENTER);
	MyInfoBox->ItemName->SetText(KrName);
	MyInfoBox->ItemName->Off();

	MyInfoBox->ItemNameLayer = CreateComponent<ContentFontRenderer>();
	MyInfoBox->ItemNameLayer->SetFont("±¼¸²");
	MyInfoBox->ItemNameLayer->SetColor({ 1.0f, 1.0f, 1.0f, 1.0f });
	MyInfoBox->ItemNameLayer->SetScale(15.0f);
	MyInfoBox->ItemNameLayer->GetTransform()->SetLocalPosition(BoxPos + float4{ 1.0f, 140 });
	MyInfoBox->ItemNameLayer->SetFontFlag(FW1_TEXT_FLAG::FW1_CENTER);
	MyInfoBox->ItemNameLayer->SetText(KrName);
	MyInfoBox->ItemNameLayer->Off();

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

void Item::InfoBoxOn()
{
	if (MyInfoBox == nullptr)
	{
		return;
	}

	if (MyInfoBox->BoxRender != nullptr)
	{
		MyInfoBox->BoxRender->On();
	}

	if (MyInfoBox->ItemBackGround != nullptr)
	{
		MyInfoBox->ItemBackGround->On();
	}

	if (MyInfoBox->ItemRender != nullptr)
	{
		MyInfoBox->ItemRender->On();
	}

	if (MyInfoBox->ItemName != nullptr)
	{
		MyInfoBox->ItemName->On();
	}

	if (MyInfoBox->ItemNameLayer != nullptr)
	{
		MyInfoBox->ItemNameLayer->On();
	}
}

void Item::InfoBoxOff()
{
	if (MyInfoBox == nullptr)
	{
		return;
	}

	if (MyInfoBox->BoxRender != nullptr)
	{
		MyInfoBox->BoxRender->Off();
	}

	if (MyInfoBox->ItemBackGround != nullptr)
	{
		MyInfoBox->ItemBackGround->Off();
	}

	if (MyInfoBox->ItemRender != nullptr)
	{
		MyInfoBox->ItemRender->Off();
	}

	if (MyInfoBox->ItemName != nullptr)
	{
		MyInfoBox->ItemName->Off();
	}

	if (MyInfoBox->ItemNameLayer != nullptr)
	{
		MyInfoBox->ItemNameLayer->Off();
	}
}

void Item::InfoBoxUpdate()
{
	if (ItemCollision->Collision(static_cast<int>(CollisionOrder::Mouse), ColType::AABBBOX2D, ColType::AABBBOX2D) != nullptr)
	{
		if (isClicked == true)
		{
			InfoBoxOff();
		}
		else
		{
			InfoBoxOn();
		}
	}
	else
	{
		InfoBoxOff();
	}
}

const std::string_view Item::GetItemNameToKr(const std::string_view& _Name)
{
	std::string Name = GameEngineString::ToUpper(_Name.data());

	if (Name == "GANIER")
	{
		return "°¡´Ï¾î";
	}
	else if (Name == "WHITETSHIRT")
	{
		return "ÇÏ¾á ¹ÝÆÈ ¸éÆ¼";
	}
	else if (Name == "BLUEPANTS")
	{
		return "ÆÄ¶õ Ã» ¹Ý¹ÙÁö";
	}
	else
	{
		return "";
	}
}