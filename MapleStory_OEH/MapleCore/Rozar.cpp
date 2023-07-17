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
	NameFont->SetFont("굴림");
	NameFont->SetScale(12.0f);
	NameFont->GetTransform()->SetLocalPosition({ -13, -36 });
	NameFont->SetText("로저");
	NameFont->SetColor({ 1.0f, 1.0f, 0.0f, 1.0f });

	std::shared_ptr<GameEngineFontRenderer> NameFont1 = CreateComponent<GameEngineFontRenderer>();
	NameFont1->SetFont("굴림");
	NameFont1->SetScale(12.0f);
	NameFont1->GetTransform()->SetLocalPosition({ -12, -36 });
	NameFont1->SetText("로저");
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
		MyWindow->SetNPC("RozarFinger0.PNG", "   로저");

		MyWindow->SetDialogText("어이~ 멋쟁이! 시간 있어? 아하하! 나는 너처럼 멋진\n모험가에게 좋은 정보를 주는 로저야.\n어이! 바빠도 잠깐만 시간 좀 내줘. 내가 특별히 유용한\n정보를 하나 알려줄게! 아하하!!!\n자~ 그럼 장난좀 쳐볼까? 에잇!");
		PlayerValue::GetValue()->SubHp(50);

		MyWindow->CreateUIButtonList(0);
		MyWindow->SetNextButton(0);

		MyWindow->CreateUIButtonList(1);
		MyWindow->SetDialogText(1, "놀랐지? Hp가 0이 되면 큰일난다구. 자, 내가 준 사과를 \n하나 먹어봐. 힘이 날거야. \n아이템 창을 열고 더블클릭하면 돼.\n내가 준 사과를 전무 먹어야 해. 먹으면 바로 Hp가 \n회복되는 것이 보일거야!");
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
		MyWindow->SetNPC("RozarFinger0.PNG", "   로저");

		MyWindow->SetDialogText("내가 준 사과를 전부 먹으라니까 그러네~ \n아이템 창을 열어서 소비 탭을 클릭해봐.\n 사과가 있을테니 더블클릭해서 먹으면 돼.");

		MyWindow->CreateUIButtonList(0);
		MyWindow->SetCloseButton(0, [this] {MyWindow->ButtonsDeath(); MyWindow->Death(); MyWindow = nullptr; });
	}
	else if (UIController::GetUIController()->isQuestInList("ROZAR0") == true && UIController::GetUIController()->ItemFind("APPLEOFROZAR", static_cast<int>(ItemType::Use)) == -1)
	{
		MyWindow = GetLevel()->CreateActor<NPCWindow>();
		MyWindow->SetNPC("RozarFinger0.PNG", "   로저");

		MyWindow->SetDialogText("어때? 아이템을 먹는거 간단하지?\n내가 가르쳐 줄 수 있는 건 여기까지야!\n아쉽지만 이제 헤어질 시간이로군\n아무쪼록 몸조심 하라구, 그럼 잘가~!");

		MyWindow->CreateUIButtonList(0);
		MyWindow->SetCloseButton(0, [this] {MyWindow->ButtonsDeath(); MyWindow->Death(); MyWindow = nullptr; });

		UIController::GetUIController()->QuestClear("ROZAR0");
	}
	else if (UIController::GetUIController()->isQuestInClearList("ROZAR0") == true && UIController::GetUIController()->isQuestInList("ROZAR0") == false)
	{
		MyWindow = GetLevel()->CreateActor<NPCWindow>();
		MyWindow->SetNPC("RozarFinger0.PNG", "   로저");

		MyWindow->SetDialogText("아무쪼록 몸조심 하라구, 그럼 잘가~ ");

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