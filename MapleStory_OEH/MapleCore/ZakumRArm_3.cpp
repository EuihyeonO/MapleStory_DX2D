#include "PrecompileHeader.h"
#include "ZakumRArm_3.h"

ZakumRArm_3::ZakumRArm_3()
{
}

ZakumRArm_3::~ZakumRArm_3()
{
}

void ZakumRArm_3::Start()
{
	ArmRender = CreateComponent<GameEngineSpriteRenderer>();

	if (nullptr == GameEngineSprite::Find("RArm3_Stand"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("MapleResources");
		NewDir.Move("MapleResources");
		NewDir.Move("Sprite");
		NewDir.Move("Monster");
		NewDir.Move("Zakum");
		NewDir.Move("Arm");
		NewDir.Move("Right_3");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("RArm3_Stand").GetFullPath());
	}


	ArmRender->CreateAnimation({ .AnimationName = "Stand",.SpriteName = "RArm3_Stand",.FrameInter = 0.09f,.Loop = true,.ScaleToTexture = true,.FrameTime = {0.13f, 0.1f,0.1f, 0.1f, 0.13f, 0.1f, 0.1f, 0.1f } });
	ArmRender->ChangeAnimation("Stand");
}

void ZakumRArm_3::Update(float _DeltaTime)
{

}

void ZakumRArm_3::Render(float _DeltaTime)
{

}
