#pragma once
#include <string>
#include <string_view>

class PlayerValue
{
	friend class Player;

public: //static

	static PlayerValue* GetValue()
	{
		return &Value;
	}

public: //local
	

	void SetMp(int _Mp)
	{
		Mp = _Mp;
	}

	int GetLevel()
	{
		return Level;
	}

	void SetLevel(int _Level)
	{
		Level = _Level;
	}

	void LevelUp()
	{
		++Level;
	}

	void AddLevel(int _Value)
	{
		Level += _Value;
	}

	int GetStr()
	{
		return Str;
	}

	void SetStr(int _Str)
	{
		Str = _Str;
	}

	void AddStr(int _Value)
	{
		Str += _Value;
	}

	int GetDex()
	{
		return Dex;
	}

	void SetDex(int _Dex)
	{
		Dex = _Dex;
	}

	void AddDex(int _Value)
	{
		Dex += _Value;
	}
	
	int GetLuk()
	{
		return Luk;
	}

	void SetLuk(int _Luk)
	{
		Luk = _Luk;
	}

	void AddLuk(int _Value)
	{
		Luk += _Value;
	}

	int GetInt()
	{
		return Int;
	}

	void SetInt(int _Int)
	{
		Int = _Int;
	}

	void AddInt(int _Value)
	{
		Int += _Value;
	}

	int GetMaxExp()
	{
		return MaxExp;
	}

	int GetExp()
	{
		return Exp;
	}

	float GetExpRate()
	{
		if(Exp != 0)
		{
			return static_cast<float>(Exp) / static_cast<float>(MaxExp);
		}
		else
		{
			return 0.0f;
		}
	}

	void SetMaxExp(int _MaxExp)
	{
		MaxExp = _MaxExp;
	}

	void AddExp(int _Exp)
	{
		Exp += _Exp;
	}

	int GetHp()
	{
		return Hp;
	}

	int GetMaxHp()
	{
		return MaxHp;
	}

	void SetMaxHp(int _MaxHp)
	{
		MaxHp = _MaxHp;
	}

	float GetHpRate()
	{
		if (Hp != 0)
		{
			return static_cast<float>(Hp) / static_cast<float>(MaxHp);
		}
		else
		{
			return 0.0f;
		}
	}

	void SubHp(int _Hp)
	{
		Hp -= _Hp;
	}

	int GetMp()
	{
		return Mp;
	}

	int GetMaxMp()
	{
		return MaxMp;
	}

	void SetMaxMp(int _MaxMp)
	{
		MaxMp = _MaxMp;
	}

	float4 GetMoveDistance()
	{
		return MoveDistance;
	}


	void SetMoveDistance(float4 _MoveDistance)
	{
		MoveDistance = _MoveDistance;
	}

	float GetMpRate()
	{
		if (Mp != 0)
		{
			return static_cast<float>(Mp) / static_cast<float>(MaxMp);
		}
		else
		{
			return 0.0f;
		}
	}

	void SubMp(int _Mp)
	{
		Mp -= _Mp;
	}

	const std::string_view& GetName()
	{
		return Name;
	}

	void SetName(const std::string_view& _Name)
	{
		Name = _Name;
	}

	PlayerValue(const PlayerValue& _Other) = delete;
	PlayerValue(PlayerValue&& _Other) noexcept = delete;
	PlayerValue& operator=(const PlayerValue& _Other) = delete;
	PlayerValue& operator=(PlayerValue&& _Other) noexcept = delete;

protected:

private:


	PlayerValue();
	~PlayerValue();

	static PlayerValue Value;
	void AddToPlayerToPlayerList(class Player* _Player);

	std::vector<class Player*> PlayerList;

	std::string Name = "";
	std::string Class = "";
	std::string GuildName = "";

	int Level = 1;

	int popularity = 0;

	int MaxHp = 100;
	int Hp = 100;

	int MaxMp = 100;
	int Mp = 100;
	
	int Str = 0;
	int Dex = 0;
	int Int = 0;
	int Luk = 0;

	float PAtt = 0.0f;
	float MAtt = 0.0f;

	float PDef = 0.0f;
	float MDef = 0.0f;
	
	int HitRate = 0;
	int EvRate = 0;

	int Jump = 0;
	int MoveSpeed = 0;

	int deftness = 0;

	int MaxExp = 100;
	int Exp = 0;

	float4 MoveDistance = { 0,0 };

	std::string Hair;
	std::string Skin;
	std::string Face;

};

