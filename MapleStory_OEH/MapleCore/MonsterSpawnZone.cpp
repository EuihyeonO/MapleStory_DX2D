#include "PrecompileHeader.h"
#include "MonsterSpawnZone.h"
#include "GreenSnail.h"
#include "Boogie.h"
#include "Spore.h"
#include "BlueSnail.h"

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
	std::map<int, std::shared_ptr<MonsterInfo>>::iterator Start = NumOfMonster.begin();
	std::map<int, std::shared_ptr<MonsterInfo>>::iterator End = NumOfMonster.end();

	for (; Start != End; Start++)
	{
		if (Start->second == nullptr)
		{
			continue;
		}

		if (Start->second->MaxNum > Start->second->CurNum)
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
		_GreenSnail->GetTransform()->SetLocalPosition({ ZoneData.WorldPosition.x + SpawnXpos, ZoneData.WorldPosition.y, -10 });
		
		NumOfMonster[static_cast<int>(MonsterName::GreenSnail)]->MonsterList.push_back(_GreenSnail->DynamicThis<MonsterBasicFunction>());
	}
		break;
	case static_cast<int>(MonsterName::Boogie):
	{
		std::shared_ptr<Boogie> _Boogie = GetLevel()->CreateActor<Boogie>();
		_Boogie->SetMyZone(this, &MonsterSpawnZone::NumOfMonsterUp);
		_Boogie->SetColMap(ColMapName);

		TransformData ZoneData = GetTransform()->GetTransDataRef();
		float SpawnXpos = GameEngineRandom::MainRandom.RandomFloat(-Range, Range);
		_Boogie->GetTransform()->SetLocalPosition({ ZoneData.WorldPosition.x + SpawnXpos, ZoneData.WorldPosition.y, -10 });

		NumOfMonster[static_cast<int>(MonsterName::Boogie)]->MonsterList.push_back(_Boogie->DynamicThis<MonsterBasicFunction>());
	}
		break;
	case static_cast<int>(MonsterName::Spore):
	{
		std::shared_ptr<Spore> _Spore = GetLevel()->CreateActor<Spore>();
		_Spore->SetMyZone(this, &MonsterSpawnZone::NumOfMonsterUp);
		_Spore->SetColMap(ColMapName);

		TransformData ZoneData = GetTransform()->GetTransDataRef();
		float SpawnXpos = GameEngineRandom::MainRandom.RandomFloat(-Range, Range);
		_Spore->GetTransform()->SetLocalPosition({ ZoneData.WorldPosition.x + SpawnXpos, ZoneData.WorldPosition.y, -10 });

		NumOfMonster[static_cast<int>(MonsterName::Spore)]->MonsterList.push_back(_Spore->DynamicThis<MonsterBasicFunction>());
	}
		break;
	case static_cast<int>(MonsterName::BlueSnail):
	{
		std::shared_ptr<BlueSnail> _BlueSnail = GetLevel()->CreateActor<BlueSnail>();
		_BlueSnail->SetMyZone(this, &MonsterSpawnZone::NumOfMonsterUp);
		_BlueSnail->SetColMap(ColMapName);

		TransformData ZoneData = GetTransform()->GetTransDataRef();
		float SpawnXpos = GameEngineRandom::MainRandom.RandomFloat(-Range, Range);
		_BlueSnail->GetTransform()->SetLocalPosition({ ZoneData.WorldPosition.x + SpawnXpos, ZoneData.WorldPosition.y, -10 });

		NumOfMonster[static_cast<int>(MonsterName::BlueSnail)]->MonsterList.push_back(_BlueSnail->DynamicThis<MonsterBasicFunction>());
	}
	break;
	default:
		break;
	}
}


void MonsterSpawnZone::AllMonsterDeath()
{
	std::map<int, std::shared_ptr<MonsterInfo>>::iterator Start = NumOfMonster.begin();
	std::map<int, std::shared_ptr<MonsterInfo>>::iterator End = NumOfMonster.end();

	for (; Start != End; Start++)
	{
		if (Start->second == nullptr)
		{
			continue;
		}
		
		size_t Size = Start->second->MonsterList.size();

		for (int i = 0; i < Size; i++)
		{
			Start->second->MonsterList[i]->Death();
			Start->second->MonsterList[i] = nullptr;
		}
	}
}