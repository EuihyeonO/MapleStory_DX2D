#include "PrecompileHeader.h"
#include "Portal.h"
#include "ContentEnums.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>

Portal::Portal()
{
}

Portal::~Portal()
{
}

void Portal::Start()
{
	PortalRender = CreateComponent<GameEngineSpriteRenderer>();
	
	if (nullptr == GameEngineSprite::Find("Portal"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("MapleResources");
		NewDir.Move("MapleResources");
		NewDir.Move("Sprite");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Portal").GetFullPath());
	}

	PortalRender->CreateAnimation({.AnimationName = "Portal",.SpriteName = "Portal",.Start = 0,.End = 7 ,.FrameInter = 0.1f,.Loop = true ,.ScaleToTexture = true });
	PortalRender->ChangeAnimation("Portal");

	GetTransform()->SetLocalPosition({ -460, 100 });
}

void Portal::Update(float _DeltaTime)
{

}

void Portal::Render(float _DeltaTime)
{

}