#include "PrecompileHeader.h"
#include "Shanks.h"
#include "Mouse.h"
#include "NPCWindow.h"

#include <GameEngineCore/GameEngineLevel.h>

Shanks::Shanks()
{
}

Shanks::~Shanks()
{
}

void Shanks::Start()
{
	ShanksRender = CreateComponent<GameEngineSpriteRenderer>();
	ShanksRender->SetScaleToTexture("ShanksStand.png");

	ShanksCollision = CreateComponent<GameEngineCollision>();
	ShanksCollision->GetTransform()->SetLocalScale({ 60, 90 });
	ShanksCollision->SetColType(ColType::AABBBOX2D);

	std::shared_ptr<GameEngineSpriteRenderer> NameCard = CreateComponent<GameEngineSpriteRenderer>();
	NameCard->SetScaleToTexture("NameBackGround.png");
	NameCard->GetTransform()->SetLocalPosition({ 0, -50 });
	NameCard->GetTransform()->SetLocalScale({ 40, 16 });
	NameCard->ColorOptionValue.MulColor.a = 0.7f;

	std::shared_ptr<GameEngineFontRenderer> NameFont = CreateComponent<GameEngineFontRenderer>();
	NameFont->SetFont("����");
	NameFont->SetScale(12.0f);
	NameFont->GetTransform()->SetLocalPosition({ -18, -43 });
	NameFont->SetText("��ũ��");
	NameFont->SetColor({ 1.0f, 1.0f, 0.0f, 1.0f });
}

void Shanks::Update(float _DeltaTime)
{
	OpenWindow();

	if (UpdateFunc != nullptr)
	{
		UpdateFunc(_DeltaTime);
	}
}

void Shanks::Render(float _DeltaTime)
{

}

void Shanks::OpenWindow()
{
	if (Mouse::GetMouse()->IsDoubleClick() == false)
	{
		return;
	}

	std::shared_ptr<GameEngineCollision> Col = ShanksCollision->Collision(static_cast<int>(CollisionOrder::Mouse), ColType::AABBBOX2D, ColType::AABBBOX2D);

	if (Col == nullptr)
	{
		return;
	}

	MyWindow = GetLevel()->CreateActor<NPCWindow>();

	MyWindow->SetNPC("SHANKSSTAND.PNG", "��ũ��");
	MyWindow->SetDialogText(" ������ ������ ������ ����� ������ �ʹٸ�, \n ������ ������ �����ָ� ��. \n �� �Ŵ��� �谡 �ʸ� ������ ����� ������ ���״�!");

	std::function<void()> ButtonFunc = std::bind(&NPCWindow::ChangeDialog, MyWindow, " �ʴ� ������ �ǰ� ���� ����̱���?\n �׷��ٸ�, �ʸ� Ŀ�׽�Ƽ�� �ٷ� �����ٰ�!\n �ʶ�� �и� ���� ������ �ɰž�!");
	MyWindow->AddToTextButton(" �Ѹ����� ����� ���� �;��.", 0, ButtonFunc);

	MyWindow->AddToTextButton(" �ѻ�콺�丮�� �ӹ��� �;��.", 0, std::bind([this] {MyWindow->ButtonsDeath(); MyWindow->Death(); MyWindow = nullptr; }));

	MyWindow->CreateUIButtonList(0);
	MyWindow->SetCloseButton(0, [this] {MyWindow->ButtonsDeath(); MyWindow->Death(); MyWindow = nullptr; });

	MyWindow->CreateUIButtonList(1);
	std::function<void()> ButtonFunc1 = std::bind(&Shanks::ChangeLevel, DynamicThis<Shanks>(), "Level_KerningCity");
	MyWindow->AddToTextButton(" ��Ŀ�׽�Ƽ�� �����ּ���.", 1, ButtonFunc1);

}

void Shanks::ChangeLevel(const std::string_view& _LevelName)
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