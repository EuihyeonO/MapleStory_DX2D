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
	NameFont->SetFont("굴림");
	NameFont->SetScale(12.0f);
	NameFont->GetTransform()->SetLocalPosition({ -18, -38 });
	NameFont->SetText("아도비스");
	NameFont->SetColor({ 1.0f, 1.0f, 0.0f, 1.0f });

	std::shared_ptr<GameEngineFontRenderer> NameFont1 = CreateComponent<GameEngineFontRenderer>();
	NameFont1->SetFont("굴림");
	NameFont1->SetScale(12.0f);
	NameFont1->GetTransform()->SetLocalPosition({ -17, -38 });
	NameFont1->SetText("아도비스");
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

	MyWindow->SetNPC("AdovisStand.PNG", "아도비스");
	MyWindow->SetNPCPos({ -187, 3 });
	MyWindow->SetNPCNamePos({ -216, -36 });

	MyWindow->SetDialogText("뭐.. 좋소. 자네는 충분한 자격이 되어 보이는 군.\n어느 단계에 도전하겠소?");

	MyWindow->CreateUIButtonList(0);
	MyWindow->CreateUIButtonList(1);
	MyWindow->CreateUIButtonList(2);
	MyWindow->CreateUIButtonList(3);

	MyWindow->AddToTextButton("폐광 동굴을 조사하러 떠난다. (1단계)", 0, [this] 
		{
			if(UIController::GetUIController()->ItemFind("FIRESTONE", static_cast<int>(ItemType::Etc)) != -1)
			{
				MyWindow->ChangeDialog("이미 불의 원석 조각을 구하지 않았는가? \n같은 단계에 다시 도전할 필요는 없소.");
				MyWindow->SetCloseButton(0, [this] {ActorDeath(); });
			}
			else
			{
				ChangeLevel("Level_ZakumRoad1");
			}
		});
	MyWindow->AddToTextButton("자쿰 던전을 탐사한다. (2단계)", 0, [this] 
		{
			if (UIController::GetUIController()->ItemFind("BREATHOFVOLCANO", static_cast<int>(ItemType::Etc)) != -1)
			{
				MyWindow->ChangeDialog("이미 화산의 숨결을 구하지 않았는가? \n같은 단계에 다시 도전할 필요는 없소.");
				MyWindow->SetCloseButton(0, [this] {ActorDeath(); });
			}
			else
			{
				ChangeLevel("Level_ZakumRoad2");
			}
		});
	MyWindow->AddToTextButton("제련을 요쳥한다. (3단계)", 0, [this] 
		{
			MyWindow->ChangeDialog("불의 원석 조각과 화산의 숨결을 모두 가져왔나?");

			MyWindow->AddToTextButton("네. 모두 가져왔습니다.", 1, [this]
				{
					if(UIController::GetUIController()->ItemFind("FIRESTONE", static_cast<int>(ItemType::Etc)) != -1 && UIController::GetUIController()->ItemFind("BREATHOFVOLCANO", static_cast<int>(ItemType::Etc)) != -1)
					{
						MyWindow->ChangeDialog("좋아 불의 눈을 제련해 주도록 하지. \n여기 불의 눈일세. 이 것을 제단에 놓으면, \n자쿰에게 도전할 수 있다네. 그럼 무운을 빌지.");

						std::shared_ptr<ItemInfo> NewItem = std::make_shared<ItemInfo>();
						NewItem->ItemName = "EYEOFFIRE";

						UIController::GetUIController()->AddToItemList(NewItem, static_cast<int>(ItemType::Etc));

						UIController::GetUIController()->DeleteToItemList("FIRESTONE", static_cast<int>(ItemType::Etc));
						UIController::GetUIController()->DeleteToItemList("BREATHOFVOLCANO", static_cast<int>(ItemType::Etc));

						MyWindow->SetCloseButton(2, [this] {ActorDeath(); });
					}
					else if(UIController::GetUIController()->ItemFind("EYEOFFIRE", static_cast<int>(ItemType::Etc)) != -1)
					{
						MyWindow->ChangeDialog("아까 불의 눈을 만들어 주지 않았나? \n어서 자쿰을 만나러 가게.");
						MyWindow->SetCloseButton(2, [this] {ActorDeath(); });
					}
					else
					{
						MyWindow->ChangeDialog("불의 원석 조각과 화산의 숨결을 모두 가져와야 한다네.");
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