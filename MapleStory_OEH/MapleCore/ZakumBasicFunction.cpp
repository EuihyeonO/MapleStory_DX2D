#include "PrecompileHeader.h"
#include "ZakumBasicFunction.h"
#include "Zakum.h"

ZakumBasicFunction::ZakumBasicFunction()
{
}

ZakumBasicFunction::~ZakumBasicFunction()
{
}

void ZakumBasicFunction::Hit(int _Damage, bool _isRealAttack)
{
	Hp -= _Damage;

	ArmRender->ChangeAnimation("Hit");

	if (Hp < 0 && _isRealAttack == true)
	{
		ArmRender->ChangeAnimation("Death");
	}
}
