#include "PrecompileHeader.h"
#include "SkillWindow.h"
#include "SkillList.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineUIRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineLevel.h>

SkillWindow::SkillWindow()
{
}

SkillWindow::~SkillWindow()
{
}

void SkillWindow::Start()
{
	GetTransform()->SetLocalPosition({0, 0, 0});
	
	SkillWindowRender = CreateComponent<GameEngineUIRenderer>();
	SkillWindowRender->SetScaleToTexture("SkillWindow0.png");

	Index0 = CreateComponent<GameEngineCollision>();
	Index0->GetTransform()->SetLocalScale({ 27, 16 });
	Index0->GetTransform()->SetLocalPosition({ -68, 110 });

	Index1 = CreateComponent<GameEngineCollision>();
	Index1->GetTransform()->SetLocalScale({ 27, 16 });
	Index1->GetTransform()->SetLocalPosition({ -36, 110 });

	Index2 = CreateComponent<GameEngineCollision>();
	Index2->GetTransform()->SetLocalScale({ 27, 16 });
	Index2->GetTransform()->SetLocalPosition({ -4, 110 });

	Index3 = CreateComponent<GameEngineCollision>();
	Index3->GetTransform()->SetLocalScale({ 27, 16 });
	Index3->GetTransform()->SetLocalPosition({ 28, 110 });

	Index4 = CreateComponent<GameEngineCollision>();
	Index4->GetTransform()->SetLocalScale({ 27, 16 });
	Index4->GetTransform()->SetLocalPosition({ 60, 110 });

	MySkillList = GetLevel()->CreateActor<SkillList>();
}

void SkillWindow::Update(float _DeltaTime) 
{
	ChangeWindowIndex();
}

void SkillWindow::Render(float _DeltaTime) 
{
}

void SkillWindow::ChangeWindowIndex()
{
	if (GameEngineInput::IsDown("LClick") == true)
	{
		std::shared_ptr<GameEngineCollision> Collision = Index0->Collision(static_cast<int>(CollisionOrder::Mouse), ColType::AABBBOX2D, ColType::AABBBOX2D);

		if (Collision != nullptr)
		{
			if (Index == 0)
			{
				return;
			}

			SkillWindowRender->SetTexture("SkillWindow0.png");
			MySkillList->IndexSkillOff(Index);
			Index = 0;
			MySkillList->IndexSkillOn(Index);
			MySkillList->SortSkillList(Index, SkillWindowRender->GetTransform()->GetWorldPosition() + float4{0, 29});
			return;
		}

		Collision = Index1->Collision(static_cast<int>(CollisionOrder::Mouse), ColType::AABBBOX2D, ColType::AABBBOX2D);

		if (Collision != nullptr)
		{
			if (Index == 1)
			{
				return;
			}

			SkillWindowRender->SetTexture("SkillWindow1.png");
			MySkillList->IndexSkillOff(Index);
			Index = 1;
			MySkillList->IndexSkillOn(Index);
			MySkillList->SortSkillList(Index, SkillWindowRender->GetTransform()->GetWorldPosition() + float4{ 0, 29 });
			return;
		}

		Collision = Index2->Collision(static_cast<int>(CollisionOrder::Mouse), ColType::AABBBOX2D, ColType::AABBBOX2D);

		if (Collision != nullptr)
		{
			if (Index == 2)
			{
				return;
			}

			SkillWindowRender->SetTexture("SkillWindow2.png");
			MySkillList->IndexSkillOff(Index);
			Index = 2;
			MySkillList->IndexSkillOn(Index);
			MySkillList->SortSkillList(Index, SkillWindowRender->GetTransform()->GetWorldPosition() + float4{ 0, 29 });
			return;
		}

		Collision = Index3->Collision(static_cast<int>(CollisionOrder::Mouse), ColType::AABBBOX2D, ColType::AABBBOX2D);

		if (Collision != nullptr)
		{
			if (Index == 3)
			{
				return;
			}

			SkillWindowRender->SetTexture("SkillWindow3.png");
			MySkillList->IndexSkillOff(Index);
			Index = 3;
			MySkillList->IndexSkillOn(Index);
			MySkillList->SortSkillList(Index, SkillWindowRender->GetTransform()->GetWorldPosition() + float4{ 0, 29 });
			return;
		}

		Collision = Index4->Collision(static_cast<int>(CollisionOrder::Mouse), ColType::AABBBOX2D, ColType::AABBBOX2D);

		if (Collision != nullptr)
		{
			if (Index == 4)
			{
				return;
			}

			SkillWindowRender->SetTexture("SkillWindow4.png");
			MySkillList->IndexSkillOff(Index);
			Index = 4;
			MySkillList->IndexSkillOn(Index);
			MySkillList->SortSkillList(Index, SkillWindowRender->GetTransform()->GetWorldPosition() + float4{ 0, 29 });

			return;
		}
	}
}
