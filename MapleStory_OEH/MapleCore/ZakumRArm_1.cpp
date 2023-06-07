#include "PrecompileHeader.h"
#include "ZakumRArm_1.h"

ZakumRArm_1::ZakumRArm_1()
{
}

ZakumRArm_1::~ZakumRArm_1()
{
}

void ZakumRArm_1::Start()
{
	ArmRender = CreateComponent<GameEngineSpriteRenderer>();

	if (nullptr == GameEngineSprite::Find("RArm1_Stand"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("MapleResources");
		NewDir.Move("MapleResources");
		NewDir.Move("Sprite");
		NewDir.Move("Monster");
		NewDir.Move("Zakum");
		NewDir.Move("Arm");
		NewDir.Move("Right_1");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("RArm1_Stand").GetFullPath());
	}


	ArmRender->CreateAnimation({ .AnimationName = "Stand",.SpriteName = "RArm1_Stand",.FrameInter = 0.09f,.Loop = true,.ScaleToTexture = true,.FrameTime = {0.13f, 0.1f,0.1f, 0.1f, 0.13f, 0.1f, 0.1f, 0.1f } });
	ArmRender->ChangeAnimation("Stand");
}

void ZakumRArm_1::Update(float _DeltaTime)
{

}

void ZakumRArm_1::Render(float _DeltaTime)
{

}
