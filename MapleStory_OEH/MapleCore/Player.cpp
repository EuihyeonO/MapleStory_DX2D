#include "PrecompileHeader.h"
#include "Player.h"
#include "PlayerValue.h"
#include "ContentEnums.h"
#include "Star.h"
#include "BuffList.h"
#include "DropItem.h"
#include "UIController.h"

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
	PlayerValue::Value.AddToPlayerToPlayerList(DynamicThis<Player>());

	TimeCounting();

	GetTransform()->SetLocalPosition({ 0, 0, -5.0f});
	GetTransform()->SetLocalScale({ 1, 1, 1 });

	BodyCollision = CreateComponent<GameEngineCollision>();
	BodyCollision->GetTransform()->SetLocalScale({ 30, 50 });
	BodyCollision->SetOrder(static_cast<int>(CollisionOrder::Player));
	BodyCollision->GetTransform()->SetLocalPosition({ 0, 25 });

	PointCollision = CreateComponent<GameEngineCollision>();
	PointCollision->GetTransform()->SetLocalScale({ 1.0f, 1.0f });
	PointCollision->GetTransform()->SetLocalPosition({ 0, 15.0f });
	PointCollision->SetOrder(static_cast<int>(CollisionOrder::PlayerPoint));

	Body = CreateComponent<GameEngineSpriteRenderer>();
	Pants = CreateComponent<GameEngineSpriteRenderer>();
	Coat = CreateComponent<GameEngineSpriteRenderer>();

	//SetOrder가 안되네?
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

	float4 RangeScale = RangeCheck->GetTransform()->GetLocalScale();
	RangeCheck->GetTransform()->SetLocalPosition({ -RangeScale.hx(), RangeScale.hy()});

	//초기애니메이션
	SkinType = "Basic";
	MoveType = "Stand";
	CoatName = "WhiteTshirt";
	PantsName = "BluePants";
	WeaponName = "Ganier";
	
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
	if (GetLevel()->GetName() == "TITLE")
	{
		TimeCounting();

		TextureAnimationUpdate();
		TextureUpdate();
		TexturePosUpdate();
		return;
	}

	TimeCounting();

	GravityUpdate(_DeltaTime);
	ActingUpdate(_DeltaTime);

	TextureAnimationUpdate();
	TextureUpdate();
	TexturePosUpdate();

	GetItem();
	CameraUpdate(_DeltaTime);

	PrevPos = GetTransform()->GetLocalPosition();
	/*Test*/
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

void Player::GravityUpdate(float _DeltaTime)
{
	if (isRopeOrLadder == true)
	{
		return;
	}

	Gravity += GravityAccel * _DeltaTime;

	if (Gravity >= 1000.0f)
	{
		Gravity = 1000.0f;
	}

	float4 PlayerPos = GetTransform()->GetLocalPosition();

	float4 MapHalfScale = { static_cast<float>(ColMap->GetWidth() / 2) ,  static_cast<float>(ColMap->GetHeight() / 2) };
	float4 ColorPos = float4{ MapHalfScale.x, MapHalfScale.y } + float4{ PlayerPos.x, -PlayerPos.y };

	GameEnginePixelColor Color = { (char)255, 0, (char)255, (char)255 };

	int X = static_cast<int>(ColorPos.x);
	int Y = static_cast<int>(ColorPos.y);

	GameEnginePixelColor MapColor = ColMap->GetPixel(static_cast<int>(ColorPos.x), static_cast<int>(ColorPos.y));

	////중력적용유무
	if (Color != MapColor)
	{
		int count = 0;

		while (Color != MapColor)
		{
			ColorPos.y++;
			count++;
			MapColor = ColMap->GetPixel(static_cast<int>(ColorPos.x), static_cast<int>(ColorPos.y));
		}

		if (count < 3 && isKeyJump == false)
		{
				GetTransform()->AddLocalPosition({ 0 , static_cast<float>(-count)});
				isGround = true;

				if (isSwing == false)
				{
					MoveType = "Stand";
				}
		}
		else
		{
			GetTransform()->AddLocalPosition({ 0 , -Gravity * _DeltaTime });

			if (isSwing == false)
			{
				MoveType = "Jump";
			}

			isGround = false;
		}
	}
	else
	{	
		float Count = 0.0f;

		while (Color == MapColor)
		{
			ColorPos.y--;
			MapColor = ColMap->GetPixel(static_cast<int>(ColorPos.x), static_cast<int>(ColorPos.y));
			Count++;
		}

		if (isKeyJump == true)
		{
			return;
		}
		
		GetTransform()->AddLocalPosition({ 0, Count - 1.0f });
		
		Gravity = 200.0f;
		isGround = true;
		
		if (isSwing == false)
		{
			if (MoveType == "Jump" && isKeyJump == false)
			{
				MoveType = "Stand";
			}
		}
		
	}
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
	if (isKeyJump == true)
	{
		JumpUpdate(_DeltaTime);
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
		Jump(_DeltaTime);
		break;
	case static_cast<int>(State::Up):
		RopeAndLadder(_DeltaTime);
		break;
	case static_cast<int>(State::Down):
		RopeAndLadder(_DeltaTime);
		break;
	case static_cast<int>(State::ShiftSkill):	
		if (ShiftSkill != nullptr)
		{
			ShiftSkill(DynamicThis<Player>());
		}
		break;
	case static_cast<int>(State::InsSkill):
		if (InsertSkill != nullptr)
		{
			InsertSkill(DynamicThis<Player>());
		}
		break;
	case static_cast<int>(State::HomeSkill):
		if (HomeSkill != nullptr)
		{
			HomeSkill(DynamicThis<Player>());
		}
		break;
	case static_cast<int>(State::PgUpSkill):
		if (PageUpSkill != nullptr)
		{
			PageUpSkill(DynamicThis<Player>());
		}
		break;
	case static_cast<int>(State::CtrlSkill):
		if (CtrlSkill != nullptr)
		{
			CtrlSkill(DynamicThis<Player>());
		}
		break;
	case static_cast<int>(State::DelSkill):
		if (DelSkill != nullptr)
		{
			DelSkill(DynamicThis<Player>());
		}
		break;
	case static_cast<int>(State::EndSkill):
		if (EndSkill != nullptr)
		{
			EndSkill(DynamicThis<Player>());
		}
		break;
	case static_cast<int>(State::PgDnSkill):
		if (PageDownSkill != nullptr)
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

void Player::CameraUpdate(float _DeltaTime)
{
	float HalfWidth = ColMap->GetWidth() * 0.5f;
	float HalfHeight = ColMap->GetHeight() * 0.5f;

	float4 PlayerPos = GetTransform()->GetLocalPosition();
	float4 CameraPos = GetLevel()->GetMainCamera()->GetTransform()->GetLocalPosition();

	// 플레이어와 카메라의 위치를 보간하여 새로운 위치 계산
	float4 newPosition = newPosition.Lerp(CameraPos, PlayerPos, 1.5f * _DeltaTime);
	
	if (newPosition.x - 425 < -HalfWidth)
	{
		newPosition.x = -HalfWidth + 425;
	}
	else if (newPosition.x + 425 > HalfWidth )
	{
		newPosition.x = HalfWidth - 425;
	}

	if (newPosition.y - 490 < -HalfHeight)
	{
		newPosition.y = -HalfHeight +490;
	}
	else if (newPosition.y + 425 > HalfHeight)
	{
		newPosition.y = HalfHeight - 425;
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