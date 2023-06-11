#include "PrecompileHeader.h"
#include "Player.h"
#include "PlayerValue.h"
#include "ContentEnums.h"
#include "Star.h"

#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineBase/GameEngineTimeEvent.h>

#include <ctime>

void Player::Jump(float _DeltaTime)
{
	if (isMovable == false)
	{
		return;
	}

	if (MoveType == "Jump" || isSwing == true)
	{
		return;
	}

	if (MoveType == "Walk" && isFlashJump == false)
	{
		if (LeftRightDir == "Right")
		{
			JumpXMove = MoveSpeed * 0.6f;
		}
		else if (LeftRightDir == "Left")
		{
			JumpXMove = -MoveSpeed * 0.6f;
		}
	}
	else
	{
		JumpXMove = 0;
	}

	MoveType = "Jump";
	isKeyJump = true;
}

void Player::JumpUpdate(float _DeltaTime)
{
	if(isSwing == false)
	{
		MoveType = "Jump";
	}

	float PrevYPos = GetTransform()->GetLocalPosition().y;

	if(GameEngineInput::IsPress("LMove") == false && GameEngineInput::IsPress("RMove") == false)
	{
		float4 NextPos = GetTransform()->GetLocalPosition() + float4{ JumpXMove * _DeltaTime , JumpPower * _DeltaTime };

		float4 MapHalfScale = { static_cast<float>(ColMap->GetWidth() / 2) ,  static_cast<float>(ColMap->GetHeight() / 2) };
		float4 ColorPos = MapHalfScale + float4{ NextPos.x, -NextPos.y };

		GameEnginePixelColor Color = { (char)255, 0, (char)255, (char)255 };
		GameEnginePixelColor MapColor = ColMap->GetPixel(static_cast<int>(ColorPos.x), static_cast<int>(ColorPos.y));

		if (Color == MapColor)
		{
			GetTransform()->AddLocalPosition({ 0 , JumpPower * _DeltaTime });
		}
		else
		{
			float4 Pos = GetTransform()->GetLocalPosition();
			GetTransform()->AddLocalPosition({ JumpXMove * _DeltaTime , JumpPower * _DeltaTime });
		}

		NextPos = GetTransform()->GetLocalPosition();
		MapHalfScale = { static_cast<float>(ColMap->GetWidth() / 2) ,  static_cast<float>(ColMap->GetHeight() / 2) };
		ColorPos = MapHalfScale + float4{ NextPos.x, -NextPos.y };

		Color = { (char)255, 0, (char)255, (char)255 };
		MapColor = ColMap->GetPixel(static_cast<int>(ColorPos.x), static_cast<int>(ColorPos.y));
		
		if (Color == MapColor)
		{
			if(isJumpUp == false)
			{
				isKeyJump = false;
				JumpPower = 585.0f;
				isFlashJump = false;

				if (isSwing == false)
				{
					MoveType = "Stand";
				}
			}
		}
	}
	else
	{
		if (isSwing == true)
		{
			if (JumpXMove == 0)
			{
				GetTransform()->AddLocalPosition({ 0 , JumpPower * _DeltaTime });
			}
			else
			{
				GetTransform()->AddLocalPosition({ (JumpXMove / abs(JumpXMove)) * MoveSpeed * _DeltaTime , JumpPower * _DeltaTime });
			}
		}
		else if (isFlashJump == true)
		{
			GetTransform()->AddLocalPosition({JumpXMove * _DeltaTime , JumpPower * _DeltaTime });
		}
		else
		{
			GetTransform()->AddLocalPosition({ 0 , JumpPower * _DeltaTime });
		}

		float4 PlayerPos = GetTransform()->GetLocalPosition();

		float4 MapHalfScale = { static_cast<float>(ColMap->GetWidth() / 2) ,  static_cast<float>(ColMap->GetHeight() / 2) };
		float4 ColorPos = MapHalfScale + float4{ PlayerPos.x, -PlayerPos.y };

		GameEnginePixelColor Color = { (char)255, 0, (char)255, (char)255 };
		GameEnginePixelColor MapColor = ColMap->GetPixel(static_cast<int>(ColorPos.x), static_cast<int>(ColorPos.y));

		if (Color == MapColor && isJumpUp == false)
		{
			isKeyJump = false;
			JumpPower = 585.0f;
			isFlashJump = false;

			if (isSwing == false)
			{
				MoveType = "Stand";
			}
		}
	}

	float4 Pos = GetTransform()->GetLocalPosition() - PrevPos;

	if (Pos.y > 0)
	{
		isJumpUp = true;
	}
	else
	{
		isJumpUp = false;
	}
}

void Player::Move(float _DeltaTime)
{
	if (isSwing == true)
	{
		return;
	}

	if (isMovable == false)
	{
		return;
	}

	if (GameEngineInput::IsPress("LMove") == true)
	{
		SetLeft();

		if (MoveType != "Jump" && isSwing == false)
		{
			MoveType = "Walk";
		}

		float4 NextPlayerPos = GetTransform()->GetLocalPosition() + float4{ -1 * MoveSpeed * _DeltaTime, 0 };

		float4 MapHalfScale = { static_cast<float>(ColMap->GetWidth() / 2) ,  static_cast<float>(ColMap->GetHeight() / 2) };
		float4 ColorPos = MapHalfScale + float4{ NextPlayerPos.x, -NextPlayerPos.y };

		GameEnginePixelColor Color = { (char)255, 0, (char)255, (char)255 };
		GameEnginePixelColor MapColor = ColMap->GetPixel(static_cast<int>(ColorPos.x), static_cast<int>(ColorPos.y));

		if (Color == MapColor)
		{
			float Count = 0;

			while (Color == MapColor)
			{
				ColorPos.y--;
				MapColor = ColMap->GetPixel(static_cast<int>(ColorPos.x), static_cast<int>(ColorPos.y));
				Count++;
			}

			float4 Vector1 = { -1, 0 };
			Vector1.Normalize();
			float4 Vector2 = { -1, Count };
			Vector2.Normalize();

			float Angle = (Vector1.x) * (Vector2.x) + (Vector1.y) * (Vector2.y);

			if (Angle > 0.2f)
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

		if (MoveType != "Jump" && isSwing == false)
		{
			MoveType = "Walk";
		}

		float4 NextPlayerPos = GetTransform()->GetLocalPosition() + float4{ 1 * MoveSpeed * _DeltaTime, 0 };

		float4 MapHalfScale = { static_cast<float>(ColMap->GetWidth() / 2) ,  static_cast<float>(ColMap->GetHeight() / 2) };
		float4 ColorPos = MapHalfScale + float4{ NextPlayerPos.x, -NextPlayerPos.y };

		GameEnginePixelColor Color = { (char)255, 0, (char)255, (char)255 };
		GameEnginePixelColor MapColor = ColMap->GetPixel(static_cast<int>(ColorPos.x), static_cast<int>(ColorPos.y));

		if (Color == MapColor)
		{
			float Count = 0;

			while (Color == MapColor)
			{
				ColorPos.y--;
				MapColor = ColMap->GetPixel(static_cast<int>(ColorPos.x), static_cast<int>(ColorPos.y));
				Count++;
			}

			float4 Vector1 = { 1, 0 };
			Vector1.Normalize();
			float4 Vector2 = { 1, Count };
			Vector2.Normalize();

			float Angle = (Vector1.x) * (Vector2.x) + (Vector1.y) * (Vector2.y);

			if (Angle > 0.2f)
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

void Player::Swing()
{
	if (isMovable == false)
	{
		return;
	}

	if (MoveType == "Swing0" || MoveType == "Swing1" || MoveType == "Swing2")
	{
		return;
	}

	int SwingType = GameEngineRandom::MainRandom.RandomInt(0, 2);

	MoveType = "Swing" + std::to_string(SwingType);
	AniIndex = 0;
	isSwing = true;

	std::shared_ptr<Star> NewStar1 = GetLevel()->CreateActor<Star>(11);
	NewStar1->SetStarName("Wednes");
	NewStar1->SetTimingTime(0.25);
	
	//std::shared_ptr<GameEngineCollision> HitMonster = RangeCheck->Collision(static_cast<int>(CollisionOrder::Monster), ColType::AABBBOX2D, ColType::AABBBOX2D);
	std::vector<std::shared_ptr<GameEngineCollision>> HitMonsterVector;
	RangeCheck->CollisionAll(static_cast<int>(CollisionOrder::Monster), HitMonsterVector, ColType::AABBBOX2D, ColType::AABBBOX2D);
	float4 PlayerPos = GetTransform()->GetWorldPosition();

	std::function<void(Star&, float)> UpdateFunction = &Star::Move;
	NewStar1->SetUpdateFuction(UpdateFunction);
	NewStar1->SetTargetMonster(HitMonsterVector, PlayerPos);
	NewStar1->SetType("Swing");

	if (isOnShadow == true)
	{
		NewStar1->Set_IsRealAttack(false);

		std::shared_ptr<Star> NewStar2 = GetLevel()->CreateActor<Star>(11);
		NewStar2->SetStarName("Wednes");
		NewStar2->SetTimingTime(0.40f);

		std::shared_ptr<GameEngineCollision> HitMonster = RangeCheck->Collision(static_cast<int>(CollisionOrder::Monster), ColType::AABBBOX2D, ColType::AABBBOX2D);

		std::function<void(Star&, float)> UpdateFunction = &Star::Move;
		NewStar2->SetUpdateFuction(UpdateFunction);
		NewStar2->SetTargetMonster(HitMonsterVector, PlayerPos);
		NewStar2->SetType("Swing");
	}
}

void Player::Idle()
{
	if (isSwing == true)
	{
		return;
	}

	if (isGround = false)
	{
		return;
	}

	if (isKeyJump == true)
	{
		return;
	}

	if (isHit == true)
	{
		return;
	}

	MoveType = "Stand";
	FrontBackDir = "Front";
}

void Player::RopeAndLadder(float _DeltaTime)
{
	if (isMovable == false)
	{
		return;
	}

	if (GameEngineInput::IsDown("Jump") == true)
	{
		isKeyJump = true;
		isRopeOrLadder = false;
		FrontBackDir = "Front";
		Gravity = 200.0f;

		if (GameEngineInput::IsDown("RMove") == true || GameEngineInput::IsPress("RMove") == true)
		{
			JumpXMove = MoveSpeed;
			SetRight();
		}
		else if (GameEngineInput::IsDown("LMove") == true || GameEngineInput::IsPress("LMove") == true)
		{
			JumpXMove = -MoveSpeed;
			SetLeft();
		}
		else
		{
			JumpXMove = 0;
		}

		JumpPower = 350.0f;

		TextureUpdate();
		return;
	}

	if (GameEngineInput::IsDown("UpKey") == true || GameEngineInput::IsPress("UpKey") == true)
	{
		RopeAndLadderUp(_DeltaTime);
	}
	else if (GameEngineInput::IsDown("DownKey") == true || GameEngineInput::IsPress("DownKey") == true)
	{
		RopeAndLadderDown(_DeltaTime);
	}
}

void Player::RopeAndLadderUp(float _DeltaTime)
{
	std::shared_ptr<GameEngineCollision> Col;
	Col = BodyCollision->Collision(static_cast<int>(CollisionOrder::RopeAndLadder), ColType::AABBBOX2D, ColType::AABBBOX2D);

	if (isRopeOrLadder == true)
	{
		if (Col == nullptr)
		{
			isRopeOrLadder = false;
			FrontBackDir = "Front";
			TextureUpdate();
		}
	}

	//위로 가는 것
	if (Col != nullptr)
	{
		//사다리가 아래에 있으면 위 방향키를 입력해도 상호작용x
		if (isGround == true && Col->GetTransform()->GetWorldPosition().y < GetTransform()->GetWorldPosition().y)
		{
			return;
		}

		//최초 사다리 탈 때 설정
		if (isRopeOrLadder == false && GameEngineInput::IsDown("UpKey") == true)
		{
			AniIndex = 0;
			AnimationCount = 0.0f;

			isRopeOrLadder = true;
			isGround = false;
			isKeyJump = false;

			MoveType = "Ladder";
			FrontBackDir = "Back";

			GetTransform()->SetLocalPosition({ Col->GetTransform()->GetWorldPosition().x, GetTransform()->GetLocalPosition().y, -5.0f });
		}
		else if (isRopeOrLadder == true && GameEngineInput::IsPress("UpKey") == true)
		{
			GetTransform()->AddLocalPosition({ 0, MoveSpeed * 0.7f * _DeltaTime });
		}
	}
}

void Player::RopeAndLadderDown(float _DeltaTime)
{
	std::shared_ptr<GameEngineCollision> Col;
	Col = BodyCollision->Collision(static_cast<int>(CollisionOrder::RopeAndLadder), ColType::AABBBOX2D, ColType::AABBBOX2D);

	if (isRopeOrLadder == true)
	{
		if (Col == nullptr)
		{
			isRopeOrLadder = false;
			FrontBackDir = "Front";
			MoveType = "Stand";
			TextureUpdate();
		}
		else if (isSameColor() == true && Col->GetTransform()->GetWorldPosition().y > GetTransform()->GetWorldPosition().y)
		{
			isRopeOrLadder = false;
			FrontBackDir = "Front";
			MoveType = "Stand";
			TextureUpdate();
		}
	}

	//위로 가는 것
	if (Col != nullptr)
	{
		//사다리가 위에 있으면 아래 방향키를 입력해도 상호작용x
		if (isGround == true && Col->GetTransform()->GetWorldPosition().y > GetTransform()->GetWorldPosition().y)
		{
			return;
		}

		//최초 사다리 탈 때 설정
		if (isRopeOrLadder == false && GameEngineInput::IsDown("DownKey") == true)
		{
			AniIndex = 0;
			AnimationCount = 0.0f;

			isRopeOrLadder = true;
			isGround = false;
			isKeyJump = false;

			MoveType = "Ladder";
			FrontBackDir = "Back";

			GetTransform()->SetLocalPosition({ Col->GetTransform()->GetWorldPosition().x, GetTransform()->GetLocalPosition().y, - 5.0f });
		}
		else if (isRopeOrLadder == true && GameEngineInput::IsPress("DownKey") == true)
		{
			GetTransform()->AddLocalPosition({ 0, -MoveSpeed * 0.7f * _DeltaTime });
		}
	}
}


void Player::Hit()
{
	isMovable = false;
	isHit = true;
	MoveType = "Alert";
	AniIndex = 0;
	AnimationCount = 0.0f;

	std::function<void(GameEngineTimeEvent::TimeEvent&, GameEngineTimeEvent*)> HitEndFunc = [=](GameEngineTimeEvent::TimeEvent& _Event, GameEngineTimeEvent* _Manager)
	{
		Player::GetCurPlayer()->SetMovable(true);
		Player::GetCurPlayer()->SetisHit(false);
		Player::GetCurPlayer()->SetMulColorAllTexture(1.0f);
	};

	GetLevel()->TimeEvent.AddEvent(1.0f, HitEndFunc, false);
}