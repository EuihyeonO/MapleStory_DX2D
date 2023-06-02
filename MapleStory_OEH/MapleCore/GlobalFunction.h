#pragma once
#include <memory>

class GlobalFunction
{

public:

	static GlobalFunction* GetValue()
	{
		return &Value;
	}

	void SetColMap(std::shared_ptr<class GameEngineTexture> _ColMap)
	{
		ColMap = _ColMap;
	}

	std::shared_ptr<class GameEngineTexture> GetColMap()
	{
		return ColMap;
	}

protected:

private:

	static GlobalFunction Value;
	
	std::shared_ptr<class GameEngineTexture> ColMap = nullptr;

private:
	GlobalFunction();
	~GlobalFunction();

	GlobalFunction(const GlobalFunction& _Other) = delete;
	GlobalFunction(GlobalFunction&& _Other) noexcept = delete;
	GlobalFunction& operator=(const GlobalFunction& _Other) = delete;
	GlobalFunction& operator=(GlobalFunction&& _Other) noexcept = delete;
};

