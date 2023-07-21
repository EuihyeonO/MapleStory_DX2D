#include "PrecompileHeader.h"
#include "DarkLord.h"
#include "NPCWindow.h"
#include "Mouse.h"
#include "PlayerValue.h"
#include "UIController.h"

#include <GameEngineCore/GameEngineLevel.h>

DarkLord::DarkLord()
{
}

DarkLord::~DarkLord()
{
}

void DarkLord::Start()
{
	DarkLordRender = CreateComponent<GameEngineSpriteRenderer>();
	DarkLordRender->SetScaleToTexture("DarkLordStand0.png");

	DarkLordCollision = CreateComponent<GameEngineCollision>();
	DarkLordCollision->SetColType(ColType::AABBBOX2D);
	DarkLordCollision->GetTransform()->SetLocalScale({ 40, 90 });
	DarkLordCollision->GetTransform()->SetLocalPosition({ 0, 15 });
}

void DarkLord::Update(float _DeltaTime) 
{
	OpenWindow();

	if (UpdateFunc != nullptr)
	{
		UpdateFunc(_DeltaTime);
	}
}

void DarkLord::Render(float _DeltaTime) 
{

}

void DarkLord::OpenWindow()
{
	if (Mouse::GetMouse()->IsDoubleClick() == false)
	{
		return;
	}

	std::shared_ptr<GameEngineCollision> Col = DarkLordCollision->Collision(static_cast<int>(CollisionOrder::Mouse), ColType::AABBBOX2D, ColType::AABBBOX2D);

	if (Col == nullptr)
	{
		return;
	}

	if (PlayerValue::GetValue()->GetClass() == "BEGINNER" && PlayerValue::GetValue()->GetLevel() >= 10)
	{
		MyWindow = GetLevel()->CreateActor<NPCWindow>();

		MyWindow->SetNPC("DarkLordStand0.PNG", "��ũ�ε�");
		MyWindow->SetNPCPos({ -187, 43 });
		MyWindow->SetNPCNamePos({ -216, -36 });

		MyWindow->SetDialogText("������ �ǰ���� �� ������...");

		MyWindow->CreateUIButtonList(0);
		MyWindow->CreateUIButtonList(1);
		MyWindow->CreateUIButtonList(2);

		MyWindow->SetCloseButton(0, [this] {ActorDeath(); });
		MyWindow->SetCloseButton(2, [this] {ActorDeath(); });
		
		//[����] ������ ��
		MyWindow->AddToTextButton("[����] ������ ��", 0, [this] {MyWindow->ChangeDialog("������ �ǰ� ������? ������, �ƹ��� �� �� �ִ°� �ƴϾ�.\n��� ���� 10�� ���� �ڸ� ������ �� �� ����.\n�����ϴ�, �ʴ� �ڰ��� ����� �� ����. �, ���� ������\n�ǰ� ������?"); });
		MyWindow->AddToTextButton("��. ������ �ǰ� �ͽ��ϴ�.", 1, [this] {MyWindow->ChangeDialog("����. �ʸ� �������� ������������.\n���� ���� ���� �ȴ� �ٴ� ��, �׸�ŭ ���� ���� ���̶�� ��\n�����."); PlayerValue::GetValue()->UpGradeClass(); });
	}
	else if (PlayerValue::GetValue()->GetClass() == "LOG" && PlayerValue::GetValue()->GetLevel() >= 30)
	{
		MyWindow = GetLevel()->CreateActor<NPCWindow>();

		MyWindow->SetNPC("DarkLordStand0.PNG", "��ũ�ε�");
		MyWindow->SetNPCPos({ -187, 43 });
		MyWindow->SetNPCNamePos({ -216, -36 });

		MyWindow->SetDialogText("������ �ǰ���� �� ������...");

		MyWindow->CreateUIButtonList(0);
		MyWindow->CreateUIButtonList(1);
		MyWindow->CreateUIButtonList(2);

		MyWindow->SetCloseButton(0, [this] {ActorDeath(); });
		MyWindow->SetCloseButton(2, [this] { ActorDeath(); });
		
		MyWindow->AddToTextButton("[����] ��ؽ��� ��", 0, [this] {MyWindow->ChangeDialog("��ؽ��� �ǰ� ���� �ǰ�? ��.. ���� ���� �ƴ��ٵ�?\n������ �ڳ׶�� ��ؽ��� �Ǵ°� ������ ���� �� ����.\n�׷� �ٷ� ��ؽ����� �������� ����. �غ�� �Ǿ���?"); });
		MyWindow->AddToTextButton("��. ��ؽ��� �� �غ� �Ǿ����ϴ�.", 1, [this] {MyWindow->ChangeDialog("����.�ڳ״� �������� ��ؽ��̾�. ��ؽ��� �������� ��. \n������, �� ������ ���ڿ��� ����ϴ� ���� �ùٸ� ���� \n�ƴϾ�. �ڽ��� ������ �ִ� ���� ���� �Ͽ� ����ϴ� ��. \n�װ��� �������� �� �̻����� ����� ���̶�� ���� \n����ص�."); PlayerValue::GetValue()->UpGradeClass(); });
	}
	else if (PlayerValue::GetValue()->GetClass() == "ASSASSIN" && PlayerValue::GetValue()->GetLevel() >= 70)
	{
		MyWindow = GetLevel()->CreateActor<NPCWindow>();

		MyWindow->SetNPC("DarkLordStand0.PNG", "��ũ�ε�");
		MyWindow->SetNPCPos({ -187, 43 });
		MyWindow->SetNPCNamePos({ -216, -36 });

		MyWindow->SetDialogText("������ �ǰ���� �� ������...");

		MyWindow->CreateUIButtonList(0);
		MyWindow->CreateUIButtonList(1);
		MyWindow->CreateUIButtonList(2);

		MyWindow->SetCloseButton(0, [this] {ActorDeath(); });
		MyWindow->SetCloseButton(2, [this] { ActorDeath(); });

		MyWindow->AddToTextButton("[����] ����� ��", 0, [this] {MyWindow->ChangeDialog("����� �ǰڴٴ�. ���� �׷��� �������ǰ�?\n�׷�. �ڳ׿��� ���� ����ħ�� ����� ���� ����̾�.\n�׷� �ٷ� ������� �������� ����. �غ�� �Ǿ���?"); });
		MyWindow->AddToTextButton("��. ����� �� �غ� �Ǿ����ϴ�.", 1, [this] {MyWindow->ChangeDialog("�������� ����� ���� �Ȱ� �ɰž�.\n���� ���� ������ �� ��ŭ ���� å���� Ŀ���ٴ� ���� �����.\n����, ���Կ� �ڸ��Ͽ� ������ ������ �ؼ��� �ȵ�.\n���̶� �������� ����� �� �ִ� ���̴�."); PlayerValue::GetValue()->UpGradeClass(); });
	}
	else if (PlayerValue::GetValue()->GetClass() == "HERMIT" && PlayerValue::GetValue()->GetLevel() >= 120)
	{
		MyWindow = GetLevel()->CreateActor<NPCWindow>();

		MyWindow->SetNPC("DarkLordStand0.PNG", "��ũ�ε�");
		MyWindow->SetNPCPos({ -187, 43 });
		MyWindow->SetNPCNamePos({ -216, -36 });

		MyWindow->SetDialogText("������ �ǰ���� �� ������...");

		MyWindow->CreateUIButtonList(0);
		MyWindow->CreateUIButtonList(1);
		MyWindow->CreateUIButtonList(2);

		MyWindow->SetCloseButton(0, [this] {ActorDeath(); });
		MyWindow->SetCloseButton(2, [this] { ActorDeath(); });

		MyWindow->AddToTextButton("[����] ������ ���谡 - ����Ʈ �ε��� ��", 0, [this] {MyWindow->ChangeDialog("����Ʈ �ε尡 �ǰڴٴ�.. �׷�. �ʶ�� ������ �� �˾Ҿ�.\n�Ѹ��� �����ο� ���谡���� ������ �� �غ� �Ǿ���?"); });
		MyWindow->AddToTextButton("��. ����Ʈ �ε尡 �� �غ� �Ǿ����ϴ�.", 1, [this] {MyWindow->ChangeDialog("���� ���԰� ���� ����, ���� �����̶� �Ҹ��� ��.\n�����̶� �¾�� ���� �ƴϾ�. ������� ��������� \n������.. ���̻��� ������ ��� ���� ����. \n���� ���� ���� �����Ӱ� �����ϸ� ��. \n�ٽ� ������ �Ǵ� ���� ���� ����� ����ϰھ�."); PlayerValue::GetValue()->UpGradeClass(); });
	}
	else if (PlayerValue::GetValue()->GetClass() == "NIGHTLORD" && PlayerValue::GetValue()->GetLevel() >= 120)
	{
		MyWindow = GetLevel()->CreateActor<NPCWindow>();

		MyWindow->SetNPC("DarkLordStand0.PNG", "��ũ�ε�");
		MyWindow->SetNPCPos({ -187, 43 });
		MyWindow->SetNPCNamePos({ -216, -36 });

		MyWindow->SetDialogText("������ �ǰ���� �� ������...");

		MyWindow->CreateUIButtonList(0);
		MyWindow->CreateUIButtonList(1);
		MyWindow->CreateUIButtonList(2);

		MyWindow->SetCloseButton(0, [this] {ActorDeath(); });

		MyWindow->AddToTextButton("[����] �Ŵ� ������ ����", 0, [this] 
			{
				MyWindow->ChangeDialog("���� �Ϸ� �ٽ� ���� ã�ƿ°���?"); 	

				MyWindow->AddToTextButton("���񿡰� �����ϰ� �ͽ��ϴ�.", 1, [this]
				{
					MyWindow->CreateUIButtonList(3);

					MyWindow->ChangeDialog("�����̶�.. ���� ������ ���� �� ���� �ִµ�, ���� �����ڳ�?");
					MyWindow->AddToTextButton("��. �����ϰڽ��ϴ�.", 2, [this] {MyWindow->ChangeDialog("�׷�. �״��� ���� �׷��ٸ�, ������ ��� �����ֵ��� ����."); });

					MyWindow->SetCloseButton(3, [this] { ChangeLevel("Level_AlterOfZakumEnt"); });
				});

				MyWindow->AddToTextButton("�ƹ� �͵� �ƴմϴ�.", 1, [this]
				{
					MyWindow->ChangeDialog("�׷�. ��Ź�� ���� �ִٸ�, ������ �ٽ� ã�ƿ͵� ����.");
					MyWindow->SetCloseButton(2, [this] { ActorDeath(); });
				}); 
			});

		MyWindow->AddToTextButton("��� �ް� �ͽ��ϴ�.", 0, [this]
			{
				MyWindow->ChangeDialog("�������� ���ؼ� ���� ������ �ʿ��� ������.\n������ â�� Ȯ���� ��. �Ƴ��� ��� �־�ξ����ϱ�.");
				
				std::shared_ptr<ItemInfo> NewItem1 = std::make_shared<ItemInfo>();
				NewItem1->EquipType = static_cast<int>(EquipType::Weapon);
				NewItem1->ItemName = "MAPLETHRONED";
				NewItem1->Class = static_cast<int>(PlayerClass::Log);
				NewItem1->Att = 30;

				UIController::GetUIController()->AddToItemList(NewItem1, static_cast<int>(ItemType::Equip));

				std::shared_ptr<ItemInfo> NewItem2 = std::make_shared<ItemInfo>();
				NewItem2->EquipType = static_cast<int>(EquipType::OnePiece);
				NewItem2->ItemName = "BLUEGOWN";

				UIController::GetUIController()->AddToItemList(NewItem2, static_cast<int>(ItemType::Equip));

				std::shared_ptr<ItemInfo> NewItem3 = std::make_shared<ItemInfo>();
				NewItem3->EquipType = static_cast<int>(EquipType::Shoes);
				NewItem3->ItemName = "EISEN";

				UIController::GetUIController()->AddToItemList(NewItem3, static_cast<int>(ItemType::Equip));


				std::shared_ptr<ItemInfo> NewItem4 = std::make_shared<ItemInfo>();
				NewItem4->EquipType = static_cast<int>(EquipType::Cap);
				NewItem4->ItemName = "RICEHAT";

				UIController::GetUIController()->AddToItemList(NewItem4, static_cast<int>(ItemType::Equip));

				MyWindow->SetCloseButton(1, [this] {ActorDeath(); });
			});
	}
	else
	{
		MyWindow = GetLevel()->CreateActor<NPCWindow>();

		MyWindow->SetNPC("DarkLordStand0.PNG", "��ũ�ε�");
		MyWindow->SetNPCPos({ -187, 43 });
		MyWindow->SetNPCNamePos({ -216, -36 });

		MyWindow->SetDialogText("������ �ǰ���� �� ������...");

		MyWindow->CreateUIButtonList(0);
		MyWindow->SetCloseButton(0, [this] {ActorDeath();});
	}
}

void DarkLord::ActorDeath()
{
	if(MyWindow != nullptr)
	{
		MyWindow->ButtonsDeath();
		MyWindow->Death();
		MyWindow = nullptr;
	}
}

void DarkLord::ChangeLevel(const std::string_view& _LevelName)
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