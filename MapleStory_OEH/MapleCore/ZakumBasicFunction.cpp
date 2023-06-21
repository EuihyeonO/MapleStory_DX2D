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

	if (Hp < 0 && _isRealAttack == true)
	{
		ArmRender->ChangeAnimation("Death");
		Zakum::GetZakum()->SubHp(_Damage + Hp);
		return;
	}

	if (isArm == true && _isRealAttack == true)
	{
		Zakum::GetZakum()->SubHp(_Damage);
	}

	if(isAttack == false)
	{
		ArmRender->ChangeAnimation("Hit");
	}
}
