#include "PrecompileHeader.h"
#include "BeginnersTown1.h"
#include "MiniMap.h"
#include "Hina.h"
#include "ContentEnums.h"
#include "GreenSnail.h"
#include "MonsterSpawnZone.h"

#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineUIRenderer.h>
#include <ctime>

BeginnersTown1::BeginnersTown1()
{
}

BeginnersTown1::~BeginnersTown1()
{
}

void BeginnersTown1::Start()
{
	//std::shared_ptr<GameEngineCamera> Camera = GetLevel()->GetCamera(100);
	//Camera->SetProjectionType(CameraType::Orthogonal);
	//Camera->GetTransform()->SetLocalPosition({0, 0, -10});
	//Camera->SetSortType(100, SortType::ZSort);

	MyMiniMap = GetLevel()->CreateActor<MiniMap>(static_cast<int>(RenderOrder::UI));
	MyMiniMap->SetMap(MapName);

	std::shared_ptr<Hina> npc = GetLevel()->CreateActor<Hina>(static_cast<int>(RenderOrder::NPC));

	std::shared_ptr<MonsterSpawnZone> Zone = GetLevel()->CreateActor<MonsterSpawnZone>();
	Zone->SetColMap(ColMapName);
	Zone->SetMonsterToZone(MonsterName::GreenSnail, 5);
	Zone->SetZonePosAndScale({ 200,0 }, 200.0f);

	LandScape0 = CreateComponent<GameEngineSpriteRenderer>();
	LandScape0->SetTexture("MapBackGround0.png");
	LandScape0->GetTransform()->SetLocalScale({2000, 2000});

	Cloud = CreateComponent<GameEngineSpriteRenderer>();
	Cloud->SetScaleToTexture("MapBackGround1.png");

	float4 CloudScale = Cloud->GetTransform()->GetLocalScale();
	Cloud->GetTransform()->SetLocalPosition({ 0, 250 });
	Cloud->GetTransform()->AddLocalScale({ CloudScale.x * 2.0f, 0 });

	LandScape2 = CreateComponent<GameEngineSpriteRenderer>();
	LandScape2->SetScaleToTexture("MapBackGround2.png");
	LandScape2->GetTransform()->SetLocalPosition({ 0, 200 });

	BackGroundLayer = CreateComponent<GameEngineSpriteRenderer>();
	BackGroundLayer->SetScaleToTexture("BeginnersTown1Layer.png");

	BackGround = CreateComponent<GameEngineSpriteRenderer>();
	BackGround->SetScaleToTexture("BeginnersTown1.png");

	Rope = CreateComponent<GameEngineSpriteRenderer>();
	Rope->SetScaleToTexture("BeginnersTown1Rope.png");

}

void BeginnersTown1::Update(float _DeltaTime)
{
	PosUpdate();
	CloudMove(_DeltaTime);
}

void BeginnersTown1::Render(float _DeltaTime) 
{
}

void BeginnersTown1::CloudMove(float _DeltaTime)
{
	XMoveConstant += 0.06f * _DeltaTime;

	if (XMoveConstant > 3.0f)
	{
		XMoveConstant -= 3.0f;
	}

	//Cloud->SetUVconstant({ XMoveConstant, 0, 3 });

	float4 CameraPos = GetLevel()->GetMainCamera()->GetTransform()->GetLocalPosition();
	LandScape2->GetTransform()->SetLocalPosition({ CameraPos.x * 0.5f , 200 });
}


void BeginnersTown1::PosUpdate()
{
	float4 CamPos = GetLevel()->GetMainCamera()->GetTransform()->GetLocalPosition();
	Cloud->GetTransform()->SetLocalPosition(CamPos + float4{0, 250});
}