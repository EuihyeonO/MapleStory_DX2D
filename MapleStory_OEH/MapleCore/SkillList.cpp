#include "PrecompileHeader.h"
#include "SkillList.h"

#include <GameEngineCore/GameEngineUIRenderer.h>
#include <GameEngineCore/GameEngineLevel.h>

SkillList::SkillList()
{
}

SkillList::~SkillList()
{
}

void SkillList::Start()
{
	for (int i = 0; i < 5; i++)
	{
		SkillVector[i].reserve(4);
	}

	InsertSkillToList(1, "LuckySeven");
	InsertSkillToList(2, "Haste");
	InsertSkillToList(3, "ShadowPartner");
}

void SkillList::Update(float _DeltaTime) 
{
}

void SkillList::Render(float _DeltaTime) 
{
}

void SkillList::InsertSkillToList(int _Index, const std::string_view& _SkillName)
{
	std::shared_ptr<SkillIcon> NewSkill = GetLevel()->CreateActor<SkillIcon>();

	NewSkill->SkillName = _SkillName.data();

	NewSkill->SkillBackGround = CreateComponent<GameEngineUIRenderer>();
	NewSkill->SkillBackGround->SetScaleToTexture("SkillBackGround.png");
	NewSkill->SkillBackGround->GetTransform()->SetLocalPosition({ -10, 0 });
	NewSkill->SkillBackGround->Off();

	NewSkill->IconRender = CreateComponent<GameEngineUIRenderer>();
	NewSkill->IconRender->SetScaleToTexture(NewSkill->SkillName + "Icon.png");
	NewSkill->IconRender->GetTransform()->SetLocalPosition(NewSkill->SkillBackGround->GetTransform()->GetLocalPosition() - float4{ 53, 0 });
	NewSkill->IconRender->Off();

	SkillVector[_Index].push_back(NewSkill);
}

void SkillList::IndexSkillOn(int _Index)
{
	int Size = SkillVector[_Index].size();
	for(int i = 0; i < Size; i++)
	{
		SkillVector[_Index][i]->SkillBackGround->On();
		SkillVector[_Index][i]->IconRender->On();
	}
}

void SkillList::IndexSkillOff(int _Index)
{
	int Size = SkillVector[_Index].size();
	for (int i = 0; i < Size; i++)
	{
		SkillVector[_Index][i]->SkillBackGround->Off();
		SkillVector[_Index][i]->IconRender->Off();
	}
}

