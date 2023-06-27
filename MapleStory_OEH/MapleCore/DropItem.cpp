#include "PrecompileHeader.h"
#include "DropItem.h"
#include "GlobalFunction.h"
#include "Player.h"
#include "UIController.h"

#include <GameEnginePlatform/GameEngineInput.h>

DropItem::DropItem()
{
}

DropItem::~DropItem()          
{
}

void DropItem::Start()
{
	DropItemRender = CreateComponent<GameEngineSpriteRenderer>();
	DropItemRender->Off();
	DropItemCollision = CreateComponent<GameEngineCollision>();
	DropItemCollision->SetOrder(static_cast<int>(CollisionOrder::DropItem));
	DropItemCollision->Off();

	ColMap = GlobalFunction::GetValue()->GetColMap();
}

void DropItem::Update(float _DeltaTime)
{
	MoveDropItem(_DeltaTime);
}

void DropItem::Render(float _DeltaTime) 
{
}

void DropItem::MoveDropItem(float _DeltaTime)
{

	if (isFuncSet == false || isInfoSet == false)
	{
		return;
	}

	if (isGet == true)
	{
		//플레이어로 다가가는 모션
		float4 CurPos = GetTransform()->GetLocalPosition();

		if (DropItemCollision->IsUpdate() == false)
		{
			GetTransform()->AddLocalPosition({ 0, 140.0f * _DeltaTime });

			if (abs(CurPos.y - StartPos.y) >= 10.0f)
			{
				DropItemCollision->On();
			}
		}
		else
		{
			float4 PlayerPos = Player::GetCurPlayer()->GetTransform()->GetWorldPosition();
			float4 GetDir = { PlayerPos.x - CurPos.x , PlayerPos.y - CurPos.y + 15.0f };
			GetDir.Normalize();

			GetTransform()->AddLocalPosition(GetDir * 250.0f * _DeltaTime);
		}

		if (DropItemCollision->Collision(static_cast<int>(CollisionOrder::PlayerPoint), ColType::AABBBOX2D, ColType::AABBBOX2D) != nullptr)
		{
			std::shared_ptr<ItemInfo> NewItem = std::make_shared<ItemInfo>();
			NewItem->ItemName = ItemName;

			UIController::GetUIController()->AddToItemList(NewItem, static_cast<int>(ItemType::Etc));
			Death();
			return;
		}
	}

	if (isGround == true)
	{
		if (UpMove == true)
		{
			VerticalMoveCount += 2.0f * _DeltaTime;
			GetTransform()->AddLocalPosition({ 0,2.0f * _DeltaTime });

			if (VerticalMoveCount >= 2.0f)
			{
				VerticalMoveCount = 0.0f;
				UpMove = false;
				DownMove = true;
			}
		}
		else if (DownMove == true)
		{
			VerticalMoveCount -= 2.0f * _DeltaTime;
			GetTransform()->AddLocalPosition({ 0, -2.0f * _DeltaTime });

			if (VerticalMoveCount <= -2.0f)
			{
				VerticalMoveCount = 0.0f;
				UpMove = true;
				DownMove = false;
			}
		}

		return;
	}

	float4 NextPos;
	float4 CurPos = GetTransform()->GetLocalPosition();

	NextPos.x = CurPos.x + 2.0f * XDistance * _DeltaTime;
	NextPos.y = CurPos.y;
	NextPos.z = -15.0f;

	float4 MapSize = ColMap->GetScale();

	float4 ColorPos;
	ColorPos.x = MapSize.hx() + NextPos.x;
	ColorPos.y = MapSize.hy() - NextPos.y;

	GameEnginePixelColor Color = { (char)255, 0, (char)255, (char)255 };
	GameEnginePixelColor MapColor = ColMap->GetPixel(static_cast<int>(ColorPos.x), static_cast<int>(ColorPos.y));

	if (Color == MapColor)
	{
		NextPos.x = CurPos.x;
		NextPos.y -= 400.0f * _DeltaTime;
	}
	else
	{
		NextPos.x = CurPos.x + 2.0f * XDistance * _DeltaTime;
		NextPos.y = Coefficient * (NextPos.x - StartPos.x) * (NextPos.x - Xintercept) + StartPos.y;
	}

	ColorPos.x = MapSize.hx() + NextPos.x;
	ColorPos.y = MapSize.hy() - NextPos.y;
	MapColor = ColMap->GetPixel(static_cast<int>(ColorPos.x), static_cast<int>(ColorPos.y));

	if (Color == MapColor)
	{
		while (Color == MapColor)
		{
			NextPos.y++;
			ColorPos.y--;

			MapColor = ColMap->GetPixel(static_cast<int>(ColorPos.x), static_cast<int>(ColorPos.y));
		}

		int ConvertYtoInt = static_cast<int>(NextPos.y);

		GetTransform()->SetLocalPosition({ NextPos.x, static_cast<float>(ConvertYtoInt - 1.0f), -15.0f});
		DropItemRender->GetTransform()->SetLocalRotation({ 0, 0, 0 });
		isGround = true;
		return;
	}

	GetTransform()->SetLocalPosition(NextPos);
	DropItemRender->GetTransform()->AddLocalRotation({ 0.0f, 0.0f, -Dir * 1440.0f * _DeltaTime });
}

void DropItem::SetDropItemInfo(const std::string_view& _ItemName)
{
	ItemName = _ItemName.data();
	DropItemRender->SetScaleToTexture(ItemName + "Icon.png");

	TransformData RenderData = DropItemRender->GetTransform()->GetTransDataRef();

	DropItemRender->GetTransform()->SetLocalPosition({ 0.0f, RenderData.LocalScale.y * 0.5f });
	DropItemRender->On();

	DropItemCollision->GetTransform()->SetLocalScale({5, 5});
	DropItemCollision->On();

	isInfoSet = true;
}

void DropItem::GetItem()
{
	isGet = true;
	StartPos = GetTransform()->GetLocalPosition();
	DropItemCollision->Off();
}
