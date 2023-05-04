#include "PrecompileHeader.h"
#include "Player.h"
#include "PlayerValue.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <ctime>

Player::Player()
{
	PlayerValue::Value.AddToPlayerToPlayerList(this);
}

Player::~Player()
{
}

void Player::Start()
{
	TimeCounting();

	GetTransform()->SetLocalPosition({ 0, 0 });
	GetTransform()->SetLocalScale({ 1, 1 });

	Body = CreateComponent<GameEngineSpriteRenderer>();
	Pants = CreateComponent<GameEngineSpriteRenderer>();
	Coat = CreateComponent<GameEngineSpriteRenderer>();
	////

	//SetOrder이 안되네?
	Weapon = CreateComponent<GameEngineSpriteRenderer>();
	Arm = CreateComponent<GameEngineSpriteRenderer>();

	CoatArm = CreateComponent<GameEngineSpriteRenderer>();
	////
	Head = CreateComponent<GameEngineSpriteRenderer>();

	Hair = CreateComponent<GameEngineSpriteRenderer>();
	Face = CreateComponent<GameEngineSpriteRenderer>();

	//로테이션이 왜 초기값이 180도?
	// 
	//SetAllPartInfoPerFrame();

	//초기애니메이션
	SkinType = "Basic";
	MoveType = "Stand";
	CoatName = "WhiteTshirt";
	PantsName = "BluePants";
	WeaponName = "Ganier";
	
	//상하의, 머리, 얼굴 등
	// 
	//FaceAndHairTextureUpdate();

	//초기 애니메이션 바로 시작하도록
	SetAllTexturePosVector();

	//AnimationCount += AniFrameList[MoveType];

}

void Player::Update(float _DeltaTime) 
{
	if (GetLevel()->GetName() == "TITLE")
	{
		TimeCounting();

		TextureAnimationUpdate();
		TextureUpdate();
		TexturePosUpdate();
		return;
	}

	TimeCounting();

	TextureAnimationUpdate();
	TextureUpdate();
	TexturePosUpdate();
	GravityUpdate(_DeltaTime);
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
	}
}

void Player::TextureUpdate()
{
	std::string BodyTexture = SkinType + "Body" + MoveType + std::to_string(AniIndex) + ".png";
	std::string ArmTexture = SkinType + "Arm" + MoveType + std::to_string(AniIndex) + ".png";
	std::string HeadTexture = SkinType + "Head" + "Front" + ".png";
	std::string HairTexture = HairName + FrontBackDir + HairStatus + ".png";
	std::string FaceTexture = FaceName + Expression + ".png";

	std::string CoatTexture = CoatName + MoveType + std::to_string(AniIndex) + ".png";
	std::string CoatArmTexture = CoatName + "Arm" + MoveType + std::to_string(AniIndex) + ".png";
	std::string PantsTexture = PantsName + MoveType + std::to_string(AniIndex) + ".png";

	std::string WeaponTexture = WeaponName + MoveType + std::to_string(AniIndex) + ".png";

	Body->SetScaleToTexture(BodyTexture);
	Arm->SetScaleToTexture(ArmTexture);
	Head->SetScaleToTexture(HeadTexture);
	Hair->SetScaleToTexture(HairTexture);
	Face->SetScaleToTexture(FaceTexture);
	Coat->SetScaleToTexture(CoatTexture);
	CoatArm->SetScaleToTexture(CoatArmTexture);
	Pants->SetScaleToTexture(PantsTexture);
	Weapon->SetScaleToTexture(WeaponTexture);
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
	Arm->GetTransform()->AddLocalPosition(BodyNavelPos[MoveType][AniIndex] + ArmToNavelPos[MoveType][AniIndex] + ArmOriginPos[MoveType][AniIndex]);

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

	float4 CoatScale = Coat->GetTransform()->GetLocalScale();
	Coat->GetTransform()->SetLocalPosition({ CoatScale.hx(), -CoatScale.hy() });
	Coat->GetTransform()->AddLocalPosition(BodyNavelPos[MoveType][AniIndex] + CoatToNavelPos[MoveType][CoatName][AniIndex] + CoatOriginPos[MoveType][CoatName][AniIndex]);
	
	float4 CoatArmScale = CoatArm->GetTransform()->GetLocalScale();
	CoatArm->GetTransform()->SetLocalPosition({ CoatArmScale.hx(), -CoatArmScale.hy() });
	CoatArm->GetTransform()->AddLocalPosition(BodyNavelPos[MoveType][AniIndex] + CoatArmToNavelPos[MoveType][CoatName][AniIndex] + CoatArmOriginPos[MoveType][CoatName][AniIndex]);
	
	float4 PantsScale = Pants->GetTransform()->GetLocalScale();
	Pants->GetTransform()->SetLocalPosition({ PantsScale.hx(), -PantsScale.hy() });
	Pants->GetTransform()->AddLocalPosition(BodyNavelPos[MoveType][AniIndex] + PantsToNavelPos[MoveType][PantsName][AniIndex] + PantsOriginPos[MoveType][PantsName][AniIndex]);

	float4 HandPos = ArmHandPos[MoveType][AniIndex] + Arm->GetTransform()->GetLocalPosition();

	float4 WeaponScale = Weapon->GetTransform()->GetLocalScale();
	Weapon->GetTransform()->SetLocalPosition({ WeaponScale.hx(), -WeaponScale.hy() });
	Weapon->GetTransform()->AddLocalPosition(HandPos + WeaponToHandPos[MoveType][WeaponName][AniIndex] + WeaponOriginPos[MoveType][WeaponName][AniIndex]);

}

void Player::SetLeft()
{
	LeftRightDir = "Left";
	GetTransform()->SetLocalScale({ 1, 1 });
}

void Player::SetRight()
{
	LeftRightDir = "Right";
	GetTransform()->SetLocalScale({ -1, 1 });
}

void Player::SetMoveType(const std::string_view& _MoveType)
{
	MoveType = _MoveType;

	AniIndex = 0;

	TextureUpdate();
	TexturePosUpdate();
}

void Player::GravityUpdate(float _DeltaTime)
{
	float Gravity = 30.0f;

	GetTransform()->AddLocalPosition({ 0, -Gravity * _DeltaTime });

	float4 PlayerPos = GetTransform()->GetLocalPosition();

	float4 MapHalfScale = { static_cast<float>(ColMap->GetWidth() / 2) ,  static_cast<float>(ColMap->GetHeight() / 2) };
	float4 ColorPos = MapHalfScale + float4{PlayerPos.x, -PlayerPos.y};

	GameEnginePixelColor Color = {(char)255, 0, (char)255, (char)255};
	GameEnginePixelColor MapColor = ColMap->GetPixel(ColorPos.x, ColorPos.y);

	if (Color == MapColor)
	{
		float PlayerYPos = static_cast<int>(PlayerPos.y);
	}


}