#include "PrecompileHeader.h"
#include "Player.h"
#include "PlayerValue.h"
#include "ContentEnums.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <ctime>

void Player::Jump(float _DeltaTime)
{

	//if (MoveType != "Jump" && (GameEngineInput::IsDown("LMove") == true || GameEngineInput::IsPress("LMove") == true))
	//{
	//	JumpMove = -MoveSpeed * 0.5f;
	//}
	//else if (MoveType != "Jump" && (GameEngineInput::IsDown("RMove") == true || GameEngineInput::IsPress("RMove") == true))
	//{
	//	JumpMove = MoveSpeed * 0.5f;
	//}

	MoveType = "Jump";

	isKeyJump = true;
}

void Player::JumpUpdate(float _DeltaTime)
{
	MoveType = "Jump";

	GetTransform()->AddLocalPosition({ 0 , JumpPower * _DeltaTime });

	float4 PlayerPos = GetTransform()->GetLocalPosition();

	float4 MapHalfScale = { static_cast<float>(ColMap->GetWidth() / 2) ,  static_cast<float>(ColMap->GetHeight() / 2) };
	float4 ColorPos = MapHalfScale + float4{ PlayerPos.x, -PlayerPos.y };

	GameEnginePixelColor Color = { (char)255, 0, (char)255, (char)255 };
	GameEnginePixelColor MapColor = ColMap->GetPixel(static_cast<int>(ColorPos.x), static_cast<int>(ColorPos.y));

	if (Color == MapColor)
	{
		isKeyJump = false;
		MoveType = "Stand";
	}
}

void Player::Move(float _DeltaTime)
{

	if (GameEngineInput::IsPress("LMove") == true)
	{
		SetLeft();
		LeftRightDir = "Left";

		if (MoveType != "Jump")
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

		if (MoveType != "Jump")
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

void Player::Idle()
{
	MoveType = "Stand";
}