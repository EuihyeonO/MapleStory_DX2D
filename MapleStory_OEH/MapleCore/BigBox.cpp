#include "PrecompileHeader.h"
#include "BigBox.h"
#include "DropItem.h"

#include <GameEngineCore/GameEngineLevel.h>

BigBox::BigBox()
{
}

BigBox::~BigBox()
{

}

void BigBox::Start()
{
	GetTransform()->SetLocalPosition({ 740, -700 });
	ColMap = GameEngineTexture::Find("ColZakumRoad1.png");

	BoxRender = CreateComponent<GameEngineSpriteRenderer>();
	BoxRender->GetTransform()->SetLocalPosition({ 0, 75 });
	
	BoxRender->CreateAnimation({ .AnimationName = "Stand",.SpriteName = "BigBoxStand",.FrameInter = 0.1f,.Loop = false,.ScaleToTexture = true });
	BoxRender->CreateAnimation({ .AnimationName = "Death",.SpriteName = "BigBoxDeath",.FrameInter = 0.2f,.Loop = false,.ScaleToTexture = true });
	
	BoxRender->SetAnimationUpdateEvent("Death", 2, [this]
		{
			if(BoxRender->IsAnimationEnd() == true && isCreateItem == false)
			{
				std::shared_ptr<DropItem> NewItem = GetLevel()->CreateActor<DropItem>();
				NewItem->SetQuadraticFunction(1.0f, GetTransform()->GetWorldPosition() + float4{ -40, 5 });
				NewItem->SetDropItemInfo("FIRESTONE", static_cast<int>(ItemType::Etc));
				isCreateItem = true;
			}
		});

	BoxRender->ChangeAnimation("Stand");

	BoxCollision = CreateComponent<GameEngineCollision>();
	BoxCollision->SetColType(ColType::AABBBOX2D);
	BoxCollision->GetTransform()->SetLocalScale({ 150, 30 });
	BoxCollision->GetTransform()->SetLocalPosition({ -20, 15 });

	UpdateFunc = &BigBox::GravityUpdate;
}

void BigBox::Update(float _DeltaTime)
{
	TimeCounting();

	if(UpdateFunc != nullptr)
	{
		UpdateFunc(*this, _DeltaTime);
	}
}

void BigBox::Render(float _DeltaTime)
{

}

bool BigBox::GravityUpdate(float _DeltaTime)
{
	float Gravity = 200.0f;

	float4 BoxPos = GetTransform()->GetLocalPosition();

	float4 MapHalfScale = { static_cast<float>(ColMap->GetWidth() / 2) ,  static_cast<float>(ColMap->GetHeight() / 2) };
	float4 ColorPos = float4{ MapHalfScale.x, MapHalfScale.y } + float4{ BoxPos.x, -BoxPos.y };

	GameEnginePixelColor Color = { (char)255, 0, (char)255, (char)255 };

	int X = static_cast<int>(ColorPos.x);
	int Y = static_cast<int>(ColorPos.y);

	GameEnginePixelColor MapColor = ColMap->GetPixel(static_cast<int>(ColorPos.x), static_cast<int>(ColorPos.y));

	if (Color != MapColor)
	{
		GetTransform()->AddLocalPosition({ 0 , -Gravity * _DeltaTime, 0 });

		isGround = false;
	}
	else
	{
		float Count = 0.0f;

		while (Color == MapColor)
		{
			ColorPos.y--;
			MapColor = ColMap->GetPixel(static_cast<int>(ColorPos.x), static_cast<int>(ColorPos.y));
			Count++;
		}

		GetTransform()->AddLocalPosition({ 0, Count - 1 });

		isGround = true;
		UpdateFunc = &BigBox::CollisionCheck;
		return true;
	}

	return false;
}

bool BigBox::CollisionCheck(float _Deltatime)
{
	std::shared_ptr<GameEngineCollision> Col = BoxCollision->Collision(static_cast<int>(CollisionOrder::DropItem), ColType::AABBBOX2D, ColType::AABBBOX2D);

	if (Col != nullptr)
	{
		std::shared_ptr<DropItem> ColItem = Col->GetActor()->DynamicThis<DropItem>();
		std::string ItemName = GameEngineString::ToUpper(ColItem->GetItemName().data());

		if (ItemName == "BOXKEY")
		{
			ColCount += TimeCount;

			if (ColCount >= 2.0f)
			{
				ColItem->GetRender()->ColorOptionValue.MulColor.a -= 1.0f * _Deltatime;

				if (ColItem->GetRender()->ColorOptionValue.MulColor.a <= 0.0f)
				{
					ColItem->Death();
					BoxRender->ChangeAnimation("Death");
					UpdateFunc = nullptr;
				}
			}

			return true;
		}
	}
	return false;
}