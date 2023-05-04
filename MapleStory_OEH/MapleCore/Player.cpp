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

	GetTransform()->SetLocalPosition({ 0, 0 });
	GetTransform()->SetLocalScale({ 1, 1 });
	//GetTransform()->SetLocalScale({ 8, 8 });

	Body = CreateComponent<GameEngineSpriteRenderer>();
	//Pants = CreateComponent<GameEngineSpriteRenderer>();
	//Coat = CreateComponent<GameEngineSpriteRenderer>();
	////
	//Weapon = CreateComponent<GameEngineSpriteRenderer>();
	Arm = CreateComponent<GameEngineSpriteRenderer>();
	//CoatArm = CreateComponent<GameEngineSpriteRenderer>();
	////
	Head = CreateComponent<GameEngineSpriteRenderer>();

	Hair = CreateComponent<GameEngineSpriteRenderer>();
	Face = CreateComponent<GameEngineSpriteRenderer>();

	//로테이션이 왜 초기값이 180도?
	// 
	//SetAllPartInfoPerFrame();

	//초기애니메이션
	MoveType = "Swing0";
	//CoatName = "WhiteTshirt";
	//PantsName = "BluePants";
	//WeaponName = "BasicSword";
	
	//상하의, 머리, 얼굴 등
	// 
	//FaceAndHairTextureUpdate();

	//초기 애니메이션 바로 시작하도록
	SetAllTexturePosVector();

	//AnimationCount += AniFrameList[MoveType];


}

void Player::Update(float _DeltaTime) 
{

	TimeCounting();

	TextureAnimationUpdate();
	TexturePosUpdate();

	//PlayerPos += float4{ -50.0f, 0.0f } *_DeltaTime;
	//GetTransform()->SetLocalPosition(PlayerPos);
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

void Player::TextureAnimationUpdate()
{
	AnimationCount += TimeCount;

	if (AnimationCount >= AniFrameList[MoveType][AniIndex])
	{
		AniIndex++;

		if (AniIndex >= AniFrameList[MoveType].size())
		{
			AniIndex = 0;
		}

		AnimationCount = 0.0f;
		
		std::string BodyTexture = SkinType + "Body" + MoveType + std::to_string(AniIndex) + ".png";
		std::string ArmTexture = SkinType + "Arm" + MoveType + std::to_string(AniIndex) + ".png";
		std::string HeadTexture = SkinType + "Head" + "Front" + ".png";
		std::string HairTexture = HairName + FrontBackDir + HairStatus + ".png";
		std::string FaceTexture = FaceName + Expression + ".png";

		//std::string CoatTexture = CoatName + MoveType + std::to_string(AniIndex) + ".png";
		//std::string CoatArmTexture = CoatName + "Arm" + MoveType + std::to_string(AniIndex) + ".png";
		//std::string PantsTexture = PantsName + MoveType + std::to_string(AniIndex) + ".png";

		Body->SetScaleToTexture(BodyTexture);
		Arm->SetScaleToTexture(ArmTexture);
		Head->SetScaleToTexture(HeadTexture);
		Hair->SetScaleToTexture(HairTexture);
		Face->SetScaleToTexture(FaceTexture);
		
	}

}


void Player::TexturePosUpdate()
{

	float4 BodyScale = Body->GetTransform()->GetLocalScale();
	Body->GetTransform()->SetLocalPosition({ BodyScale.hx(), -BodyScale.hy()});	
	//Origin
	Body->GetTransform()->AddLocalPosition(BodyOriginPos[MoveType][AniIndex]);
 ;

	float4 ArmScale = Arm->GetTransform()->GetLocalScale();
	Arm->GetTransform()->SetLocalPosition({ ArmScale.hx(), -ArmScale.hy() });
	//Origin
	float4 Pos1 = BodyNavelPos[MoveType][AniIndex];
	float4 Pos2 = ArmToNavelPos[MoveType][AniIndex];
	float4 Pos3 = ArmOriginPos[MoveType][AniIndex];

	Arm->GetTransform()->AddLocalPosition(BodyNavelPos[MoveType][AniIndex] + ArmToNavelPos[MoveType][AniIndex] + ArmOriginPos[MoveType][AniIndex]);

	float4 Pos = Arm->GetTransform()->GetLocalPosition();

	float4 HeadScale = Head->GetTransform()->GetLocalScale();
	Head->GetTransform()->SetLocalPosition({ HeadScale.hx(), -HeadScale.hy() });
	Head->GetTransform()->AddLocalPosition(BodyNeckPos[MoveType][AniIndex] + HeadToNeckPos[FrontBackDir] + HeadOriginPos[FrontBackDir]);

	float4 HeadPos = Head->GetTransform()->GetLocalPosition();
	float4 BrowPos = HeadPos + HeadBrowPos[FrontBackDir];

	float4 HairScale = Hair->GetTransform()->GetLocalScale();
	Hair->GetTransform()->SetLocalPosition({ HairScale.hx(), -HairScale.hy() });
	Hair->GetTransform()->AddLocalPosition(BrowPos + HairToBrowPos[HairName][FrontBackDir] + HairOriginPos[HairName][FrontBackDir]);

	float4 FaceScale = Face->GetTransform()->GetLocalScale();
	Face->GetTransform()->SetLocalPosition({ FaceScale.hx(), -FaceScale.hy() });
	Face->GetTransform()->AddLocalPosition(BrowPos + FaceToBrowPos[FaceName][Expression] + FaceOriginPos[FaceName][Expression]);
}

void Player::SetAllTexturePosVector()
{
	//Frame
	AniFrameList["Stand"].push_back(0.5f);
	AniFrameList["Stand"].push_back(0.5f);
	AniFrameList["Stand"].push_back(0.5f);
	AniFrameList["Stand"].push_back(0.5f);

	AniFrameList["Walk"].push_back(0.18f);
	AniFrameList["Walk"].push_back(0.18f);
	AniFrameList["Walk"].push_back(0.18f);
	AniFrameList["Walk"].push_back(0.18f);
	
	AniFrameList["Swing0"].push_back(0.3f);
	AniFrameList["Swing0"].push_back(0.15f);
	AniFrameList["Swing0"].push_back(0.35f);

	AniFrameList["Swing1"].push_back(0.3f);
	AniFrameList["Swing1"].push_back(0.15f);
	AniFrameList["Swing1"].push_back(0.35f);

		//Origin은 X반전 Y그대로
		
	//Body
	BodyOriginPos["Stand"].push_back({ -16, 31 });
	BodyOriginPos["Stand"].push_back({ -17, 31 });
	BodyOriginPos["Stand"].push_back({ -18, 31 });
	BodyOriginPos["Stand"].push_back({ -17, 31 });
	BodyOriginPos["Walk"].push_back({ -19, 32 });
	BodyOriginPos["Walk"].push_back({ -16, 32 });
	BodyOriginPos["Walk"].push_back({ -19, 32 });
	BodyOriginPos["Walk"].push_back({ -21, 31 });
	BodyOriginPos["Swing0"].push_back({ -11, 27 });
	BodyOriginPos["Swing0"].push_back({ -11, 31 });
	BodyOriginPos["Swing0"].push_back({ -38, 27 });


		//x는 그대로, y는 반전 
	BodyNavelPos["Stand"].push_back({ -8, 21 });
	BodyNavelPos["Stand"].push_back({ -7, 20 });
	BodyNavelPos["Stand"].push_back({ -6, 21 });
	BodyNavelPos["Stand"].push_back({ -7, 20 });
	BodyNavelPos["Walk"].push_back({ -6, 20 });
	BodyNavelPos["Walk"].push_back({ -6, 20 });
	BodyNavelPos["Walk"].push_back({ -6, 20 });
	BodyNavelPos["Walk"].push_back({ -6, 18 });
	BodyNavelPos["Swing0"].push_back({ -1, 16 });
	BodyNavelPos["Swing0"].push_back({ -8, 20 });
	BodyNavelPos["Swing0"].push_back({ -29, 17 });
	
	//
	BodyNeckPos["Stand"].push_back({ -4, 32 });
	BodyNeckPos["Stand"].push_back({ -4, 32 });
	BodyNeckPos["Stand"].push_back({ -4, 32 });
	BodyNeckPos["Stand"].push_back({ -4, 32 });
	BodyNeckPos["Walk"].push_back({ -4, 32 });
	BodyNeckPos["Walk"].push_back({ -4, 31 });
	BodyNeckPos["Walk"].push_back({ -4, 32 });
	BodyNeckPos["Walk"].push_back({ -4, 31 });
	BodyNeckPos["Swing0"].push_back({ -9, 26 });
	BodyNeckPos["Swing0"].push_back({ -10, 31 });
	BodyNeckPos["Swing0"].push_back({ -37, 25 });
	
	//Arm

	ArmOriginPos["Stand"].push_back({ -5, 9 });
	ArmOriginPos["Stand"].push_back({ -5, 9 });
	ArmOriginPos["Stand"].push_back({ -6, 9 });
	ArmOriginPos["Stand"].push_back({ -5, 9 });
	ArmOriginPos["Walk"].push_back({ -6, 8 });
	ArmOriginPos["Walk"].push_back({ -6, 9 });
	ArmOriginPos["Walk"].push_back({ -6, 9 });
	ArmOriginPos["Walk"].push_back({ -7, 7});
	ArmOriginPos["Swing0"].push_back({ -7, 7});
	ArmOriginPos["Swing0"].push_back({ -7, 7 });
	ArmOriginPos["Swing0"].push_back({ -6, 7 });
		//X 반전, Y그대로
	ArmToNavelPos["Stand"].push_back({ 13, -1 });
	ArmToNavelPos["Stand"].push_back({ 13, 0 });
	ArmToNavelPos["Stand"].push_back({ 13, -1 });
	ArmToNavelPos["Stand"].push_back({ 13, 0 });
	ArmToNavelPos["Walk"].push_back({ 12, 2 });
	ArmToNavelPos["Walk"].push_back({ 6, -1 });
	ArmToNavelPos["Walk"].push_back({ 12, 2 });
	ArmToNavelPos["Walk"].push_back({ 13, 4 });
	ArmToNavelPos["Swing0"].push_back({ -5, 2 });
	ArmToNavelPos["Swing0"].push_back({ -5, 4});
	ArmToNavelPos["Swing0"].push_back({ 8, 18 });
	//Head
	
	HeadOriginPos["Front"] = float4{ -19, 17 };
	
	HeadToNeckPos["Front"] = float4{ 0, 15 };
	      //x,y 둘다반전
	HeadBrowPos["Front"] = float4{ -4, 5 };

	//Hair

	HairOriginPos["Toven"]["Front"] = float4{-24, 15};
	      //x,y 둘다반전
	HairToBrowPos["Toven"]["Front"] = float4{9, -1};

	//Face

	FaceOriginPos["Face1"]["Default"] = float4{ -13, 8 };
		//x,y 둘다반전
	FaceToBrowPos["Face1"]["Default"] = float4{ 1, -12 };
}