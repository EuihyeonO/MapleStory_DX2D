#pragma once
#include <GameEngineCore/GameEngineActor.h>

class GameEngineSpriteRenderer;
class MonsterSpawnZone : public GameEngineActor
{

public:

	MonsterSpawnZone();
	~MonsterSpawnZone();

	MonsterSpawnZone(const MonsterSpawnZone& _Other) = delete;
	MonsterSpawnZone(MonsterSpawnZone&& _Other) noexcept = delete;
	MonsterSpawnZone& operator=(const MonsterSpawnZone& _Other) = delete;
	MonsterSpawnZone& operator=(MonsterSpawnZone&& _Other) noexcept = delete;

	void NumOfMonsterUp(int _MonsterName)
	{
		NumOfMonster[_MonsterName].second++;
	}

	void NumOfMonsterDown(int _MonsterName)
	{
		if (NumOfMonster[_MonsterName].second <= 0)
		{
			MsgAssert("SpawnZone�� ��ϵ� ���� ������ ���ڰ� 0�����Դϴ�. ���� ������ ���� ���� �ʿ䰡 �ֽ��ϴ�. ȣ���Լ� MonsterSpawnZone::NumOfMonsterDown ");
		}

		NumOfMonster[_MonsterName].second--;
	}

	template<typename EnumType>
	void SetMonsterToZone(EnumType _MonsterName, int _MaxNumber)
	{
		std::map<int, std::pair<int, int>>::iterator Start = NumOfMonster.begin();
		std::map<int, std::pair<int, int>>::iterator End = NumOfMonster.end();

		for (;Start != End; Start++)
		{
			if (Start->first == static_cast<int>(_MonsterName))
			{
				MsgAssert("�̹� SpawnZone�� ���õ� �����Դϴ�. ȣ���Լ� MonsterSpawnZone::SetMonsterToZone, �����̸�(EnumType�� int��) : " + std::to_string(static_cast<int>(_MonsterName)));
			}
		}

		NumOfMonster[static_cast<int>(_MonsterName)].first = _MaxNumber;
		NumOfMonster[static_cast<int>(_MonsterName)].second = 0;
	}

	void SetZonePosAndScale(float4 _Pos, float _Length)
	{
		GetTransform()->SetLocalPosition(_Pos);
		Range = _Length;
	}

	void SetColMap(const std::string_view& _ColMapName)
	{
		ColMapName = _ColMapName;
	}

protected:
	void Start();
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;
private:

	void SpawnUpdate();
	void SpawnMonster(int _MonsterName);

	// �����̸�, �ִ� �� , ���� ��
	std::map<int, std::pair<int, int>> NumOfMonster;
	std::string ColMapName = "";
	float Range = 0.0f;
};

