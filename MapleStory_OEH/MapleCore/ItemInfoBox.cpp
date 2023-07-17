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

void Item::SetMyInfoBox()
{
	MyInfoBox = std::make_shared<ItemInfoBox>();

	if (ItemType == static_cast<int>(ItemType::Equip))
	{
		MyInfoBox->BoxRender = CreateComponent<ContentUIRenderer>();
		MyInfoBox->BoxRender->GetTransform()->SetLocalScale({ 200, 300 });
		MyInfoBox->BoxRender->ColorOptionValue.PlusColor = { 1.0f, 1.0f, 1.0f, 0.0f };
		MyInfoBox->BoxRender->ColorOptionValue.MulColor = { 0.1f, 0.25f, 0.5f, 0.8f };
		MyInfoBox->BoxRender->GetTransform()->SetLocalPosition({ 90, -140, -50.0f });
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

		MyInfoBox->StatInfo = CreateComponent<ContentUIRenderer>();
		MyInfoBox->StatInfo->SetScaleToTexture("InfoBoxStat.PNG");
		MyInfoBox->StatInfo->GetTransform()->SetLocalPosition(BoxPos + float4{ 12 , 79 });
		MyInfoBox->StatInfo->Off();

		std::string_view KrName = GetItemNameToKr(MyInfo->ItemName);

		MyInfoBox->ItemName = CreateComponent<ContentFontRenderer>();
		MyInfoBox->ItemName->SetFont("굴림");
		MyInfoBox->ItemName->SetColor({ 1.0f, 1.0f, 1.0f, 1.0f });
		MyInfoBox->ItemName->SetScale(15.0f);
		MyInfoBox->ItemName->GetTransform()->SetLocalPosition(BoxPos + float4{ 0, 140 });
		MyInfoBox->ItemName->SetFontFlag(FW1_TEXT_FLAG::FW1_CENTER);
		MyInfoBox->ItemName->SetText(KrName);
		MyInfoBox->ItemName->Off();

		MyInfoBox->ItemNameLayer = CreateComponent<ContentFontRenderer>();
		MyInfoBox->ItemNameLayer->SetFont("굴림");
		MyInfoBox->ItemNameLayer->SetColor({ 1.0f, 1.0f, 1.0f, 1.0f });
		MyInfoBox->ItemNameLayer->SetScale(15.0f);
		MyInfoBox->ItemNameLayer->GetTransform()->SetLocalPosition(BoxPos + float4{ 1.0f, 140 });
		MyInfoBox->ItemNameLayer->SetFontFlag(FW1_TEXT_FLAG::FW1_CENTER);
		MyInfoBox->ItemNameLayer->SetText(KrName);
		MyInfoBox->ItemNameLayer->Off();

		SetRequiredStat();
		SetStatRender();
		StatRenderOff();
	}
	else /*if (ItemType == static_cast<int>(ItemType::Etc))*/
	{
		MyInfoBox->BoxRender = CreateComponent<ContentUIRenderer>();
		MyInfoBox->BoxRender->GetTransform()->SetLocalScale({ 300, 120 });
		MyInfoBox->BoxRender->ColorOptionValue.PlusColor = { 1.0f, 1.0f, 1.0f, 0.0f };
		MyInfoBox->BoxRender->ColorOptionValue.MulColor = { 0.1f, 0.25f, 0.5f, 0.8f };
		MyInfoBox->BoxRender->GetTransform()->SetLocalPosition({ 140, -40, -50.0f });

		MyInfoBox->BoxRender->Off();

		float4 BoxPos = MyInfoBox->BoxRender->GetTransform()->GetLocalPosition();

		MyInfoBox->ItemBackGround = CreateComponent<ContentUIRenderer>();
		MyInfoBox->ItemBackGround->GetTransform()->SetLocalScale({ 64, 64 });
		MyInfoBox->ItemBackGround->GetTransform()->SetLocalPosition(BoxPos + float4{ -105, -10 });
		MyInfoBox->ItemBackGround->ColorOptionValue.PlusColor = { 1.0f, 1.0f, 1.0f, 0.0f };
		MyInfoBox->ItemBackGround->ColorOptionValue.MulColor = { 0.95f, 0.95f, 0.95f, 0.8f };

		MyInfoBox->ItemRender = CreateComponent<ContentUIRenderer>();
		MyInfoBox->ItemRender->SetScaleToTexture(MyInfo->ItemName + "Icon.png");
		MyInfoBox->ItemRender->GetTransform()->SetLocalScale(MyInfoBox->ItemRender->GetTransform()->GetLocalScale() * 2.0f);
		MyInfoBox->ItemRender->GetTransform()->SetLocalPosition(MyInfoBox->ItemBackGround->GetTransform()->GetLocalPosition());
		MyInfoBox->ItemRender->Off();

		std::string_view KrName = GetItemNameToKr(MyInfo->ItemName);

		MyInfoBox->ItemName = CreateComponent<ContentFontRenderer>();
		MyInfoBox->ItemName->SetFont("굴림");
		MyInfoBox->ItemName->SetColor({ 1.0f, 1.0f, 1.0f, 1.0f });
		MyInfoBox->ItemName->SetScale(15.0f);
		MyInfoBox->ItemName->GetTransform()->SetLocalPosition(BoxPos + float4{ 0, 55 });
		MyInfoBox->ItemName->SetFontFlag(FW1_TEXT_FLAG::FW1_CENTER);
		MyInfoBox->ItemName->SetText(KrName);
		MyInfoBox->ItemName->Off();

		MyInfoBox->ItemNameLayer = CreateComponent<ContentFontRenderer>();
		MyInfoBox->ItemNameLayer->SetFont("굴림");
		MyInfoBox->ItemNameLayer->SetColor({ 1.0f, 1.0f, 1.0f, 1.0f });
		MyInfoBox->ItemNameLayer->SetScale(15.0f);
		MyInfoBox->ItemNameLayer->GetTransform()->SetLocalPosition(BoxPos + float4{ 1.0f, 55 });
		MyInfoBox->ItemNameLayer->SetFontFlag(FW1_TEXT_FLAG::FW1_CENTER);
		MyInfoBox->ItemNameLayer->SetText(KrName);
		MyInfoBox->ItemNameLayer->Off();

		MyInfoBox->ToolTip = CreateComponent<ContentFontRenderer>();
		MyInfoBox->ToolTip->SetFont("굴림");
		MyInfoBox->ToolTip->SetColor({ 1.0f, 1.0f, 1.0f, 1.0f });
		MyInfoBox->ToolTip->SetScale(13.0f);
		MyInfoBox->ToolTip->GetTransform()->SetLocalPosition(BoxPos + float4{ -68, 22 });
		SetItemToolTip(MyInfoBox->ToolTip);
		MyInfoBox->ToolTip->Off();
	}
}

void Item::SetInfoBoxPos()
{
	if (MyInfoBox == nullptr)
	{
		return;
	}


	if (MyInfoBox->BoxRender != nullptr)
	{
		float4 InfoBoxScreenPos = MyInfoBox->BoxRender->GetTransform()->GetWorldPosition();

		if (InfoBoxScreenPos.x >= 250.0f)
		{
			MyInfoBox->BoxRender->GetTransform()->AddLocalPosition({ 240.0f - InfoBoxScreenPos.x, 0.0f, -50.0f });

			float4 BoxPos = MyInfoBox->BoxRender->GetTransform()->GetLocalPosition();

			if (MyInfoBox->ItemBackGround != nullptr)
			{
				MyInfoBox->ItemBackGround->GetTransform()->SetLocalPosition(BoxPos + float4{ -105, -10 });
			}

			if (MyInfoBox->ItemRender != nullptr)
			{
				MyInfoBox->ItemRender->GetTransform()->SetLocalPosition(MyInfoBox->ItemBackGround->GetTransform()->GetLocalPosition());
			}

			if (MyInfoBox->ItemName != nullptr)
			{
				MyInfoBox->ItemName->GetTransform()->SetLocalPosition(BoxPos + float4{ 0, 55 });
			}

			if (MyInfoBox->ItemNameLayer != nullptr)
			{
				MyInfoBox->ItemNameLayer->GetTransform()->SetLocalPosition(BoxPos + float4{ 1.0f, 55 });
			}

			if (MyInfoBox->ToolTip != nullptr)
			{
				MyInfoBox->ToolTip->GetTransform()->SetLocalPosition(BoxPos + float4{ -68, 22 });
			}

			if (MyInfoBox->StatInfo != nullptr)
			{
				MyInfoBox->StatInfo->GetTransform()->SetLocalPosition(BoxPos + float4{ 12, 79 });
			}
		}
	}
}

void Item::SetRequiredStat()
{
	if (MyInfoBox == nullptr)
	{
		return;
	}

	if (ItemType != static_cast<int>(ItemType::Equip))
	{
		return;
	}

	MyRequiredStat = std::make_shared<ReQuiredStatInfo>();

	std::string_view ItemName = MyInfo->ItemName;

	if (ItemName == "WHITETSHIRT" || ItemName == "BLUEPANTS" || ItemName == "Ganier")
	{
		*MyRequiredStat = { 0, 0, 0, 0, 0 };
	}
	//else if (ItemName == "Ganier")
	//{
	//	*MyRequiredStat = { 0, 0, 0, 0, 0 };
	//}
}

void Item::SetStatRender()
{
	if (MyInfoBox == nullptr)
	{
		return;
	}

	MyInfoBox->ReQuiredStat = std::make_shared<StatRenderer>();

	MyInfoBox->ReQuiredStat->LevRender.reserve(4);
	MyInfoBox->ReQuiredStat->StrRender.reserve(4);
	MyInfoBox->ReQuiredStat->DexRender.reserve(4);
	MyInfoBox->ReQuiredStat->IntRender.reserve(4);
	MyInfoBox->ReQuiredStat->LukRender.reserve(4);

	if (MyRequiredStat != nullptr)
	{
		float4 InfoBoxScreenPos = MyInfoBox->BoxRender->GetTransform()->GetWorldPosition();

		ReQuiredStatInfo CopyStatInfo = *MyRequiredStat;

		for (int i = 0; CopyStatInfo.ReQuiredLev >= 0; i++)
		{
			if (i == 0 && CopyStatInfo.ReQuiredLev == 0)
			{
				MyInfoBox->ReQuiredStat->LevRender.push_back(CreateComponent<ContentUIRenderer>());
				MyInfoBox->ReQuiredStat->LevRender[i]->SetScaleToTexture("InfoBoxStatNum0.png");
				break;
			}
			else if (CopyStatInfo.ReQuiredLev == 0)
			{
				break;
			}

			int Num = CopyStatInfo.ReQuiredLev % 10;
			CopyStatInfo.ReQuiredLev /= 10;

			MyInfoBox->ReQuiredStat->LevRender.push_back(CreateComponent<ContentUIRenderer>());
			MyInfoBox->ReQuiredStat->LevRender[i]->SetScaleToTexture("InfoBoxStatNum" + std::to_string(Num) + ".png");
		}

		size_t LevSize = MyInfoBox->ReQuiredStat->LevRender.size();

		for (int i = 0; i < LevSize; i++)
		{
			MyInfoBox->ReQuiredStat->LevRender[LevSize - 1 - i]->GetTransform()->SetLocalPosition({ InfoBoxScreenPos.x + 40.5f + i * 6.0f, -33.5f, -60.0f });
		}

		for (int i = 0; CopyStatInfo.ReQuiredStr >= 0; i++)
		{
			if (i == 0 && CopyStatInfo.ReQuiredStr == 0)
			{
				MyInfoBox->ReQuiredStat->StrRender.push_back(CreateComponent<ContentUIRenderer>());
				MyInfoBox->ReQuiredStat->StrRender[i]->SetTexture("InfoBoxStatNum0.png");
				MyInfoBox->ReQuiredStat->StrRender[i]->GetTransform()->SetLocalScale({ 5, 7 });
				break;
			}
			else if (CopyStatInfo.ReQuiredStr == 0)
			{
				break;
			}

			int Num = CopyStatInfo.ReQuiredStr % 10;
			CopyStatInfo.ReQuiredStr /= 10;

			MyInfoBox->ReQuiredStat->StrRender.push_back(CreateComponent<ContentUIRenderer>());
			MyInfoBox->ReQuiredStat->StrRender[i]->SetTexture("InfoBoxStatNum" + std::to_string(Num) + ".png");
			MyInfoBox->ReQuiredStat->StrRender[i]->GetTransform()->SetLocalScale({ 5, 7 });
		}

		size_t StrSize = MyInfoBox->ReQuiredStat->StrRender.size();

		for (int i = 0; i < StrSize; i++)
		{
			MyInfoBox->ReQuiredStat->StrRender[StrSize - 1 - i]->GetTransform()->SetLocalPosition({ InfoBoxScreenPos.x + 40.5f + i * 6.0f, -43.5f, -60.0f });
		}

		for (int i = 0; CopyStatInfo.ReQuiredDex >= 0; i++)
		{
			if (i == 0 && CopyStatInfo.ReQuiredDex == 0)
			{
				MyInfoBox->ReQuiredStat->DexRender.push_back(CreateComponent<ContentUIRenderer>());
				MyInfoBox->ReQuiredStat->DexRender[i]->SetScaleToTexture("InfoBoxStatNum0.png");
				break;
			}
			else if (CopyStatInfo.ReQuiredDex == 0)
			{
				break;
			}

			int Num = CopyStatInfo.ReQuiredDex % 10;
			CopyStatInfo.ReQuiredDex /= 10;

			MyInfoBox->ReQuiredStat->DexRender.push_back(CreateComponent<ContentUIRenderer>());
			MyInfoBox->ReQuiredStat->DexRender[i]->SetScaleToTexture("InfoBoxStatNum" + std::to_string(Num) + ".png");
		}

		size_t DexSize = MyInfoBox->ReQuiredStat->DexRender.size();

		for (int i = 0; i < DexSize; i++)
		{
			MyInfoBox->ReQuiredStat->DexRender[DexSize - 1 - i]->GetTransform()->SetLocalPosition({ InfoBoxScreenPos.x + 40.5f + i * 6.0f, -53.5f, -60.0f });
		}

		for (int i = 0; CopyStatInfo.ReQuiredInt >= 0; i++)
		{
			if (i == 0 && CopyStatInfo.ReQuiredInt == 0)
			{
				MyInfoBox->ReQuiredStat->IntRender.push_back(CreateComponent<ContentUIRenderer>());
				MyInfoBox->ReQuiredStat->IntRender[i]->SetScaleToTexture("InfoBoxStatNum0.png");
				break;
			}
			else if (CopyStatInfo.ReQuiredInt == 0)
			{
				break;
			}

			int Num = CopyStatInfo.ReQuiredInt % 10;
			CopyStatInfo.ReQuiredInt /= 10;

			MyInfoBox->ReQuiredStat->IntRender.push_back(CreateComponent<ContentUIRenderer>());
			MyInfoBox->ReQuiredStat->IntRender[i]->SetScaleToTexture("InfoBoxStatNum" + std::to_string(Num) + ".png");
		}

		size_t IntSize = MyInfoBox->ReQuiredStat->IntRender.size();

		for (int i = 0; i < IntSize; i++)
		{
			MyInfoBox->ReQuiredStat->IntRender[IntSize - 1 - i]->GetTransform()->SetLocalPosition({ InfoBoxScreenPos.x + 40.5f + i * 6.0f, -63.5f, -60.0f });
		}

		for (int i = 0; CopyStatInfo.ReQuiredLuk >= 0; i++)
		{
			if (i == 0 && CopyStatInfo.ReQuiredLuk == 0)
			{
				MyInfoBox->ReQuiredStat->LukRender.push_back(CreateComponent<ContentUIRenderer>());
				MyInfoBox->ReQuiredStat->LukRender[i]->SetScaleToTexture("InfoBoxStatNum0.png");
				break;
			}
			else if (CopyStatInfo.ReQuiredLuk == 0)
			{
				break;
			}

			int Num = CopyStatInfo.ReQuiredLuk % 10;
			CopyStatInfo.ReQuiredLuk /= 10;

			MyInfoBox->ReQuiredStat->LukRender.push_back(CreateComponent<ContentUIRenderer>());
			MyInfoBox->ReQuiredStat->LukRender[i]->SetScaleToTexture("InfoBoxStatNum" + std::to_string(Num) + ".png");
		}

		size_t LukSize = MyInfoBox->ReQuiredStat->LukRender.size();

		for (int i = 0; i < LukSize; i++)
		{
			MyInfoBox->ReQuiredStat->LukRender[LukSize - 1 - i]->GetTransform()->SetLocalPosition({ InfoBoxScreenPos.x + 40.5f + i * 6.0f, -73.5f, -60.0f });
		}
	}
}

void Item::StatRenderOn()
{
	if (MyInfoBox->ReQuiredStat == nullptr)
	{
		return;
	}

	for (int i = 0; i < MyInfoBox->ReQuiredStat->LevRender.size(); i++)
	{
		MyInfoBox->ReQuiredStat->LevRender[i]->On();
	}

	for (int i = 0; i < MyInfoBox->ReQuiredStat->StrRender.size(); i++)
	{
		MyInfoBox->ReQuiredStat->StrRender[i]->On();
	}

	for (int i = 0; i < MyInfoBox->ReQuiredStat->DexRender.size(); i++)
	{
		MyInfoBox->ReQuiredStat->DexRender[i]->On();
	}

	for (int i = 0; i < MyInfoBox->ReQuiredStat->IntRender.size(); i++)
	{
		MyInfoBox->ReQuiredStat->IntRender[i]->On();
	}

	for (int i = 0; i < MyInfoBox->ReQuiredStat->LukRender.size(); i++)
	{
		MyInfoBox->ReQuiredStat->LukRender[i]->On();
	}
}


void Item::StatRenderOff()
{
	if (MyInfoBox->ReQuiredStat == nullptr)
	{
		return;
	}

	for (int i = 0; i < MyInfoBox->ReQuiredStat->LevRender.size(); i++)
	{
		MyInfoBox->ReQuiredStat->LevRender[i]->Off();
	}

	for (int i = 0; i < MyInfoBox->ReQuiredStat->StrRender.size(); i++)
	{
		MyInfoBox->ReQuiredStat->StrRender[i]->Off();
	}

	for (int i = 0; i < MyInfoBox->ReQuiredStat->DexRender.size(); i++)
	{
		MyInfoBox->ReQuiredStat->DexRender[i]->Off();
	}

	for (int i = 0; i < MyInfoBox->ReQuiredStat->IntRender.size(); i++)
	{
		MyInfoBox->ReQuiredStat->IntRender[i]->Off();
	}

	for (int i = 0; i < MyInfoBox->ReQuiredStat->LukRender.size(); i++)
	{
		MyInfoBox->ReQuiredStat->LukRender[i]->Off();
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

	if (MyInfoBox->ToolTip != nullptr)
	{
		MyInfoBox->ToolTip->On();
	}

	if (MyInfoBox->StatInfo != nullptr)
	{
		MyInfoBox->StatInfo->On();
	}

	StatRenderOn();

	SetInfoBoxPos();
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

	if (MyInfoBox->ToolTip != nullptr)
	{
		MyInfoBox->ToolTip->Off();
	}

	if (MyInfoBox->StatInfo != nullptr)
	{
		MyInfoBox->StatInfo->Off();
	}

	StatRenderOff();

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
		return "가니어";
	}
	else if (Name == "WHITETSHIRT")
	{
		return "하얀 반팔 면티";
	}
	else if (Name == "BLUEPANTS")
	{
		return "파란 청 반바지";
	}
	else if (Name == "MIRROROFSERA")
	{
		return "세라의 거울";
	}
	else if (Name == "APPLEOFROZAR")
	{
		return "로저의 사과";
	}
	else if (Name == "BREATHOFVOLCANO")
	{
		return "화산의 숨결";
	}
	else if (Name == "BOXKEY")
	{
		return "상자의 열쇠";
	}
	else if (Name == "FIRESTONE")
	{
		return "불의 원석 조각";
	}
	else if (Name == "EYEOFFIRE")
	{
		return "불의 눈";
	}
	else
	{
		return "";
	}
}

void Item::SetItemToolTip(std::shared_ptr<class ContentFontRenderer>  _FontRenderer)
{
	if (MyInfo->ItemName == "MIRROROFSERA")
	{
		_FontRenderer->SetText("화려한 장식이 있는 세라의 거울이다.");
	}
	else if (MyInfo->ItemName == "APPLEOFROZAR")
	{
		_FontRenderer->SetText("빨갛게 잘 익은 사과이다.\nHp를 50 회복시킨다.");
	}
	else if (MyInfo->ItemName == "BREATHOFVOLCANO")
	{
		_FontRenderer->SetText("제물을 제련하는데 필요한\n화산의 뜨거운 열기가 담겨있다.");
	}
	else if (MyInfo->ItemName == "BOXKEY")
	{
		_FontRenderer->SetText("폐광 어딘가에 있는\n커다란 상자를 여는 열쇠이다.");
	}
	else if (MyInfo->ItemName == "FIRESTONE")
	{
		_FontRenderer->SetText("제물을 제련하는데 필요한 원석이다.\n불의 기운을 지니고 있다.");
	}
	else if (MyInfo->ItemName == "EYEOFFIRE")
	{
		_FontRenderer->SetText("자쿰을 소환하기 위한 제물이다.\n제단에 놓으면 자쿰을 소환할 수 있다.");
	}
}