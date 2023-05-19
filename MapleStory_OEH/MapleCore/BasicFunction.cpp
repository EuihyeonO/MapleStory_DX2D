#include "PrecompileHeader.h"
#include "BasicFunction.h"
#include <ctime>

BasicFunction::BasicFunction()
{
}

BasicFunction::~BasicFunction()
{
}

void BasicFunction::TimeCounting()
{
	CurTime = static_cast<float>(clock());

	TimeCount = (CurTime - PrevTime) / 1000.0f;

	PrevTime = CurTime;
}
