#include "PrecompileHeader.h"
#include "Player.h"
#include "PlayerValue.h"
#include "ContentEnums.h"
#include "Star.h"
#include "BuffList.h"
#include "DropItem.h"
#include "UIController.h"
#include "Mouse.h"

#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCoreWindow.h>
#include <GameEngineBase/GameEngineRandom.h>

#include <ctime>

//test
#include "DamageRender.h"

std::shared_ptr<Player> Player::CurPlayer = nullptr;

Player::Player()
{
}

Player::~Player()
{

}

void Player::Start()
{
	CurPlayer = DynamicThis<Player>();
	TimeCounting();

	GetTransform()->SetLocalPosition({ 0, 0, -5.0f});
	GetTransform()->SetLocalScale({ 1, 1, 1 });

	FootCollision = CreateComponent<GameEngineCollision>();
	FootCollision->SetColType(ColType::AABBBOX2D);
	FootCollision->GetTransform()->SetLocalScale({ 2, 2 });
	FootCollision->SetOrder(static_cast<int>(CollisionOrder::Player));

	BodyCollision = CreateComponent<GameEngineCollision>();
	BodyCollision->GetTransform()->SetLocalScale({ 30, 50 });
	BodyCollision->SetOrder(static_cast<int>(CollisionOrder::Player));
	BodyCollision->GetTransform()->SetLocalPosition({ 0, 25 });
	BodyCollision->SetColType(ColType::AABBBOX2D);

	PointCollision = CreateComponent<GameEngineCollision>();
	PointCollision->GetTransform()->SetLocalScale({ 1.0f, 1.0f });
	PointCollision->GetTransform()->SetLocalPosition({ 0, 15.0f });
	PointCollision->SetOrder(static_cast<int>(CollisionOrder::PlayerPoint));

	Body = CreateComponent<GameEngineSpriteRenderer>();
	Pants = CreateComponent<GameEngineSpriteRenderer>();
	Coat = CreateComponent<GameEngineSpriteRenderer>();
	Cap = CreateComponent<GameEngineSpriteRenderer>();
	Cap->Off();

	Arm = CreateComponent<GameEngineSpriteRenderer>();
	CoatArm = CreateComponent<GameEngineSpriteRenderer>();
	Head = CreateComponent<GameEngineSpriteRenderer>();
	Hair = CreateComponent<GameEngineSpriteRenderer>();
	Face = CreateComponent<GameEngineSpriteRenderer>();
	Weapon = CreateComponent<GameEngineSpriteRenderer>();
	
	//콜리전
	RangeCheck = CreateComponent<GameEngineCollision>();
	RangeCheck->GetTransform()->SetLocalScale({ PlayerValue::Value.GetAttackDistance() , 100.0f});
	RangeCheck->SetOrder(static_cast<int>(CollisionOrder::Range));
	RangeCheck->SetColType(ColType::AABBBOX2D);

	float4 RangeScale = RangeCheck->GetTransform()->GetLocalScale();
	RangeCheck->GetTransform()->SetLocalPosition({ -RangeScale.hx(), RangeScale.hy()});

	HairName = PlayerValue::Value.Hair;
	FaceName = PlayerValue::Value.Face;
	SkinType = PlayerValue::Value.Skin;

	CoatName = UIController::GetUIController()->GetEquipItem(static_cast<int>(EquipType::Coat))->ItemName;
	WeaponName = UIController::GetUIController()->GetEquipItem(static_cast<int>(EquipType::Weapon))->ItemName;
	PantsName = UIController::GetUIController()->GetEquipItem(static_cast<int>(EquipType::Pants))->ItemName;
	
	//초기애니메이션
	MoveType = "Stand";

	WeaponType = static_cast<int>(WeaponType::Claw);

	MyBuffList = GetLevel()->CreateActor<BuffList>();

	WSkill = &Player::LuckySeven;
	ESkill = &Player::Avenger;
	SetAllTexturePosVector();
	CreateAllKey();
	
	CtrlSkill = &Player::Swing;

}

void Player::Update(float _DeltaTime)
{
	TimeCounting();

	if (GetLevel()->GetName() == "TITLE")
	{

		BasicUpdate(_DeltaTime);

		return;
	}

	FallingDown(_DeltaTime);
	ActingUpdate(_DeltaTime);

	BasicUpdate(_DeltaTime);
	CameraUpdate(_DeltaTime);


	if (GameEngineInput::IsKey("MyTest") == false)
	{
		GameEngineInput::CreateKey("MyTest", 'B');
	}

	if (GameEngineInput::IsDown("MyTest") == true)
	{
	}
}

void Player::BasicUpdate(float _DeltaTime)
{
	TextureAnimationUpdate();
	TextureUpdate();
	TexturePosUpdate();

	GetItem();	
	StatusFuncUpdate();
}

void Player::Render(float _DeltaTime) 
{

}

void Player::SetLeft()
{
	LeftRightDir = "Left";
	GetTransform()->SetLocalScale({1, 1, 1});
}

void Player::SetRight()
{
	LeftRightDir = "Right";
	GetTransform()->SetLocalScale({ -1, 1, 1 });
}

void Player::SetMoveType(const std::string_view& _MoveType)
{
	MoveType = _MoveType;

	AniIndex = 0;

	TextureUpdate();
	TexturePosUpdate();
}

void Player::CreateAllKey()
{
	if (GameEngineInput::IsKey("LMove") == false)
	{
		GameEngineInput::CreateKey("LMove", VK_LEFT);
		GameEngineInput::CreateKey("RMove", VK_RIGHT);
		GameEngineInput::CreateKey("Jump", 'C');
		GameEngineInput::CreateKey("GetItem", 'Z');
		GameEngineInput::CreateKey("UpKey", VK_UP);
		GameEngineInput::CreateKey("DownKey", VK_DOWN);
		GameEngineInput::CreateKey("ShiftSkill", VK_LSHIFT);
		GameEngineInput::CreateKey("InsSkill", VK_INSERT);
		GameEngineInput::CreateKey("HomeSkill", VK_HOME);
		GameEngineInput::CreateKey("PgUpSkill", VK_PRIOR);
		GameEngineInput::CreateKey("CtrlSkill", VK_LCONTROL);
		GameEngineInput::CreateKey("DelSkill", VK_DELETE);
		GameEngineInput::CreateKey("EndSkill", VK_END);
		GameEngineInput::CreateKey("PgDnSkill", VK_NEXT);
	}
}

void Player::ActingUpdate(float _DeltaTime)
{	
	if (isKnockBack == true)
	{
		KnockBackUpdate(_DeltaTime);
		return;
	}

	if (isKeyJump == true)
	{
		JumpUpdate(_DeltaTime);
	}

	if (isHit == true)
	{
		return;
	}

	if (isRopeOrLadder == true)
	{
		RopeAndLadder(_DeltaTime);
		return;
	}

	int State = GetStateByKeyInput();

	switch (State)
	{
	case static_cast<int>(State::Move):
		Move(_DeltaTime);
		break;
	case static_cast<int>(State::Jump):
		if(isCannotJump == false)
		{
			Jump(_DeltaTime);
		}
		break;
	case static_cast<int>(State::Up):
		RopeAndLadder(_DeltaTime);
		break;
	case static_cast<int>(State::Down):
		RopeAndLadder(_DeltaTime);
		break;
	case static_cast<int>(State::ShiftSkill):	
		if (ShiftSkill != nullptr && isLockSkill == false)
		{
			ShiftSkill(DynamicThis<Player>());
		}
		break;
	case static_cast<int>(State::InsSkill):
		if (InsertSkill != nullptr && isLockSkill == false)
		{
			InsertSkill(DynamicThis<Player>());
		}
		break;
	case static_cast<int>(State::HomeSkill):
		if (HomeSkill != nullptr && isLockSkill == false)
		{
			HomeSkill(DynamicThis<Player>());
		}
		break;
	case static_cast<int>(State::PgUpSkill):
		if (PageUpSkill != nullptr && isLockSkill == false)
		{
			PageUpSkill(DynamicThis<Player>());
		}
		break;
	case static_cast<int>(State::CtrlSkill):
		CtrlSkill(DynamicThis<Player>());
		break;
	case static_cast<int>(State::DelSkill):
		if (DelSkill != nullptr && isLockSkill == false)
		{
			DelSkill(DynamicThis<Player>());
		}
		break;
	case static_cast<int>(State::EndSkill):
		if (EndSkill != nullptr && isLockSkill == false)
		{
			EndSkill(DynamicThis<Player>());
		}
		break;
	case static_cast<int>(State::PgDnSkill):
		if (PageDownSkill != nullptr && isLockSkill == false)
		{
			PageDownSkill(DynamicThis<Player>());
		}
		break;
	case -1:
		Idle();
		break;
	}
}

int Player::GetStateByKeyInput() const
{
	if (GameEngineInput::IsDown("UpKey") == true || GameEngineInput::IsPress("UpKey") == true)
	{
		return static_cast<int>(State::Up);
	}
	else if (GameEngineInput::IsDown("DownKey") == true || GameEngineInput::IsPress("DownKey") == true)
	{
		return static_cast<int>(State::Down);
	}
	else if (GameEngineInput::IsDown("ShiftSkill") == true)
	{
		return static_cast<int>(State::ShiftSkill);
	}
	else if (GameEngineInput::IsDown("InsSkill") == true)
	{
		return static_cast<int>(State::InsSkill);
	}
	else if (GameEngineInput::IsDown("HomeSkill") == true)
	{
		return static_cast<int>(State::HomeSkill);
	}
	else if (GameEngineInput::IsDown("PgUpSkill") == true)
	{
		return static_cast<int>(State::PgUpSkill);
	}
	else if (GameEngineInput::IsDown("CtrlSkill") == true)
	{
		return static_cast<int>(State::CtrlSkill);
	}
	else if (GameEngineInput::IsDown("DelSkill") == true)
	{
		return static_cast<int>(State::DelSkill);
	}
	else if (GameEngineInput::IsDown("EndSkill") == true)
	{
		return static_cast<int>(State::EndSkill);
	}
	else if (GameEngineInput::IsDown("PgDnSkill") == true)
	{
		return static_cast<int>(State::PgDnSkill);
	}
	if (GameEngineInput::IsDown("Jump") == true)
	{
		return static_cast<int>(State::Jump);
	}
	else if (GameEngineInput::IsPress("LMove") == true || GameEngineInput::IsPress("RMove") == true)
	{
		return static_cast<int>(State::Move);
	}
	else
	{
		return -1;
	}
}

float Num = 0.0f;

void Player::CameraUpdate(float _DeltaTime)
{
	float HalfWidth = ColMap->GetWidth() * 0.5f;
	float HalfHeight = ColMap->GetHeight() * 0.5f;

	float4 PlayerPos = GetTransform()->GetLocalPosition();
	float4 CameraPos = GetLevel()->GetMainCamera()->GetTransform()->GetLocalPosition();

	PlayerPos.z = 0.0f;
	CameraPos.z = 0.0f;

	float4 newPosition = newPosition.Lerp(CameraPos, PlayerPos, 4.0f * _DeltaTime);

	float MaxY = 350.0f;
	float MinY = 490.0f;
	
	if (GetLevel()->GetName() == "ALTEROFZAKUM")
	{
		MaxY = 425.0f;
	}
	else if (GetLevel()->GetName() == "ZAKUMROAD1" || GetLevel()->GetName() == "JAZZBAR")
	{
		MinY = 250.0f;
	}


	if (newPosition.x - 425 < -HalfWidth)
	{
		newPosition.x = -HalfWidth + 425;
	}
	else if (newPosition.x + 425 > HalfWidth )
	{
		newPosition.x = HalfWidth - 425;
	}

	if (newPosition.y - MinY < -HalfHeight)
	{
		newPosition.y = -HalfHeight + MinY;
	}
	else if (newPosition.y + MaxY > HalfHeight)
	{
		newPosition.y = HalfHeight - MaxY;
	}

	if (GetLevel()->GetName() == "JAZZBAR")
	{
		newPosition.x = 0.0f;
	}

	if (GetLevel()->GetName() == "ALTEROFZAKUMENT")
	{
		newPosition.y = -30.0f;
	}

	GetLevel()->GetMainCamera()->GetTransform()->SetLocalPosition(newPosition);
}

bool Player::isSameColor()
{
	float4 PlayerPos = GetTransform()->GetLocalPosition();

	float4 MapHalfScale = { static_cast<float>(ColMap->GetWidth() / 2) ,  static_cast<float>(ColMap->GetHeight() / 2) };
	float4 ColorPos = MapHalfScale + float4{ PlayerPos.x, -PlayerPos.y };

	GameEnginePixelColor Color = { (char)255, 0, (char)255, (char)255 };
	GameEnginePixelColor MapColor = ColMap->GetPixel(static_cast<int>(ColorPos.x), static_cast<int>(ColorPos.y));

	return Color == MapColor;
}


void Player::GetItem()
{
	if (GameEngineInput::IsDown("GetItem") == false)
	{
		return;
	}

	std::shared_ptr<GameEngineCollision> collision = BodyCollision->Collision(static_cast<int>(CollisionOrder::DropItem), ColType::AABBBOX2D, ColType::AABBBOX2D);
	
	if (collision != nullptr && GameEngineInput::IsDown("GetItem") == true)
	{
		std::shared_ptr<DropItem> _Item = collision->GetActor()->DynamicThis<DropItem>();
		_Item->GetItem();
	}
}

void Player::FallingDown(float _DeltaTime)
{
	if (isKeyJump == true || isRopeOrLadder == true)
	{
		return;
	}

	float4 MapHalfScale = { static_cast<float>(ColMap->GetWidth() / 2) ,  static_cast<float>(ColMap->GetHeight() / 2) };

	GameEnginePixelColor Magenta = { (char)255, (char)0, (char)255, (char)255 };
	GameEnginePixelColor White = { (char)255, (char)255, (char)255, (char)255 };

	float4 CurPos = GetTransform()->GetLocalPosition();
	float4 CurColorPos = MapHalfScale + float4{ CurPos.x, -CurPos.y };
	GameEnginePixelColor CurColor = ColMap->GetPixel(static_cast<int>(CurColorPos.x), static_cast<int>(CurColorPos.y));

	if (CurColor == Magenta)
	{
		return;
	}

	isFalling = true;

	if(isSwing == false && isKnockBack == false)
	{
		MoveType = "Jump";
	}

	Gravity += GravityAccel * _DeltaTime;

	if (Gravity > 800.0f)
	{
		Gravity = 800.0f;
	}

	float4 NextPos = GetTransform()->GetLocalPosition() + float4{ FallingXMove * _DeltaTime , -Gravity * _DeltaTime };
	
	if (abs(NextPos.y - CurPos.y) > 15)
	{
		NextPos.y += 5.0f;
	}

	float4 NextColorPos = MapHalfScale + float4{ NextPos.x, -NextPos.y };
	GameEnginePixelColor NextColor = ColMap->GetPixel(static_cast<int>(NextColorPos.x), static_cast<int>(NextColorPos.y));


	if (CurColor == White && NextColor == White)
	{
		GetTransform()->SetLocalPosition(NextPos + float4{0, 0, -5.0f});
		return;
	}
	else if (CurColor == White && NextColor == Magenta)
	{
		float Count = 0.5f;

		while (NextColor == Magenta)
		{
			NextPos = GetTransform()->GetLocalPosition() + float4{ Count * FallingXMove * _DeltaTime , Count * -Gravity * _DeltaTime };
			NextColorPos = MapHalfScale + float4{ NextPos.x, -NextPos.y };
			NextColor = ColMap->GetPixel(static_cast<int>(NextColorPos.x), static_cast<int>(NextColorPos.y));

			Count *= 0.5f;
		}

		Gravity = 200.0f;
		FallingXMove = 0.0f;

		if (isSwing == false && isKnockBack == false)
		{
			MoveType = "Stand";
		}

		JumpPower = 600.0f;
		isFalling = false;
		isFlashJump = false;

		float4 RealNextPos = { NextColorPos.x - MapHalfScale.x, MapHalfScale.y - NextColorPos.y - 1.0f, -5.0f };
		GetTransform()->SetLocalPosition(RealNextPos);
		return;
	}
}