#include "PrecompileHeader.h"
#include "Adovis.h"
#include "Mouse.h"
#include "NPCWindow.h"
#include "UIController.h"

#include <GameEngineCore/GameEngineLevel.h>

Adovis::Adovis()
{
}

Adovis::~Adovis()
{
}

void Adovis::Start()
{
	AdovisRender = CreateComponent<GameEngineSpriteRenderer>();
	AdovisRender->CreateAnimation({ .AnimationName = "Stand",.SpriteName = "Adovis",.Loop = true,.ScaleToTexture = true,.FrameTime = {3.0f, 0.12f, 0.2f, 0.12f} });
	AdovisRender->ChangeAnimation("Stand");

	AdovisCollision = CreateComponent<GameEngineCollision>();
	AdovisCollision->GetTransform()->SetLocalScale({ 30, 50 });
	AdovisCollision->SetColType(ColType::AABBBOX2D);

	std::shared_ptr<GameEngineSpriteRenderer> NameCard = CreateComponent<GameEngineSpriteRenderer>();
	NameCard->SetScaleToTexture("NameBackGround.png");
	NameCard->GetTransform()->SetLocalPosition({ 5.0f, -45 });
	NameCard->GetTransform()->SetLocalScale({ 58, 16 });
	NameCard->ColorOptionValue.MulColor.a = 0.7f;

	std::shared_ptr<GameEngineFontRenderer> NameFont = CreateComponent<GameEngineFontRenderer>();
	NameFont->SetFont("����");
	NameFont->SetScale(12.0f);
	NameFont->GetTransform()->SetLocalPosition({ -18, -38 });
	NameFont->SetText("�Ƶ���");
	NameFont->SetColor({ 1.0f, 1.0f, 0.0f, 1.0f });

	std::shared_ptr<GameEngineFontRenderer> NameFont1 = CreateComponent<GameEngineFontRenderer>();
	NameFont1->SetFont("����");
	NameFont1->SetScale(12.0f);
	NameFont1->GetTransform()->SetLocalPosition({ -17, -38 });
	NameFont1->SetText("�Ƶ���");
	NameFont1->SetColor({ 1.0f, 1.0f, 0.0f, 1.0f });
}

void Adovis::Update(float _DeltaTime) 
{
	OpenWindow();

	if (UpdateFunc != nullptr)
	{
		UpdateFunc(_DeltaTime);
	}
}

void Adovis::Render(float _DeltaTime) 
{

}

void Adovis::OpenWindow()
{
	if (Mouse::GetMouse()->IsDoubleClick() == false)
	{
		return;
	}

	std::shared_ptr<GameEngineCollision> Col = AdovisCollision->Collision(static_cast<int>(CollisionOrder::Mouse), ColType::AABBBOX2D, ColType::AABBBOX2D);

	if (Col == nullptr)
	{
		return;
	}

	MyWindow = GetLevel()->CreateActor<NPCWindow>();

	MyWindow->SetNPC("AdovisStand.PNG", "�Ƶ���");
	MyWindow->SetNPCPos({ -187, 3 });
	MyWindow->SetNPCNamePos({ -216, -36 });

	MyWindow->SetDialogText("��.. ����. �ڳ״� ����� �ڰ��� �Ǿ� ���̴� ��.\n��� �ܰ迡 �����ϰڼ�?");

	MyWindow->CreateUIButtonList(0);
	MyWindow->CreateUIButtonList(1);
	MyWindow->CreateUIButtonList(2);
	MyWindow->CreateUIButtonList(3);

	MyWindow->AddToTextButton("�� ������ �����Ϸ� ������. (1�ܰ�)", 0, [this] 
		{
			if(UIController::GetUIController()->ItemFind("FIRESTONE", static_cast<int>(ItemType::Etc)) != -1)
			{
				MyWindow->ChangeDialog("�̹� ���� ���� ������ ������ �ʾҴ°�? \n���� �ܰ迡 �ٽ� ������ �ʿ�� ����.");
				MyWindow->SetCloseButton(0, [this] {ActorDeath(); });
			}
			else
			{
				ChangeLevel("Level_ZakumRoad1");
			}
		});
	MyWindow->AddToTextButton("���� ������ Ž���Ѵ�. (2�ܰ�)", 0, [this] 
		{
			if (UIController::GetUIController()->ItemFind("BREATHOFVOLCANO", static_cast<int>(ItemType::Etc)) != -1)
			{
				MyWindow->ChangeDialog("�̹� ȭ���� ������ ������ �ʾҴ°�? \n���� �ܰ迡 �ٽ� ������ �ʿ�� ����.");
				MyWindow->SetCloseButton(0, [this] {ActorDeath(); });
			}
			else
			{
				ChangeLevel("Level_ZakumRoad2");
			}
		});
	MyWindow->AddToTextButton("������ �䫊�Ѵ�. (3�ܰ�)", 0, [this] 
		{
			MyWindow->ChangeDialog("���� ���� ������ ȭ���� ������ ��� �����Գ�?");

			MyWindow->AddToTextButton("��. ��� �����Խ��ϴ�.", 1, [this]
				{
					if(UIController::GetUIController()->ItemFind("FIRESTONE", static_cast<int>(ItemType::Etc)) != -1 && UIController::GetUIController()->ItemFind("BREATHOFVOLCANO", static_cast<int>(ItemType::Etc)) != -1)
					{
						MyWindow->ChangeDialog("���� ���� ���� ������ �ֵ��� ����. \n���� ���� ���ϼ�. �� ���� ���ܿ� ������, \n���񿡰� ������ �� �ִٳ�. �׷� ������ ����.");

						std::shared_ptr<ItemInfo> NewItem = std::make_shared<ItemInfo>();
						NewItem->ItemName = "EYEOFFIRE";

						UIController::GetUIController()->AddToItemList(NewItem, static_cast<int>(ItemType::Etc));

						UIController::GetUIController()->DeleteToItemList("FIRESTONE", static_cast<int>(ItemType::Etc));
						UIController::GetUIController()->DeleteToItemList("BREATHOFVOLCANO", static_cast<int>(ItemType::Etc));

						MyWindow->SetCloseButton(2, [this] {ActorDeath(); });
					}
					else if(UIController::GetUIController()->ItemFind("EYEOFFIRE", static_cast<int>(ItemType::Etc)) != -1)
					{
						MyWindow->ChangeDialog("�Ʊ� ���� ���� ����� ���� �ʾҳ�? \n� ������ ������ ����.");
						MyWindow->SetCloseButton(2, [this] {ActorDeath(); });
					}
					else
					{
						MyWindow->ChangeDialog("���� ���� ������ ȭ���� ������ ��� �����;� �Ѵٳ�.");
						MyWindow->SetCloseButton(2, [this] {ActorDeath(); });
					}
				});
		});

}

void Adovis::ActorDeath()
{
	if (MyWindow != nullptr)
	{
		MyWindow->ButtonsDeath();
		MyWindow->Death();
		MyWindow = nullptr;
	}
}

void Adovis::ChangeLevel(const std::string_view& _LevelName)
{
	MyWindow->ButtonsDeath();
	MyWindow->Death();
	MyWindow = nullptr;

	std::weak_ptr<GameEngineUIRenderer> Black = CreateComponent<GameEngineUIRenderer>();
	Black.lock()->ColorOptionValue.MulColor = { 0.0f, 0.0f, 0.0f, 0.0f };
	Black.lock()->GetTransform()->SetWorldPosition({ 0, 0, 1 });
	Black.lock()->GetTransform()->SetLocalScale({ 800, 600 });

	UpdateFunc = std::bind([this, Black, _LevelName](float _Deltatime)
		{
			Black.lock()->ColorOptionValue.MulColor.a += 1.0f * _Deltatime;

			if (Black.lock()->ColorOptionValue.MulColor.a >= 1.0f)
			{
				Black.lock()->Death();
				GameEngineCore::ChangeLevel(_LevelName);
				UpdateFunc = nullptr;
			}
		}, std::placeholders::_1);
}