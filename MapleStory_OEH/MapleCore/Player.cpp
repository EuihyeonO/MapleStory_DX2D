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

	Body = CreateComponent<GameEngineSpriteRenderer>();
	Arm = CreateComponent<GameEngineSpriteRenderer>();
	Head = CreateComponent<GameEngineSpriteRenderer>();

	Hair = CreateComponent<GameEngineSpriteRenderer>();
	Face = CreateComponent<GameEngineSpriteRenderer>();

	//로테이션이 왜 초기값이 180도?
	Body->GetTransform()->SetWorldRotation({0, 0, 0});
	Arm->GetTransform()->SetWorldRotation({0, 0, 0});
	Head->GetTransform()->SetWorldRotation({0, 0, 0});

	Hair->GetTransform()->SetWorldRotation({0, 0, 0});
	Face->GetTransform()->SetWorldRotation({0, 0, 0});

	//부모설정
	Body->GetTransform()->SetParent(&PlayerTransForm);

	Arm->GetTransform()->SetParent(Body->GetTransform());
	Head->GetTransform()->SetParent(Body->GetTransform());
	Hair->GetTransform()->SetParent(Head->GetTransform());
	Face->GetTransform()->SetParent(Head->GetTransform());

	//크기, 위치 벡터 
	ArmScaleAndPosList["Stand"].push_back({ { 10, 19 }, { 11, 4 } });
	ArmScaleAndPosList["Stand"].push_back({ { 10, 19 }, { 12, 4 } });
	ArmScaleAndPosList["Stand"].push_back({ { 11, 19 }, { 13, 4 } });
	ArmScaleAndPosList["Stand"].push_back({ { 10, 19 }, { 12, 4 } });

	ArmScaleAndPosList["Walk"].push_back({ { 12, 17 }, { 12, 5 } });
	ArmScaleAndPosList["Walk"].push_back({ { 13, 17 }, {  3, 3 } });
	ArmScaleAndPosList["Walk"].push_back({ { 12, 17 }, { 13, 5 } });
	ArmScaleAndPosList["Walk"].push_back({ { 14, 15 }, { 13, 6 } });

	BodyScaleAndPosList["Stand"].push_back({ { 21, 31 }, {  0, 0 } });
	BodyScaleAndPosList["Stand"].push_back({ { 22, 31 }, {  0, 0 } });
	BodyScaleAndPosList["Stand"].push_back({ { 23, 31 }, { -1, 0 } });
	BodyScaleAndPosList["Stand"].push_back({ { 22, 31 }, {  0, 0 } });
	
	BodyScaleAndPosList["Walk"].push_back({ { 27, 32 }, {  0, 0 } });
	BodyScaleAndPosList["Walk"].push_back({ { 26, 32 }, {  2, 0 } });
	BodyScaleAndPosList["Walk"].push_back({ { 24, 32 }, {  -2, 0 } });
	BodyScaleAndPosList["Walk"].push_back({ { 29, 31 }, {  -1, -1 } });

	HeadScaleAndPosList["Stand"].push_back({ { 39, 35 }, {   2, 31 } });
	HeadScaleAndPosList["Stand"].push_back({ { 39, 35 }, {   2, 31 } });
	HeadScaleAndPosList["Stand"].push_back({ { 39, 35 }, {   3, 31 } });
	HeadScaleAndPosList["Stand"].push_back({ { 39, 35 }, {   2, 31 } });
	
	HeadScaleAndPosList["Walk"].push_back({ { 39, 35 }, {  2, 30 } });
	HeadScaleAndPosList["Walk"].push_back({ { 39, 35 }, {  0, 29 } });
	HeadScaleAndPosList["Walk"].push_back({ { 39, 35 }, {  4, 30 } });
	HeadScaleAndPosList["Walk"].push_back({ { 39, 35 }, {  3, 30 } });

	HairScaleAndPosList["Toven"]["Front"]["Hair"].first = {38, 22};
	HairScaleAndPosList["Toven"]["Front"]["Hair"].second = {-1, 9};

	HairScaleAndPosList["Toven"]["Front"]["Cap"].first = {35, 20};
	HairScaleAndPosList["Toven"]["Front"]["Cap"].second = {-1, 8};

	FaceScaleAndPosList["Face1"]["Default"].first = { 26, 16 };
	FaceScaleAndPosList["Face1"]["Default"].second = { -3,-7 };
	//프레임설정
	AniFrameList["Stand"] = 0.5f;
	AniFrameList["Walk"] = 0.18f;

	//초기애니메이션
	MoveType = "Walk";

	//상하의, 머리, 얼굴 등
	FashionTextureUpdate();

	//초기 애니메이션 바로 시작하도록
	AnimationCount += AniFrameList[MoveType];
}

void Player::Update(float _DeltaTime) 
{

	TimeCounting();
	AnimationUpdate();
	FashionPosUpdate();

	//PlayerPos += float4{ -100.0f, 0.0f } *_DeltaTime;
	//PlayerTransForm.SetLocalPosition(PlayerPos);

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

		Body->SetTexture(BodyTexture);
		Arm->SetTexture(ArmTexture);
		Head->SetTexture(HeadTexture);
		
		Body->GetTransform()->SetWorldScale(BodyScaleAndPosList[MoveType][AniIndex].first);
		Body->GetTransform()->SetLocalPosition(BodyScaleAndPosList[MoveType][AniIndex].second);

		Arm->GetTransform()->SetWorldScale((ArmScaleAndPosList[MoveType][AniIndex]).first);
		Arm->GetTransform()->SetLocalPosition((ArmScaleAndPosList[MoveType][AniIndex]).second);

		Head->GetTransform()->SetWorldScale((HeadScaleAndPosList[MoveType][AniIndex]).first);
		Head->GetTransform()->SetLocalPosition((HeadScaleAndPosList[MoveType][AniIndex]).second);

		AniIndex++;
	}
}

void Player::FashionTextureUpdate()
{
	Hair->SetTexture(HairName + FrontBackDir + HairStatus + ".png");
	
	float4 HairScale = HairScaleAndPosList[HairName][FrontBackDir][HairStatus].first;
	Hair->GetTransform()->SetWorldScale(HairScale);

	Face->SetTexture(FaceName + Expression + ".png");

	float4 FaceScale = FaceScaleAndPosList[FaceName][Expression].first;
	Face->GetTransform()->SetWorldScale(FaceScale);

	FashionPosUpdate();
}

void Player::FashionPosUpdate()
{
	float4 HairPos = HairScaleAndPosList[HairName][FrontBackDir][HairStatus].second;
	Hair->GetTransform()->SetLocalPosition(HairPos);

	float4 FacePos = FaceScaleAndPosList[FaceName][Expression].second;
	Face->GetTransform()->SetLocalPosition(FacePos);
}