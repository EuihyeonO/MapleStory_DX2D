#include "PrecompileHeader.h"
#include "AlterOfZakum.h"
#include "Zakum.h"
#include "Boogie.h"
#include "DropItem.h"
#include "RingPortal.h"
#include "ContentRenderer.h"

#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineBase/GameEngineThread.h>

bool AlterOfZakum::isLoadEnd = false;

AlterOfZakum::AlterOfZakum()
{
}

AlterOfZakum::~AlterOfZakum()
{
}

void AlterOfZakum::Start()
{
	LandScape0 = CreateComponent<ContentRenderer>();
	LandScape0->SetTexture("ZakumLandScape0.png");
	LandScape0->GetTransform()->SetLocalScale({ 200 * 6, 600 });
	LandScape0->GetTransform()->SetLocalPosition({ 0, 100.0f });
	LandScape0->SetUVconstant({ 0, 0, 6, 1 });

	LandScape1 = CreateComponent<GameEngineSpriteRenderer>();
	LandScape1->SetScaleToTexture("ZakumLandScape1.png");

	LandScape2 = CreateComponent<GameEngineSpriteRenderer>();
	LandScape2->SetScaleToTexture("ZakumLandScape1.png");

	LandScape3 = CreateComponent<GameEngineSpriteRenderer>();
	LandScape3->SetScaleToTexture("ZakumLandScape3.png");
	LandScape3->GetTransform()->SetLocalPosition({ 530, 80.0f, -2.0f });

	LandScape4 = CreateComponent<GameEngineSpriteRenderer>();
	LandScape4->SetScaleToTexture("ZakumLandScape4.png");
	LandScape4->GetTransform()->SetLocalPosition({ -400, 80.0f, -2.0f });

	BackGround = CreateComponent<GameEngineSpriteRenderer>();
	BackGround->SetScaleToTexture("AlterOfZakum.png");
	BackGround->GetTransform()->AddLocalPosition({ 0, 0, -3.0f });

	AlterBack = CreateComponent<GameEngineSpriteRenderer>();
	AlterBack->SetScaleToTexture("Alter1.png");
	AlterBack->GetTransform()->SetLocalPosition({ 50.0f, 70.0f , -1.0f });

	Layer = CreateComponent<GameEngineSpriteRenderer>();
	Layer->SetScaleToTexture("AlterOfZakumLayer.png");
	Layer->GetTransform()->SetLocalPosition({ 0, 0, -10.0f });

	Magma = CreateComponent<ContentRenderer>();
	Magma->SetTexture("Magma.png");
	Magma->GetTransform()->SetLocalScale({ 264 * 5, 96 });
	Magma->GetTransform()->SetLocalPosition({ 0, -220, -6.0f });
	Magma->SetUVconstant({ 0, 0, 5, 1 });

	RingPortal1 = GetLevel()->CreateActor<RingPortal>();
	RingPortal1->GetTransform()->SetLocalPosition({ 430, 220, -8 });
	RingPortal1->SetLinkedPos({ -410, 150, -8 });
	
	RingPortal2 = GetLevel()->CreateActor<RingPortal>();
	RingPortal2->GetTransform()->SetLocalPosition({ -410, 210, -8 });
	RingPortal2->SetLinkedPos({ 430, 160, -8 });

	std::shared_ptr<GameEngineSpriteRenderer> FootHold0 = CreateComponent<GameEngineSpriteRenderer>();
	FootHold0->SetScaleToTexture("FootHold1.png");
	FootHold0->GetTransform()->SetLocalPosition({ -450.0f, 130.0f, -4.0f });

	std::shared_ptr<GameEngineSpriteRenderer> FootHold1 = CreateComponent<GameEngineSpriteRenderer>();
	FootHold1->SetScaleToTexture("FootHold0.png");
	FootHold1->GetTransform()->SetLocalPosition({ -375.0f, 60.0f, -4.0f });

	std::shared_ptr<GameEngineSpriteRenderer> FootHold2 = CreateComponent<GameEngineSpriteRenderer>();
	FootHold2->SetScaleToTexture("FootHold1.png");
	FootHold2->GetTransform()->SetLocalPosition({ -430.0f, -10.0f, -4.0f });

	std::shared_ptr<GameEngineSpriteRenderer> Rope1 = CreateComponent<GameEngineSpriteRenderer>();
	Rope1->SetScaleToTexture("ZakumRope1.png");
	Rope1->GetTransform()->SetLocalPosition({ 370.0f, 100.0f, -4.0f });
	
	std::shared_ptr<GameEngineSpriteRenderer> Rope2 = CreateComponent<GameEngineSpriteRenderer>();
	Rope2->SetScaleToTexture("ZakumRope1.png");
	Rope2->GetTransform()->SetLocalPosition({ -450.0f, -55.0f, -4.0f });

	TransformData Rope1Data = Rope1->GetTransform()->GetTransDataRef();
	TransformData Rope2Data = Rope2->GetTransform()->GetTransDataRef();

	std::shared_ptr<GameEngineCollision> RopeCol1 = CreateComponent<GameEngineCollision>();
	RopeCol1->GetTransform()->SetLocalScale(Rope1Data.LocalScale);
	RopeCol1->GetTransform()->SetLocalPosition(Rope1Data.LocalPosition);
	RopeCol1->SetOrder(static_cast<int>(CollisionOrder::RopeAndLadder));

	std::shared_ptr<GameEngineCollision> RopeCol2 = CreateComponent<GameEngineCollision>();
	RopeCol2->GetTransform()->SetLocalScale(Rope2Data.LocalScale);
	RopeCol2->GetTransform()->SetLocalPosition(Rope2Data.LocalPosition);
	RopeCol2->SetOrder(static_cast<int>(CollisionOrder::RopeAndLadder));

	UpdateFunc = std::bind(&AlterOfZakum::SpawnZakum, this, std::placeholders::_1);

	Alter = CreateComponent<GameEngineSpriteRenderer>();
	Alter->SetScaleToTexture("Alter0.png");
	Alter->GetTransform()->SetLocalPosition({ 0, -180.0f , -6.0f });

	AlterCollision = CreateComponent<GameEngineCollision>();
	AlterCollision->SetColType(ColType::AABBBOX2D);
	AlterCollision->GetTransform()->SetLocalScale({ Alter->GetTransform()->GetLocalScale().hx(),Alter->GetTransform()->GetLocalScale().hy() });
	AlterCollision->GetTransform()->SetLocalPosition(Alter->GetTransform()->GetLocalPosition() + float4{0, 30});

}

void AlterOfZakum::Update(float _DeltaTime) 
{
	MagmaMove(_DeltaTime);
	LandScapeMove();

	if (UpdateFunc != nullptr)
	{
		UpdateFunc(_DeltaTime);
	}
}

void AlterOfZakum::Render(float _DeltaTime)
{
}

void AlterOfZakum::LandScapeMove()
{
	float4 CameraPos = GetLevel()->GetMainCamera()->GetTransform()->GetLocalPosition();
	float4 MapSize = GameEngineTexture::Find("AlterOfZakum.png")->GetScale();

	float4 CameraPosPerMapScaleRatio = { CameraPos.x / MapSize.x, CameraPos.y / MapSize.y };

	LandScape1->GetTransform()->SetLocalPosition({ 100.0f * CameraPosPerMapScaleRatio.x - 200.0f , 600.0f * CameraPosPerMapScaleRatio.y + 60.0f , -1.0f});
	LandScape2->GetTransform()->SetLocalPosition({ 100.0f * CameraPosPerMapScaleRatio.x + 300.0f , 600.0f * CameraPosPerMapScaleRatio.y + 50.0f , -1.0f });

}

void AlterOfZakum::MagmaMove(float _DeltaTime)
{
	Magma_UVXMove += 0.025f * _DeltaTime;

	if (Magma_UVXMove >= 5)
	{
		Magma_UVXMove -= 5.0f;
	}

	Magma->SetUVconstant({ Magma_UVXMove, 0, 5, 1 });
}


void LoadAllResources(GameEngineThread* Thread)
{
	if (nullptr == GameEngineSprite::Find("ZakumSpawn"))
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("MapleResources");
		NewDir.Move("MapleResources");
		NewDir.Move("AlterOfZakum");
		NewDir.Move("AlterOfZakumSprite");
		NewDir.Move("Monster");
		NewDir.Move("Zakum");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("ZakumSpawn").GetFullPath());

		NewDir.Move("Phase1");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Phase1_1Attack").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("1AtEffect0").GetFullPath());

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Phase1_2Attack").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("2AtEffect0").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("2AtEffect1").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("2AtEffect2").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("2AtEffect3").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("2AtEffect4").GetFullPath());

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Phase1_3Attack").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("3AtEffect").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("3AtObj").GetFullPath());

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Phase1_1Skill").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("1SkEffect").GetFullPath());

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Phase1_2Skill").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("2SkEffect").GetFullPath());

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Phase1_3Skill").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("3SkEffect").GetFullPath());

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Phase1Die").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Phase1Hit").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Phase1Stand").GetFullPath());

		NewDir.Move("1AtEffect1");

		std::vector<GameEngineFile> File = NewDir.GetAllFile({ ".Png", });

		for (size_t i = 0; i < File.size(); i++)
		{
			GameEngineTexture::Load(File[i].GetFullPath());
		}

		NewDir.MoveParent();

		NewDir.MoveParent();
		NewDir.Move("Phase2");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Phase2_1Attack").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Phase2_2Attack").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Phase2_3Attack").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Phase2_1Skill").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Phase2_2Skill").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Phase2_3Skill").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Phase2Die").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Phase2Hit").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Phase2Stand").GetFullPath());

		NewDir.MoveParent();
		NewDir.Move("Phase3");

		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Phase3_1Attack").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Phase3_2Attack").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Phase3_3Attack").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Phase3_1Skill").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Phase3_2Skill").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Phase3_3Skill").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Phase3Die").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Phase3Hit").GetFullPath());
		GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Phase3Stand").GetFullPath());
	}

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

	AlterOfZakum::isLoadEnd = true;
}

void AlterOfZakum::SpawnZakum(float _DeltaTime)
{
	if (AlterCollision == nullptr)
	{
		return;
	}

	std::shared_ptr<GameEngineCollision> Col = AlterCollision->Collision(static_cast<int>(CollisionOrder::DropItem), ColType::AABBBOX2D, ColType::AABBBOX2D);

	if (Col != nullptr)
	{
		std::shared_ptr<DropItem> ColItem = Col->GetActor()->DynamicThis<DropItem>();
		std::string ItemName = GameEngineString::ToUpper(ColItem->GetItemName().data());

		if (ItemName == "EYEOFFIRE")
		{
			if (isLoadStart == false)
			{
				GameEngineCore::JobQueue.Work(LoadAllResources);
				isLoadStart = true;
			}

			if (isLoadEnd == true)
			{
				ColItem->GetRender()->ColorOptionValue.MulColor.a -= 1.0f * _DeltaTime;

				if (ColItem->GetRender()->ColorOptionValue.MulColor.a <= 0.0f)
				{
					ColItem->GetRender()->ColorOptionValue.MulColor.a = 0.0f;
					ColItem->Death();
					
					std::shared_ptr<Zakum> NewZakum = GetLevel()->CreateActor<Zakum>();
					UpdateFunc = nullptr;
				}
			}

		}
	}
}
