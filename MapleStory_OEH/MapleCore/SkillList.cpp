#include "PrecompileHeader.h"
#include "SkillList.h"
#include "Mouse.h"
#include "QuickSlot.h"
#include "Player.h"
#include "UIController.h"

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

	InsertSkillToList(1, "LuckySeven");
	InsertSkillToList(2, "Haste");
	InsertSkillToList(2, "JavelinBooster");
	InsertSkillToList(3, "ShadowPartner");
	InsertSkillToList(3, "Avenger");
	InsertSkillToList(3, "FlashJump");
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

void SkillList::InsertSkillToList(int _Index, const std::string_view& _SkillName)
{
	std::shared_ptr<SkillIcon> NewSkill = GetLevel()->CreateActor<SkillIcon>(static_cast<int>(RenderOrder::Mouse));

	NewSkill->SkillName = _SkillName.data();

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

	SetSkillFunc(NewSkill);

	SkillVector[_Index].push_back(NewSkill);
}

void SkillList::SetSkillFunc(std::shared_ptr<SkillList::SkillIcon> _SkillIcon)
{
	if (_SkillIcon == nullptr)
	{
		return;
	}

	if (_SkillIcon->SkillName == "Haste")
	{
		_SkillIcon->SkillFunc = &Player::Haste;
	}
	else if (_SkillIcon->SkillName == "LuckySeven")
	{
		_SkillIcon->SkillFunc = &Player::LuckySeven;
	}
	else if (_SkillIcon->SkillName == "JavelinBooster")
	{
		_SkillIcon->SkillFunc = &Player::JavelinBooster;
	}
	else if (_SkillIcon->SkillName == "ShadowPartner")
	{
		_SkillIcon->SkillFunc = &Player::ShadowPartner;
	}
	else if (_SkillIcon->SkillName == "Avenger")
	{
		_SkillIcon->SkillFunc = &Player::Avenger;
	}
	else if (_SkillIcon->SkillName == "FlashJump")
	{
		_SkillIcon->SkillFunc = &Player::FlashJump;
	}
}

void SkillList::IndexSkillOn(int _Index)
{
	size_t Size = SkillVector[_Index].size();
	for(size_t i = 0; i < Size; i++)
	{
		SkillVector[_Index][i]->SkillBackGround->On();
		SkillVector[_Index][i]->IconRender->On();
		SkillVector[_Index][i]->IconCollision->On();
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
	}
}

void SkillList::SortSkillList(int _Index, float4 _Pos)
{
	size_t Size = SkillVector[_Index].size();
	for (size_t i = 0; i < Size; i++)
	{
		SkillVector[_Index][i]->SkillBackGround->GetTransform()->SetLocalPosition(_Pos + float4{ -10, -static_cast<float>(i * 40) });
		SkillVector[_Index][i]->IconRender->GetTransform()->SetLocalPosition(SkillVector[_Index][i]->SkillBackGround->GetTransform()->GetLocalPosition() - float4{ 53, 0 });
		SkillVector[_Index][i]->IconCollision ->GetTransform()->SetLocalPosition(SkillVector[_Index][i]->SkillBackGround->GetTransform()->GetLocalPosition() - float4{ 53, 0 });
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