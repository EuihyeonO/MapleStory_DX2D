#include "PrecompileHeader.h"
#include "MonsterBasicFunction.h"

#include <GameEngineBase/GameEngineRandom.h>

#include <ctime>

MonsterBasicFunction::MonsterBasicFunction()
{
}

MonsterBasicFunction::~MonsterBasicFunction()
{
}

void MonsterBasicFunction::GravityUpdate(float _DeltaTime)
{
	Gravity += GravityAccel * _DeltaTime;

	float4 PlayerPos = GetTransform()->GetLocalPosition();

	float4 MapHalfScale = { static_cast<float>(ColMap->GetWidth() / 2) ,  static_cast<float>(ColMap->GetHeight() / 2) };
	float4 ColorPos = float4{ MapHalfScale.x, MapHalfScale.y } + float4{ PlayerPos.x, -PlayerPos.y };

	GameEnginePixelColor Color = { (char)255, 0, (char)255, (char)255 };

	int X = static_cast<int>(ColorPos.x);
	int Y = static_cast<int>(ColorPos.y);

	GameEnginePixelColor MapColor = ColMap->GetPixel(static_cast<int>(ColorPos.x), static_cast<int>(ColorPos.y));

	if (Color != MapColor)
	{
		GetTransform()->AddLocalPosition({ 0 , -Gravity * _DeltaTime, 0 });

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

	}
}

void MonsterBasicFunction::SetColMap(const std::string_view& _MapName)
{
	ColMap = GameEngineTexture::Find(_MapName);
}

void MonsterBasicFunction::Move(float _DeltaTime)
{
	if (MoveDistance >= 150.0f)
	{
		DirUpdate();
		MoveDistance = 0.0f;
		return;
	}

	float Dir = 1.0f;
	if (LeftRightDir == "Left")
	{
		Dir = -1.0f;
	}

	float4 MapHalfScale = { static_cast<float>(ColMap->GetWidth() / 2) ,  static_cast<float>(ColMap->GetHeight() / 2) };

	GameEnginePixelColor Magenta = { (char)255, (char)0, (char)255, (char)255 };
	GameEnginePixelColor White = { (char)255, (char)255, (char)255, (char)255 };

	float4 CurPos = GetTransform()->GetLocalPosition();
	float4 CurColorPos = MapHalfScale + float4{ CurPos.x, -CurPos.y };
	GameEnginePixelColor CurColor = ColMap->GetPixel(static_cast<int>(CurColorPos.x), static_cast<int>(CurColorPos.y));

	float4 NextPos = GetTransform()->GetLocalPosition() + float4{ Dir * MoveSpeed * _DeltaTime , 0 };
	float4 NextColorPos = MapHalfScale + float4{ NextPos.x, -NextPos.y };
	GameEnginePixelColor NextColor = ColMap->GetPixel(static_cast<int>(NextColorPos.x), static_cast<int>(NextColorPos.y));

	//내리막길 or 절벽
	if (CurColor == White)
	{
		GravityUpdate(_DeltaTime);
		return;
	}

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
				return;
			}
		}

		if (DownCount < 10)
		{
			GetTransform()->SetLocalPosition(NextPos +float4{0, static_cast<float>(-DownCount)});
			MoveDistance += MoveSpeed * _DeltaTime;
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

			if (UpCount >= 20)
			{
				MoveDistance += MoveSpeed * _DeltaTime;
				return;
			}
		}

		if (UpCount < 20)
		{
			float4 NextPosDir = NextPos - CurPos;
			NextPosDir.Normalize();

			float4 NextUpPosDir = NextPos + float4{ 0, static_cast<float>(UpCount) } - CurPos;
			NextUpPosDir.Normalize();

			float DotProduct = NextPosDir.x * NextUpPosDir.x + NextPosDir.y * NextUpPosDir.y;

			if (DotProduct > 0.0f)
			{
				GetTransform()->SetLocalPosition(NextPos + float4{ 0, static_cast<float>(UpCount - 1) });
				MoveDistance += MoveSpeed * _DeltaTime;
				return;
			}
		}
	}
}

void MonsterBasicFunction::DirUpdate()
{
	if(MoveType == "MOVE")
	{	
		MoveDistance = 0.0f;
			
		int MoveTypeNumber = GameEngineRandom::MainRandom.RandomInt(0, 10);
		
		if (MoveTypeNumber != 2)
		{
			MoveTypeNumber = MoveTypeNumber % 2;
		}

		switch (MoveTypeNumber)
		{
		case 0:
			if(LeftRightDir != "Left")
			{
				BasicRender->ChangeAnimation("MOVE");
			}
			MoveType = "MOVE";
			SetLeft();
			break;
		case 1:
			if (LeftRightDir != "Right")
			{
				BasicRender->ChangeAnimation("MOVE");
			}
			MoveType = "MOVE";
			SetRight();
			break;
		case 2:
			BasicRender->ChangeAnimation("STAND");
			AniIndex = 0;
			MoveType = "STAND";
			break;
		}
	}

	else if (MoveType == "STAND" || MoveType == "HIT")
	{		
		int MoveTypeNumber = GameEngineRandom::MainRandom.RandomInt(0, 2);

		switch (MoveTypeNumber)
		{
		case 0:
			BasicRender->ChangeAnimation("MOVE");
			MoveType = "MOVE";
			SetLeft();
			break;
		case 1:
			BasicRender->ChangeAnimation("MOVE");
			MoveType = "MOVE";
			SetRight();
			break;
		case 2:
			AniIndex = 0;
			MoveType = "STAND";
			break;
		}
	}
}

void MonsterBasicFunction::StatusUpdate(float _DeltaTtime)
{
	if (isDeathStart == true)
	{
		MonsterDeath(_DeltaTtime);
		return;
	}

	if (MoveType == "MOVE")
	{
		Move(_DeltaTtime);
	}
	else if (MoveType == "FLY")
	{
		Fly(_DeltaTtime);
	}
	else if (MoveType == "STAND")
	{
		Stand();
	}
	else if (MoveType == "SPAWN")
	{
		Spawn(_DeltaTtime);
	}
	else if (MoveType == "ATTACK")
	{
		Attack();
	}
}

void MonsterBasicFunction::Stand()
{
	StandTime += TimeCount;

	if (StandTime >= 1.5f)
	{
		DirUpdate();
		StandTime = 0.0f;
	}
}

void MonsterBasicFunction::SetLeft()
{
	AniIndex = 0;
	LeftRightDir = "Left";
	GetTransform()->SetLocalScale({ 1, 1, 1 });
}

void MonsterBasicFunction::SetRight()
{
	AniIndex = 0;
	LeftRightDir = "Right";
	GetTransform()->SetLocalScale({ -1, 1, 1 });
}

void MonsterBasicFunction::TimeCounting()
{
	CurTime = static_cast<float>(clock());
	TimeCount = (CurTime - PrevTime) / 1000.0f;
	PrevTime = CurTime;
}