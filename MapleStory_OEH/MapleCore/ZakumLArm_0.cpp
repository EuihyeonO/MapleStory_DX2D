#include "PrecompileHeader.h"
#include "ZakumLArm_0.h"

ZakumLArm_0::ZakumLArm_0()
{
}

ZakumLArm_0::~ZakumLArm_0()
{
}

void ZakumLArm_0::Start()
{
	ArmRender = CreateComponent<GameEngineSpriteRenderer>();

	if (nullptr == GameEngineSprite::Find("LArm0_Stand"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("MapleResources");
		NewDir.Move("MapleResources");
		NewDir.Move("Sprite");
		NewDir.Move("Monster");
		NewDir.Move("Zakum");
		NewDir.Move("Arm");
		NewDir.Move("Left_0");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("LArm0_Stand").GetFullPath());
	}


	ArmRender->CreateAnimation({ .AnimationName = "Stand",.SpriteName = "LArm0_Stand",.FrameInter = 0.09f,.Loop = true,.ScaleToTexture = true,.FrameTime = {0.13f, 0.1f,0.1f, 0.1f, 0.13f, 0.1f, 0.1f, 0.1f } });
	ArmRender->ChangeAnimation("Stand");
}

void ZakumLArm_0::Update(float _DeltaTime)
{

}

void ZakumLArm_0::Render(float _DeltaTime)
{

}
