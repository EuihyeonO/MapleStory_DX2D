#include "PrecompileHeader.h"
#include "SkillList.h"
#include "Mouse.h"
#include "QuickSlot.h"
#include "Player.h"
#include "UIController.h"
#include "ContentFontRenderer.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineLevel.h>

std::shared_ptr<GameEngineUIRenderer> SkillList::SkillIcon::IconCopy = nullptr;
std::function<void(std::shared_ptr<class Player>)> SkillList::SkillIcon::FunctionCopy = nullptr;

SkillList::SkillList()
{
}

SkillList::~SkillList()
{
}

void SkillList::Start()
{
	SkillIcon::IconCopy = nullptr;

	for (int i = 0; i < 5; i++)
	{
		SkillVector[i].reserve(4);
	}

	InsertSkillToList(0, "FlashJump");
	InsertSkillToList(1, "LuckySeven");
	InsertSkillToList(1, "KeenEyes");
	InsertSkillToList(2, "Haste");
	InsertSkillToList(2, "JavelinBooster");
	InsertSkillToList(3, "ShadowPartner");
	InsertSkillToList(3, "Avenger");
	InsertSkillToList(4, "HeroesOfMaple");
	InsertSkillToList(4, "TripleThrow");
}

void SkillList::Update(float _DeltaTime) 
{	
	if (GameEngineInput::IsDown("LClick") == true)
	{
		SkillCopy();
	}

	ColPosUpdate();
}

void SkillList::Render(float _DeltaTime) 
{
}

void SkillList::InsertSkillToList(int _Index, const std::string_view& _SkillName, bool _isPassive)
{
	std::shared_ptr<SkillIcon> NewSkill = GetLevel()->CreateActor<SkillIcon>(static_cast<int>(RenderOrder::Mouse));

	NewSkill->SkillName = _SkillName.data();
	NewSkill->isPassive = _isPassive;

	NewSkill->SkillBackGround = CreateComponent<GameEngineUIRenderer>();
	NewSkill->SkillBackGround->SetScaleToTexture("SkillBackGround.png");
	NewSkill->SkillBackGround->GetTransform()->SetLocalPosition({ -10, 0 });
	NewSkill->SkillBackGround->Off();

	NewSkill->IconRender = CreateComponent<GameEngineUIRenderer>();
	NewSkill->IconRender->SetScaleToTexture(NewSkill->SkillName + "Icon.png");
	NewSkill->IconRender->GetTransform()->SetLocalPosition(NewSkill->SkillBackGround->GetTransform()->GetLocalPosition() - float4{ 53, 0 });
	NewSkill->IconRender->Off();

	TransformData IconData = NewSkill->IconRender->GetTransform()->GetTransDataRef();

	NewSkill->IconCollision = CreateComponent<GameEngineCollision>(static_cast<int>(CollisionOrder::SkillMoveIcon));
	NewSkill->IconCollision->GetTransform()->SetLocalScale(IconData.LocalScale);
	NewSkill->IconCollision->GetTransform()->SetLocalPosition(IconData.LocalPosition);
	NewSkill->IconCollision->Off();

	NewSkill->SkillNameFont = CreateComponent<ContentFontRenderer>();
	NewSkill->SkillNameFont->SetFont("굴림");
	NewSkill->SkillNameFont->SetScale(12);
	NewSkill->SkillNameFont->SetColor({ 0.0f, 0.0f, 0.0f, 1.0f });
	NewSkill->SkillNameFont->Off();

	NewSkill->SkillLv = CreateComponent<ContentFontRenderer>();
	NewSkill->SkillLv->SetFont("굴림");
	NewSkill->SkillLv->SetScale(12);
	NewSkill->SkillLv->SetColor({ 0.0f, 0.0f, 0.0f, 1.0f });
	NewSkill->SkillLv->Off();
	
	NewSkill->LvUpBt = GetLevel()->CreateActor<ContentButton>();
	NewSkill->LvUpBt->SetReleaseTexture("LvUpRelease.png");
	NewSkill->LvUpBt->SetHoverTexture("LvUpHover.png");
	NewSkill->LvUpBt->SetPressTexture("LvUpPress.png");
	NewSkill->LvUpBt->SetAllScale({12, 12});
	NewSkill->LvUpBt->Off();

	SetSkillIcon(NewSkill);

	SkillVector[_Index].push_back(NewSkill);
}

void SkillList::IndexSkillOn(int _Index)
{
	size_t Size = SkillVector[_Index].size();

	for(size_t i = 0; i < Size; i++)
	{
		SkillVector[_Index][i]->SkillBackGround->On();
		SkillVector[_Index][i]->IconRender->On();
		SkillVector[_Index][i]->SkillNameFont->On();
		SkillVector[_Index][i]->SkillLv->On();
		SkillVector[_Index][i]->LvUpBt->On();
		
		if(SkillVector[_Index][i]->isPassive == false)
		{
			SkillVector[_Index][i]->IconCollision->On();
		}
	}

	CurIndex = _Index;
}

void SkillList::IndexSkillOff(int _Index)
{
	size_t Size = SkillVector[_Index].size();

	for (size_t i = 0; i < Size; i++)
	{
		SkillVector[_Index][i]->SkillBackGround->Off();
		SkillVector[_Index][i]->IconRender->Off();
		SkillVector[_Index][i]->IconCollision->Off();
		SkillVector[_Index][i]->SkillNameFont->Off();
		SkillVector[_Index][i]->SkillLv->Off();
		SkillVector[_Index][i]->LvUpBt->Off();
	}
}

void SkillList::SortSkillList(int _Index, float4 _Pos)
{
	size_t Size = SkillVector[_Index].size();
	
	for (size_t i = 0; i < Size; i++)
	{
		SkillVector[_Index][i]->SkillBackGround->GetTransform()->SetLocalPosition(_Pos + float4{ -10, -static_cast<float>(i * 40) });
		float4 BgPos = SkillVector[_Index][i]->SkillBackGround->GetTransform()->GetLocalPosition();

		SkillVector[_Index][i]->IconRender->GetTransform()->SetLocalPosition(BgPos - float4{ 53, 0 });
		SkillVector[_Index][i]->IconCollision ->GetTransform()->SetLocalPosition(BgPos - float4{ 53, 0 });
		SkillVector[_Index][i]->SkillNameFont->GetTransform()->SetLocalPosition(BgPos - float4{ 30, -17 });
		SkillVector[_Index][i]->SkillLv->GetTransform()->SetLocalPosition(BgPos - float4{ 30, 1 });
		SkillVector[_Index][i]->LvUpBt->SetAllPos(BgPos - float4{ -60, 9 });
	}
}

std::shared_ptr<GameEngineCollision> SkillList::CollisionCheck()
{
	std::shared_ptr<GameEngineCollision> CurMouseCollision = Mouse::GetMouse()->GetMouseCollision();
	std::shared_ptr<GameEngineCollision> Col = CurMouseCollision->Collision(static_cast<int>(CollisionOrder::SkillMoveIcon), ColType::AABBBOX2D, ColType::AABBBOX2D);

	if (Col == nullptr)
	{
		return Col;
	}

	else return Col;
}

std::shared_ptr<GameEngineCollision> SkillList::CollisionCheckToQuickSlot()
{
	std::shared_ptr<GameEngineCollision> CurMouseCollision = Mouse::GetMouse()->GetMouseCollision();
	std::shared_ptr<GameEngineCollision> Col = CurMouseCollision->Collision(static_cast<int>(CollisionOrder::QuickSlotSkill), ColType::AABBBOX2D, ColType::AABBBOX2D);

	if (Col == nullptr)
	{
		return Col;
	}

	else return Col;
}

std::shared_ptr<SkillList::SkillIcon> SkillList::FindParantOfCol(std::shared_ptr<GameEngineCollision> _Col)
{
	if (_Col == nullptr)
	{
		return nullptr;
	}

	std::map<int, std::vector<std::shared_ptr<SkillIcon>>>::iterator Start = SkillVector.begin();
	std::map<int, std::vector<std::shared_ptr<SkillIcon>>>::iterator End = SkillVector.end();

	for (; Start != End; Start++)
	{
		for (int i = 0; i < Start->second.size(); i++)
		{
			if (Start->second[i]->IconCollision == _Col)
			{
				return Start->second[i];
			}
		}
	}

	return nullptr;
}

void SkillList::SkillCopy()
{
	if (SkillIcon::IconCopy != nullptr)
	{
		std::shared_ptr<GameEngineCollision> Col = CollisionCheckToQuickSlot();
		
		if(Col == nullptr)
		{
			SkillIcon::IconCopy->Death();
			SkillIcon::IconCopy = nullptr;
			return;
		}

		else
		{
			Col->GetActor()->DynamicThis<QuickSlot>()->GetSlotFunc(Col)(*UIController::GetUIController(), SkillIcon::IconCopy->GetTexName(), SkillIcon::FunctionCopy);
			
			SkillIcon::IconCopy->Death();
			SkillIcon::FunctionCopy = nullptr;
			SkillIcon::IconCopy = nullptr;
		}
	}
	else
	{
		SkillCopy(FindParantOfCol(CollisionCheck()));
	}
}

void SkillList::SkillCopy(std::shared_ptr<SkillList::SkillIcon> _SkillIcon)
{
	if (_SkillIcon == nullptr)
	{
		return;
	}

	SkillIcon::IconCopy = CreateComponent<GameEngineUIRenderer>();
	SkillIcon::IconCopy->SetScaleToTexture(_SkillIcon->SkillName + "Icon.png");
	SkillIcon::IconCopy->GetTransform()->SetParent(Mouse::GetMouse()->GetTransform());
	SkillIcon::IconCopy->GetTransform()->SetLocalPosition({ -12, 12, 1});
	SkillIcon::IconCopy->ColorOptionValue.MulColor = { 1, 1, 1, 0.8f };

	SkillIcon::FunctionCopy = _SkillIcon->SkillFunc;
}

void SkillList::ColPosUpdate()
{
	float4 CamPos = GetLevel()->GetMainCamera()->GetTransform()->GetLocalPosition();

	for (int i = 0; i < SkillVector[CurIndex].size(); i++)
	{
		if (SkillVector[CurIndex][i] != nullptr && SkillVector[CurIndex][i]->IconCollision != nullptr && SkillVector[CurIndex][i]->IconCollision->IsUpdate() == true)
		{
			SkillVector[CurIndex][i]->IconCollision->GetTransform()->SetLocalPosition(CamPos + SkillVector[CurIndex][i]->SkillBackGround->GetTransform()->GetLocalPosition() - float4{ 53, 0 });
		}
	}
}

void SkillList::SetSkillIcon(std::shared_ptr<SkillList::SkillIcon> _SkillIcon)
{
	if (_SkillIcon == nullptr)
	{
		return;
	}

	PlayerValue* Value = PlayerValue::GetValue();

	std::weak_ptr<SkillIcon> Weak_SkillIcon = _SkillIcon;

	if (Weak_SkillIcon.lock()->SkillName == "Haste")
	{
		Weak_SkillIcon.lock()->SkillFunc = &Player::Haste;
		Weak_SkillIcon.lock()->SkillNameFont->SetText("헤이스트");
		Weak_SkillIcon.lock()->SkillLv->SetText(std::to_string(Value->GetHasteLv()));
		
		if (Value->GetHasteLv() >= 20 || Value->GetSkillPoint() <= 0)
		{
			Weak_SkillIcon.lock()->LvUpBt->SetAllTexture("LvUpDisable.png");
		};

		Weak_SkillIcon.lock()->LvUpBt->SetEvent([=, this] {if (Value->GetHasteLv() < 20 && Value->GetSkillPoint() > 0) { Value->HasteLvUp(); } if(Value->GetHasteLv() == 20){ Weak_SkillIcon.lock()->LvUpBt->SetAllTexture("LvUpDisable.png"); } Weak_SkillIcon.lock()->SkillLv->SetText(std::to_string(Value->GetHasteLv())); });
		Weak_SkillIcon.lock()->LvUpBt->SetPressEvent([=, this] {if (Value->GetHasteLv() < 20 && Value->GetSkillPoint() > 0) { Value->HasteLvUp(); } if(Value->GetHasteLv() == 20){ Weak_SkillIcon.lock()->LvUpBt->SetAllTexture("LvUpDisable.png"); } Weak_SkillIcon.lock()->SkillLv->SetText(std::to_string(Value->GetHasteLv())); });
		Weak_SkillIcon.lock()->LvUpBt->SetPressStartTime(0.3f);
	}
	else if (Weak_SkillIcon.lock()->SkillName == "LuckySeven")
	{
		Weak_SkillIcon.lock()->SkillFunc = &Player::LuckySeven;
		Weak_SkillIcon.lock()->SkillNameFont->SetText("럭키 세븐");
		Weak_SkillIcon.lock()->SkillLv->SetText(std::to_string(Value->GetLuckySevenLv()));
		
		if (Value->GetLuckySevenLv() >= 20 || Value->GetSkillPoint() <= 0)
		{
			Weak_SkillIcon.lock()->LvUpBt->SetAllTexture("LvUpDisable.png");
		};

		Weak_SkillIcon.lock()->LvUpBt->SetEvent([=, this] {if (Value->GetLuckySevenLv() < 20 && Value->GetSkillPoint() > 0) { Value->LuckySevenLvUp(); } if (Value->GetLuckySevenLv() == 20) { Weak_SkillIcon.lock()->LvUpBt->SetAllTexture("LvUpDisable.png"); } Weak_SkillIcon.lock()->SkillLv->SetText(std::to_string(Value->GetLuckySevenLv())); });
		Weak_SkillIcon.lock()->LvUpBt->SetPressEvent([=, this] {if (Value->GetLuckySevenLv() < 20 && Value->GetSkillPoint() > 0) { Value->LuckySevenLvUp(); } if (Value->GetLuckySevenLv() == 20) { Weak_SkillIcon.lock()->LvUpBt->SetAllTexture("LvUpDisable.png"); } Weak_SkillIcon.lock()->SkillLv->SetText(std::to_string(Value->GetLuckySevenLv())); });
		Weak_SkillIcon.lock()->LvUpBt->SetPressStartTime(0.3f);
	}
	else if (Weak_SkillIcon.lock()->SkillName == "TripleThrow")
	{
		Weak_SkillIcon.lock()->SkillFunc = &Player::TripleThrow;
		Weak_SkillIcon.lock()->SkillNameFont->SetText("트리플 스로우");
		Weak_SkillIcon.lock()->SkillLv->SetText(std::to_string(Value->GetTripleThrowLv()));

		if (Value->GetTripleThrowLv() >= 20 || Value->GetSkillPoint() <= 0)
		{
			Weak_SkillIcon.lock()->LvUpBt->SetAllTexture("LvUpDisable.png");
		};

		Weak_SkillIcon.lock()->LvUpBt->SetEvent([=, this] {if (Value->GetTripleThrowLv() < 20 && Value->GetSkillPoint() > 0) { Value->TripleThrowLvUp(); } if (Value->GetTripleThrowLv() == 20) { Weak_SkillIcon.lock()->LvUpBt->SetAllTexture("LvUpDisable.png"); } Weak_SkillIcon.lock()->SkillLv->SetText(std::to_string(Value->GetTripleThrowLv())); });
		Weak_SkillIcon.lock()->LvUpBt->SetPressEvent([=, this] {if (Value->GetTripleThrowLv() < 20 && Value->GetSkillPoint() > 0) { Value->TripleThrowLvUp(); } if (Value->GetTripleThrowLv() == 20) { Weak_SkillIcon.lock()->LvUpBt->SetAllTexture("LvUpDisable.png"); } Weak_SkillIcon.lock()->SkillLv->SetText(std::to_string(Value->GetTripleThrowLv())); });
		Weak_SkillIcon.lock()->LvUpBt->SetPressStartTime(0.3f);
	}
	else if (Weak_SkillIcon.lock()->SkillName == "KeenEyes")
	{
		Weak_SkillIcon.lock()->SkillFunc = &Player::KeenEyes;
		Weak_SkillIcon.lock()->SkillNameFont->SetText("킨 아이즈");
		Weak_SkillIcon.lock()->SkillLv->SetText(std::to_string(Value->GetKeenEyesLv()));
		
		if (Value->GetKeenEyesLv() >= 20 || Value->GetSkillPoint() <= 0) 
		{
			Weak_SkillIcon.lock()->LvUpBt->SetAllTexture("LvUpDisable.png");
		};

		Weak_SkillIcon.lock()->LvUpBt->SetEvent([=, this] {if (Value->GetKeenEyesLv() < 20 && Value->GetSkillPoint() > 0) { Weak_SkillIcon.lock()->SkillFunc(Player::GetCurPlayer()); } if (Value->GetKeenEyesLv() == 20) { Weak_SkillIcon.lock()->LvUpBt->SetAllTexture("LvUpDisable.png"); } Weak_SkillIcon.lock()->SkillLv->SetText(std::to_string(Value->GetKeenEyesLv())); });
		Weak_SkillIcon.lock()->LvUpBt->SetPressEvent([=, this] {if (Value->GetKeenEyesLv() < 20 && Value->GetSkillPoint() > 0) { Weak_SkillIcon.lock()->SkillFunc(Player::GetCurPlayer()); } if (Value->GetKeenEyesLv() == 20) { Weak_SkillIcon.lock()->LvUpBt->SetAllTexture("LvUpDisable.png"); } Weak_SkillIcon.lock()->SkillLv->SetText(std::to_string(Value->GetKeenEyesLv())); });
		Weak_SkillIcon.lock()->LvUpBt->SetPressStartTime(0.3f);
	}
	else if (Weak_SkillIcon.lock()->SkillName == "JavelinBooster")
	{
		Weak_SkillIcon.lock()->SkillFunc = &Player::JavelinBooster;
		Weak_SkillIcon.lock()->SkillNameFont->SetText("자벨린 부스터");
		Weak_SkillIcon.lock()->SkillLv->SetText(std::to_string(Value->GetJavelinBoosterLv()));
		
		if (Value->GetJavelinBoosterLv() >= 20 || Value->GetSkillPoint() <= 0)
		{
			Weak_SkillIcon.lock()->LvUpBt->SetAllTexture("LvUpDisable.png");
		};

		Weak_SkillIcon.lock()->LvUpBt->SetEvent([=, this] {if (Value->GetJavelinBoosterLv() < 20 && Value->GetSkillPoint() > 0) { Value->JavelinBoosterLvUp(); } if (Value->GetJavelinBoosterLv() == 20) { Weak_SkillIcon.lock()->LvUpBt->SetAllTexture("LvUpDisable.png"); } Weak_SkillIcon.lock()->SkillLv->SetText(std::to_string(Value->GetJavelinBoosterLv())); });
		Weak_SkillIcon.lock()->LvUpBt->SetPressEvent([=, this] {if (Value->GetJavelinBoosterLv() < 20 && Value->GetSkillPoint() > 0) { Value->JavelinBoosterLvUp(); } if (Value->GetJavelinBoosterLv() == 20) { Weak_SkillIcon.lock()->LvUpBt->SetAllTexture("LvUpDisable.png"); } Weak_SkillIcon.lock()->SkillLv->SetText(std::to_string(Value->GetJavelinBoosterLv())); });
		Weak_SkillIcon.lock()->LvUpBt->SetPressStartTime(0.3f);
	}
	else if (Weak_SkillIcon.lock()->SkillName == "ShadowPartner")
	{
		Weak_SkillIcon.lock()->SkillFunc = &Player::ShadowPartner;
		Weak_SkillIcon.lock()->SkillNameFont->SetText("쉐도우 파트너");
		Weak_SkillIcon.lock()->SkillLv->SetText(std::to_string(Value->GetShadowPartnerLv()));
		
		if (Value->GetShadowPartnerLv() >= 20 || Value->GetSkillPoint() <= 0)
		{
			Weak_SkillIcon.lock()->LvUpBt->SetAllTexture("LvUpDisable.png");
		};

		Weak_SkillIcon.lock()->LvUpBt->SetEvent([=, this] {if (Value->GetShadowPartnerLv() < 20 && Value->GetSkillPoint() > 0) { Value->ShadowPartnerLvUp(); } if (Value->GetShadowPartnerLv() == 20) { Weak_SkillIcon.lock()->LvUpBt->SetAllTexture("LvUpDisable.png"); } Weak_SkillIcon.lock()->SkillLv->SetText(std::to_string(Value->GetShadowPartnerLv())); });
		Weak_SkillIcon.lock()->LvUpBt->SetPressEvent([=, this] {if (Value->GetShadowPartnerLv() < 20 && Value->GetSkillPoint() > 0) { Value->ShadowPartnerLvUp(); } if (Value->GetShadowPartnerLv() == 20) { Weak_SkillIcon.lock()->LvUpBt->SetAllTexture("LvUpDisable.png"); } Weak_SkillIcon.lock()->SkillLv->SetText(std::to_string(Value->GetShadowPartnerLv())); });
		Weak_SkillIcon.lock()->LvUpBt->SetPressStartTime(0.3f);
	}
	else if (Weak_SkillIcon.lock()->SkillName == "Avenger")
	{
		Weak_SkillIcon.lock()->SkillFunc = &Player::Avenger;
		Weak_SkillIcon.lock()->SkillNameFont->SetText("어벤져");
		Weak_SkillIcon.lock()->SkillLv->SetText(std::to_string(Value->GetAvengerLv()));
		
		if (Value->GetAvengerLv() >= 20 || Value->GetSkillPoint() <= 0)
		{
			Weak_SkillIcon.lock()->LvUpBt->SetAllTexture("LvUpDisable.png");
		};

		Weak_SkillIcon.lock()->LvUpBt->SetEvent([=, this] {if (Value->GetAvengerLv() < 20 && Value->GetSkillPoint() > 0) { Value->AvengerLvUp(); } if (Value->GetAvengerLv() == 20) { Weak_SkillIcon.lock()->LvUpBt->SetAllTexture("LvUpDisable.png"); } Weak_SkillIcon.lock()->SkillLv->SetText(std::to_string(Value->GetAvengerLv())); });
		Weak_SkillIcon.lock()->LvUpBt->SetPressEvent([=, this] {if (Value->GetAvengerLv() < 20 && Value->GetSkillPoint() > 0) { Value->AvengerLvUp(); } if (Value->GetAvengerLv() == 20) { Weak_SkillIcon.lock()->LvUpBt->SetAllTexture("LvUpDisable.png"); } Weak_SkillIcon.lock()->SkillLv->SetText(std::to_string(Value->GetAvengerLv())); });
		Weak_SkillIcon.lock()->LvUpBt->SetPressStartTime(0.3f);
	}
	else if (Weak_SkillIcon.lock()->SkillName == "FlashJump")
	{
		Weak_SkillIcon.lock()->SkillFunc = &Player::FlashJump;
		Weak_SkillIcon.lock()->SkillNameFont->SetText("플래시 점프");
		Weak_SkillIcon.lock()->SkillLv->SetText(std::to_string(Value->GetFlashJumpLv()));
		
		if (Value->GetFlashJumpLv() >= 20 || Value->GetSkillPoint() <= 0)
		{
			Weak_SkillIcon.lock()->LvUpBt->SetAllTexture("LvUpDisable.png");
		};

		Weak_SkillIcon.lock()->LvUpBt->SetEvent([=, this] {if (Value->GetFlashJumpLv() < 20 && Value->GetSkillPoint() > 0) { Value->FlashJumpLvUp(); } if (Value->GetFlashJumpLv() == 20) { Weak_SkillIcon.lock()->LvUpBt->SetAllTexture("LvUpDisable.png"); } Weak_SkillIcon.lock()->SkillLv->SetText(std::to_string(Value->GetFlashJumpLv())); });
		Weak_SkillIcon.lock()->LvUpBt->SetPressEvent([=, this] {if (Value->GetFlashJumpLv() < 20 && Value->GetSkillPoint() > 0) { Value->FlashJumpLvUp(); } if (Value->GetFlashJumpLv() == 20) { Weak_SkillIcon.lock()->LvUpBt->SetAllTexture("LvUpDisable.png"); } Weak_SkillIcon.lock()->SkillLv->SetText(std::to_string(Value->GetFlashJumpLv())); });
		Weak_SkillIcon.lock()->LvUpBt->SetPressStartTime(0.3f);
	}
	else if (Weak_SkillIcon.lock()->SkillName == "HeroesOfMaple")
	{
		Weak_SkillIcon.lock()->SkillFunc = &Player::HeroesOfMaple;
		Weak_SkillIcon.lock()->SkillNameFont->SetText("메이플 용사");
		Weak_SkillIcon.lock()->SkillLv->SetText(std::to_string(Value->GetHeroesOfMapleLv()));

		if (Value->GetHeroesOfMapleLv() >= 20 || Value->GetSkillPoint() <= 0)
		{
			Weak_SkillIcon.lock()->LvUpBt->SetAllTexture("LvUpDisable.png");
		};

		Weak_SkillIcon.lock()->LvUpBt->SetEvent([=, this] {if (Value->GetHeroesOfMapleLv() < 20 && Value->GetSkillPoint() > 0) { Value->HeroesOfMapleLvUp(); } if (Value->GetHeroesOfMapleLv() == 20) { Weak_SkillIcon.lock()->LvUpBt->SetAllTexture("LvUpDisable.png"); } Weak_SkillIcon.lock()->SkillLv->SetText(std::to_string(Value->GetHeroesOfMapleLv())); });
		Weak_SkillIcon.lock()->LvUpBt->SetPressEvent([=, this] {if (Value->GetHeroesOfMapleLv() < 20 && Value->GetSkillPoint() > 0) { Value->HeroesOfMapleLvUp(); } if (Value->GetHeroesOfMapleLv() == 20) { Weak_SkillIcon.lock()->LvUpBt->SetAllTexture("LvUpDisable.png"); } Weak_SkillIcon.lock()->SkillLv->SetText(std::to_string(Value->GetHeroesOfMapleLv())); });
		Weak_SkillIcon.lock()->LvUpBt->SetPressStartTime(0.3f);
	}
}