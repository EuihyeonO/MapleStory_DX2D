#include "PrecompileHeader.h"
#include "ZakumLArm_2.h"

ZakumLArm_2::ZakumLArm_2()
{
}

ZakumLArm_2::~ZakumLArm_2()
{
}

void ZakumLArm_2::Start()
{
	ArmRender = CreateComponent<GameEngineSpriteRenderer>();

	if (nullptr == GameEngineSprite::Find("LArm2_Stand"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("MapleResources");
		NewDir.Move("MapleResources");
		NewDir.Move("Sprite");
		NewDir.Move("Monster");
		NewDir.Move("Zakum");
		NewDir.Move("Arm");
		NewDir.Move("Left_2");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("LArm2_Stand").GetFullPath());
	}


	ArmRender->CreateAnimation({ .AnimationName = "Stand",.SpriteName = "LArm2_Stand",.FrameInter = 0.09f,.Loop = true,.ScaleToTexture = true,.FrameTime = {0.13f, 0.1f,0.1f, 0.1f, 0.13f, 0.1f, 0.1f, 0.1f } });
	ArmRender->ChangeAnimation("Stand");
}

void ZakumLArm_2::Update(float _DeltaTime)
{

}

void ZakumLArm_2::Render(float _DeltaTime)
{

}
