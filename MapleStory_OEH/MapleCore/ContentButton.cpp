#include "PrecompileHeader.h"
#include "ContentButton.h"

#include <GameEnginePlatform/GameEngineInput.h>

ContentButton::ContentButton()
{
}

ContentButton::~ContentButton()
{
}

void ContentButton::Start()
{
	GameEngineButton::Start();
	MyRender = CreateComponent<GameEngineSpriteRenderer>();
	MyCollision = CreateComponent<GameEngineCollision>();
	MyCollision->SetColType(ColType::AABBBOX2D);
}

void ContentButton::Update(float _Delta)
{
	if(isUIRender == true)
	{
		float4 Scale = GetRender()->GetTransform()->GetWorldScale();
		float4 Pos = GetRender()->GetTransform()->GetWorldPosition();
		MyRender->Off();
		GetRender()->On();
	}
	else
	{
		float4 Scale = MyRender->GetTransform()->GetWorldScale();
		float4 Pos = MyRender->GetTransform()->GetWorldPosition();
		MyRender->On();
		GetRender()->Off();
	}

	// 랜더러 => 크 자 이 공 부  월드 => 뷰 => 투영 => 뷰포트
	//                                               스크린
	//                                               마우스

	// 이카메라가 원근 투영이면
	GameEngineCamera* Camera = GetRender()->GetCamera();

	// 랜더러 
	float4x4 ViewPort = Camera->GetViewPort();
	float4x4 Proj = Camera->GetProjection();
	float4x4 View = Camera->GetView();

	float4 Mouse = GameEngineInput::GetMousePosition() + float4{ -8, -10 };

	Mouse *= ViewPort.InverseReturn();
	Mouse *= Proj.InverseReturn();
	Mouse *= View.InverseReturn();


	CollisionData MouseData;
	MouseData.SPHERE.Center = Mouse.DirectFloat3;
	MouseData.SPHERE.Radius = 0.0f;

	if(isUIRender == true)
	{
		if (true == GameEngineTransform::AABB2DToSpehre2D(GetRender()->GetTransform()->GetCollisionData(), MouseData))
		{
			if (ContentHoverImage != "")
			{
				GetRender()->SetTexture(ContentHoverImage);
			}

			if (true == GameEngineInput::IsPress("EngineMouseLeft"))
			{
				if (ContentPressImage != "")
				{
					GetRender()->SetTexture(ContentPressImage);
				}
				
			}

			if (true == GameEngineInput::IsUp("EngineMouseLeft"))
			{
				if (nullptr != Click)
				{
					Click();
				}
			}
		}
		else
		{
			if (ContentReleaseImage != "")
			{
				GetRender()->SetTexture(ContentReleaseImage);
			}
		}
	}
	else
	{
		if (nullptr != MyCollision->Collision(static_cast<int>(CollisionOrder::Mouse), ColType::AABBBOX2D, ColType::SPHERE2D))
		{
			if (ContentHoverImage != "")
			{
				MyRender->SetTexture(ContentHoverImage);
				GetTransform()->SetLocalScale(HoverScale);
				GetTransform()->SetLocalPosition(HoverPos);
			}

			if (true == GameEngineInput::IsPress("EngineMouseLeft"))
			{
				if (ContentPressImage != "")
				{
					MyRender->SetTexture(ContentPressImage);
					GetTransform()->SetLocalScale(PressScale);
					GetTransform()->SetLocalPosition(PressPos);
				}
			}

			if (true == GameEngineInput::IsUp("EngineMouseLeft"))
			{
				if (nullptr != Click)
				{
					Click();
				}
			}
		}
		else
		{
			if (ContentReleaseImage != "")
			{
				MyRender->SetTexture(ContentReleaseImage);
				GetTransform()->SetLocalScale(ReleaseScale);
				GetTransform()->SetLocalPosition(ReleasePos);
			}
		}
	}
}