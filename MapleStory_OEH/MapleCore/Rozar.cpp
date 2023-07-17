#include "PrecompileHeader.h"
#include "Rozar.h"
#include "UIController.h"
#include "NPCWindow.h"
#include "Mouse.h"

#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineLevel.h>

Rozar::Rozar()
{
}

Rozar::~Rozar()
{
}

void Rozar::Start()
{
	TimeCounting();

	RozarRender = CreateComponent<GameEngineSpriteRenderer>();
	Status = "STAND";

	GetTransform()->SetLocalPosition({ -20, 220 });

	RozarCollision = CreateComponent<GameEngineCollision>();
	RozarCollision->GetTransform()->SetLocalScale({ 40, 60 });
	RozarCollision->SetColType(ColType::AABBBOX2D);

	std::shared_ptr<GameEngineSpriteRenderer> NameCard = CreateComponent<GameEngineSpriteRenderer>();
	NameCard->SetScaleToTexture("NameBackGround.png");
	NameCard->GetTransform()->SetLocalPosition({ 0, -44 });
	NameCard->GetTransform()->SetLocalScale({ 29, 16 });
	NameCard->ColorOptionValue.MulColor.a = 0.7f;

	std::shared_ptr<GameEngineFontRenderer> NameFont = CreateComponent<GameEngineFontRenderer>();
	NameFont->SetFont("����");
	NameFont->SetScale(12.0f);
	NameFont->GetTransform()->SetLocalPosition({ -13, -36 });
	NameFont->SetText("����");
	NameFont->SetColor({ 1.0f, 1.0f, 0.0f, 1.0f });

	std::shared_ptr<GameEngineFontRenderer> NameFont1 = CreateComponent<GameEngineFontRenderer>();
	NameFont1->SetFont("����");
	NameFont1->SetScale(12.0f);
	NameFont1->GetTransform()->SetLocalPosition({ -12, -36 });
	NameFont1->SetText("����");
	NameFont1->SetColor({ 1.0f, 1.0f, 0.0f, 1.0f });
}

void Rozar::Update(float _DeltaTime) 
{
	TimeCounting();
	TextureUpdate();
	OpenWindow();
}

void Rozar::Render(float _DeltaTime) 
{
}

void Rozar::TextureUpdate()
{
	if (Status == "STAND")
	{
		if (AniIndex == 0)
		{
			RozarRender->SetScaleToTexture("RozarStand0.png");
			AniIndex++;
		}

		AnimationCount += TimeCount;

		if (AnimationCount >= 5.0f)
		{
			AnimationCount = 0.0f;
			AniIndex = 0;
			StatusUpdate();
		}
	}
	else if (Status == "FINGER")
	{
		if (AniIndex == 0)
		{
			RozarRender->SetScaleToTexture("RozarFinger0.png");
			AniIndex++;
		}

		AnimationCount += TimeCount;

		if (AnimationCount >= 5.0f)
		{
			AnimationCount = 0.0f;
			AniIndex = 0;
			StatusUpdate();
		}
	}
	else if (Status == "WINK")
	{
		if (AniIndex == 0)
		{
			RozarRender->SetScaleToTexture("RozarWink0.png");
			AniIndex++;
		}

		AnimationCount += TimeCount;

		if (AnimationCount >= WinkFrame[0] && AniIndex == 1)
		{
			RozarRender->SetScaleToTexture("RozarWink1.png");
			AniIndex++;
			AnimationCount = 0.0f;
		}

		if (AnimationCount >= WinkFrame[1])
		{
			AnimationCount = 0.0f;
			AniIndex = 0;
			StatusUpdate();
		}
	}
}

void Rozar::StatusUpdate()
{
	int StatusType = GameEngineRandom::MainRandom.RandomInt(0, 5);

	if (StatusType > 3)
	{
		StatusType = 0;
	}

	switch (StatusType)
	{
	case 0:
		Status = "STAND";
		break;
	case 1:
		Status = "FINGER";
		break;
	case 2:
		Status = "WINK";
		break;
	}
}

void Rozar::OpenWindow()
{
	if (Mouse::GetMouse()->IsDoubleClick() == false)
	{
		return;
	}

	std::shared_ptr<GameEngineCollision> Col = RozarCollision->Collision(static_cast<int>(CollisionOrder::Mouse), ColType::AABBBOX2D, ColType::AABBBOX2D);

	if (Col == nullptr)
	{
		return;
	}

	if (UIController::GetUIController()->isQuestInClearList("ROZAR0") == false && UIController::GetUIController()->isQuestInList("ROZAR0") == false)
	{
		MyWindow = GetLevel()->CreateActor<NPCWindow>();
		MyWindow->SetNPC("RozarFinger0.PNG", "   ����");

		MyWindow->SetDialogText("����~ ������! �ð� �־�? ������! ���� ��ó�� ����\n���谡���� ���� ������ �ִ� ������.\n����! �ٺ��� ��� �ð� �� ����. ���� Ư���� ������\n������ �ϳ� �˷��ٰ�! ������!!!\n��~ �׷� �峭�� �ĺ���? ����!");
		PlayerValue::GetValue()->SubHp(50);

		MyWindow->CreateUIButtonList(0);
		MyWindow->SetNextButton(0);

		MyWindow->CreateUIButtonList(1);
		MyWindow->SetDialogText(1, "�����? Hp�� 0�� �Ǹ� ū�ϳ��ٱ�. ��, ���� �� ����� \n�ϳ� �Ծ��. ���� ���ž�. \n������ â�� ���� ����Ŭ���ϸ� ��.\n���� �� ����� ���� �Ծ�� ��. ������ �ٷ� Hp�� \nȸ���Ǵ� ���� ���ϰž�!");
		MyWindow->SetCloseButton(1, [this] 
			{
				MyWindow->ButtonsDeath(); 
				MyWindow->Death(); 
				MyWindow = nullptr; 
				std::shared_ptr<ItemInfo> NewItem = std::make_shared<ItemInfo>();
				NewItem->ItemName = "APPLEOFROZAR";

				UIController::GetUIController()->AddToItemList(NewItem, static_cast<int>(ItemType::Use));
			});

		UIController::GetUIController()->AddToQuestList("ROZAR0");
	}
	else if (UIController::GetUIController()->isQuestInList("ROZAR0") == true && UIController::GetUIController()->ItemFind("APPLEOFROZAR", static_cast<int>(ItemType::Use)) != -1)
	{
		MyWindow = GetLevel()->CreateActor<NPCWindow>();
		MyWindow->SetNPC("RozarFinger0.PNG", "   ����");

		MyWindow->SetDialogText("���� �� ����� ���� ������ϱ� �׷���~ \n������ â�� ��� �Һ� ���� Ŭ���غ�.\n ����� �����״� ����Ŭ���ؼ� ������ ��.");

		MyWindow->CreateUIButtonList(0);
		MyWindow->SetCloseButton(0, [this] {MyWindow->ButtonsDeath(); MyWindow->Death(); MyWindow = nullptr; });
	}
	else if (UIController::GetUIController()->isQuestInList("ROZAR0") == true && UIController::GetUIController()->ItemFind("APPLEOFROZAR", static_cast<int>(ItemType::Use)) == -1)
	{
		MyWindow = GetLevel()->CreateActor<NPCWindow>();
		MyWindow->SetNPC("RozarFinger0.PNG", "   ����");

		MyWindow->SetDialogText("�? �������� �Դ°� ��������?\n���� ������ �� �� �ִ� �� ���������!\n�ƽ����� ���� ����� �ð��̷α�\n�ƹ��ɷ� ������ �϶�, �׷� �߰�~!");

		MyWindow->CreateUIButtonList(0);
		MyWindow->SetCloseButton(0, [this] {MyWindow->ButtonsDeath(); MyWindow->Death(); MyWindow = nullptr; });

		UIController::GetUIController()->QuestClear("ROZAR0");
	}
	else if (UIController::GetUIController()->isQuestInClearList("ROZAR0") == true && UIController::GetUIController()->isQuestInList("ROZAR0") == false)
	{
		MyWindow = GetLevel()->CreateActor<NPCWindow>();
		MyWindow->SetNPC("RozarFinger0.PNG", "   ����");

		MyWindow->SetDialogText("�ƹ��ɷ� ������ �϶�, �׷� �߰�~ ");

		MyWindow->CreateUIButtonList(0);
		MyWindow->SetCloseButton(0, [this] {MyWindow->ButtonsDeath(); MyWindow->Death(); MyWindow = nullptr; });
	}
}

void Rozar::ActorDeath()
{
	if (MyWindow != nullptr)
	{
		MyWindow->ButtonsDeath();
		MyWindow->Death();
		MyWindow = nullptr;
	}
}