#include "PrecompileHeader.h"
#include "Aura.h"
#include "NPCWindow.h"
#include "Mouse.h"
#include "UIController.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineLevel.h>

Aura::Aura()
{
}

Aura::~Aura()
{
} 

void Aura::Start()
{
	AuraRender = CreateComponent<GameEngineSpriteRenderer>();
	AuraRender->CreateAnimation({ .AnimationName = "Stand",.SpriteName = "Aura",.Loop = true,.ScaleToTexture = true,. FrameTime = {3.0f, 0.15f, 0.2f, 0.15f} });
	AuraRender->ChangeAnimation("Stand");

	std::shared_ptr<GameEngineSpriteRenderer> NameCard = CreateComponent<GameEngineSpriteRenderer>();
	NameCard->SetScaleToTexture("NameBackGround.png");
	NameCard->GetTransform()->SetLocalPosition({ 0, -47 });
	NameCard->GetTransform()->SetLocalScale({ 40, 16 });
	NameCard->ColorOptionValue.MulColor.a = 0.7f;

	std::shared_ptr<GameEngineFontRenderer> NameFont = CreateComponent<GameEngineFontRenderer>();
	NameFont->SetFont("굴림");
	NameFont->SetScale(12.0f);
	NameFont->GetTransform()->SetLocalPosition({ -18, -40 });
	NameFont->SetText("아우라");
	NameFont->SetColor({ 1.0f, 1.0f, 0.0f, 1.0f });

	AuraCollision = CreateComponent<GameEngineCollision>();
	AuraCollision->SetColType(ColType::AABBBOX2D);
	AuraCollision->GetTransform()->SetLocalScale({60, 80});
	
	GetLevel()->IsDebugSwitch();
}

void Aura::Update(float _DeltaTime)
{
	OpenWindow();

	if (UpdateFunc != nullptr)
	{
		UpdateFunc(_DeltaTime);
	}

}

void Aura::Render(float _DeltaTime)
{

}

void Aura::OpenWindow()
{
	if (Mouse::GetMouse()->IsDoubleClick() == false)
	{
		return;
	}

	std::shared_ptr<GameEngineCollision> Col = AuraCollision->Collision(static_cast<int>(CollisionOrder::Mouse), ColType::AABBBOX2D, ColType::AABBBOX2D);

	if (Col == nullptr)
	{
		return;
	}

	MyWindow = GetLevel()->CreateActor<NPCWindow>();

	MyWindow->SetNPC("AURA.PNG", "아우라");
	MyWindow->SetDialogText(" 시련을 통과하고 싶다면, 이곳 어딘가에 있는 불의 원석을 \n 저에게 가져오시면 됩니다. \n 곳곳에 있는 상자들이 수상하던데, 가서 살펴보는건 어떤가요?");
	
	std::function<void()> ButtonFunc = std::bind(&Aura::ItemCheck, DynamicThis<Aura>());
	MyWindow->AddToTextButton(" ☞불의 원석을 가져왔습니다.", 0, ButtonFunc);

	MyWindow->AddToTextButton(" ☞포기하겠습니다.", 0, std::bind(&Aura::ChangeLevel, DynamicThis<Aura>(),"Level_AlterOfZakumEnt"));

	MyWindow->CreateUIButtonList(0);
	MyWindow->SetCloseButton(0, [this] {MyWindow->ButtonsDeath(); MyWindow->Death(); MyWindow = nullptr; });
}

void Aura::ChangeLevel(const std::string_view& _LevelName)
{
	MyWindow->ButtonsDeath();
	MyWindow->Death();
	MyWindow = nullptr;

	std::weak_ptr<GameEngineUIRenderer> Black = CreateComponent<GameEngineUIRenderer>();
	Black.lock()->ColorOptionValue.MulColor = { 0.0f, 0.0f, 0.0f, 0.0f };
	Black.lock()->GetTransform()->SetWorldPosition({ 0, 0, 1 });
	Black.lock()->GetTransform()->SetLocalScale({ 800, 600 });

	UpdateFunc = std::bind([Black, _LevelName](float _Deltatime)
	{
			Black.lock()->ColorOptionValue.MulColor.a += 2.0f * _Deltatime;

			if (Black.lock()->ColorOptionValue.MulColor.a >= 1.0f)
			{
				Black.lock()->Death();
				GameEngineCore::ChangeLevel(_LevelName);
			}	
	}, std::placeholders::_1);
}

void Aura::ItemCheck()
{
	int Index = UIController::GetUIController()->ItemFind("FireStone", static_cast<int>(ItemType::Etc));

	if (Index == -1)
	{
		std::function<void()> Func = std::bind(&NPCWindow::ChangeDialog, MyWindow, " 불의 원석을 가져오신게 맞나요?\n 이 지역 어딘가에 숨겨져 있다고 합니다.");
		
		MyWindow->CreateUIButtonList(1);
		
		std::function<void()> ButtonFunc1 = [this]
		{
			MyWindow->ButtonsDeath();
			MyWindow->Death();
			MyWindow = nullptr;
		};

		MyWindow->AddToTextButton(" ☞다시 찾아보겠습니다.", 1, ButtonFunc1);

		Func();
	}
	else
	{
		std::function<void()> Func = std::bind(&NPCWindow::ChangeDialog, MyWindow, " 불의 원석을 가져오셨군요.\n 다시 제단 입구로 보내드리겠습니다.");

		MyWindow->CreateUIButtonList(1);

		std::function<void()> ButtonFunc1 = std::bind(&Aura::ChangeLevel, DynamicThis<Aura>(), "Level_AlterOfZakumEnt");
		MyWindow->AddToTextButton(" ☞보내주세요.", 1, ButtonFunc1);

		Func();
	}
}