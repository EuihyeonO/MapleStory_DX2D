#include "PrecompileHeader.h"
#include "ZakumRArm_2.h"

ZakumRArm_2::ZakumRArm_2()
{
}

ZakumRArm_2::~ZakumRArm_2()
{
}

void ZakumRArm_2::Start()
{
	ArmRender = CreateComponent<GameEngineSpriteRenderer>();

	if (nullptr == GameEngineSprite::Find("RArm2_Stand"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("MapleResources");
		NewDir.Move("MapleResources");
		NewDir.Move("Sprite");
		NewDir.Move("Monster");
		NewDir.Move("Zakum");
		NewDir.Move("Arm");
		NewDir.Move("Right_2");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("RArm2_Stand").GetFullPath());
	}


	ArmRender->CreateAnimation({ .AnimationName = "Stand",.SpriteName = "RArm2_Stand",.FrameInter = 0.09f,.Loop = true,.ScaleToTexture = true,.FrameTime = {0.13f, 0.1f,0.1f, 0.1f, 0.13f, 0.1f, 0.1f, 0.1f } });
	ArmRender->ChangeAnimation("Stand");
}

void ZakumRArm_2::Update(float _DeltaTime)
{

}

void ZakumRArm_2::Render(float _DeltaTime)
{

}
