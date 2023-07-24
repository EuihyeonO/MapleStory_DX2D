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
		Player::GetCurPlayer()->SetShiftSkill(_Skill);

	}

	void SetInsSkillAllPlayer(std::function<void(std::shared_ptr<class Player>)> _Skill)
	{
		Player::GetCurPlayer()->SetInsSkill(_Skill);

	}

	void SetHomeSkillAllPlayer(std::function<void(std::shared_ptr<class Player>)> _Skill)
	{
		Player::GetCurPlayer()->SetHomeSkill(_Skill);

	}

	void SetPgUpSkillAllPlayer(std::function<void(std::shared_ptr<class Player>)> _Skill)
	{
		Player::GetCurPlayer()->SetPgUpSkill(_Skill);

	}

	void SetCtrlSkillAllPlayer(std::function<void(std::shared_ptr<class Player>)> _Skill)
	{
		Player::GetCurPlayer()->SetCtrlSkill(_Skill);

	}


	void SetDelSkillAllPlayer(std::function<void(std::shared_ptr<class Player>)> _Skill)
	{
		Player::GetCurPlayer()->SetDelSkill(_Skill);

	}

	void SetEndSkillAllPlayer(std::function<void(std::shared_ptr<class Player>)> _Skill)
	{
		Player::GetCurPlayer()->SetEndSkill(_Skill);
	}


	void SetPgDnSkillAllPlayer(std::function<void(std::shared_ptr<class Player>)> _Skill)
	{
			Player::GetCurPlayer()->SetPgDnSkill(_Skill);
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
		Exp -= MaxExp;
		MaxExp = static_cast<int>(MaxExp * 1.08f);
		StatPoint += 5;
		SkillPoint += 3;
		MaxHp = static_cast<int>(Hp * 1.035f);
		MaxMp = static_cast<int>(Mp * 1.02f);
		Hp = MaxHp;
		Mp = MaxMp;

		Player::GetCurPlayer()->Level_Up();
		PlayerValue::Value.AttUpdate();
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
			return round(0.0f);
		}
	}

	void SetMaxExp(int _MaxExp)
	{
		MaxExp = _MaxExp;
	}

	void AddExp(int _Exp)
	{
		Exp += _Exp;

		while (Exp >= MaxExp)
		{
			LevelUp();
		}
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

	void AddHp(int _Hp)
	{
		Hp += _Hp;

		if (Hp >= MaxHp)
		{
			Hp = MaxHp;
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

	void AddStatPoint(int _Sp)
	{
		StatPoint += _Sp;
	}

	int GetStatPoint()
	{
		return StatPoint;
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

	void AttUpdate()
	{ 
		Att = Luk * 5.0f + EquipAtt * (Luk * 0.25f + Level) + Level * 2.5f;

		MaxAttack = Att * 1.2f;
		MinAttack = Att * 0.8f;
	}

	void AddToEquipAtt(int _Att)
	{
		EquipAtt += _Att;
	}

	void SubToEquipAtt(int _Att)
	{
		EquipAtt -= _Att;
	}

	void AddToEquipDef(int _Def)
	{
		EquipDef += _Def;
	}

	void SubToEquipDef(int _Def)
	{
		EquipDef -= _Def;
	}

	float GetMaxAtt()
	{
		return MaxAttack;
	}

	float GetMinAtt()
	{
		return MinAttack;
	}

	const std::string_view GetPrevLevelName()
	{
		return PrevLevelName;
	}

	PlayerValue(const PlayerValue& _Other) = delete;
	PlayerValue(PlayerValue&& _Other) noexcept = delete;
	PlayerValue& operator=(const PlayerValue& _Other) = delete;
	PlayerValue& operator=(PlayerValue&& _Other) noexcept = delete;

	const std::string_view GetSkin()
	{
		return Skin;
	}

	const std::string_view GetHair()
	{
		return Hair;
	}

	const std::string_view GetFace()
	{
		return Face;
	}

	void SetFace(const std::string_view& _FaceName)
	{
		Face = _FaceName;

		if (Player::GetCurPlayer() != nullptr)
		{
			Player::GetCurPlayer()->SetFaceName(_FaceName);
		}
	}

	const std::string_view GetClass()
	{
		return Class;
	}

	const std::string_view GetClassKr()
	{
		if (Class == "BEGINNER")
		{
			return "초보자";
		}
		else if (Class == "LOG")
		{
			return "로그";
		}
		else if (Class == "ASSASSIN")
		{
			return "어쌔신";
		}
		else if (Class == "HERMIT")
		{
			return "허밋";
		}
		else if (Class == "NIGHTLORD")
		{
			return "나이트로드";
		}
		else
		{
			return "";
		}
	}

	void UpGradeClass()
	{
		if (Grade == 4)
		{
			return;
		}

		if (Class == "BEGINNER" && Level >= 10)
		{
			Class = "LOG";
			Grade++;
		}
		else if (Class == "LOG" && Level >= 30)
		{
			Class = "ASSASSIN";
			Grade++;
		}
		else if (Class == "ASSASSIN" && Level >=70)
		{
			Class = "HERMIT";
			Grade++;
		}
		else if (Class == "HERMIT" && Level >= 120)
		{
			Class = "NIGHTLORD";
			Grade++;
		}

	}

protected:

private:

	PlayerValue();
	~PlayerValue();

	static PlayerValue Value;

	std::string PrevLevelName;

//인게임 정보
private:

	std::string Name = "";
	std::string Class = "BEGINNER";
	std::string GuildName = "";
	int Grade = 0;
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

	int StatPoint = 0;

	float Att = 0.0f;
	float EquipAtt = 0.0f;
	float MaxAttack = 0.0f;
	float MinAttack = 0.0f;

	float Def = 0.0f;
	float EquipDef = 0.0f;
	
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

	std::string Hair = "Toven";
	std::string Skin = "Basic";
	std::string Face = "Face1";
	
	//스킬 관련
public:
	
	int GetSkillPoint()
	{
		return SkillPoint;
	}

	int GetKeenEyesLv()
	{
		return KeenEyesLv;
	}

	void KeenEyesLvUp()
	{
		KeenEyesLv++;
		SkillPoint--;
		AttackDistance += 10.0f;
	}

	int GetJavelinBoosterLv()
	{
		return JavelinBoosterLv;
	}

	void JavelinBoosterLvUp()
	{
		JavelinBoosterLv++;
		SkillPoint--;
	}

	int GetHasteLv()
	{
		return HasteLv;
	}

	void HasteLvUp()
	{
		HasteLv++;
		SkillPoint--;
	}

	int GetShadowPartnerLv()
	{
		return ShadowPartnerLv;
	}

	void ShadowPartnerLvUp()
	{
		ShadowPartnerLv++;
		SkillPoint--;
	}

	int GetAvengerLv()
	{
		return AvengerLv;
	}

	void AvengerLvUp()
	{
		AvengerLv++;
		SkillPoint--;
	}

	int GetLuckySevenLv()
	{
		return LuckySevenLv;
	}

	void LuckySevenLvUp()
	{
		LuckySevenLv++;
		SkillPoint--;
	}

	int GetTripleThrowLv()
	{
		return TripleThrowLv;
	}

	void TripleThrowLvUp()
	{
		TripleThrowLv++;
		SkillPoint--;
	}

	int GetFlashJumpLv()
	{
		return FlashJumpLv;
	}

	void FlashJumpLvUp()
	{
		FlashJumpLv++;
		SkillPoint--;
	}

	int GetHeroesOfMapleLv()
	{
		return HeroesOfMapleLv;
	}

	void HeroesOfMapleLvUp()
	{
		HeroesOfMapleLv++;
		SkillPoint--;
	}

private:
	int SkillPoint = 0;

	int JavelinBoosterLv = 0;
	int KeenEyesLv = 0;
	int HasteLv = 0;
	int ShadowPartnerLv = 0;
	int LuckySevenLv = 0;
	int AvengerLv = 0;
	int TripleThrowLv = 0;
	int HeroesOfMapleLv = 0;
	int FlashJumpLv = 20;
};

