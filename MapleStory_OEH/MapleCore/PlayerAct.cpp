#include "PrecompileHeader.h"
#include "Player.h"
#include "PlayerValue.h"
#include "ContentEnums.h"
#include "Star.h"
#include "DamageRender.h"
#include "KeyBox.h"

#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineBase/GameEngineTimeEvent.h>

#include <ctime>

void Player::Jump(float _DeltaTime)
{
	if (isMovable == false || isRopeOrLadder == true)
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
	float4 MapHalfScale = { static_cast<float>(ColMap->GetWidth() / 2) ,  static_cast<float>(ColMap->GetHeight() / 2) };

	GameEnginePixelColor Magenta = { (char)255, (char)0, (char)255, (char)255 };
	GameEnginePixelColor White = { (char)255, (char)255, (char)255, (char)255 };

	float4 CurPos = GetTransform()->GetLocalPosition();
	float4 CurColorPos = MapHalfScale + float4{ CurPos.x, -CurPos.y };
	GameEnginePixelColor CurColor = ColMap->GetPixel(static_cast<int>(CurColorPos.x), static_cast<int>(CurColorPos.y));

	Gravity += GravityAccel * _DeltaTime;

	if (Gravity > 1000.0f)
	{
		Gravity = 1000.0f;
	}

	float4 NextPos = GetTransform()->GetLocalPosition() + float4{ JumpXMove * _DeltaTime , (JumpPower - Gravity) * _DeltaTime };
	float4 NextColorPos = MapHalfScale + float4{ NextPos.x, -NextPos.y };
	GameEnginePixelColor NextColor = ColMap->GetPixel(static_cast<int>(NextColorPos.x), static_cast<int>(NextColorPos.y));

	if (NextPos.y - CurPos.y < 0.0f && CurColor == White && NextColor == Magenta)
	{
		float Count = 0.5f;

		while (NextColor == Magenta)
		{
			NextPos = GetTransform()->GetLocalPosition() + float4{ Count * JumpXMove * _DeltaTime , Count * (JumpPower - Gravity) * _DeltaTime };
			NextColorPos = MapHalfScale + float4{ NextPos.x, -NextPos.y };
			NextColor = ColMap->GetPixel(static_cast<int>(NextColorPos.x), static_cast<int>(NextColorPos.y));

			Count *= 0.5f;
		}

		Gravity = 200.0f;

		if(isSwing == false)
		{
			MoveType = "Stand";
		}

		isKeyJump = false;
		isFlashJump = false;
		JumpPower = 600.0f;

		float4 RealNextPos = { NextColorPos.x - MapHalfScale.x, MapHalfScale.y - NextColorPos.y - 1.0f, -5.0f };
		GetTransform()->SetLocalPosition(RealNextPos);
		return;
	}

	float4 RealNextPos = { NextColorPos.x - MapHalfScale.x, MapHalfScale.y - NextColorPos.y, -5.0f };
	GetTransform()->SetLocalPosition(RealNextPos);
}

void Player::Move(float _DeltaTime)
{
	if (isSwing == true)
	{
		return;
	}

	if (isKeyJump == true || isFalling == true)
	{
		if (GameEngineInput::IsPress("LMove") == true)
		{
			SetLeft();
		}
		else if (GameEngineInput::IsPress("RMove") == true)
		{
			SetRight();
		}

		return;
	}

	float4 MapHalfScale = { static_cast<float>(ColMap->GetWidth() / 2) ,  static_cast<float>(ColMap->GetHeight() / 2) };

	GameEnginePixelColor Magenta = { (char)255, (char)0, (char)255, (char)255 };
	GameEnginePixelColor White = { (char)255, (char)255, (char)255, (char)255 };

	float4 CurPos = GetTransform()->GetLocalPosition();
	float4 CurColorPos = MapHalfScale + float4{ CurPos.x, -CurPos.y };
	GameEnginePixelColor CurColor = ColMap->GetPixel(static_cast<int>(CurColorPos.x), static_cast<int>(CurColorPos.y));
	
	float MoveDir = 0.0f;

	if (GameEngineInput::IsPress("LMove") == true)
	{
		SetLeft();
		MoveType = "Walk";
		MoveDir = -1.0f;
	}
	else if (GameEngineInput::IsPress("RMove") == true)
	{
		SetRight();
		MoveType = "Walk";
		MoveDir = 1.0f;
	}

	float4 NextPos = GetTransform()->GetLocalPosition() + float4{ MoveDir * MoveSpeed * _DeltaTime , 0};
	float4 NextColorPos = MapHalfScale + float4{ NextPos.x, -NextPos.y };
	GameEnginePixelColor NextColor = ColMap->GetPixel(static_cast<int>(NextColorPos.x), static_cast<int>(NextColorPos.y));

	//내리막길 or 절벽

	if (CurColor == Magenta && NextColor == White)
	{
		float4 CopyNextColorPos = NextColorPos;
		GameEnginePixelColor CopyNextColor = NextColor;

		int DownCount = 0;

		while (CopyNextColor == White)
		{
			CopyNextColorPos.y++;
			CopyNextColor = ColMap->GetPixel(static_cast<int>(CopyNextColorPos.x), static_cast<int>(CopyNextColorPos.y));
			DownCount++;

			if (DownCount >= 10)
			{
				//낙하함수
				GetTransform()->SetLocalPosition(NextPos);

				if (LeftRightDir == "Left")
				{
					FallingXMove = -MoveSpeed;
				}
				else if (LeftRightDir == "Right")
				{
					FallingXMove = MoveSpeed;

				}

				return;
			}
		}

		if (DownCount < 10)
		{
			GetTransform()->SetLocalPosition(NextPos);
			return;
		}
	}

	if (CurColor == Magenta && NextColor == Magenta)
	{
		float4 CopyNextColorPos = NextColorPos;
		GameEnginePixelColor CopyNextColor = NextColor;

		int UpCount = 0;

		while (CopyNextColor == Magenta)
		{
			CopyNextColorPos.y--;
			CopyNextColor = ColMap->GetPixel(static_cast<int>(CopyNextColorPos.x), static_cast<int>(CopyNextColorPos.y));
			UpCount++;

			if (UpCount >= 10)
			{
				return;
			}
		}

		if (UpCount < 10)
		{
			float4 NextPosDir = NextPos - CurPos;
			NextPosDir.Normalize();
			
			float4 NextUpPosDir = NextPos + float4{0, static_cast<float>(UpCount)} - CurPos;
			NextUpPosDir.Normalize();
				
			float DotProduct = NextPosDir.x * NextUpPosDir.x + NextPosDir.y * NextUpPosDir.y;
			
			if (DotProduct > 0.0f)
			{
				GetTransform()->SetLocalPosition(NextPos + float4{ 0, static_cast<float>(UpCount - 1)});
				return;
			}
		}
	}
}

void Player::Swing()
{
	if (isMovable == false || isSwing == true)
	{
		return;
	}

	if (MoveType == "Swing0" || MoveType == "Swing1" || MoveType == "Swing2")
	{
		return;
	}

	std::vector<std::shared_ptr<GameEngineCollision>> HitMonsterVector;
	std::shared_ptr<GameEngineCollision> HitObject = RangeCheck->Collision(static_cast<int>(CollisionOrder::Object), ColType::AABBBOX2D, ColType::AABBBOX2D);
	
	if (HitObject != nullptr)
	{
		if (HitObject->GetTransform()->GetWorldPosition().XYDistance(GetTransform()->GetWorldPosition()) < 80.0f)
		{
			int StabType = GameEngineRandom::MainRandom.RandomInt(0,1);
			HitObject->GetActor()->DynamicThis<KeyBox>()->Hit();

			MoveType = "Stab" + std::to_string(StabType);
			AniIndex = 0;
			AnimationCount = 0.0f;
			isSwing = true;

			return;
		}
	}

	RangeCheck->CollisionAll(static_cast<int>(CollisionOrder::Monster), HitMonsterVector, ColType::AABBBOX2D, ColType::AABBBOX2D);

	int SwingType = GameEngineRandom::MainRandom.RandomInt(0, 2);

	MoveType = "Swing" + std::to_string(SwingType);
	AnimationCount = 0.0f;
	AniIndex = 0;
	isSwing = true;
	
	std::shared_ptr<Star> NewStar1 = GetLevel()->CreateActor<Star>(11);
	NewStar1->SetStarName("Wednes");
	NewStar1->SetTimingTime(0.25);

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

	if (isFalling == true)
	{
		return;
	}

	JumpPower = 600.0f;
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
		AnimationCount = 0.0f;
		AniIndex = 0;
		MoveType = "Jump";
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
			MoveType = "Stand";
			FrontBackDir = "Front";
			TextureUpdate();
		}
	}

	//위로 가는 것
	if (Col != nullptr)
	{
		//최초 사다리 탈 때 설정
		if (isRopeOrLadder == false && GameEngineInput::IsDown("UpKey") == true)
		{	
			if (Col->GetTransform()->GetWorldPosition().y < GetTransform()->GetWorldPosition().y)
			{
				return;
			}

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

		//최초 사다리 탈 때 설정
		if (isRopeOrLadder == false && GameEngineInput::IsDown("DownKey") == true)
		{
			if (Col->GetTransform()->GetWorldPosition().y > GetTransform()->GetWorldPosition().y)
			{
				return;
			}

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


void Player::Hit(int _Damage)
{
	if (isKnockBack == true)
	{
		return;
	}

	if(isHit == false)
	{
		isHit = true;

		if (isDamagedDouble == true)
		{
			PlayerValue::Value.SubHp(2 * _Damage);

			std::shared_ptr<DamageRender> NewDR = GetLevel()->CreateActor<DamageRender>();
			NewDR->PushDamageToQueue(2 * _Damage);
			NewDR->GetTransform()->SetWorldPosition(GetTransform()->GetWorldPosition() + float4{ -16.0f, 55.0f });
		}
		else
		{
			PlayerValue::Value.SubHp(_Damage);

			std::shared_ptr<DamageRender> NewDR = GetLevel()->CreateActor<DamageRender>();
			NewDR->PushDamageToQueue(_Damage);
			NewDR->GetTransform()->SetWorldPosition(GetTransform()->GetWorldPosition() + float4{ -16.0f, 55.0f });
		}
	}

	if(isRopeOrLadder == false && isSwing == false)
	{
		isMovable = false;
		MoveType = "Alert";
		AniIndex = 0;
		AnimationCount = 0.0f;
	}

	std::function<void(GameEngineTimeEvent::TimeEvent&, GameEngineTimeEvent*)> HitEndFunc = [this](GameEngineTimeEvent::TimeEvent& _Event, GameEngineTimeEvent* _Manager)
	{
		isMovable = true;
		isHit = false;
		SetMulColorAllTexture(1.0f);
	};

	GetLevel()->TimeEvent.AddEvent(1.0f, HitEndFunc, false);
}


void Player::KnockBack(float4 _Dir, float _Distance, int _Damage, float _Speed, float _MinTime)
{
	if (isKnockBack == false)
	{
		isKnockBack = true;

		if (isKeyJump == true)
		{
			isKeyJump = false;
			isFlashJump = false;
			JumpPower = 600.0f;
			Gravity = 200.0f;
		}

		if (isRopeOrLadder == true)
		{
			FrontBackDir = "Front";
			isRopeOrLadder = false;
		}

		std::shared_ptr<DamageRender> NewDR = GetLevel()->CreateActor<DamageRender>();
		NewDR->GetTransform()->SetWorldPosition(GetTransform()->GetWorldPosition() + float4{ -16.0f, 55.0f });
		
		if (isDamagedDouble == true)
		{
			PlayerValue::Value.SubHp(2 * _Damage);
			NewDR->PushDamageToQueue(2 * _Damage);
		}
		else
		{
			PlayerValue::Value.SubHp(_Damage);
			NewDR->PushDamageToQueue(_Damage);
		}

		if (_Dir.x > 0)
		{
			SetLeft();
		}
		else
		{
			SetRight();
		}

		isMovable = false;
		MoveType = "Alert";
		AniIndex = 0;
		AnimationCount = 0.0f;

		if(MyKnockBackInfo == nullptr)
		{
			MyKnockBackInfo = std::make_shared<KnockBackInfo>();
			MyKnockBackInfo->Dir = _Dir;
			MyKnockBackInfo->Distance = _Distance;
			MyKnockBackInfo->Speed = _Speed;
			MyKnockBackInfo->MinTime = _MinTime;
		}
		else
		{
			MsgAssert("KnockBackInfo 널포인터 검사 필요");
			return;
		}
	}
}

void Player::KnockBackUpdate(float _DeltaTime)
{
	if (MyKnockBackInfo == nullptr)
	{
		MsgAssert("넉백인포가 Nullptr인데 넉백되었습니다.");
	}

	if (isFalling == false && MyKnockBackInfo->Time > 0.0f && MyKnockBackInfo->Dir.y > 0.0f)
	{
		MyKnockBackInfo->Dir = { 0, 0 };
	}

	MyKnockBackInfo->Time += TimeCount;

	float4 MapHalfScale = { static_cast<float>(ColMap->GetWidth() / 2) ,  static_cast<float>(ColMap->GetHeight() / 2) };

	GameEnginePixelColor Magenta = { (char)255, (char)0, (char)255, (char)255 };
	GameEnginePixelColor White = { (char)255, (char)255, (char)255, (char)255 };

	float4 CurPos = GetTransform()->GetLocalPosition();
	float4 CurColorPos = MapHalfScale + float4{ CurPos.x, -CurPos.y };
	GameEnginePixelColor CurColor = ColMap->GetPixel(static_cast<int>(CurColorPos.x), static_cast<int>(CurColorPos.y));
	
	float4 NextPos = CurPos + MyKnockBackInfo->Dir * MyKnockBackInfo->Speed *_DeltaTime;
	float4 NextColorPos = MapHalfScale + float4{ NextPos.x, -NextPos.y };
	GameEnginePixelColor NextColor = ColMap->GetPixel(static_cast<int>(NextColorPos.x), static_cast<int>(NextColorPos.y));

	float MoveDistance = sqrt((NextPos.x - CurPos.x) * (NextPos.x - CurPos.x) + (NextPos.y - CurPos.y) * (NextPos.y - CurPos.y));

	bool isUp = false;

	if (NextPos.y > CurPos.y)
	{
		isUp = true;
	}

	if (CurColor == White && NextColor == Magenta)
	{
		float4 NextUpPos = NextPos + float4{ 0, 15.0f };
		float4 NextUpColorPos = MapHalfScale + float4{ NextUpPos.x, -NextUpPos.y };
		GameEnginePixelColor NextUpColor = ColMap->GetPixel(static_cast<int>(NextUpColorPos.x), static_cast<int>(NextUpColorPos.y));


		if (isUp == false && NextUpColor != Magenta)
		{
			MyKnockBackInfo->Dir.y = 0.0f;
			MyKnockBackInfo->Dir.Normalize();

			float4 CopyNextColorPos = NextColorPos;
			GameEnginePixelColor CopyNextColor = NextColor;

			while (CopyNextColor == Magenta)
			{
				CopyNextColorPos.y--;
				CopyNextColor = ColMap->GetPixel(static_cast<int>(CopyNextColorPos.x), static_cast<int>(CopyNextColorPos.y));
			}

			float4 RealNextColor = float4{ CopyNextColorPos.x - MapHalfScale.x, MapHalfScale.y - CopyNextColorPos.y } + float4{ 0, -1};
			GetTransform()->SetLocalPosition(RealNextColor + float4{0, 0, -5.0f});
		}
		else
		{
			float4 NextUpPos = NextPos + float4{ 0, 20.0f };
			float4 NextUpColorPos = MapHalfScale + float4{ NextUpPos.x, -NextUpPos.y };
			GameEnginePixelColor NextUpColor = ColMap->GetPixel(static_cast<int>(NextUpColorPos.x), static_cast<int>(NextUpColorPos.y));

			if (NextUpColor == Magenta)
			{
			}
			else
			{
				GetTransform()->SetLocalPosition(NextPos + float4{ 0, 0, -5.0f });
			}
		}
	}
	else if(CurColor == Magenta && NextColor == Magenta)
	{
		MyKnockBackInfo->Dir.y = 0.0f;
		MyKnockBackInfo->Dir.Normalize();

		NextPos = CurPos + MyKnockBackInfo->Dir * MyKnockBackInfo->Speed *_DeltaTime;
		//내적

		int UpCount = 0;

		float4 CopyNextColorPos = NextColorPos;
		GameEnginePixelColor CopyNextColor = NextColor;

		while (CopyNextColor == Magenta)
		{
			UpCount++;
			CopyNextColorPos.y--;
			CopyNextColor = ColMap->GetPixel(static_cast<int>(CopyNextColorPos.x), static_cast<int>(CopyNextColorPos.y));
			
			if (UpCount >= 10)
			{
				break;
			}
		}

		if(UpCount < 10)
		{
			float4 NextPosDir = NextPos - CurPos;
			NextPosDir.Normalize();

			float4 NextUpPosDir = NextPos + float4{ 0, static_cast<float>(UpCount) } - CurPos;
			NextUpPosDir.Normalize();

			float DotProduct = NextPosDir.x * NextUpPosDir.x + NextPosDir.y * NextUpPosDir.y;

			if (DotProduct > 0.2f)
			{
				GetTransform()->SetLocalPosition(NextPos + float4{ 0, static_cast<float>(UpCount - 1)});
			}
		}
	}
	else
	{
		GetTransform()->SetLocalPosition(NextPos);
	}

	MyKnockBackInfo->Distance -= MoveDistance;

	if ((MyKnockBackInfo->Distance <= 0 && isFalling == false) || MyKnockBackInfo->Time >= MyKnockBackInfo->MinTime)
	{
		isMovable = true;
		isKnockBack = false;
		MoveType = "Stand";

		
		if(CurColor == Magenta)
		{
			isFalling = false;
		}

		SetMulColorAllTexture(1.0f);

		MyKnockBackInfo = nullptr;
	}

}