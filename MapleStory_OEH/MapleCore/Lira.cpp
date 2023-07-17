#include "Lira.h"
#include "PrecompileHeader.h"
#include "Lira.h"
#include "NPCWindow.h"
#include "UIController.h"
#include "Mouse.h"

#include <GameEngineCore/GameEngineLevel.h>

Lira::Lira()
{
}

Lira::~Lira()
{
}

void Lira::Start()
{
	LiraRender = CreateComponent<GameEngineSpriteRenderer>();

	LiraCollision = CreateComponent<GameEngineCollision>();
	LiraCollision->GetTransform()->SetLocalScale({ 30, 50 });
	LiraCollision->SetColType(ColType::AABBBOX2D);

	std::shared_ptr<GameEngineSpriteRenderer> NameCard = CreateComponent<GameEngineSpriteRenderer>();
	NameCard->SetScaleToTexture("NameBackGround.png");
	NameCard->GetTransform()->SetLocalPosition({ 0.5, -50 });
	NameCard->GetTransform()->SetLocalScale({ 29, 16 });
	NameCard->ColorOptionValue.MulColor.a = 0.7f;

	std::shared_ptr<GameEngineFontRenderer> NameFont = CreateComponent<GameEngineFontRenderer>();
	NameFont->SetFont("굴림");
	NameFont->SetScale(12.0f);
	NameFont->GetTransform()->SetLocalPosition({ -11, -42 });
	NameFont->SetText("리라");
	NameFont->SetColor({ 1.0f, 1.0f, 0.0f, 1.0f });

	std::shared_ptr<GameEngineFontRenderer> NameFont1 = CreateComponent<GameEngineFontRenderer>();
	NameFont1->SetFont("굴림");
	NameFont1->SetScale(12.0f);
	NameFont1->GetTransform()->SetLocalPosition({ -10, -42 });
	NameFont1->SetText("리라");
	NameFont1->SetColor({ 1.0f, 1.0f, 0.0f, 1.0f });
	
	LiraRender->CreateAnimation({ .AnimationName = "STAND",.SpriteName = "Lira",.Loop = true,.ScaleToTexture = true,.FrameTime = {3.0f, 0.15f, 0.2f, 0.15f}});
	LiraRender->ChangeAnimation("STAND");
}

void Lira::Update(float _DeltaTime) 
{
	OpenWindow();

	if (UpdateFunc != nullptr)
	{
		UpdateFunc(_DeltaTime);
	}
}

void Lira::Render(float _DeltaTime) 
{

}

void Lira::OpenWindow()
{
	if (Mouse::GetMouse()->IsDoubleClick() == false)
	{
		return;
	}

	std::shared_ptr<GameEngineCollision> Col = LiraCollision->Collision(static_cast<int>(CollisionOrder::Mouse), ColType::AABBBOX2D, ColType::AABBBOX2D);

	if (Col == nullptr)
	{
		return;
	}

	if (UIController::GetUIController()->ItemFind("BREATHOFVOLCANO", static_cast<int>(ItemType::Etc)) == -1)
	{
		MyWindow = GetLevel()->CreateActor<NPCWindow>();
		MyWindow->SetNPC("LIRASTAND0.PNG", "   리라");

		MyWindow->SetDialogText("저 험한 길을 어떻게 건너 온 거에요? 대단해요.\n자 여기 불의 눈을 연성하는데 필요한 재료입니다.\n자쿰으로 통하는 문으로 보내드릴게요.");

		MyWindow->CreateUIButtonList(0);
		MyWindow->AddToTextButton("보내주세요.", 0, [this] 
			{
				std::shared_ptr<ItemInfo> NewItem = std::make_shared<ItemInfo>();
				NewItem->ItemName = "BREATHOFVOLCANO";
				UIController::GetUIController()->AddToItemList(NewItem, static_cast<int>(ItemType::Etc));
				ChangeLevel("Level_AlterOfZakumEnt");
				MyWindow->ButtonsDeath(); 
				MyWindow->Death(); 
				MyWindow = nullptr; 
			});
	}
}

void Lira::ChangeLevel(const std::string_view& _LevelName)
{
	std::weak_ptr<GameEngineUIRenderer> Black = CreateComponent<GameEngineUIRenderer>();
	Black.lock()->ColorOptionValue.MulColor = { 0.0f, 0.0f, 0.0f, 0.0f };
	Black.lock()->GetTransform()->SetWorldPosition({ 0, 0, 1 });
	Black.lock()->GetTransform()->SetLocalScale({ 800, 600 });

	UpdateFunc = std::bind([this, Black, _LevelName](float _Deltatime)
		{
			Black.lock()->ColorOptionValue.MulColor.a += 2.0f * _Deltatime;

			if (Black.lock()->ColorOptionValue.MulColor.a >= 1.0f)
			{
				Black.lock()->Death();
				GameEngineCore::ChangeLevel(_LevelName);
				UpdateFunc = nullptr;
			}
		}, std::placeholders::_1);
}