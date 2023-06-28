#include "PrecompileHeader.h"
#include "Zakum.h"

#include <GameEngineCore/GameEngineSprite.h>
#include <GameEngineBase/GameEngineDirectory.h>

void Zakum::LArm_0_UnLoad()
{
	if (nullptr != GameEngineSprite::Find("LArm0_Stand"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("MapleResources");
		NewDir.Move("MapleResources");
		NewDir.Move("AlterOfZakum");
		NewDir.Move("AlterOfZakumSprite");
		NewDir.Move("Monster");
		NewDir.Move("Zakum");
		NewDir.Move("ZakumArm");
		NewDir.Move("Left_0");

		GameEngineSprite::UnLoad("LArm0_Stand");
		GameEngineSprite::UnLoad("LArm0_Death");
		GameEngineSprite::UnLoad("LArm0_Hit");
		GameEngineSprite::UnLoad("LArm0_1Attack");
		GameEngineSprite::UnLoad("LArm0_1AtEffect");
		GameEngineSprite::UnLoad("LArm0_2Attack");
		GameEngineSprite::UnLoad("LArm0_2AtEffect");
	}

}

void Zakum::LArm_1_UnLoad()
{
	if (nullptr != GameEngineSprite::Find("LArm1_Stand"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("MapleResources");
		NewDir.Move("MapleResources");
		NewDir.Move("AlterOfZakum");
		NewDir.Move("AlterOfZakumSprite");
		NewDir.Move("Monster");
		NewDir.Move("Zakum");
		NewDir.Move("ZakumArm");
		NewDir.Move("Left_1");

		GameEngineSprite::UnLoad("LArm1_Stand");
		GameEngineSprite::UnLoad("LArm1_Death");
		GameEngineSprite::UnLoad("LArm1_Hit");
		GameEngineSprite::UnLoad("LArm1_1Attack");
		GameEngineSprite::UnLoad("LArm1_1AtEffect");
		GameEngineSprite::UnLoad("LArm1_1AtObj0");
		GameEngineSprite::UnLoad("LArm1_1AtObj1");
		GameEngineSprite::UnLoad("LArm1_1AtObj2");
		GameEngineSprite::UnLoad("LArm1_Skill");
	}

}

void Zakum::LArm_2_UnLoad()
{
	if (nullptr != GameEngineSprite::Find("LArm2_Stand"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("MapleResources");
		NewDir.Move("MapleResources");
		NewDir.Move("AlterOfZakum");
		NewDir.Move("AlterOfZakumSprite");
		NewDir.Move("Monster");
		NewDir.Move("Zakum");
		NewDir.Move("ZakumArm");
		NewDir.Move("Left_2");

		GameEngineSprite::UnLoad("LArm2_Stand");
		GameEngineSprite::UnLoad("LArm2_Death");
		GameEngineSprite::UnLoad("LArm2_Hit");
		GameEngineSprite::UnLoad("LArm2_1Skill");
		GameEngineSprite::UnLoad("LArm2_2Skill");
		GameEngineSprite::UnLoad("LArm2_3Skill");
		GameEngineSprite::UnLoad("LArm2_4Skill");
	}
}

void Zakum::LArm_3_UnLoad()
{
	if (nullptr != GameEngineSprite::Find("LArm3_Stand"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("MapleResources");
		NewDir.Move("MapleResources");
		NewDir.Move("AlterOfZakum");
		NewDir.Move("AlterOfZakumSprite");
		NewDir.Move("Monster");
		NewDir.Move("Zakum");
		NewDir.Move("ZakumArm");
		NewDir.Move("Left_3");

		GameEngineSprite::UnLoad("LArm3_Stand");
		GameEngineSprite::UnLoad("LArm3_Death");
		GameEngineSprite::UnLoad("LArm3_Hit");
		GameEngineSprite::UnLoad("LArm3_1Attack");
		GameEngineSprite::UnLoad("LArm3_1AtEffect");
		GameEngineSprite::UnLoad("LArm3_2Attack");
		GameEngineSprite::UnLoad("LArm3_2AtEffect");
	}
}

void Zakum::RArm_0_UnLoad()
{
	if (nullptr != GameEngineSprite::Find("RArm0_Stand"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("MapleResources");
		NewDir.Move("MapleResources");
		NewDir.Move("AlterOfZakum");
		NewDir.Move("AlterOfZakumSprite");
		NewDir.Move("Monster");
		NewDir.Move("Zakum");
		NewDir.Move("ZakumArm");
		NewDir.Move("Right_0");

		GameEngineSprite::UnLoad("RArm0_Stand");
		GameEngineSprite::UnLoad("RArm0_Death");
		GameEngineSprite::UnLoad("RArm0_Hit");
		GameEngineSprite::UnLoad("RArm0_1Attack");
		GameEngineSprite::UnLoad("RArm0_1AtEffect");
		GameEngineSprite::UnLoad("RArm0_2Attack");
		GameEngineSprite::UnLoad("RArm0_2AtEffect");
	}
}

void Zakum::RArm_1_UnLoad()
{
	if (nullptr != GameEngineSprite::Find("RArm1_Stand"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("MapleResources");
		NewDir.Move("MapleResources");
		NewDir.Move("AlterOfZakum");
		NewDir.Move("AlterOfZakumSprite");
		NewDir.Move("Monster");
		NewDir.Move("Zakum");
		NewDir.Move("ZakumArm");
		NewDir.Move("Right_1");

		GameEngineSprite::UnLoad("RArm1_Stand");
		GameEngineSprite::UnLoad("RArm1_Death");
		GameEngineSprite::UnLoad("RArm1_Hit");
		GameEngineSprite::UnLoad("RArm1_1Attack");
		GameEngineSprite::UnLoad("RArm1_1AtEffect");
		GameEngineSprite::UnLoad("RArm1_1AtObj");
		GameEngineSprite::UnLoad("RArm1_2Attack");
		GameEngineSprite::UnLoad("RArm1_2AtObj0");
		GameEngineSprite::UnLoad("RArm1_2AtObj1");
		GameEngineSprite::UnLoad("RArm1_2AtObj2");
		GameEngineSprite::UnLoad("RArm1_2AtObj3");
		GameEngineSprite::UnLoad("RArm1_2AtObj4");
		GameEngineSprite::UnLoad("RArm1_2AtObj5");
		GameEngineSprite::UnLoad("RArm1_2AtEffect");
	}
}

void Zakum::RArm_2_UnLoad()
{
	if (nullptr != GameEngineSprite::Find("RArm2_Stand"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("MapleResources");
		NewDir.Move("MapleResources");
		NewDir.Move("AlterOfZakum");
		NewDir.Move("AlterOfZakumSprite");
		NewDir.Move("Monster");
		NewDir.Move("Zakum");
		NewDir.Move("ZakumArm");
		NewDir.Move("Right_2");

		GameEngineSprite::UnLoad("RArm2_Stand");
		GameEngineSprite::UnLoad("RArm2_Death");
		GameEngineSprite::UnLoad("RArm2_Hit");
		GameEngineSprite::UnLoad("RArm2_1Skill");
		GameEngineSprite::UnLoad("RArm2_1SkEffect");
		GameEngineSprite::UnLoad("RArm2_2Skill");
		GameEngineSprite::UnLoad("RArm2_2SkEffect");
	}
}

void Zakum::RArm_3_UnLoad()
{
	if (nullptr != GameEngineSprite::Find("RArm3_Stand"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("MapleResources");
		NewDir.Move("MapleResources");
		NewDir.Move("AlterOfZakum");
		NewDir.Move("AlterOfZakumSprite");
		NewDir.Move("Monster");
		NewDir.Move("Zakum");
		NewDir.Move("ZakumArm");
		NewDir.Move("Right_3");

		GameEngineSprite::UnLoad("RArm3_Stand");
		GameEngineSprite::UnLoad("RArm3_Death");
		GameEngineSprite::UnLoad("RArm3_Hit");
		GameEngineSprite::UnLoad("RArm3_1Attack");
		GameEngineSprite::UnLoad("RArm3_1AtEffect");
		GameEngineSprite::UnLoad("RArm3_2Attack");
		GameEngineSprite::UnLoad("RArm3_2AtEffect");
	}
}
