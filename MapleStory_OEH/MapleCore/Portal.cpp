#include "PrecompileHeader.h"
#include "Portal.h"
#include "ContentEnums.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEnginePlatform/GameEngineInput.h>

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

	PortalCollision = CreateComponent<GameEngineCollision>();
	
	PortalCollision->GetTransform()->SetLocalPosition({ 0, -80 });
	PortalCollision->GetTransform()->SetLocalScale({ 70, 80 });
}

void Portal::Update(float _DeltaTime)
{
	std::shared_ptr<GameEngineCollision> Collision = PortalCollision->Collision(static_cast<int>(CollisionOrder::Player), ColType::AABBBOX2D, ColType::AABBBOX2D);
	
	if (Collision != nullptr)
	{
		if (GameEngineInput::IsDown("UpKey") == true)
		{
			GameEngineCore::ChangeLevel(LinkedMap);
		}
	}
}

void Portal::Render(float _DeltaTime)
{
}
