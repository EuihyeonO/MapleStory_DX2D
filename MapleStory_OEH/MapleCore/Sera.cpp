#include "PrecompileHeader.h"
#include "Sera.h"
#include "Mouse.h"
#include "NPCWindow.h"
#include "UIController.h"

#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineCore/GameEngineLevel.h>

Sera::Sera()
{
}

Sera::~Sera()
{
}

void Sera::Start()
{
	SeraRender = CreateComponent<GameEngineSpriteRenderer>();
	SeraRender->CreateAnimation({ .AnimationName = "STAND",.SpriteName = "SeraStand",.FrameInter = 2.0f,.Loop = false,.ScaleToTexture = true });
	SeraRender->CreateAnimation({ .AnimationName = "HAIR",.SpriteName = "SeraHair",.Loop = false,.ScaleToTexture = true,.FrameTime = {0.3f, 0.3f, 4.4f} });
	SeraRender->CreateAnimation({ .AnimationName = "MOVE",.SpriteName = "SeraMove",.FrameInter = 0.3f,.Loop = true,.ScaleToTexture = true});
	
	SeraRender->SetAnimationUpdateEvent("STAND", 0, [this] {if (SeraRender->IsAnimationEnd() == true) { ChangeStatus(); }});
	SeraRender->SetAnimationUpdateEvent("HAIR", 2, [this] {if (SeraRender->IsAnimationEnd() == true) { ChangeStatus(); }});
	SeraRender->SetAnimationStartEvent("MOVE", 3, [this] {if (GameEngineRandom::MainRandom.RandomInt(0, 5) == 1) { Dir *= -1.0f; }});
	
	SeraRender->ChangeAnimation("STAND");

	SeraCollision = CreateComponent<GameEngineCollision>();
	SeraCollision->GetTransform()->SetLocalScale({ 30, 50 });
	SeraCollision->SetColType(ColType::AABBBOX2D);

	std::shared_ptr<GameEngineSpriteRenderer> NameCard = CreateComponent<GameEngineSpriteRenderer>();
	NameCard->SetScaleToTexture("NameBackGround.png");
	NameCard->GetTransform()->SetLocalPosition({ 0, -45 });
	NameCard->GetTransform()->SetLocalScale({ 33, 16 });
	NameCard->ColorOptionValue.MulColor.a = 0.7f;

	std::shared_ptr<GameEngineFontRenderer> NameFont = CreateComponent<GameEngineFontRenderer>();
	NameFont->SetFont("굴림");
	NameFont->SetScale(12.0f);
	NameFont->SetFontFlag(FW1_TEXT_FLAG::FW1_CENTER);
	NameFont->GetTransform()->SetLocalPosition({ 0, -37 });
	NameFont->SetText("세라");
	NameFont->SetColor({ 1.0f, 1.0f, 0.0f, 1.0f });

	std::shared_ptr<GameEngineFontRenderer> NameFont1 = CreateComponent<GameEngineFontRenderer>();
	NameFont1->SetFont("굴림");
	NameFont1->SetScale(12.0f);
	NameFont1->SetFontFlag(FW1_TEXT_FLAG::FW1_CENTER);
	NameFont1->GetTransform()->SetLocalPosition({ 1, -37 });
	NameFont1->SetText("세라");
	NameFont1->SetColor({ 1.0f, 1.0f, 0.0f, 1.0f });
}

void Sera::Update(float _DeltaTime) 
{
	if(UpdateFunc != nullptr)
	{
		UpdateFunc(_DeltaTime);
	}

	OpenWindow();
}

void Sera::Render(float _DeltaTime) 
{

}


void Sera::ChangeStatus()
{
	int Num = GameEngineRandom::MainRandom.RandomInt(0, 2);

	switch (Num)
	{
	case 0:
		Status = "STAND";
		SeraRender->ChangeAnimation(Status);
		UpdateFunc = nullptr;
		break;
	case 1:
		Status = "HAIR";
		SeraRender->ChangeAnimation(Status);
		UpdateFunc = nullptr;
		break;
	case 2:
		Status = "MOVE";
		SeraRender->ChangeAnimation(Status);
		UpdateFunc = std::bind(&Sera::MoveUpdate, DynamicThis<Sera>(), std::placeholders::_1);
		break;
	}
}

void Sera::MoveUpdate(float _DeltaTime)
{
	float4 MyPos = GetTransform()->GetLocalPosition();

	if (MyPos.x < 300)
	{
		Dir = { 1, 0 };
	}
	else if (MyPos.x > 500)
	{
		Dir = { -1, 0 }; 
	}

	if (Dir.x > 0)
	{
		float4 Scale = GetTransform()->GetLocalScale();
		GetTransform()->SetLocalScale({ -abs(Scale.x), Scale.y });
	}
	else
	{
		float4 Scale = GetTransform()->GetLocalScale();
		GetTransform()->SetLocalScale({ abs(Scale.x), Scale.y });
	}

	GetTransform()->AddLocalPosition(Dir * 20.0f * _DeltaTime);
	MoveDistance += 25.0f * _DeltaTime;
	
	if (MoveDistance >= 100.0f)
	{
		MoveDistance = 0.0f;
		ChangeStatus();
	}
}

void Sera::OpenWindow()
{
	if (Mouse::GetMouse()->IsDoubleClick() == false)
	{
		return;
	}

	std::shared_ptr<GameEngineCollision> Col = SeraCollision->Collision(static_cast<int>(CollisionOrder::Mouse), ColType::AABBBOX2D, ColType::AABBBOX2D);

	if (Col == nullptr)
	{
		return;
	}

	if (UIController::GetUIController()->isQuestInList("HINA0") == true && UIController::GetUIController()->ItemFind("MIRROROFSERA", static_cast<int>(ItemType::Etc)) == -1)
	{
		MyWindow = GetLevel()->CreateActor<NPCWindow>();
		MyWindow->SetNPC("SeraStand.PNG", "   세라");

		MyWindow->SetDialogText("이걸 언제 다 널지... 에휴... 네? 제 거울 말이세요? \n혹시 히나의 부탁을 받고 오신 거에요?");

		MyWindow->CreateUIButtonList(0);
		MyWindow->CreateUIButtonList(1);
		MyWindow->AddToTextButton("거울을 빌리러 왔어요.", 0, [this]
			{
				MyWindow->ChangeDialog("아휴~ 직접 오면 될 것을... 하여튼 게으른 건 \n알아 준다니까요. 여기 제 거울 받으세요. \n아이템 인벤토리 창을 단축키 I 를 누르면 열 수 있으니 \n거울을 제대로 받았는지 확인한 다음, 히나에게 가 보세요.");
				std::shared_ptr<ItemInfo> NewItem = std::make_shared<ItemInfo>();
				NewItem->ItemName = "MIRROROFSERA";

				UIController::GetUIController()->AddToItemList(NewItem, static_cast<int>(ItemType::Etc));
			});

		MyWindow->AddToTextButton("아뇨.", 0, [this] {MyWindow->ChangeDialog("으음? 왜 거울을 받지 않으시는 건가요? #p2101#의 부탁을 들어주기 싫어지신 건가요?"); });
		MyWindow->SetCloseButton(0, [this] {MyWindow->ButtonsDeath(); MyWindow->Death(); MyWindow = nullptr; });
		MyWindow->SetCloseButton(1, [this] {MyWindow->ButtonsDeath(); MyWindow->Death(); MyWindow = nullptr; });
	}
	else if(UIController::GetUIController()->isQuestInList("HINA0") == true && UIController::GetUIController()->ItemFind("MIRROROFSERA", static_cast<int>(ItemType::Etc)) != -1)
	{
		MyWindow = GetLevel()->CreateActor<NPCWindow>();
		MyWindow->SetNPC("SeraStand.PNG", "   세라");

		MyWindow->SetDialogText("아직 히나에게 거울을 가져가시지 않은 모양이네요? \n서둘러 주세요~ ");
		MyWindow->CreateUIButtonList(0);
		MyWindow->SetCloseButton(0, [this] {MyWindow->ButtonsDeath(); MyWindow->Death(); MyWindow = nullptr; });
	}
	else if (UIController::GetUIController()->isQuestInList("HINA0") == false)
	{
		MyWindow = GetLevel()->CreateActor<NPCWindow>();
		MyWindow->SetNPC("SeraStand.PNG", "   세라");

		MyWindow->SetDialogText("아휴.. 이 많은 빨래들을 언제 다 널지..");
		MyWindow->CreateUIButtonList(0);
		MyWindow->SetCloseButton(0, [this] {MyWindow->ButtonsDeath(); MyWindow->Death(); MyWindow = nullptr; });
	}
}

void Sera::ActorDeath()
{
	if (MyWindow != nullptr)
	{
		MyWindow->Death();
		MyWindow = nullptr;
	}
}