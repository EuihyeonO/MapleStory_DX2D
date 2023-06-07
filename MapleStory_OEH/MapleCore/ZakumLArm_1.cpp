#include "PrecompileHeader.h"
#include "ZakumLArm_1.h"

ZakumLArm_1::ZakumLArm_1()
{
}

ZakumLArm_1::~ZakumLArm_1()
{
}

void ZakumLArm_1::Start()
{
	ArmRender = CreateComponent<GameEngineSpriteRenderer>();

	if (nullptr == GameEngineSprite::Find("LArm1_Stand"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("MapleResources");
		NewDir.Move("MapleResources");
		NewDir.Move("Sprite");
		NewDir.Move("Monster");
		NewDir.Move("Zakum");
		NewDir.Move("Arm");
		NewDir.Move("Left_1");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("LArm1_Stand").GetFullPath());
	}


	ArmRender->CreateAnimation({ .AnimationName = "Stand",.SpriteName = "LArm1_Stand",.FrameInter = 0.09f,.Loop = true,.ScaleToTexture = true,.FrameTime = {0.13f, 0.1f,0.1f, 0.1f, 0.13f, 0.1f, 0.1f, 0.1f } });
	ArmRender->ChangeAnimation("Stand");
}

void ZakumLArm_1::Update(float _DeltaTime)
{

}

void ZakumLArm_1::Render(float _DeltaTime)
{

}
