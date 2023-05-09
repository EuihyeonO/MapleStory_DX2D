#include "PrecompileHeader.h"
#include "MiniMap.h"
#include "Player.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>

MiniMap::MiniMap()
{
}

MiniMap::~MiniMap()
{
}

void MiniMap::Start()
{
	Filter = CreateComponent<GameEngineSpriteRenderer>();
	Filter->SetScaleToTexture("Filter.png");

	Map = CreateComponent<GameEngineSpriteRenderer>();

	MiniMapBox = CreateComponent<GameEngineSpriteRenderer>();
	MiniMapBox->SetScaleToTexture("MiniMapBox.png");

	UserMark = CreateComponent<GameEngineSpriteRenderer>();
	UserMark->SetScaleToTexture("user.png");
}

void MiniMap::Update(float _DeltaTime)
{
	float4 CameraPos = GetLevel()->GetMainCamera()->GetTransform()->GetLocalPosition();

	MiniMapBox->GetTransform()->SetLocalPosition(CameraPos + float4{ -400, 300 } + float4{ 100, -100 });
	float4 MapBoxPos = MiniMapBox->GetTransform()->GetLocalPosition();

	Map->GetTransform()->SetLocalPosition(MapBoxPos + float4{0, -45});

	float4 MiniMapPos = Map->GetTransform()->GetLocalPosition();
	float4 PlayerPos = Player::GetCurPlayer()->GetTransform()->GetLocalPosition();

	Filter->GetTransform()->SetLocalPosition(MiniMapPos + float4{0, 15});
	UserMark->GetTransform()->SetLocalPosition(MiniMapPos + PlayerPos * DownSizeRatio);
}

void MiniMap::Render(float _DeltaTime) 
{
}

void MiniMap::SetMap(const std::string_view& _MapName)
{
	Map->SetTexture(_MapName);
	Map->GetTransform()->SetLocalScale({ 190.0f, 135.0f });

	std::shared_ptr<GameEngineTexture> SettingMap = GameEngineTexture::Find(_MapName);
	float4 MapScale = { static_cast<float>(SettingMap->GetWidth()), static_cast<float>(SettingMap->GetHeight()) };

	DownSizeRatio = { 190.0f / MapScale.x, 135.0f / MapScale.y };
}