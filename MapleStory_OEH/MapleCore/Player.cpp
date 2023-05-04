#include "PrecompileHeader.h"
#include "Player.h"
#include "PlayerValue.h"
#include "ContentEnums.h"

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
	WeaponName = "BasicSword";
	
	MoveSpeed = 100.0f;

	SetAllTexturePosVector();
	CreateAllKey();
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

	ActingUpdate(_DeltaTime);
	GravityUpdate(_DeltaTime);

	TextureAnimationUpdate();
	TextureUpdate();
	TexturePosUpdate();

	CameraUpdate();
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
	Gravity = 300.0f;
	
	float4 PlayerPos = GetTransform()->GetLocalPosition();

	float4 MapHalfScale = { static_cast<float>(ColMap->GetWidth() / 2) ,  static_cast<float>(ColMap->GetHeight() / 2) };
	float4 ColorPos = MapHalfScale + float4{ PlayerPos.x, -PlayerPos.y };

	GameEnginePixelColor Color = { (char)255, 0, (char)255, (char)255 };
	GameEnginePixelColor MapColor = ColMap->GetPixel(ColorPos.x, ColorPos.y);
	
	if (Color != MapColor)
	{
		GetTransform()->AddLocalPosition({ 0, -Gravity * _DeltaTime });
		isGround = false;
	}
	else
	{
		float Count = 0.0f;

		while (Color == MapColor)
		{
			ColorPos.y--;
			MapColor = ColMap->GetPixel(ColorPos.x, ColorPos.y);
			Count++;
		}
		GetTransform()->AddLocalPosition({ 0, Count - 1 });
		isGround = true;
	}
}

void Player::Idle()
{
	MoveType = "Stand";
}

void Player::Move(float _DeltaTime)
{

	if (GameEngineInput::IsPress("LMove") == true)
	{
		SetLeft();
		LeftRightDir = "Left";
		MoveType = "Walk";

		float4 NextPlayerPos = GetTransform()->GetLocalPosition() + float4{-1 * MoveSpeed * _DeltaTime, 0 };

		float4 MapHalfScale = { static_cast<float>(ColMap->GetWidth() / 2) ,  static_cast<float>(ColMap->GetHeight() / 2) };
		float4 ColorPos = MapHalfScale + float4{ NextPlayerPos.x, -NextPlayerPos.y };

		GameEnginePixelColor Color = { (char)255, 0, (char)255, (char)255 };
		GameEnginePixelColor MapColor = ColMap->GetPixel(ColorPos.x, ColorPos.y);

		if (Color == MapColor)
		{
			float Count = 0;
			
			while (Color == MapColor)
			{
				ColorPos.y--;
				MapColor = ColMap->GetPixel(ColorPos.x, ColorPos.y);
				Count++;
			}

			float4 Vector1 = {-1, 0};
			Vector1.Normalize();
			float4 Vector2 = { -1, Count };
			Vector2.Normalize();

			float Angle = (Vector1.x) * (Vector2.x) + (Vector1.y) * (Vector2.y);

			if (Angle > 0.5f)
			{
				GetTransform()->AddLocalPosition({ -1 * MoveSpeed * _DeltaTime, 0 });
			}
		}
		else
		{
			GetTransform()->AddLocalPosition({ -1 * MoveSpeed * _DeltaTime, 0 });
		}
	}

	if (GameEngineInput::IsPress("RMove") == true)
	{
		SetRight();
		LeftRightDir = "Right";
		MoveType = "Walk";

		float4 NextPlayerPos = GetTransform()->GetLocalPosition() + float4{ 1 * MoveSpeed * _DeltaTime, 0 };

		float4 MapHalfScale = { static_cast<float>(ColMap->GetWidth() / 2) ,  static_cast<float>(ColMap->GetHeight() / 2) };
		float4 ColorPos = MapHalfScale + float4{ NextPlayerPos.x, -NextPlayerPos.y };

		GameEnginePixelColor Color = { (char)255, 0, (char)255, (char)255 };
		GameEnginePixelColor MapColor = ColMap->GetPixel(ColorPos.x, ColorPos.y);

		if (Color == MapColor)
		{
			float Count = 0;

			while (Color == MapColor)
			{
				ColorPos.y--;
				MapColor = ColMap->GetPixel(ColorPos.x, ColorPos.y);
				Count++;
			}

			float4 Vector1 = { 1, 0 };
			Vector1.Normalize();
			float4 Vector2 = { 1, Count };
			Vector2.Normalize();

			float Angle = (Vector1.x) * (Vector2.x) + (Vector1.y) * (Vector2.y);

			if (Angle > 0.5f)
			{
				GetTransform()->AddLocalPosition({ 1 * MoveSpeed * _DeltaTime, 0 });
			}
		}
		else
		{
			GetTransform()->AddLocalPosition({ 1 * MoveSpeed * _DeltaTime, 0 });
		}		
	}
}

void Player::CreateAllKey()
{
	if (GameEngineInput::IsKey("LMove") == false)
	{
		GameEngineInput::CreateKey("LMove", VK_LEFT);
		GameEngineInput::CreateKey("RMove", VK_RIGHT);
	}
}

void Player::ActingUpdate(float _DeltaTime)
{
	int Key = GetKeyInput();

	switch (Key)
	{
	case static_cast<int>(InputKey::Move):
		Move(_DeltaTime);
		break;
	case static_cast<int>(InputKey::Jump):
		break;
	case -1:
		Idle();
	}
}

int Player::GetKeyInput()
{
	if (GameEngineInput::IsPress("LMove") == true || GameEngineInput::IsPress("RMove") == true)
	{
		return static_cast<int>(InputKey::Move);
	}
	else
	{
		return -1;
	}
}

void Player::CameraUpdate()
{
	int HalfWidth = ColMap->GetWidth() * 0.5f;
	int HalfHeight = ColMap->GetHeight() * 0.5f;

	float4 PlayerPos = GetTransform()->GetLocalPosition();
	float4 CameraPos = PlayerPos;

	if (CameraPos.x - 400 < -HalfWidth)
	{
		CameraPos.x = -HalfWidth + 400;
	}
	else if (CameraPos.x + 400 > HalfWidth - 40)
	{
		CameraPos.x = HalfWidth - 40 - 400;
	}

	if (CameraPos.y - 300 < -(HalfHeight - 185))
	{
		CameraPos.y = -(HalfHeight - 185) + 300;
	}
	else if (CameraPos.y + 300 > HalfHeight)
	{
		CameraPos.y = HalfHeight - 300;
	}

	GetLevel()->GetMainCamera()->GetTransform()->SetLocalPosition(CameraPos);
}