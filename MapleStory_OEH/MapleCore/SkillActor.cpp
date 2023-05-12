#include "PrecompileHeader.h"
#include "SkillActor.h"
#include "Player.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <ctime>

SkillActor::SkillActor()
{
}

SkillActor::~SkillActor()
{
}

void SkillActor::Start()
{
	TimeCounting();
}

void SkillActor::Update(float _DeltaTime)
{
	if (IconRender->IsUpdate() == true)
	{
		float4 CameraPos = GetLevel()->GetMainCamera()->GetTransform()->GetLocalPosition();
		IconRender->GetTransform()->SetLocalPosition(CameraPos + float4{ 400, 300 } - float4{ 16, 16 });
	}

	if (UpdateFunc != nullptr)
	{
		UpdateFunc(*this);
	}
}

void SkillActor::Render(float _DeltaTime)
{
}

void SkillActor::SetSkillActor(const std::string_view& _SkillName)
{
	SkillName = _SkillName.data();
	
	AnimationRender = CreateComponent<GameEngineSpriteRenderer>();	

	IconRender = CreateComponent<GameEngineSpriteRenderer>();
	IconRender->SetScaleToTexture(SkillName + "Icon.png");

	SetSkillAnimation();
	SetUpdateFunc();

}

void SkillActor::SetSkillAnimation()
{	
	AniFrameList[SkillName].push_back(0.09f);

	if(SkillName == "Haste")
	{
		SkillOriginPosVector[SkillName].push_back({ 0,  25 });
		SkillOriginPosVector[SkillName].push_back({ 0,  25 });
		SkillOriginPosVector[SkillName].push_back({ 0,  25 });
		SkillOriginPosVector[SkillName].push_back({ 0,  25 });
		SkillOriginPosVector[SkillName].push_back({ 0,  25 });
		SkillOriginPosVector[SkillName].push_back({ 0,  25 });
		SkillOriginPosVector[SkillName].push_back({ 0,  25 });
		SkillOriginPosVector[SkillName].push_back({ 0,  25 });
		SkillOriginPosVector[SkillName].push_back({ 0,  25 });
	}
}

void SkillActor::SetUpdateFunc()
{
	if (SkillName == "Haste")
	{
		UpdateFunc = &SkillActor::Haste;
	}
}

void SkillActor::Haste()
{
	TimeCounting();

	AnimationCount += TimeCount;

	if (AnimationIndex < SkillOriginPosVector["Haste"].size() && AniFrameList["Haste"][0] <= AnimationCount)
	{
		std::string TextureName = "Haste" + std::to_string(AnimationIndex) + ".png";

		Player* CurPlayer = Player::GetCurPlayer();
		float4 Pos = CurPlayer->GetTransform()->GetWorldPosition();

		if (CurPlayer->GetLeftRightDir() == "Right")
		{
			AnimationRender->SetScaleToTexture(TextureName);
		}
		else if (CurPlayer->GetLeftRightDir() == "Left")
		{
			AnimationRender->SetScaleToTexture(TextureName);
			float4 Scale = AnimationRender->GetTransform()->GetLocalScale();
			AnimationRender->GetTransform()->SetLocalScale({ -Scale.x, Scale.y });
		}


		AnimationRender->GetTransform()->SetLocalPosition(Pos +  SkillOriginPosVector["Haste"][AnimationIndex]);
		AnimationCount = 0.0f;
		AnimationIndex++;
	}
	else if (AnimationIndex >= SkillOriginPosVector["Haste"].size())
	{
		AnimationRender->Death();
		AnimationRender = nullptr;
		UpdateFunc = nullptr;
	}
}

void SkillActor::TimeCounting()
{	
	CurTime = static_cast<float>(clock());

	TimeCount = (CurTime - PrevTime) / 1000.0f;

	PrevTime = CurTime;	
}
