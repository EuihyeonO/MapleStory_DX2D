#include "PrecompileHeader.h"
#include "Level_AlterOfZakum.h"
#include "Player.h"
#include "BottomBar.h"
#include "StatusWindow.h"
#include "Mouse.h"
#include "SkillWindow.h"
#include "UIWindowManager.h"
#include "QuickSlot.h"
#include "PlayerValue.h"
#include "GlobalFunction.h"
#include "AlterOfZakum.h"
#include "MapleCore.h"

Level_AlterOfZakum::Level_AlterOfZakum()
{
}

Level_AlterOfZakum::~Level_AlterOfZakum()
{
}

void Level_AlterOfZakum::Start()
{
	SetName("ALTEROFZAKUM");

	GetMainCamera()->SetProjectionType(CameraType::Orthogonal);
	GetCamera(100)->SetProjectionType(CameraType::Orthogonal);

	GetMainCamera()->SetSortType(0, SortType::ZSort);
	GetCamera(100)->SetSortType(0, SortType::ZSort);
}

void Level_AlterOfZakum::Update(float _DeltaTime)
{
}

void Level_AlterOfZakum::LevelChangeStart()
{
	LoadResources();
	ActorCreate();

	MapleCore::BGMPlayer.Stop();
	MapleCore::BGMPlayer = GameEngineSound::Play("Zakum.mp3");
}

void Level_AlterOfZakum::LevelChangeEnd()
{
	ActorDeath();
	UnLoadResources();
}

void Level_AlterOfZakum::LoadSprite()
{
	if (nullptr == GameEngineSprite::Find("Poison"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("MapleResources");
		NewDir.Move("MapleResources");
		NewDir.Move("AlterOfZakum");
		NewDir.Move("AlterOfZakumSprite");
		NewDir.Move("StatusEffect");
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Poison").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("SkillLock").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("MoreMiss").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("DamagedDouble").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("CannotJump").GetFullPath());
	}

	if (nullptr == GameEngineSprite::Find("BoogieMove"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("MapleResources");
		NewDir.Move("MapleResources");
		NewDir.Move("AlterOfZakum");
		NewDir.Move("AlterOfZakumSprite");
		NewDir.Move("Monster");
		NewDir.Move("Boogie");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("BoogieMove").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("BoogieStand").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("BoogieHit").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("BoogieDeath").GetFullPath());
	}

	if (nullptr == GameEngineSprite::Find("SmallZakum0Fly"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("MapleResources");
		NewDir.Move("MapleResources");
		NewDir.Move("AlterOfZakum");
		NewDir.Move("AlterOfZakumSprite");
		NewDir.Move("Monster");
		NewDir.Move("SmallZakum0");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("SmallZakum0Fly").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("SmallZakum0Hit").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("SmallZakum0Death").GetFullPath());
	}

	if (nullptr == GameEngineSprite::Find("SmallZakum1Fly"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("MapleResources");
		NewDir.Move("MapleResources");
		NewDir.Move("AlterOfZakum");
		NewDir.Move("AlterOfZakumSprite");
		NewDir.Move("Monster");
		NewDir.Move("SmallZakum1");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("SmallZakum1Fly").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("SmallZakum1Hit").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("SmallZakum1Attack").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("SmallZakum1Death").GetFullPath());
	}

	if (nullptr == GameEngineSprite::Find("SmallZakum2Fly"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("MapleResources");
		NewDir.Move("MapleResources");
		NewDir.Move("AlterOfZakum");
		NewDir.Move("AlterOfZakumSprite");
		NewDir.Move("Monster");
		NewDir.Move("SmallZakum2");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("SmallZakum2Fly").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("SmallZakum2Hit").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("SmallZakum2Attack").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("SmallZakum2Death").GetFullPath());
	}

	if (nullptr == GameEngineSprite::Find("LArm0_Stand"))
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

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("LArm0_Stand").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("LArm0_Death").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("LArm0_Hit").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("LArm0_1Attack").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("LArm0_1AtEffect").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("LArm0_2Attack").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("LArm0_2AtEffect").GetFullPath());
	}

	if (nullptr == GameEngineSprite::Find("LArm1_Stand"))
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

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("LArm1_Stand").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("LArm1_Death").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("LArm1_Hit").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("LArm1_1Attack").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("LArm1_1AtEffect").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("LArm1_1AtObj0").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("LArm1_1AtObj1").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("LArm1_1AtObj2").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("LArm1_Skill").GetFullPath());
	}

	if (nullptr == GameEngineSprite::Find("LArm2_Stand"))
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

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("LArm2_Stand").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("LArm2_Death").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("LArm2_Hit").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("LArm2_1Skill").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("LArm2_2Skill").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("LArm2_3Skill").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("LArm2_4Skill").GetFullPath());
	}

	if (nullptr == GameEngineSprite::Find("LArm3_Stand"))
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

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("LArm3_Stand").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("LArm3_Death").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("LArm3_Hit").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("LArm3_1Attack").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("LArm3_1AtEffect").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("LArm3_2Attack").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("LArm3_2AtEffect").GetFullPath());
	}

	if (nullptr == GameEngineSprite::Find("RArm0_Stand"))
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

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("RArm0_Stand").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("RArm0_Death").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("RArm0_Hit").GetFullPath());		
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("RArm0_1Attack").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("RArm0_1AtEffect").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("RArm0_2Attack").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("RArm0_2AtEffect").GetFullPath());
	}

	if (nullptr == GameEngineSprite::Find("RArm1_Stand"))
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

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("RArm1_Stand").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("RArm1_Death").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("RArm1_Hit").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("RArm1_1Attack").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("RArm1_1AtEffect").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("RArm1_1AtObj").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("RArm1_2Attack").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("RArm1_2AtObj0").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("RArm1_2AtObj1").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("RArm1_2AtObj2").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("RArm1_2AtObj3").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("RArm1_2AtObj4").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("RArm1_2AtObj5").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("RArm1_2AtEffect").GetFullPath());
	}

	if (nullptr == GameEngineSprite::Find("RArm2_Stand"))
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

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("RArm2_Stand").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("RArm2_Death").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("RArm2_Hit").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("RArm2_1Skill").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("RArm2_1SkEffect").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("RArm2_2Skill").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("RArm2_2SkEffect").GetFullPath());
	}

	if (nullptr == GameEngineSprite::Find("RArm3_Stand"))
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

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("RArm3_Stand").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("RArm3_Death").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("RArm3_Hit").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("RArm3_1Attack").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("RArm3_1AtEffect").GetFullPath());		
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("RArm3_2Attack").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("RArm3_2AtEffect").GetFullPath());
	}
}

void Level_AlterOfZakum::LoadResources()
{
	if (nullptr == GameEngineSprite::Find("AlterOfZakum.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("MapleResources");
		NewDir.Move("MapleResources");
		NewDir.Move("AlterOfZakum");
		NewDir.Move("AlterOfZakumNotSprite");

		std::vector<GameEngineFile> File = NewDir.GetAllFile({ ".Png", });
		for (size_t i = 0; i < File.size(); i++)
		{
			GameEngineTexture::Load(File[i].GetFullPath());
		}
		
		LoadSprite();
	}
	else
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("MapleResources");
		NewDir.Move("MapleResources");
		NewDir.Move("AlterOfZakum");
		NewDir.Move("AlterOfZakumNotSprite");

		std::vector<GameEngineFile> File = NewDir.GetAllFile({ ".Png", });
		for (size_t i = 0; i < File.size(); i++)
		{
			GameEngineTexture::ReLoad(File[i].GetFullPath());
		}

		ReLoadSprite();
	}
}

void Level_AlterOfZakum::ActorCreate()
{
	if (Map == nullptr)
	{
		Map = CreateActor<AlterOfZakum>();

		std::string ColMapName = Map->GetColMapName().data();
		std::shared_ptr<GameEngineTexture> ColMap = GameEngineTexture::Find(ColMapName);

		GlobalFunction::GetValue()->SetColMap(ColMap);
	}

	if(MyPlayer == nullptr)
	{
		MyPlayer = CreateActor<Player>();
		MyPlayer->SetRight();
		MyPlayer->SetColMap(Map->GetColMapName());
		MyPlayer->SetCurPlayer(MyPlayer);
	}

	if (MyMouse == nullptr)
	{
		MyMouse = CreateActor<Mouse>();
		MyMouse->SetCurMouse(MyMouse);
	}

	if(MyQuickSlot == nullptr)
	{
		MyQuickSlot = CreateActor<QuickSlot>();
	}
	if(MyBottomBar == nullptr)
	{
		MyBottomBar = CreateActor<BottomBar>();
	}

	if (MyUIWindowManager == nullptr)
	{
		MyUIWindowManager = CreateActor<UIWindowManager>();
	}
}

void Level_AlterOfZakum::ActorDeath()
{
	if (MyPlayer != nullptr)
	{
		MyPlayer->Death();
		MyPlayer = nullptr;
	}

	if (MyMouse != nullptr)
	{
		MyMouse->Death();
		MyMouse = nullptr;
	}

	if (MyQuickSlot != nullptr)
	{
		MyQuickSlot->Death();
		MyMouse = nullptr;
	}
	if (MyBottomBar != nullptr)
	{
		MyBottomBar->Death();
		MyBottomBar = nullptr;
	}

	if (MyUIWindowManager != nullptr)
	{
		MyUIWindowManager->AllWindowDeath();
		MyUIWindowManager->Death();
		MyUIWindowManager = nullptr;
	}

	if (Map != nullptr)
	{
		Map->Death();
		Map = nullptr;
	}
}

void Level_AlterOfZakum::UnLoadSprite()
{
	if (nullptr != GameEngineSprite::Find("Poison"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("MapleResources");
		NewDir.Move("MapleResources");
		NewDir.Move("AlterOfZakum");
		NewDir.Move("AlterOfZakumSprite");
		NewDir.Move("StatusEffect");
		GameEngineSprite::UnLoad("Poison");
		GameEngineSprite::UnLoad("SkillLock");
		GameEngineSprite::UnLoad("MoreMiss");
		GameEngineSprite::UnLoad("DamagedDouble");
		GameEngineSprite::UnLoad("CannotJump");
	}

	if (nullptr != GameEngineSprite::Find("BoogieMove"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("MapleResources");
		NewDir.Move("MapleResources");
		NewDir.Move("AlterOfZakum");
		NewDir.Move("AlterOfZakumSprite");
		NewDir.Move("Monster");
		NewDir.Move("Boogie");

		GameEngineSprite::UnLoad("BoogieMove");
		GameEngineSprite::UnLoad("BoogieStand");
		GameEngineSprite::UnLoad("BoogieHit");
		GameEngineSprite::UnLoad("BoogieDeath");
	}

	if (nullptr != GameEngineSprite::Find("SmallZakum0Fly"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("MapleResources");
		NewDir.Move("MapleResources");
		NewDir.Move("AlterOfZakum");
		NewDir.Move("AlterOfZakumSprite");
		NewDir.Move("Monster");
		NewDir.Move("SmallZakum0");

		GameEngineSprite::UnLoad("SmallZakum0Fly");
		GameEngineSprite::UnLoad("SmallZakum0Hit");
		GameEngineSprite::UnLoad("SmallZakum0Death");
	}

	if (nullptr != GameEngineSprite::Find("SmallZakum1Fly"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("MapleResources");
		NewDir.Move("MapleResources");
		NewDir.Move("AlterOfZakum");
		NewDir.Move("AlterOfZakumSprite");
		NewDir.Move("Monster");
		NewDir.Move("SmallZakum1");

		GameEngineSprite::UnLoad("SmallZakum1Fly");
		GameEngineSprite::UnLoad("SmallZakum1Hit");
		GameEngineSprite::UnLoad("SmallZakum1Attack");
		GameEngineSprite::UnLoad("SmallZakum1Death");
	}

	if (nullptr != GameEngineSprite::Find("SmallZakum2Fly"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("MapleResources");
		NewDir.Move("MapleResources");
		NewDir.Move("AlterOfZakum");
		NewDir.Move("AlterOfZakumSprite");
		NewDir.Move("Monster");
		NewDir.Move("SmallZakum2");

		GameEngineSprite::UnLoad("SmallZakum2Fly");
		GameEngineSprite::UnLoad("SmallZakum2Hit");
		GameEngineSprite::UnLoad("SmallZakum2Attack");
		GameEngineSprite::UnLoad("SmallZakum2Death");
	}

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

void Level_AlterOfZakum::ReLoadSprite()
{
	if (nullptr != GameEngineSprite::Find("Poison"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("MapleResources");
		NewDir.Move("MapleResources");
		NewDir.Move("AlterOfZakum");
		NewDir.Move("AlterOfZakumSprite");
		NewDir.Move("StatusEffect");
		GameEngineSprite::ReLoad("Poison");
		GameEngineSprite::ReLoad("SkillLock");
		GameEngineSprite::ReLoad("MoreMiss");
		GameEngineSprite::ReLoad("DamagedDouble");
		GameEngineSprite::ReLoad("CannotJump");
	}

	if (nullptr != GameEngineSprite::Find("BoogieMove"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("MapleResources");
		NewDir.Move("MapleResources");
		NewDir.Move("AlterOfZakum");
		NewDir.Move("AlterOfZakumSprite");
		NewDir.Move("Monster");
		NewDir.Move("Boogie");

		GameEngineSprite::ReLoad("BoogieMove");
		GameEngineSprite::ReLoad("BoogieStand");
		GameEngineSprite::ReLoad("BoogieHit");
		GameEngineSprite::ReLoad("BoogieDeath");
	}

	if (nullptr != GameEngineSprite::Find("SmallZakum0Fly"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("MapleResources");
		NewDir.Move("MapleResources");
		NewDir.Move("AlterOfZakum");
		NewDir.Move("AlterOfZakumSprite");
		NewDir.Move("Monster");
		NewDir.Move("SmallZakum0");

		GameEngineSprite::ReLoad("SmallZakum0Fly");
		GameEngineSprite::ReLoad("SmallZakum0Hit");
		GameEngineSprite::ReLoad("SmallZakum0Death");
	}

	if (nullptr != GameEngineSprite::Find("SmallZakum1Fly"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("MapleResources");
		NewDir.Move("MapleResources");
		NewDir.Move("AlterOfZakum");
		NewDir.Move("AlterOfZakumSprite");
		NewDir.Move("Monster");
		NewDir.Move("SmallZakum1");

		GameEngineSprite::ReLoad("SmallZakum1Fly");
		GameEngineSprite::ReLoad("SmallZakum1Hit");
		GameEngineSprite::ReLoad("SmallZakum1Attack");
		GameEngineSprite::ReLoad("SmallZakum1Death");
	}

	if (nullptr != GameEngineSprite::Find("SmallZakum2Fly"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("MapleResources");
		NewDir.Move("MapleResources");
		NewDir.Move("AlterOfZakum");
		NewDir.Move("AlterOfZakumSprite");
		NewDir.Move("Monster");
		NewDir.Move("SmallZakum2");

		GameEngineSprite::ReLoad("SmallZakum2Fly");
		GameEngineSprite::ReLoad("SmallZakum2Hit");
		GameEngineSprite::ReLoad("SmallZakum2Attack");
		GameEngineSprite::ReLoad("SmallZakum2Death");
	}

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

		GameEngineSprite::ReLoad("LArm0_Stand");
		GameEngineSprite::ReLoad("LArm0_Death");
		GameEngineSprite::ReLoad("LArm0_Hit");
		GameEngineSprite::ReLoad("LArm0_1Attack");
		GameEngineSprite::ReLoad("LArm0_1AtEffect");
		GameEngineSprite::ReLoad("LArm0_2Attack");
		GameEngineSprite::ReLoad("LArm0_2AtEffect");
	}

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

		GameEngineSprite::ReLoad("LArm1_Stand");
		GameEngineSprite::ReLoad("LArm1_Death");
		GameEngineSprite::ReLoad("LArm1_Hit");
		GameEngineSprite::ReLoad("LArm1_1Attack");
		GameEngineSprite::ReLoad("LArm1_1AtEffect");
		GameEngineSprite::ReLoad("LArm1_1AtObj0");
		GameEngineSprite::ReLoad("LArm1_1AtObj1");
		GameEngineSprite::ReLoad("LArm1_1AtObj2");
		GameEngineSprite::ReLoad("LArm1_Skill");
	}

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

		GameEngineSprite::ReLoad("LArm2_Stand");
		GameEngineSprite::ReLoad("LArm2_Death");
		GameEngineSprite::ReLoad("LArm2_Hit");
		GameEngineSprite::ReLoad("LArm2_1Skill");
		GameEngineSprite::ReLoad("LArm2_2Skill");
		GameEngineSprite::ReLoad("LArm2_3Skill");
		GameEngineSprite::ReLoad("LArm2_4Skill");
	}

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

		GameEngineSprite::ReLoad("LArm3_Stand");
		GameEngineSprite::ReLoad("LArm3_Death");
		GameEngineSprite::ReLoad("LArm3_Hit");
		GameEngineSprite::ReLoad("LArm3_1Attack");
		GameEngineSprite::ReLoad("LArm3_1AtEffect");
		GameEngineSprite::ReLoad("LArm3_2Attack");
		GameEngineSprite::ReLoad("LArm3_2AtEffect");
	}

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

		GameEngineSprite::ReLoad("RArm0_Stand");
		GameEngineSprite::ReLoad("RArm0_Death");
		GameEngineSprite::ReLoad("RArm0_Hit");
		GameEngineSprite::ReLoad("RArm0_1Attack");
		GameEngineSprite::ReLoad("RArm0_1AtEffect");
		GameEngineSprite::ReLoad("RArm0_2Attack");
		GameEngineSprite::ReLoad("RArm0_2AtEffect");
	}

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

		GameEngineSprite::ReLoad("RArm1_Stand");
		GameEngineSprite::ReLoad("RArm1_Death");
		GameEngineSprite::ReLoad("RArm1_Hit");
		GameEngineSprite::ReLoad("RArm1_1Attack");
		GameEngineSprite::ReLoad("RArm1_1AtEffect");
		GameEngineSprite::ReLoad("RArm1_1AtObj");
		GameEngineSprite::ReLoad("RArm1_2Attack");
		GameEngineSprite::ReLoad("RArm1_2AtObj0");
		GameEngineSprite::ReLoad("RArm1_2AtObj1");
		GameEngineSprite::ReLoad("RArm1_2AtObj2");
		GameEngineSprite::ReLoad("RArm1_2AtObj3");
		GameEngineSprite::ReLoad("RArm1_2AtObj4");
		GameEngineSprite::ReLoad("RArm1_2AtObj5");
		GameEngineSprite::ReLoad("RArm1_2AtEffect");
	}

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

		GameEngineSprite::ReLoad("RArm2_Stand");
		GameEngineSprite::ReLoad("RArm2_Death");
		GameEngineSprite::ReLoad("RArm2_Hit");
		GameEngineSprite::ReLoad("RArm2_1Skill");
		GameEngineSprite::ReLoad("RArm2_1SkEffect");
		GameEngineSprite::ReLoad("RArm2_2Skill");
		GameEngineSprite::ReLoad("RArm2_2SkEffect");
	}

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

		GameEngineSprite::ReLoad("RArm3_Stand");
		GameEngineSprite::ReLoad("RArm3_Death");
		GameEngineSprite::ReLoad("RArm3_Hit");
		GameEngineSprite::ReLoad("RArm3_1Attack");
		GameEngineSprite::ReLoad("RArm3_1AtEffect");
		GameEngineSprite::ReLoad("RArm3_2Attack");
		GameEngineSprite::ReLoad("RArm3_2AtEffect");
	}
}

void Level_AlterOfZakum::UnLoadResources()
{
	UnLoadSprite();

	if (nullptr != GameEngineTexture::Find("AlterOfZakum.png"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("MapleResources");
		NewDir.Move("MapleResources");
		NewDir.Move("AlterOfZakum");
		NewDir.Move("AlterOfZakumNotSprite");

		std::vector<GameEngineFile> File = NewDir.GetAllFile({ ".Png", });

		for (size_t i = 0; i < File.size(); i++)
		{
			std::string FileFullPath = File[i].GetFullPath();
			std::string FileName = "";
			size_t Count = 0;

			for (Count = FileFullPath.size(); Count > 0; Count--)
			{
				char a = FileFullPath[Count];
				if (FileFullPath[Count] == '\\')
				{
					break;
				}
			}

			for (size_t j = Count + 1; j < FileFullPath.size(); j++)
			{
				FileName.push_back(FileFullPath[j]);
			}

			GameEngineTexture::UnLoad(FileName);
		}
	}
}