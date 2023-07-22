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
	NameFont->SetFont("����");
	NameFont->SetScale(12.0f);
	NameFont->GetTransform()->SetLocalPosition({ 13, -32 });
	NameFont->SetText("����");
	NameFont->SetColor({ 1.0f, 1.0f, 0.0f, 1.0f });

	std::shared_ptr<GameEngineFontRenderer> NameFont1 = CreateComponent<GameEngineFontRenderer>();
	NameFont1->SetFont("����");
	NameFont1->SetScale(12.0f);
	NameFont1->GetTransform()->SetLocalPosition({ 14, -32 });
	NameFont1->SetText("����");
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
	MyWindow->SetNPC("HINASMILE00.PNG", "   ����");
	
	if (UIController::GetUIController()->isQuestInList("HINA0") == true && UIController::GetUIController()->ItemFind("MIRROROFSERA", static_cast<int>(ItemType::Etc)) == -1)
	{
		MyWindow->SetDialogText("���� ��Ͽ��� ���� �� �� ���̾��? ���� ����� ���� �ٵ�...\n���⼭ ����� ���̴ϱ� ���� ã�� �� ���� �ſ���.");

		MyWindow->CreateUIButtonList(0);
		MyWindow->SetCloseButton(0, [this] {MyWindow->ButtonsDeath(); MyWindow->Death(); MyWindow = nullptr; });
	}
	else if (UIController::GetUIController()->isQuestInList("HINA0") == true && UIController::GetUIController()->ItemFind("MIRROROFSERA", static_cast<int>(ItemType::Etc)) != -1)
	{
		MyWindow->SetDialogText("��! ���� ����� �ſ��� ���� ���̱���! ���� ������. \n���..�Ǻΰ� �������� �ʾҰ���...? ����~");

		MyWindow->CreateUIButtonList(0);
		MyWindow->SetNextButton(0);
		MyWindow->SetDialogText(1, "���� �������� ���� ���� ��ҷ� �̵��� �� �ִ�\n������ �Ա��� �� �� ���� �ſ���. \n�װ��� ��Ż�̶�� �θ��� �� �� ������ ����Ű �� �� ������ \n���� ��ҷ� �̵��� �� �־��. �׷� �߰���~");
		MyWindow->CreateUIButtonList(1);
		MyWindow->SetCloseButton(1, [this] {MyWindow->ButtonsDeath(); MyWindow->Death(); MyWindow = nullptr; UIController::GetUIController()->DeleteToItemList("MIRROROFSERA", static_cast<int>(ItemType::Etc)); UIController::GetUIController()->QuestClear("HINA0"); });
	}
	else if (UIController::GetUIController()->isQuestInClearList("HINA0") == true)
	{
		MyWindow->SetDialogText("���� �������� ���� ���� ��ҷ� �̵��� �� �ִ�\n������ �Ա��� �� �� ���� �ſ���. \n�װ��� ��Ż�̶�� �θ��� �� �� ������ ����Ű �� �� ������ \n���� ��ҷ� �̵��� �� �־��. �׷� �߰���~");

		MyWindow->CreateUIButtonList(0);
		MyWindow->SetCloseButton(0, [this] {MyWindow->ButtonsDeath(); MyWindow->Death(); MyWindow = nullptr; });
	}
	else if(UIController::GetUIController()->isQuestInClearList("HINA0") == false && UIController::GetUIController()->isQuestInList("HINA0") == false)
	{
		MyWindow->SetDialogText("���ο� �����ڱ���? ���� ���� ������? \n���� �̰����� �˷� �帱�״� �� ��� �����غ�����. \n�켱 ���񿡰� ���� �ɱ� ���ؼ� \n���콺�� ������� ����Ŭ���� �ϸ� �ȴ�ϴ�.\n��, �� ����Ű�� ������ �̵��� �� �ֱ���.\n���� Alt Ű�� ������ �����Ͻ� �� �־��. ");

		MyWindow->CreateUIButtonList(0);
		MyWindow->SetNextButton(0);

		MyWindow->SetDialogText(1, "��~ �׳����� �޺��� �ʹ� ������ �ɿ�? \n�� ������� �Ǻΰ� �� ���� �����ڳ�... ��� ����? \n�˼������� �ٻ��� �����ôٸ� \n���⼭ ���� ���� ������ ������ �ΰ� �ִ� \n���� ��Ͽ��Լ� �ſ� �� ������ �ּ���.");
		MyWindow->CreateUIButtonList(1);
		
		MyWindow->AddToTextButton("�� ������ �帱�Կ�.", 1, [this] {MyWindow->ChangeDialog("�����ϴ�. ���� ��ϴ� ������� ������ �ΰ� ���� �ſ���."); UIController::GetUIController()->AddToQuestList("HINA0"); });
		MyWindow->AddToTextButton("�Ⱦ��.", 1, [this] {MyWindow->ChangeDialog("�� ��Ź�� ����ֱ� �����Ű���? \n����~ ������ �ٲ�� �ٽ� ã�ƿ� �ּ���."); });
		
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