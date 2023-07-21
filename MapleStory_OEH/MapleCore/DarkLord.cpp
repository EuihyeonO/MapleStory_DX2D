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

		MyWindow->SetNPC("DarkLordStand0.PNG", "다크로드");
		MyWindow->SetNPCPos({ -187, 43 });
		MyWindow->SetNPCNamePos({ -216, -36 });

		MyWindow->SetDialogText("도적이 되고싶은 자 나에게...");

		MyWindow->CreateUIButtonList(0);
		MyWindow->CreateUIButtonList(1);
		MyWindow->CreateUIButtonList(2);

		MyWindow->SetCloseButton(0, [this] {ActorDeath(); });
		MyWindow->SetCloseButton(2, [this] {ActorDeath(); });
		
		//[전직] 도적의 길
		MyWindow->AddToTextButton("[전직] 도적의 길", 0, [this] {MyWindow->ChangeDialog("도적이 되고 싶은가? 하지만, 아무나 할 수 있는건 아니야.\n적어도 레벨 10이 넘은 자만 도적이 될 수 있지.\n보아하니, 너는 자격이 충분한 것 같군. 어때, 정말 도적이\n되고 싶은가?"); });
		MyWindow->AddToTextButton("네. 도적이 되고 싶습니다.", 1, [this] {MyWindow->ChangeDialog("좋아. 너를 도적으로 전직시켜주지.\n나와 같은 길을 걷는 다는 건, 그만큼 쉽지 않은 길이라는 걸\n명심해."); PlayerValue::GetValue()->UpGradeClass(); });
	}
	else if (PlayerValue::GetValue()->GetClass() == "LOG" && PlayerValue::GetValue()->GetLevel() >= 30)
	{
		MyWindow = GetLevel()->CreateActor<NPCWindow>();

		MyWindow->SetNPC("DarkLordStand0.PNG", "다크로드");
		MyWindow->SetNPCPos({ -187, 43 });
		MyWindow->SetNPCNamePos({ -216, -36 });

		MyWindow->SetDialogText("도적이 되고싶은 자 나에게...");

		MyWindow->CreateUIButtonList(0);
		MyWindow->CreateUIButtonList(1);
		MyWindow->CreateUIButtonList(2);

		MyWindow->SetCloseButton(0, [this] {ActorDeath(); });
		MyWindow->SetCloseButton(2, [this] { ActorDeath(); });
		
		MyWindow->AddToTextButton("[전직] 어쌔신의 길", 0, [this] {MyWindow->ChangeDialog("어쌔신이 되고 싶은 건가? 후.. 쉬운 길이 아닐텐데?\n하지만 자네라면 어쌔신이 되는게 나쁘지 않을 것 같아.\n그럼 바로 어쌔신으로 전직시켜 주지. 준비는 되었나?"); });
		MyWindow->AddToTextButton("네. 어쌔신이 될 준비가 되었습니다.", 1, [this] {MyWindow->ChangeDialog("좋아.자네는 이제부터 어쌔신이야. 어쌔신은 강해져야 해. \n하지만, 그 강함을 약자에게 사용하는 것은 올바른 길이 \n아니야. 자신이 가지고 있는 힘을 옳은 일에 사용하는 것. \n그것은 강해지는 일 이상으로 어려운 일이라는 것을 \n명심해둬."); PlayerValue::GetValue()->UpGradeClass(); });
	}
	else if (PlayerValue::GetValue()->GetClass() == "ASSASSIN" && PlayerValue::GetValue()->GetLevel() >= 70)
	{
		MyWindow = GetLevel()->CreateActor<NPCWindow>();

		MyWindow->SetNPC("DarkLordStand0.PNG", "다크로드");
		MyWindow->SetNPCPos({ -187, 43 });
		MyWindow->SetNPCNamePos({ -216, -36 });

		MyWindow->SetDialogText("도적이 되고싶은 자 나에게...");

		MyWindow->CreateUIButtonList(0);
		MyWindow->CreateUIButtonList(1);
		MyWindow->CreateUIButtonList(2);

		MyWindow->SetCloseButton(0, [this] {ActorDeath(); });
		MyWindow->SetCloseButton(2, [this] { ActorDeath(); });

		MyWindow->AddToTextButton("[전직] 허밋의 길", 0, [this] {MyWindow->ChangeDialog("허밋이 되겠다니. 벌써 그렇게 강해진건가?\n그래. 자네에겐 나의 가르침이 헛되지 않은 모양이야.\n그럼 바로 허밋으로 전직시켜 주지. 준비는 되었나?"); });
		MyWindow->AddToTextButton("네. 허밋이 될 준비가 되었습니다.", 1, [this] {MyWindow->ChangeDialog("이제부터 허밋의 길을 걷게 될거야.\n강한 힘을 가지게 된 만큼 너의 책임이 커진다는 것을 기억해.\n또한, 강함에 자만하여 수련을 게을리 해서도 안돼.\n힘이란 언제든지 사라질 수 있는 것이니."); PlayerValue::GetValue()->UpGradeClass(); });
	}
	else if (PlayerValue::GetValue()->GetClass() == "HERMIT" && PlayerValue::GetValue()->GetLevel() >= 120)
	{
		MyWindow = GetLevel()->CreateActor<NPCWindow>();

		MyWindow->SetNPC("DarkLordStand0.PNG", "다크로드");
		MyWindow->SetNPCPos({ -187, 43 });
		MyWindow->SetNPCNamePos({ -216, -36 });

		MyWindow->SetDialogText("도적이 되고싶은 자 나에게...");

		MyWindow->CreateUIButtonList(0);
		MyWindow->CreateUIButtonList(1);
		MyWindow->CreateUIButtonList(2);

		MyWindow->SetCloseButton(0, [this] {ActorDeath(); });
		MyWindow->SetCloseButton(2, [this] { ActorDeath(); });

		MyWindow->AddToTextButton("[전직] 진정한 모험가 - 나이트 로드의 길", 0, [this] {MyWindow->ChangeDialog("나이트 로드가 되겠다니.. 그래. 너라면 도달할 줄 알았어.\n한명의 자유로운 모험가에서 영웅이 될 준비가 되었나?"); });
		MyWindow->AddToTextButton("네. 나이트 로드가 될 준비가 되었습니다.", 1, [this] {MyWindow->ChangeDialog("너의 강함과 선한 의지, 용기는 영웅이라 불릴만 해.\n영웅이란 태어나는 것이 아니야. 노력으로 만들어지는 \n것이지.. 더이상은 나에게 배울 것이 없어. \n이젠 너의 길을 자유롭게 모험하면 돼. \n다시 만나게 되는 날에 너의 모습을 기대하겠어."); PlayerValue::GetValue()->UpGradeClass(); });
	}
	else if (PlayerValue::GetValue()->GetClass() == "NIGHTLORD" && PlayerValue::GetValue()->GetLevel() >= 120)
	{
		MyWindow = GetLevel()->CreateActor<NPCWindow>();

		MyWindow->SetNPC("DarkLordStand0.PNG", "다크로드");
		MyWindow->SetNPCPos({ -187, 43 });
		MyWindow->SetNPCNamePos({ -216, -36 });

		MyWindow->SetDialogText("도적이 되고싶은 자 나에게...");

		MyWindow->CreateUIButtonList(0);
		MyWindow->CreateUIButtonList(1);
		MyWindow->CreateUIButtonList(2);

		MyWindow->SetCloseButton(0, [this] {ActorDeath(); });

		MyWindow->AddToTextButton("[자쿰] 거대 석상의 공포", 0, [this] 
			{
				MyWindow->ChangeDialog("무슨 일로 다시 나를 찾아온거지?"); 	

				MyWindow->AddToTextButton("자쿰에게 도전하고 싶습니다.", 1, [this]
				{
					MyWindow->CreateUIButtonList(3);

					MyWindow->ChangeDialog("자쿰이라.. 정말 위험한 길이 될 수도 있는데, 정말 괜찮겠나?");
					MyWindow->AddToTextButton("네. 도전하겠습니다.", 2, [this] {MyWindow->ChangeDialog("그래. 그대의 뜻이 그렇다면, 자쿰의 길로 보내주도록 하지."); });

					MyWindow->SetCloseButton(3, [this] { ChangeLevel("Level_AlterOfZakumEnt"); });
				});

				MyWindow->AddToTextButton("아무 것도 아닙니다.", 1, [this]
				{
					MyWindow->ChangeDialog("그래. 부탁할 것이 있다면, 언제든 다시 찾아와도 좋아.");
					MyWindow->SetCloseButton(2, [this] { ActorDeath(); });
				}); 
			});

		MyWindow->AddToTextButton("장비를 받고 싶습니다.", 0, [this]
			{
				MyWindow->ChangeDialog("강해지기 위해선 좋은 장비또한 필요한 법이지.\n아이템 창을 확인해 봐. 아끼는 장비를 넣어두었으니까.");
				
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

		MyWindow->SetNPC("DarkLordStand0.PNG", "다크로드");
		MyWindow->SetNPCPos({ -187, 43 });
		MyWindow->SetNPCNamePos({ -216, -36 });

		MyWindow->SetDialogText("도적이 되고싶은 자 나에게...");

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