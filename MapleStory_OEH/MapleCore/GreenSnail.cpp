#include "PrecompileHeader.h"
#include "GreenSnail.h"
#include "MonsterSpawnZone.h"
#include "ContentRenderer.h"

GreenSnail::GreenSnail()
{
	MyName = static_cast<int>(MonsterName::GreenSnail);
}

GreenSnail::~GreenSnail()
{
}

void GreenSnail::Start()
{
	TimeCounting();
	SetAnimationList();

	SetMoveSpeed(20.0f);

	BasicRender = CreateComponent<ContentRenderer>();
	BasicRender->SetScaleToTexture("GreenSnailStand0.png");
	BasicRender->SetMulColor({ 1, 1, 1, 0.0f });
	
	TransformData RenderData = BasicRender->GetTransform()->GetTransDataRef();
	BasicRender->GetTransform()->SetLocalPosition({ 0, RenderData.LocalScale.hy() });

	BasicCollision = CreateComponent<GameEngineCollision>();
	BasicCollision->GetTransform()->SetLocalScale({ abs(RenderData.LocalScale.x), abs(RenderData.LocalScale.y) });
	BasicCollision->GetTransform()->SetLocalPosition(RenderData.LocalPosition);
	BasicCollision->SetOrder(static_cast<int>(CollisionOrder::Monster));
}

void GreenSnail::Update(float _DeltaTime)
{
	TransformData Data = GetTransform()->GetTransDataRef();

	TimeCounting();
	Spawn(_DeltaTime);

	GravityUpdate(_DeltaTime);
	SetDropItemList();
	if(isSpawnAnimationEnd == true)
	{
		if(MoveType != "Hit" && MoveType != "Death")
		{
			DirUpdate();
			Move(_DeltaTime);
		}

		TextureUpdate();
	}
}

void GreenSnail::Render(float _DeltaTime)
{
}

void GreenSnail::Spawn(float _DeltaTime)
{
	if (isSpawnAnimationEnd == true || IsGround() == false)
	{
		return;
	}

	RenderAlpha += 2.5f * _DeltaTime;

	if (RenderAlpha >= 1.0f)
	{
		RenderAlpha = 1.0f;
		isSpawnAnimationEnd = true;
	}

	BasicRender->SetMulColor({ 1,1,1, RenderAlpha });
}


void GreenSnail::TextureUpdate()
{
	AnimationCount += TimeCount;

	if (AnimationCount >= FrameList[MoveType][AniIndex])
	{
		AnimationCount = 0.0f;

		AniIndex++;

		if (AniIndex >= FrameList[MoveType].size())
		{
			if (MoveType == "Hit")
			{
				MoveType = "Move";
			}

			AniIndex = 0;
		}
		
		std::string TextureName = "GreenSnail" + MoveType + std::to_string(AniIndex) + ".png";
		BasicRender->SetScaleToTexture(TextureName);

		TransformData RenderData = BasicRender->GetTransform()->GetTransDataRef();
		BasicRender->GetTransform()->SetLocalPosition({ 0, RenderData.LocalScale.hy() });

		BasicCollision->GetTransform()->SetLocalScale({ abs(RenderData.LocalScale.x), abs(RenderData.LocalScale.y) });
		BasicCollision->GetTransform()->SetLocalPosition(RenderData.LocalPosition);
	}
}

void GreenSnail::Hit()
{
	MoveType = "Hit";
	AniIndex = 0;

	std::string TextureName = "GreenSnail" + MoveType + std::to_string(AniIndex) + ".png";
	BasicRender->SetScaleToTexture(TextureName);

	TransformData RenderData = BasicRender->GetTransform()->GetTransDataRef();
	BasicRender->GetTransform()->SetLocalPosition({ 0, RenderData.LocalScale.hy() });

	BasicCollision->GetTransform()->SetLocalScale({ abs(RenderData.LocalScale.x), abs(RenderData.LocalScale.y) });
	BasicCollision->GetTransform()->SetLocalPosition(RenderData.LocalPosition);

}

void GreenSnail::SetAnimationList()
{
	{
		FrameList["Stand"].push_back(0.0f);
	}

	{
		FrameList["Move"].reserve(8);

		FrameList["Move"].push_back(0.18f);
		FrameList["Move"].push_back(0.18f);
		FrameList["Move"].push_back(0.18f);
		FrameList["Move"].push_back(0.18f);
		FrameList["Move"].push_back(0.18f);
		FrameList["Move"].push_back(0.18f);
		FrameList["Move"].push_back(0.18f);
		FrameList["Move"].push_back(0.18f);
	}

	{
		FrameList["Hit"].push_back(0.6f);
	}
}

void GreenSnail::SetDropItemList()
{
	DropItemList.reserve(4);

	DropItemList.push_back({ "GreenShell", 75 });
}