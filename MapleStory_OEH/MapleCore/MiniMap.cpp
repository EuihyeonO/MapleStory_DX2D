#include "PrecompileHeader.h"
#include "MiniMap.h"
#include "Player.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineUIRenderer.h>
#include <GameEngineCore/GameEngineCamera.h>

MiniMap::MiniMap()
{
}

MiniMap::~MiniMap()
{
}

void MiniMap::Start()
{
	CreateInputKey();

	Filter = CreateComponent<GameEngineUIRenderer>();
	Filter->SetScaleToTexture("Filter.png");

	Map = CreateComponent<GameEngineUIRenderer>();

	MiniMapBox = CreateComponent<GameEngineUIRenderer>();
	MiniMapBox->SetScaleToTexture("MiniMapBox.png");

	UserMark = CreateComponent<GameEngineUIRenderer>();
	UserMark->SetScaleToTexture("userposPoint.png");

	MiniMapOff();


	MiniMapBox->GetTransform()->SetLocalPosition(float4{ -400, 300 } + float4{ 100, -100 });
	float4 MapBoxPos = MiniMapBox->GetTransform()->GetLocalPosition();

	Map->GetTransform()->SetLocalPosition(MapBoxPos + float4{ 0, -45 });
}

void MiniMap::Update(float _DeltaTime)
{
	GetKetInput();
	MiniMapUpdate();
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

void MiniMap::MiniMapOn()
{
	Filter->On();
	Map->On();
	MiniMapBox->On();
	UserMark->On();
	MarkOn();
}

void MiniMap::MiniMapOff()
{
	Filter->Off();
	Map->Off();
	MiniMapBox->Off();
	UserMark->Off();
	MarkOff();
}

bool MiniMap::MiniMapOnOff()
{
	if (MiniMapBox->IsUpdate() == false)
	{
		MiniMapOn();
		UpdateFunction.push_back(&MiniMap::PosUpdate);
		return true;
	}
	else
	{
		MiniMapOff();
		return true;
	}
}

bool MiniMap::PosUpdate()
{
	float4 MiniMapPos = Map->GetTransform()->GetLocalPosition();

	if(Player::GetCurPlayer() != nullptr)
	{
		float4 PlayerPos = Player::GetCurPlayer()->GetTransform()->GetLocalPosition();

		Filter->GetTransform()->SetLocalPosition(MiniMapPos + float4{ 0, 15 });
		UserMark->GetTransform()->SetLocalPosition(MiniMapPos + (PlayerPos + float4{0, 25}) * DownSizeRatio);
	}

	if (MiniMapBox->IsUpdate() == true) 
	{
		return false;
	}
	else
	{
		return true;
	}
}

void MiniMap::CreateInputKey()
{
	if (GameEngineInput::IsKey("MiniMapOpen") == false)
	{
		GameEngineInput::CreateKey("MiniMapOpen", 'M');
	}
}

void MiniMap::GetKetInput()
{
	if (GameEngineInput::IsDown("MiniMapOpen") == true)
	{
		UpdateFunction.push_back(&MiniMap::MiniMapOnOff);
	}
}

void MiniMap::MiniMapUpdate()
{
	if (UpdateFunction.size() == 0)
	{
		return;
	}

	std::list<std::function<bool(MiniMap&)>>::iterator StartIter = UpdateFunction.begin();
	std::list<std::function<bool(MiniMap&)>>::iterator EndIter = UpdateFunction.end();

	for (; StartIter != EndIter; )
	{
		std::function<bool(MiniMap&)> Func = *StartIter;
		bool IsEnd = Func(*this);

		if (IsEnd == true)
		{
			StartIter = UpdateFunction.erase(StartIter);
			continue;
		}

		StartIter++;
	}
}

void MiniMap::SetNPCToMiniMap(float4 _Pos)
{
	std::shared_ptr<GameEngineUIRenderer> NewNPCPoint = CreateComponent<GameEngineUIRenderer>();
	NewNPCPoint->SetScaleToTexture("NPCPosPoint.png");
	
	float4 MiniMapPos = Map->GetTransform()->GetLocalPosition();
	NewNPCPoint->GetTransform()->SetLocalPosition(MiniMapPos + _Pos * DownSizeRatio);

	NPCMarkList.push_back(NewNPCPoint);

	MarkOff();
}


void MiniMap::SetPortalToMiniMap(float4 _Pos)
{
	std::shared_ptr<GameEngineUIRenderer> NewPortalPoint = CreateComponent<GameEngineUIRenderer>();
	NewPortalPoint->SetScaleToTexture("PortalPosPoint.png");

	float4 MiniMapPos = Map->GetTransform()->GetLocalPosition();
	NewPortalPoint->GetTransform()->SetLocalPosition(MiniMapPos + (_Pos + float4{0, -80}) * DownSizeRatio);

	PortalMarkList.push_back(NewPortalPoint);

	MarkOff();
}

void MiniMap::MarkOn()
{
	std::list<std::shared_ptr<GameEngineUIRenderer>>::iterator StartIter = NPCMarkList.begin();
	std::list<std::shared_ptr<GameEngineUIRenderer>>::iterator EndIter = NPCMarkList.end();

	for (; StartIter != EndIter; StartIter++)
	{
		(*StartIter)->On();
	}

	StartIter = PortalMarkList.begin();
	EndIter = PortalMarkList.end();

	for (; StartIter != EndIter; StartIter++)
	{
		(*StartIter)->On();
	}
}

void MiniMap::MarkOff()
{
	std::list<std::shared_ptr<GameEngineUIRenderer>>::iterator StartIter = NPCMarkList.begin();
	std::list<std::shared_ptr<GameEngineUIRenderer>>::iterator EndIter = NPCMarkList.end();

	for (; StartIter != EndIter; StartIter++)
	{
		(*StartIter)->Off();
	}

	StartIter = PortalMarkList.begin();
	EndIter = PortalMarkList.end();

	for (; StartIter != EndIter; StartIter++)
	{
		(*StartIter)->Off();
	}
}