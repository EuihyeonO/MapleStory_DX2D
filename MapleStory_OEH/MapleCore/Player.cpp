#include "PrecompileHeader.h"
#include "Player.h"
#include "PlayerValue.h"
#include "ContentEnums.h"
#include "Star.h"
#include "BuffList.h"

#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEnginePlatform/GameEngineInput.h>

#include <GameEngineCore/GameEngineCoreWindow.h>

#include <ctime>

Player* Player::CurPlayer = nullptr;

Player::Player()
{
	PlayerValue::Value.AddToPlayerToPlayerList(this);
	CurPlayer = this;
}

Player::~Player()
{

}

void Player::Start()
{
	TimeCounting();

	GetTransform()->SetLocalPosition({ 0, 0, -static_cast<float>(RenderOrder::Player) });
	GetTransform()->SetLocalScale({ 1, 1, 1 });

	BodyCollision = CreateComponent<GameEngineCollision>();
	BodyCollision->GetTransform()->SetLocalScale({ 30, 50 });
	BodyCollision->SetOrder(static_cast<int>(CollisionOrder::Player));

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

	CameraUpdate();

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

	float4 PlayerPos = GetTransform()->GetLocalPosition();

	float4 MapHalfScale = { static_cast<float>(ColMap->GetWidth() / 2) ,  static_cast<float>(ColMap->GetHeight() / 2) };
	float4 ColorPos = float4{ MapHalfScale.x, MapHalfScale.y } + float4{ PlayerPos.x, -PlayerPos.y };

	GameEnginePixelColor Color = { (char)255, 0, (char)255, (char)255 };

	int X = static_cast<int>(ColorPos.x);
	int Y = static_cast<int>(ColorPos.y);

	GameEnginePixelColor MapColor = ColMap->GetPixel(static_cast<int>(ColorPos.x), static_cast<int>(ColorPos.y));

	//중력적용유무
	if (Color != MapColor)
	{
		GetTransform()->AddLocalPosition({ 0 , -Gravity * _DeltaTime, 0 });
		

		//이걸 안달아주면 공중에서 JUMP애니메이션으로 안바뀌거나, 공중이 아닌데 JUMP로 바뀌는 등 어색함이 발생
		//했었는데, 이제 안생기는 것 같아서 완전히 확인 될 때 까지 임시로 주석걸어놓음
		 
		//int count = 0;
		//while (Color != MapColor)
		//{
		//	ColorPos.y++;
		//	count++;
		//	MapColor = ColMap->GetPixel(static_cast<int>(ColorPos.x), static_cast<int>(ColorPos.y));
		//}

		//if(isSwing == false && count > 3)
		//{
		// MoveType = "Jump";
		//}
		if(isSwing == false)
		{
			MoveType = "Jump";
		}

		isGround = false;
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

		GetTransform()->AddLocalPosition({ 0, Count - 1 });

		Gravity = 200.0f;
		isGround = true;

		if (isSwing == false)
		{
			if(MoveType == "Jump")
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
		GameEngineInput::CreateKey("Swing", VK_LCONTROL);
		GameEngineInput::CreateKey("Jump", 'C');
		GameEngineInput::CreateKey("Qskill", 'Q');
		GameEngineInput::CreateKey("Wskill", 'W');
		GameEngineInput::CreateKey("Eskill", 'E');
		GameEngineInput::CreateKey("UpKey", VK_UP);
		GameEngineInput::CreateKey("DownKey", VK_DOWN);
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
	case static_cast<int>(State::Swing):
		Swing();
		break;
	case static_cast<int>(State::Up):
		RopeAndLadder(_DeltaTime);
		break;
	case static_cast<int>(State::Down):
		RopeAndLadder(_DeltaTime);
		break;
	case static_cast<int>(State::Qskill):	
		ShadowPartner();
		break;
	case static_cast<int>(State::Wskill):
		//if (WSkill != nullptr)
		//{
		//	WSkill(*this);
		//}
		Avenger();
		break;
	case static_cast<int>(State::Eskill):
		//if (ESkill != nullptr)
		//{
		//	ESkill(*this);
		//}
		JavelinBooster();
		break;
	case -1:
		Idle();
		break;
	}
}

int Player::GetStateByKeyInput() const
{
	if (GameEngineInput::IsDown("Jump") == true)
	{
		return static_cast<int>(State::Jump);
	}
	else if (GameEngineInput::IsDown("QSkill") == true)
	{
		return static_cast<int>(State::Qskill);
	}
	else if (GameEngineInput::IsDown("UpKey") == true || GameEngineInput::IsPress("UpKey") == true)
	{
		return static_cast<int>(State::Up);
	}
	else if (GameEngineInput::IsDown("DownKey") == true || GameEngineInput::IsPress("DownKey") == true)
	{
		return static_cast<int>(State::Down);
	}
	else if (GameEngineInput::IsDown("WSkill") == true)
	{
		return static_cast<int>(State::Wskill);
	}
	else if (GameEngineInput::IsDown("ESkill") == true)
	{
		return static_cast<int>(State::Eskill);
	}
	else if (GameEngineInput::IsDown("Swing") == true)
	{
		return static_cast<int>(State::Swing);
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

void Player::CameraUpdate()
{
	float HalfWidth = ColMap->GetWidth() * 0.5f;
	float HalfHeight = ColMap->GetHeight() * 0.5f;

	float4 PlayerPos = GetTransform()->GetLocalPosition();
	float4 CameraPos = PlayerPos;

	if (CameraPos.x - 450 < -HalfWidth)
	{
		CameraPos.x = -HalfWidth + 450;
	}
	else if (CameraPos.x + 400 > HalfWidth - 50)
	{
		CameraPos.x = HalfWidth - 450;
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

bool Player::isSameColor()
{
	float4 PlayerPos = GetTransform()->GetLocalPosition();

	float4 MapHalfScale = { static_cast<float>(ColMap->GetWidth() / 2) ,  static_cast<float>(ColMap->GetHeight() / 2) };
	float4 ColorPos = MapHalfScale + float4{ PlayerPos.x, -PlayerPos.y };

	GameEnginePixelColor Color = { (char)255, 0, (char)255, (char)255 };
	GameEnginePixelColor MapColor = ColMap->GetPixel(static_cast<int>(ColorPos.x), static_cast<int>(ColorPos.y));

	return Color == MapColor;
}