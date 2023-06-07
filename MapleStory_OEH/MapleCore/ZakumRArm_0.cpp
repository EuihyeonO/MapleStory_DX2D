#include "PrecompileHeader.h"
#include "ZakumRArm_0.h"

ZakumRArm_0::ZakumRArm_0()
{
}

ZakumRArm_0::~ZakumRArm_0()
{
}

void ZakumRArm_0::Start()
{
	ArmRender = CreateComponent<GameEngineSpriteRenderer>();

	if (nullptr == GameEngineSprite::Find("RArm0_Stand"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("MapleResources");
		NewDir.Move("MapleResources");
		NewDir.Move("Sprite");
		NewDir.Move("Monster");
		NewDir.Move("Zakum");
		NewDir.Move("Arm");
		NewDir.Move("Right_0");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("RArm0_Stand").GetFullPath());
	}


	ArmRender->CreateAnimation({ .AnimationName = "Stand",.SpriteName = "RArm0_Stand",.FrameInter = 0.09f,.Loop = true,.ScaleToTexture = true,.FrameTime = {0.13f, 0.1f,0.1f, 0.1f, 0.13f, 0.1f, 0.1f, 0.1f } });
	ArmRender->ChangeAnimation("Stand");
}

void ZakumRArm_0::Update(float _DeltaTime) 
{

}

void ZakumRArm_0::Render(float _DeltaTime) 
{

}
