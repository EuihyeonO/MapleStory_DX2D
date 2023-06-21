#pragma once

class FlyingMonsterBasicFunction
{

public:

	FlyingMonsterBasicFunction();
	~FlyingMonsterBasicFunction();

	FlyingMonsterBasicFunction(const FlyingMonsterBasicFunction& _Other) = delete;
	FlyingMonsterBasicFunction(FlyingMonsterBasicFunction&& _Other) noexcept = delete;
	FlyingMonsterBasicFunction& operator=(const FlyingMonsterBasicFunction& _Other) = delete;
	FlyingMonsterBasicFunction& operator=(FlyingMonsterBasicFunction&& _Other) noexcept = delete;

protected:

private:

};

