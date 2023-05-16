#include "PrecompileHeader.h"
#include "MonsterBasicFunction.h"

#include <GameEngineBase/GameEngineRandom.h>

#include <GameEngineCore/GameEngineSpriteRenderer.h>

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
	if (MoveType == "Stand")
	{
		return;
	}

	if (LeftRightDir == "Left")
	{
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

			if (Angle > 0.5f)
			{
				GetTransform()->AddLocalPosition({ -1 * MoveSpeed * _DeltaTime, 0 });
			}
		}
		else
		{
			if (isAbleJump == false)
			{
				MoveDistance += MoveSpeed * _DeltaTime;
				return;
			}

			GetTransform()->AddLocalPosition({ -1 * MoveSpeed * _DeltaTime, 0 });
		}
	}

	else if (LeftRightDir == "Right")
	{
		float4 NextPos = GetTransform()->GetLocalPosition() + float4{ 1 * MoveSpeed * _DeltaTime, 0 };

		float4 MapHalfScale = { static_cast<float>(ColMap->GetWidth() / 2) ,  static_cast<float>(ColMap->GetHeight() / 2) };
		float4 ColorPos = MapHalfScale + float4{ NextPos.x + 20.0f, -NextPos.y };

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

			if (Angle > 0.5f)
			{
				GetTransform()->AddLocalPosition({ 1 * MoveSpeed * _DeltaTime, 0 });
			}
		}
		else
		{
			if (isAbleJump == false)
			{
				MoveDistance += MoveSpeed * _DeltaTime;
				return;
			}

			GetTransform()->AddLocalPosition({ 1 * MoveSpeed * _DeltaTime, 0 });
		}
	}

	MoveDistance += MoveSpeed * _DeltaTime;
}

void MonsterBasicFunction::DirUpdate()
{
	if(MoveType == "Move" && MoveDistance >= 50.0f && AniIndex == 0)
	{	
		MoveDistance = 0.0f;

		int MoveTypeNumber = GameEngineRandom::MainRandom.RandomInt(0, 7);
		
		if (MoveTypeNumber > 2)
		{
			MoveTypeNumber = 2;
		}

		switch (MoveTypeNumber)
		{
		case 0:
			MoveType = "Move";
			SetLeft();
			break;
		case 1:
			MoveType = "Move";
			SetRight();
			break;
		case 2:
			AniIndex = 0;
			MoveType = "Stand";
			break;
		}
	}

	else if (MoveType == "Stand")
	{
		StandTime += TimeCount;

		if (StandTime >= 1.0f)
		{
			StandTime = 0.0f;

			int MoveTypeNumber = GameEngineRandom::MainRandom.RandomInt(0, 2);

			switch (MoveTypeNumber)
			{
			case 0:
				MoveType = "Move";
				SetLeft();
				break;
			case 1:
				MoveType = "Move";
				SetRight();
				break;
			case 2:
				AniIndex = 0;
				MoveType = "Stand";
				break;
			}
		}
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