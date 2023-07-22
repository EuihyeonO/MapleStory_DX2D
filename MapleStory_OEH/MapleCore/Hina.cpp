#include "PrecompileHeader.h"
#include "Hina.h"
#include "Mouse.h"
#include "NPCWindow.h"
#include "UIController.h"

#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <ctime>

Hina::Hina()
{
}

Hina::~Hina()
{
}

void Hina::Start()
{
	TimeCounting();
	SetFrameList();
	
	HinaRender = CreateComponent<GameEngineSpriteRenderer>();
	Status = "NORMAL";

	HinaCollision = CreateComponent<GameEngineCollision>();
	HinaCollision->GetTransform()->SetLocalScale({ 30, 50 });
	HinaCollision->SetColType(ColType::AABBBOX2D);

	std::shared_ptr<GameEngineSpriteRenderer> NameCard = CreateComponent<GameEngineSpriteRenderer>();
	NameCard->SetScaleToTexture("NameBackGround.png");
	NameCard->GetTransform()->SetLocalPosition({ 0.5, -40 });
	NameCard->GetTransform()->SetLocalScale({ 29, 16 });
	NameCard->ColorOptionValue.MulColor.a = 0.7f;

	std::shared_ptr<GameEngineFontRenderer> NameFont = CreateComponent<GameEngineFontRenderer>();
	NameFont->SetFont("굴림");
	NameFont->SetScale(12.0f);
	NameFont->GetTransform()->SetLocalPosition({ 13, -32 });
	NameFont->SetText("히나");
	NameFont->SetColor({ 1.0f, 1.0f, 0.0f, 1.0f });

	std::shared_ptr<GameEngineFontRenderer> NameFont1 = CreateComponent<GameEngineFontRenderer>();
	NameFont1->SetFont("굴림");
	NameFont1->SetScale(12.0f);
	NameFont1->GetTransform()->SetLocalPosition({ 14, -32 });
	NameFont1->SetText("히나");
	NameFont1->SetColor({ 1.0f, 1.0f, 0.0f, 1.0f });

	GetTransform()->SetLocalScale({ -1, 1 });
	GetTransform()->SetLocalPosition({ -541, 244 });
}

void Hina::Update(float _DeltaTime)
{
	TimeCounting();
	OpenWindow();
	TextureUpdate();
}

void Hina::Render(float _DeltaTime) 
{

}

void Hina::OpenWindow()
{
	if (Mouse::GetMouse()->IsDoubleClick() == false)
	{
		return;
	}

	std::shared_ptr<GameEngineCollision> Col = HinaCollision->Collision(static_cast<int>(CollisionOrder::Mouse), ColType::AABBBOX2D, ColType::AABBBOX2D);

	if (Col == nullptr)
	{
		return;
	}

	MyWindow = GetLevel()->CreateActor<NPCWindow>();
	MyWindow->SetNPC("HINASMILE00.PNG", "   히나");
	
	if (UIController::GetUIController()->isQuestInList("HINA0") == true && UIController::GetUIController()->ItemFind("MIRROROFSERA", static_cast<int>(ItemType::Etc)) == -1)
	{
		MyWindow->SetDialogText("세라 언니에게 아직 안 가 보셨어요? 동쪽 언덕에 있을 텐데...\n여기서 가까운 곳이니까 쉽게 찾을 수 있을 거예요.");

		MyWindow->CreateUIButtonList(0);
		MyWindow->SetCloseButton(0, [this] {MyWindow->ButtonsDeath(); MyWindow->Death(); MyWindow = nullptr; });
	}
	else if (UIController::GetUIController()->isQuestInList("HINA0") == true && UIController::GetUIController()->ItemFind("MIRROROFSERA", static_cast<int>(ItemType::Etc)) != -1)
	{
		MyWindow->SetDialogText("앗! 세라 언니의 거울을 가져 오셨군요! 정말 고마워요. \n어디..피부가 상하지는 않았겠지...? 흐음~");

		MyWindow->CreateUIButtonList(0);
		MyWindow->SetNextButton(0);
		MyWindow->SetDialogText(1, "이제 우측으로 가면 다음 장소로 이동할 수 있는\n빛나는 입구를 볼 수 있을 거예요. \n그것을 포탈이라고 부르는 데 그 위에서 방향키 ↑ 를 누르면 \n다음 장소로 이동할 수 있어요. 그럼 잘가요~");
		MyWindow->CreateUIButtonList(1);
		MyWindow->SetCloseButton(1, [this] {MyWindow->ButtonsDeath(); MyWindow->Death(); MyWindow = nullptr; UIController::GetUIController()->DeleteToItemList("MIRROROFSERA", static_cast<int>(ItemType::Etc)); UIController::GetUIController()->QuestClear("HINA0"); });
	}
	else if (UIController::GetUIController()->isQuestInClearList("HINA0") == true)
	{
		MyWindow->SetDialogText("이제 우측으로 가면 다음 장소로 이동할 수 있는\n빛나는 입구를 볼 수 있을 거예요. \n그것을 포탈이라고 부르는 데 그 위에서 방향키 ↑ 를 누르면 \n다음 장소로 이동할 수 있어요. 그럼 잘가요~");

		MyWindow->CreateUIButtonList(0);
		MyWindow->SetCloseButton(0, [this] {MyWindow->ButtonsDeath(); MyWindow->Death(); MyWindow = nullptr; });
	}
	else if(UIController::GetUIController()->isQuestInClearList("HINA0") == false && UIController::GetUIController()->isQuestInList("HINA0") == false)
	{
		MyWindow->SetDialogText("새로운 여행자군요? 아직 많이 낯설죠? \n제가 이것저것 알려 드릴테니 잘 듣고 따라해보세요. \n우선 저희에게 말을 걸기 위해선 \n마우스로 저희들을 더블클릭을 하면 된답니다.\n좌, 우 방향키를 누르면 이동할 수 있구요.\n왼쪽 Alt 키를 누르면 점프하실 수 있어요. ");

		MyWindow->CreateUIButtonList(0);
		MyWindow->SetNextButton(0);

		MyWindow->SetDialogText(1, "아~ 그나저나 햇빛이 너무 따가운 걸요? \n내 백옥같은 피부가 다 상해 버리겠네... 어떻게 하지? \n죄송하지만 바쁘지 않으시다면 \n여기서 멀지 않은 곳에서 빨래를 널고 있는 \n세라 언니에게서 거울 좀 빌려와 주세요.");
		MyWindow->CreateUIButtonList(1);
		
		MyWindow->AddToTextButton("네 가져다 드릴게요.", 1, [this] {MyWindow->ChangeDialog("고맙습니다. 세라 언니는 언덕에서 빨래를 널고 있을 거예요."); UIController::GetUIController()->AddToQuestList("HINA0"); });
		MyWindow->AddToTextButton("싫어요.", 1, [this] {MyWindow->ChangeDialog("제 부탁을 들어주기 싫으신가요? \n흐음~ 마음이 바뀌면 다시 찾아와 주세요."); });
		
		MyWindow->CreateUIButtonList(2);
		MyWindow->SetCloseButton(2, [this] {MyWindow->ButtonsDeath(); MyWindow->Death(); MyWindow = nullptr; });
	}
}

void Hina::TextureUpdate()
{
	if(Status != "CRY")
	{
		std::string TextureName = "HINA" + Status + std::to_string(AniIndex) + ".png";
		HinaRender->SetScaleToTexture(TextureName);
	}
	else
	{
		int Index = AniIndex % 5;
		std::string TextureName = "HINA" + Status + std::to_string(Index) + ".png";
		HinaRender->SetScaleToTexture(TextureName);
	}

	AnimationCount += TimeCount;
	
	if (AnimationCount >= FrameList[Status][AniIndex])
	{
		AniIndex++;
		AnimationCount = 0.0f;

		if (AniIndex >= FrameList[Status].size())
		{
			AniIndex = 0;

			if(Status != "NORMAL")
			{
				Status = "NORMAL";
			}
			else
			{
				StatusUpdate();
			}
		}
	}
}

void Hina::StatusUpdate()
{
	int StatusType = GameEngineRandom::MainRandom.RandomInt(0, 8);
	
	if (StatusType > 4)
	{
		StatusType = 0;
	}

	switch (StatusType)
	{
	case 0:
		Status = "NORMAL";
		break;
	case 1:
		Status = "SMILE0";
		break;
	case 2:
		Status = "SMILE1";
		break;
	case 3:
		Status = "BEWILDERED";
		break;
	case 4:
		Status = "CRY";
		break;
	}
}

void Hina::SetFrameList()
{
	FrameList["NORMAL"].push_back(1.5f);
	FrameList["NORMAL"].push_back(0.1f);
	FrameList["NORMAL"].push_back(0.1f);
	FrameList["NORMAL"].push_back(1.0f);

	FrameList["SMILE0"].push_back(5.0f);

	FrameList["SMILE1"].push_back(5.0f);

	FrameList["BEWILDERED"].push_back(0.15f);
	FrameList["BEWILDERED"].push_back(0.15f);
	FrameList["BEWILDERED"].push_back(0.15f);
	FrameList["BEWILDERED"].push_back(0.15f);
	FrameList["BEWILDERED"].push_back(4.4f);


	for (int i = 0; i < 10; i++) 
	{
		FrameList["CRY"].push_back(0.1f);
		FrameList["CRY"].push_back(0.1f);
		FrameList["CRY"].push_back(0.1f);
		FrameList["CRY"].push_back(0.1f);
		FrameList["CRY"].push_back(0.1f);
	}

}	

void Hina::ActorDeath()
{
	if (MyWindow != nullptr)
	{
		MyWindow->ButtonsDeath();
		MyWindow->Death();
		MyWindow = nullptr;
	}
}