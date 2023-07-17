#include "PrecompileHeader.h"
#include "MiniMap.h"
#include "Player.h"
#include "ContentFontRenderer.h"
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

	MapMark = CreateComponent<GameEngineUIRenderer>();

	WorldNameWhiteLayer = CreateComponent<ContentFontRenderer>();
	WorldNameBlackLayer1 = CreateComponent<ContentFontRenderer>();
	WorldNameBlackLayer2 = CreateComponent<ContentFontRenderer>();
	
	WorldName = CreateComponent<ContentFontRenderer>();

	MapNameWhiteLayer = CreateComponent<ContentFontRenderer>();
	MapNameBlackLayer1 = CreateComponent<ContentFontRenderer>();
	MapNameBlackLayer2 = CreateComponent<ContentFontRenderer>();

	MapName = CreateComponent<ContentFontRenderer>();

	MiniMapOff();

	MiniMapBox->GetTransform()->SetLocalPosition(float4{ -400, 300 } + float4{ 100, -100 });
	float4 MapBoxPos = MiniMapBox->GetTransform()->GetLocalPosition();

	MapMark->GetTransform()->SetLocalPosition(MapBoxPos + float4{ -72, 58 });
	Map->GetTransform()->SetLocalPosition(MapBoxPos + float4{ 0, -45 });
	
	WorldNameBlackLayer1->SetFont("±¼¸²");
	WorldNameBlackLayer1->SetScale(13.0f);
	WorldNameBlackLayer1->SetColor({ 0.0f, 0.0f, 0.0f, 1.0f });
	WorldNameBlackLayer1->GetTransform()->SetLocalPosition(MapBoxPos + float4{ -50, 75 });
	
	WorldNameBlackLayer2->SetFont("±¼¸²");
	WorldNameBlackLayer2->SetScale(13.0f);
	WorldNameBlackLayer2->SetColor({ 0.0f, 0.0f, 0.0f, 1.0f });
	WorldNameBlackLayer2->GetTransform()->SetLocalPosition(MapBoxPos + float4{ -51, 75 });

	WorldNameWhiteLayer->SetFont("±¼¸²");
	WorldNameWhiteLayer->SetScale(13.0f);
	WorldNameWhiteLayer->SetColor({ 1.0f, 1.0f, 1.0f, 1.0f });
	WorldNameWhiteLayer->GetTransform()->SetLocalPosition(MapBoxPos + float4{ -49, 76, -1 });

	WorldName->SetFont("±¼¸²");
	WorldName->SetScale(13.0f);
	WorldName->SetColor({ 1.0f, 1.0f, 1.0f, 1.0f });
	WorldName->GetTransform()->SetLocalPosition(MapBoxPos + float4{ -50, 76, -1 });

	//
	MapNameBlackLayer1->SetFont("±¼¸²");
	MapNameBlackLayer1->SetScale(13.0f);
	MapNameBlackLayer1->SetColor({ 0.0f, 0.0f, 0.0f, 1.0f });
	MapNameBlackLayer1->GetTransform()->SetLocalPosition(MapBoxPos + float4{ -50, 56 });
	
	MapNameBlackLayer2->SetFont("±¼¸²");
	MapNameBlackLayer2->SetScale(13.0f);
	MapNameBlackLayer2->SetColor({ 0.0f, 0.0f, 0.0f, 1.0f });
	MapNameBlackLayer2->GetTransform()->SetLocalPosition(MapBoxPos + float4{ -51, 56 });
	
	MapNameWhiteLayer->SetFont("±¼¸²");
	MapNameWhiteLayer->SetScale(13.0f);
	MapNameWhiteLayer->SetColor({ 1.0f, 1.0f, 1.0f, 1.0f });
	MapNameWhiteLayer->GetTransform()->SetLocalPosition(MapBoxPos + float4{ -49, 57, -1});
	
	MapName->SetFont("±¼¸²");
	MapName->SetScale(13.0f);
	MapName->SetColor({ 1.0f, 1.0f, 1.0f, 1.0f });
	MapName->GetTransform()->SetLocalPosition(MapBoxPos + float4{ -50, 57, -1 });
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
	MapMark->On();

	WorldName->On();
	WorldNameWhiteLayer->On();
	WorldNameBlackLayer1->On();
	WorldNameBlackLayer2->On();

	MapName->On();
	MapNameWhiteLayer->On();
	MapNameBlackLayer1->On();
	MapNameBlackLayer2->On();
	MarkOn();
}

void MiniMap::MiniMapOff()
{
	Filter->Off();
	Map->Off();
	MiniMapBox->Off();
	UserMark->Off();
	MapMark->Off();

	WorldName->Off();
	WorldNameWhiteLayer->Off();
	WorldNameBlackLayer1->Off();
	WorldNameBlackLayer2->Off();

	MapName->Off();
	MapNameWhiteLayer->Off();
	MapNameBlackLayer1->Off();
	MapNameBlackLayer2->Off();

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


void MiniMap::SetMapMark(const std::string_view& _MarkName)
{
	MapMark->SetScaleToTexture(_MarkName);
}

void MiniMap::SetWorldName(const std::string_view& _MarkName)
{
	WorldName->SetText(_MarkName);
	WorldNameWhiteLayer->SetText(_MarkName);
	WorldNameBlackLayer1->SetText(_MarkName);
	WorldNameBlackLayer2->SetText(_MarkName);
}

void MiniMap::SetMapName(const std::string_view& _MarkName)
{
	MapName->SetText(_MarkName);
	MapNameWhiteLayer->SetText(_MarkName);
	MapNameBlackLayer1->SetText(_MarkName);
	MapNameBlackLayer2->SetText(_MarkName);

}