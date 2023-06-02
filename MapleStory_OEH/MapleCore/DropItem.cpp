#include "PrecompileHeader.h"
#include "DropItem.h"
#include "GlobalFunction.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

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

	float4 NextPos;
	float4 CurPos = GetTransform()->GetLocalPosition();

	NextPos.x = CurPos.x + 2.0f * XDistance * _DeltaTime;
	NextPos.y = CurPos.y;
	//NextPos.y = Coefficient * (NextPos.x - StartPos.x) * (NextPos.x - Xintercept) + StartPos.y;

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

		GetTransform()->SetLocalPosition({ NextPos.x, static_cast<float>(ConvertYtoInt - 1.0f)});
		return;
	}

	GetTransform()->SetLocalPosition(NextPos);
	//if (Color == MapColor)
	//{
	//	while (Color == MapColor)
	//	{
	//		NextPos.y++;
	//		ColorPos.y--;

	//		MapColor = ColMap->GetPixel(static_cast<int>(ColorPos.x), static_cast<int>(ColorPos.y));
	//	}

	//	int ConvertYtoInt = static_cast<int>(NextPos.y);

	//	GetTransform()->SetLocalPosition({ CurPos.x, static_cast<float>(ConvertYtoInt - 1.0f)});
	//	DropItemRender->GetTransform()->SetLocalRotation({ 0, 0, 0 });
	//	return;
	//}

	//GetTransform()->SetLocalPosition(NextPos);
	//DropItemRender->GetTransform()->AddLocalRotation({ 0, 0, -Dir * 720.0f * _DeltaTime });
}

void DropItem::SetDropItemInfo(const std::string_view& _ItemName)
{
	std::string ItemName = _ItemName.data();
	DropItemRender->SetScaleToTexture(ItemName + ".png");

	TransformData RenderData = DropItemRender->GetTransform()->GetTransDataRef();

	DropItemRender->GetTransform()->SetLocalPosition({ 0.0f, RenderData.LocalScale.y * 0.5f });
	DropItemRender->On();

	DropItemCollision->GetTransform()->SetLocalScale(RenderData.LocalScale);
	DropItemCollision->On();

	isInfoSet = true;
}