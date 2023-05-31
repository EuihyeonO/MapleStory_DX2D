#include "PrecompileHeader.h"
#include "Item.h"

#include <GameEngineCore/GameEngineUIRenderer.h>
Item::Item()
{
}

Item::~Item()
{
}

void Item::Start()
{
	ItemRender = CreateComponent<GameEngineUIRenderer>();
}

void Item::Update(float _DeltaTime) 
{
}

void Item::Render(float _DeltaTime) 
{
}

void Item::SetItemInfo(const std::string_view& _ItemName, int _ItemType)
{
	ItemName = _ItemName;
	ItemType = static_cast<int>(_ItemType);

	ItemRender->SetScaleToTexture(ItemName + "Icon.png");
}