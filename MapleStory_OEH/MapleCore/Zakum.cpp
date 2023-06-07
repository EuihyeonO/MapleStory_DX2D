#include "PrecompileHeader.h"
#include "Zakum.h"
#include "ZakumRArm_0.h"
#include "ZakumRArm_1.h"
#include "ZakumRArm_2.h"
#include "ZakumRArm_3.h"

#include "ZakumLArm_0.h"
#include "ZakumLArm_1.h"
#include "ZakumLArm_2.h"
#include "ZakumLArm_3.h"

#include <GameEngineCore/GameEngineLevel.h>
Zakum::Zakum()
{
}

Zakum::~Zakum()
{
}

void Zakum::Start()
{
	TimeCounting();
	//std::string_view AnimationName = "";
	//std::string_view SpriteName = "";
	//size_t Start = static_cast<size_t>(-1);
	//size_t End = static_cast<size_t>(-1);
	//float FrameInter = 0.1f;
	//bool Loop = true;
	//bool ScaleToTexture = false;
	//std::vector<size_t> FrameIndex = std::vector<size_t>();
	//std::vector<float> FrameTime = std::vector<float>();

	BodyRender = CreateComponent<GameEngineSpriteRenderer>();
	
	if (nullptr == GameEngineSprite::Find("ZakumSpawn"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("MapleResources");
		NewDir.Move("MapleResources");
		NewDir.Move("Sprite");
		NewDir.Move("Monster");
		NewDir.Move("Zakum");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("ZakumSpawn").GetFullPath());

		NewDir.Move("Phase1");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Phase1Stand").GetFullPath());
	}

	BodyRender->CreateAnimation({ .AnimationName = "Phase1Stand",.SpriteName = "Phase1Stand",.FrameInter = 0.09f,.Loop = true,.ScaleToTexture = true });
	

	//BodyRender->ChangeAnimation("Spawn");
	//AnimationName = "Spawn";
}
void Zakum::Update(float _DeltaTime)
{
	if(AniIndex != -1)
	{
		TimeCounting();
		AniCount += TimeCount;

		if (AniCount >= 0.12f)
		{
			AniIndex++;
			AniCount = 0.0f;

			if (AniIndex >= 19)
			{
				BodyRender->ChangeAnimation("Phase1Stand");
				GetTransform()->SetLocalPosition({ 0.0f, 20.0f, -5.0f });

				AniIndex = -1;

				RArm_0 = GetLevel()->CreateActor<ZakumRArm_0>();
				RArm_0->GetTransform()->SetLocalPosition({ 130, 110, -4.0f });
				RArm_1 = GetLevel()->CreateActor<ZakumRArm_1>();	
				RArm_1->GetTransform()->SetLocalPosition({ 160, 60, -4.0f });
				RArm_2 = GetLevel()->CreateActor<ZakumRArm_2>();	
				RArm_2->GetTransform()->SetLocalPosition({ 170, -10, -4.0f });
				RArm_3 = GetLevel()->CreateActor<ZakumRArm_3>();	 
				RArm_3->GetTransform()->SetLocalPosition({ 180, -80, -4.0f });

				LArm_0 = GetLevel()->CreateActor<ZakumLArm_0> ();
				LArm_0->GetTransform()->SetLocalPosition({ -110, 110, -4.0f });
				LArm_1 = GetLevel()->CreateActor<ZakumLArm_1>();
				LArm_1->GetTransform()->SetLocalPosition({ -140, 60, -4.0f });
				LArm_2 = GetLevel()->CreateActor<ZakumLArm_2>();
				LArm_2->GetTransform()->SetLocalPosition({ -140, -10, -4.0f });
				LArm_3 = GetLevel()->CreateActor<ZakumLArm_3>();
				LArm_3->GetTransform()->SetLocalPosition({ -140, -80, -4.0f });
				return;
			}

			GetTransform()->SetLocalPosition({28.0f, 28.0f, -2.0f });
			BodyRender->SetScaleToTexture("ZakumSpawn" + std::to_string(AniIndex) + ".png");
		}
	}

}
void Zakum::Render(float _DeltaTime)
{

}