#include "PrecompileHeader.h"
#include "ZakumLArm_3.h"

ZakumLArm_3::ZakumLArm_3()
{
}

ZakumLArm_3::~ZakumLArm_3()
{
}

void ZakumLArm_3::Start()
{
	ArmRender = CreateComponent<GameEngineSpriteRenderer>();

	if (nullptr == GameEngineSprite::Find("LArm3_Stand"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("MapleResources");
		NewDir.Move("MapleResources");
		NewDir.Move("Sprite");
		NewDir.Move("Monster");
		NewDir.Move("Zakum");
		NewDir.Move("Arm");
		NewDir.Move("Left_3");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("LArm3_Stand").GetFullPath());
	}


	ArmRender->CreateAnimation({ .AnimationName = "Stand",.SpriteName = "LArm3_Stand",.FrameInter = 0.09f,.Loop = true,.ScaleToTexture = true,.FrameTime = {0.13f, 0.1f,0.1f, 0.1f, 0.13f, 0.1f, 0.1f, 0.1f } });
	ArmRender->ChangeAnimation("Stand");
}

void ZakumLArm_3::Update(float _DeltaTime)
{

}

void ZakumLArm_3::Render(float _DeltaTime)
{

}
