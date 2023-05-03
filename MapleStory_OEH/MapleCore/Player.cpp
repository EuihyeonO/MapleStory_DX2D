#include "PrecompileHeader.h"
#include "Player.h"
#include "PlayerValue.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <ctime>

Player::Player()
{
}

Player::~Player()
{
}

void Player::Start()
{
	TimeCounting();

	PlayerTransForm.SetLocalPosition({ 0, 0 });
	PlayerTransForm.SetLocalScale({ 8, 8 });

	Body = CreateComponent<GameEngineSpriteRenderer>();
	Pants = CreateComponent<GameEngineSpriteRenderer>();
	Coat = CreateComponent<GameEngineSpriteRenderer>();
	//
	Weapon = CreateComponent<GameEngineSpriteRenderer>();
	Arm = CreateComponent<GameEngineSpriteRenderer>();
	CoatArm = CreateComponent<GameEngineSpriteRenderer>();
	//
	Head = CreateComponent<GameEngineSpriteRenderer>();

	Hair = CreateComponent<GameEngineSpriteRenderer>();
	Face = CreateComponent<GameEngineSpriteRenderer>();

	//로테이션이 왜 초기값이 180도?

	Body->GetTransform()->SetWorldRotation({0, 0, 0});	
	Coat->GetTransform()->SetWorldRotation({0, 0, 0});
	//
	Arm->GetTransform()->SetWorldRotation({0, 0, 0});
	CoatArm->GetTransform()->SetWorldRotation({ 0, 0, 0 });
	Weapon->GetTransform()->SetWorldRotation({ 0, 0, 0 });

	Head->GetTransform()->SetWorldRotation({0, 0, 0});
	//
	Hair->GetTransform()->SetWorldRotation({0, 0, 0});
	Face->GetTransform()->SetWorldRotation({0, 0, 0});
	Pants->GetTransform()->SetWorldRotation({0, 0, 0});

	//부모설정
	Body->GetTransform()->SetParent(&PlayerTransForm);
	Coat->GetTransform()->SetParent(&PlayerTransForm);	
	Arm->GetTransform()->SetParent(&PlayerTransForm);
	CoatArm->GetTransform()->SetParent(&PlayerTransForm);	
	Head->GetTransform()->SetParent(&PlayerTransForm);
	Face->GetTransform()->SetParent(&PlayerTransForm);
	Hair->GetTransform()->SetParent(&PlayerTransForm);
	Pants->GetTransform()->SetParent(&PlayerTransForm);
	Weapon->GetTransform()->SetParent(&PlayerTransForm);

	SetAllPartInfoPerFrame();
	
	//초기애니메이션
	MoveType = "Stand";
	CoatName = "WhiteTshirt";
	PantsName = "BluePants";
	WeaponName = "BasicSword";
	//상하의, 머리, 얼굴 등
	FaceAndHairTextureUpdate();

	//초기 애니메이션 바로 시작하도록
	AnimationCount += AniFrameList[MoveType];
}

void Player::Update(float _DeltaTime) 
{

	TimeCounting();
	AnimationUpdate();
	FaceAndHairPosUpdate();

	//PlayerPos += float4{ -50.0f, 0.0f } *_DeltaTime;
	//PlayerTransForm.SetLocalPosition(PlayerPos);

	//Body->GetTransform()->SetWorldRotation({ 180, 0, 0 });
	//Arm->GetTransform()->SetWorldRotation({ 180, 0, 0 });

}

void Player::Render(float _DeltaTime) 
{
}

void Player::TimeCounting()
{
	CurTime = static_cast<float>(clock());

	TimeCount = (CurTime - PrevTime) / 1000.0f;

	PrevTime = CurTime;
}

void Player::AnimationUpdate()
{
	AnimationCount += TimeCount;

	if (AnimationCount >= AniFrameList[MoveType])
	{
		AnimationCount = 0.0f;

		if (AniIndex >= ArmScaleAndPosList[MoveType].size())
		{
			AniIndex = 0;
		}
		
		std::string BodyTexture = SkinType + "Body" + MoveType + std::to_string(AniIndex) + ".png";
		std::string ArmTexture = SkinType + "Arm" + MoveType + std::to_string(AniIndex) + ".png";
		std::string HeadTexture = SkinType + "Head" + "Front" + ".png";
		std::string CoatTexture = CoatName + MoveType + std::to_string(AniIndex) + ".png";
		std::string CoatArmTexture = CoatName + "Arm" + MoveType + std::to_string(AniIndex) + ".png";
		std::string PantsTexture = PantsName + MoveType + std::to_string(AniIndex) + ".png";
		

		Body->SetTexture(BodyTexture);
		Coat->SetTexture(CoatTexture);
		Arm->SetTexture(ArmTexture);
		CoatArm->SetTexture(CoatArmTexture);
		Pants->SetTexture(PantsTexture);
		Head->SetTexture(HeadTexture);		

		Body->GetTransform()->SetLocalScale(BodyScaleAndPosList[MoveType][AniIndex].first);
		Body->GetTransform()->SetLocalPosition(BodyScaleAndPosList[MoveType][AniIndex].second);

		Coat->GetTransform()->SetLocalScale((CoatScaleAndPosList[CoatName][MoveType][AniIndex]).first);
		Coat->GetTransform()->SetLocalPosition((CoatScaleAndPosList[CoatName][MoveType][AniIndex]).second);

		Arm->GetTransform()->SetLocalScale((ArmScaleAndPosList[MoveType][AniIndex]).first);
		Arm->GetTransform()->SetLocalPosition((ArmScaleAndPosList[MoveType][AniIndex]).second);

		CoatArm->GetTransform()->SetLocalScale((CoatArmScaleAndPosList[CoatName][MoveType][AniIndex]).first);
		CoatArm->GetTransform()->SetLocalPosition((CoatArmScaleAndPosList[CoatName][MoveType][AniIndex]).second);

		Head->GetTransform()->SetLocalScale((HeadScaleAndPosList[MoveType][AniIndex]).first);
		Head->GetTransform()->SetLocalPosition((HeadScaleAndPosList[MoveType][AniIndex]).second);

		Pants->GetTransform()->SetLocalScale((PantsScaleAndPosList[PantsName][MoveType][AniIndex]).first);
		Pants->GetTransform()->SetLocalPosition((PantsScaleAndPosList[PantsName][MoveType][AniIndex]).second);

		if(WeaponName != "NONE")
		{
			std::string WeaponTexture = WeaponName + MoveType + std::to_string(AniIndex) + ".png";
			Weapon->SetTexture(WeaponTexture);

			Weapon->GetTransform()->SetLocalScale((WeaponScaleAndPosList[WeaponName][MoveType][AniIndex]).first);
			Weapon->GetTransform()->SetLocalPosition((WeaponScaleAndPosList[WeaponName][MoveType][AniIndex]).second);
		}
		else
		{
			Weapon->GetTransform()->SetWorldScale({ 0, 0 });
		}

		AniIndex = 0;
	}
}

void Player::FaceAndHairTextureUpdate()
{
	Hair->SetTexture(HairName + FrontBackDir + HairStatus + ".png");
	
	float4 HairScale = HairScaleAndPosList[HairName][FrontBackDir][HairStatus].first;
	Hair->GetTransform()->SetLocalScale(HairScale);

	Face->SetTexture(FaceName + Expression + ".png");

	float4 FaceScale = FaceScaleAndPosList[FaceName][Expression].first;
	Face->GetTransform()->SetLocalScale(FaceScale);

	FaceAndHairPosUpdate();
}

void Player::FaceAndHairPosUpdate()
{
	float4 HeadPos = Head->GetTransform()->GetLocalPosition();

	float4 HairPos = HairScaleAndPosList[HairName][FrontBackDir][HairStatus].second;
	Hair->GetTransform()->SetLocalPosition(HeadPos + HairPos);

	float4 FacePos = FaceScaleAndPosList[FaceName][Expression].second;
	Face->GetTransform()->SetLocalPosition(HeadPos + FacePos);
}

void Player::SetAllPartInfoPerFrame()
{
	//크기, 위치 벡터 
	ArmScaleAndPosList["Stand"].push_back({ { 10, 19 }, { 10.5f, 4 } });
	ArmScaleAndPosList["Stand"].push_back({ { 10, 19 }, { 12, 4 } });
	ArmScaleAndPosList["Stand"].push_back({ { 11, 19 }, { 12, 4 } });
	ArmScaleAndPosList["Stand"].push_back({ { 10, 19 }, { 12, 4 } });

	ArmScaleAndPosList["Walk"].push_back({ { 12, 17 }, {   12, 5.5 } });
	ArmScaleAndPosList["Walk"].push_back({ { 13, 17 }, {  6.5, 3.5 } });
	ArmScaleAndPosList["Walk"].push_back({ { 12, 17 }, {   12, 4.5 } });
	ArmScaleAndPosList["Walk"].push_back({ { 14, 15 }, { 12.5,   5 } });

	BodyScaleAndPosList["Stand"].push_back({ { 21, 31 }, {  0, 0 } });
	BodyScaleAndPosList["Stand"].push_back({ { 22, 31 }, {  0, 0 } });
	BodyScaleAndPosList["Stand"].push_back({ { 23, 31 }, { -1, 0 } });
	BodyScaleAndPosList["Stand"].push_back({ { 22, 31 }, {  0, 0 } });

	BodyScaleAndPosList["Walk"].push_back({ { 27, 32 }, {  0,  0 } });
	BodyScaleAndPosList["Walk"].push_back({ { 26, 32 }, {  3,  0 } });
	BodyScaleAndPosList["Walk"].push_back({ { 24, 32 }, { -1, -1 } });
	BodyScaleAndPosList["Walk"].push_back({ { 29, 31 }, { -1, -1 } });

	HeadScaleAndPosList["Stand"].push_back({ { 39, 35 }, { 2, 31 } });
	HeadScaleAndPosList["Stand"].push_back({ { 39, 35 }, { 2, 31 } });
	HeadScaleAndPosList["Stand"].push_back({ { 39, 35 }, { 2, 31 } });
	HeadScaleAndPosList["Stand"].push_back({ { 39, 35 }, { 2, 31 } });

	HeadScaleAndPosList["Walk"].push_back({ { 39, 35 }, { 2, 29.5 } });
	HeadScaleAndPosList["Walk"].push_back({ { 39, 35 }, { 2, 28.5 } });
	HeadScaleAndPosList["Walk"].push_back({ { 39, 35 }, { 2, 29.5 } });
	HeadScaleAndPosList["Walk"].push_back({ { 39, 35 }, { 2, 28.5 } });

	CoatScaleAndPosList["WhiteTshirt"]["Stand"].push_back({ { 14, 14 }, { 1.5, 8.5 } });
	CoatScaleAndPosList["WhiteTshirt"]["Stand"].push_back({ { 14, 14 }, {   2, 8.5 } });
	CoatScaleAndPosList["WhiteTshirt"]["Stand"].push_back({ { 14, 14 }, { 1.5, 8.5 } });
	CoatScaleAndPosList["WhiteTshirt"]["Stand"].push_back({ { 14, 14 }, {   2, 8.5 } });
	
	CoatScaleAndPosList["WhiteTshirt"]["Walk"].push_back({ { 15, 15 }, { 2.5, 8.5f } });
	CoatScaleAndPosList["WhiteTshirt"]["Walk"].push_back({ { 16, 16 }, {   3, 8    } });
	CoatScaleAndPosList["WhiteTshirt"]["Walk"].push_back({ { 15, 15 }, { 2.5, 7.5  } });
	CoatScaleAndPosList["WhiteTshirt"]["Walk"].push_back({ { 15, 15 }, {   2, 7    } });

	CoatArmScaleAndPosList["WhiteTshirt"]["Stand"].push_back({ { 5, 7 }, { 8.5, 10  } });
	CoatArmScaleAndPosList["WhiteTshirt"]["Stand"].push_back({ { 5, 6 }, { 8.5, 10  } });
	CoatArmScaleAndPosList["WhiteTshirt"]["Stand"].push_back({ { 4, 5 }, { 8.5f, 11 } });
	CoatArmScaleAndPosList["WhiteTshirt"]["Stand"].push_back({ { 5, 6 }, { 8.5, 10  } });

	CoatArmScaleAndPosList["WhiteTshirt"]["Walk"].push_back({ { 5, 5 }, { 8.5, 11.5 } });
	CoatArmScaleAndPosList["WhiteTshirt"]["Walk"].push_back({ { 5, 6 }, { 8.5, 9    } });
	CoatArmScaleAndPosList["WhiteTshirt"]["Walk"].push_back({ { 5, 5 }, { 8.5, 10.5 } });
	CoatArmScaleAndPosList["WhiteTshirt"]["Walk"].push_back({ { 5, 4 }, {   8, 10   } });

	PantsScaleAndPosList["BluePants"]["Stand"].push_back({ { 16, 11 }, { 2, -0.5 } });
	PantsScaleAndPosList["BluePants"]["Stand"].push_back({ { 16, 11 }, { 2, -0.5 } });
	PantsScaleAndPosList["BluePants"]["Stand"].push_back({ { 16, 11 }, { 2, -0.5 } });
	PantsScaleAndPosList["BluePants"]["Stand"].push_back({ { 16, 11 }, { 2, -0.5 } });
	
	PantsScaleAndPosList["BluePants"]["Walk"].push_back({ { 14, 13 }, { 3, -2.5 } });
	PantsScaleAndPosList["BluePants"]["Walk"].push_back({ { 17, 12 }, { 2, -2.5 } });
	PantsScaleAndPosList["BluePants"]["Walk"].push_back({ { 14, 12 }, { 3, -2.5 } });
	PantsScaleAndPosList["BluePants"]["Walk"].push_back({ { 14, 11 }, { 2.5, -2 } });

	WeaponScaleAndPosList["BasicSword"]["Stand"].push_back({ { 41, 13 },{ -3, -3 } });
	WeaponScaleAndPosList["BasicSword"]["Stand"].push_back({ { 41, 13 },{ -3, -3 } });
	WeaponScaleAndPosList["BasicSword"]["Stand"].push_back({ { 41, 13 },{ -3, -3 } });
	WeaponScaleAndPosList["BasicSword"]["Stand"].push_back({ { 41, 13 },{ -3, -3 } });

	HairScaleAndPosList["Toven"]["Front"]["Hair"].first = { 38, 22 };
	HairScaleAndPosList["Toven"]["Front"]["Hair"].second = { 0, 8 };

	HairScaleAndPosList["Toven"]["Front"]["Cap"].first = { 35, 20 };
	HairScaleAndPosList["Toven"]["Front"]["Cap"].second = { -1, 8 };

	FaceScaleAndPosList["Face1"]["Default"].first = { 26, 16 };
	FaceScaleAndPosList["Face1"]["Default"].second = { -3,-7 };
	//프레임설정
	AniFrameList["Stand"] = 0.5f;
	AniFrameList["Walk"] = 0.18f;
}