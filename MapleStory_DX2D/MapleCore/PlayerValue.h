#pragma once
#include <string>
#include <string_view>

class PlayerValue
{

public: //static
	
	static PlayerValue* GetValue()
	{
		return &Value;
	}

public: //local

	int GetHp()
	{
		return Hp;
	}

	void SetHp(int _Hp)
	{
		Hp = _Hp;
	}

	int GetMp()
	{
		return Mp;
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

	std::string Name = "";
	std::string Class = "";
	std::string GuildName = "";

	int Level = 0;

	int popularity = 0;

	int Hp = 0;
	int Mp = 0;
	
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

	int Exp = 0;
	float ExpRate = 0.0f;

	std::string Hair;
	std::string Skin;

};

