#pragma once
#include "Player.h"

#include <string>
#include <string_view>
#include <memory>

class PlayerValue
{
	friend Player;

public: //static

	static PlayerValue* GetValue()
	{
		return &Value;
	}

public: //local
	void SetShiftSkillAllPlayer(std::function<void(std::shared_ptr<class Player>)> _Skill)
	{
		for (int i = 0; i < PlayerList.size(); i++)
		{
			PlayerList[i]->SetShiftSkill(_Skill);
		}
	}

	void SetInsSkillAllPlayer(std::function<void(std::shared_ptr<class Player>)> _Skill)
	{
		for (int i = 0; i < PlayerList.size(); i++)
		{
			PlayerList[i]->SetInsSkill(_Skill);
		}
	}

	void SetHomeSkillAllPlayer(std::function<void(std::shared_ptr<class Player>)> _Skill)
	{
		for (int i = 0; i < PlayerList.size(); i++)
		{
			PlayerList[i]->SetHomeSkill(_Skill);
		}
	}

	void SetPgUpSkillAllPlayer(std::function<void(std::shared_ptr<class Player>)> _Skill)
	{
		for (int i = 0; i < PlayerList.size(); i++)
		{
			PlayerList[i]->SetPgUpSkill(_Skill);
		}
	}

	void SetCtrlSkillAllPlayer(std::function<void(std::shared_ptr<class Player>)> _Skill)
	{
		for (int i = 0; i < PlayerList.size(); i++)
		{
			PlayerList[i]->SetCtrlSkill(_Skill);
		}
	}


	void SetDelSkillAllPlayer(std::function<void(std::shared_ptr<class Player>)> _Skill)
	{
		for (int i = 0; i < PlayerList.size(); i++)
		{
			PlayerList[i]->SetDelSkill(_Skill);
		}
	}

	void SetEndSkillAllPlayer(std::function<void(std::shared_ptr<class Player>)> _Skill)
	{
		for (int i = 0; i < PlayerList.size(); i++)
		{
			PlayerList[i]->SetEndSkill(_Skill);
		}
	}


	void SetPgDnSkillAllPlayer(std::function<void(std::shared_ptr<class Player>)> _Skill)
	{
		for (int i = 0; i < PlayerList.size(); i++)
		{
			PlayerList[i]->SetPgDnSkill(_Skill);
		}
	}

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
		
		if (Hp <= 0)
		{
			Hp = 0;
		}

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

	float GetAttackDistance()
	{
		return AttackDistance;
	}

	float GetAttackSpeed()
	{
		return AttackSpeed;
	}

	void PlusAttackSpeed(float _Speed)
	{
		AttackSpeed = BasicAttackSpeed + _Speed;
	}

	void SetAttackSpeedToBasic()
	{
		AttackSpeed = BasicAttackSpeed;
	}

	void SetPrevLevelName(const std::string_view& _LevelName)
	{
		PrevLevelName = _LevelName;
	}

	const std::string_view GetPrevLevelName()
	{
		return PrevLevelName;
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
	void AddToPlayerToPlayerList( std::shared_ptr<class Player> _Player);

	std::vector<std::shared_ptr<class Player>> PlayerList;
	std::string PrevLevelName;

//인게임 정보
private:

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
	
	float AttackDistance = 200.0f;
	float AttackSpeed = 1.0f;
	float BasicAttackSpeed = 1.0f;

	std::string Hair;
	std::string Skin;
	std::string Face;
	
	//스킬 관련
public:
		
	int GetKeenEyesLevel()
	{
		return KeenEyesLevel;
	}

	void KeenEyesLevelUp()
	{
		KeenEyesLevel++;
		AttackDistance += 10.0f;
	}

	int GetJavelinBoosterLevel()
	{
		return JavelinBoosterLevel;
	}

	void JavelinBooster()
	{
		JavelinBoosterLevel++;
	}

private:

	int JavelinBoosterLevel = 0;
	int KeenEyesLevel = 0;
};

