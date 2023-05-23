#include "PrecompileHeader.h"
#include "MonsterSpawnZone.h"
#include "GreenSnail.h"

#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineBase/GameEngineRandom.h>

MonsterSpawnZone::MonsterSpawnZone()
{
}

MonsterSpawnZone::~MonsterSpawnZone()
{
} 

void MonsterSpawnZone::Start()
{

}

void MonsterSpawnZone::Update(float _DeltaTime) 
{
	SpawnUpdate();
}

void MonsterSpawnZone::Render(float _DeltaTime)
{
}

void MonsterSpawnZone::SpawnUpdate()
{
	std::map<int, std::pair<int, int>>::iterator Start = NumOfMonster.begin();
	std::map<int, std::pair<int, int>>::iterator End = NumOfMonster.end();

	for (; Start != End; Start++)
	{
		if (Start->second.first > Start->second.second)
		{
			SpawnMonster(Start->first);
		}
	}
}


void MonsterSpawnZone::SpawnMonster(int _MonsterName)
{
	switch (_MonsterName)
	{
	case static_cast<int>(MonsterName::GreenSnail):
	{
		std::shared_ptr<GreenSnail> _GreenSnail = GetLevel()->CreateActor<GreenSnail>();
		_GreenSnail->SetMyZone(this,&MonsterSpawnZone::NumOfMonsterUp);
		_GreenSnail->SetColMap(ColMapName);
		
		TransformData ZoneData = GetTransform()->GetTransDataRef();
		float SpawnXpos = GameEngineRandom::MainRandom.RandomFloat(-Range, Range);
		_GreenSnail->GetTransform()->SetLocalPosition({ ZoneData.WorldPosition.x + SpawnXpos, ZoneData.WorldPosition.y });
	}
		break;
	default:
		break;
	}
}
