#include "PrecompileHeader.h"
#include "Player.h"
#include "PlayerValue.h"
#include "Star.h"
#include "MonsterBasicFunction.h"
#include "StarHitEffect.h"
#include "DamageRender.h"

#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <ctime>

Star::Star()
{
}

Star::~Star()
{
}

void Star::Start()
{

	AttackDistance = PlayerValue::GetValue()->GetAttackDistance();
	TimeCounting();

	StarRender = CreateComponent<GameEngineSpriteRenderer>();	
	StarRender->Off();

	StarCollision = CreateComponent<GameEngineCollision>();
	StarCollision->SetOrder(static_cast<int>(CollisionOrder::Star));
	StarCollision->Off();

	if (Player::GetCurPlayer()->GetLeftRightDir() == "Left")
	{
		Dir = {-1, 0};
		GetTransform()->SetLocalPosition({ -25, 0 });
	}
	else if (Player::GetCurPlayer()->GetLeftRightDir() == "Right")
	{
		Dir = { 1, 0 };
		GetTransform()->SetLocalPosition({ 25, 0 });
	}

	SetStartPos();
}

void Star::Update(float _DeltaTime)
{

	TimeCounting();

	if(UpdateFuction != nullptr)
	{
		UpdateFuction(*this, _DeltaTime);
	}

}

void Star::Render(float _DeltaTime)
{

}

void Star::BasicAnimationUpdate()
{	
	if (isSet == false)
	{
		return;
	}

	AnimationCount += TimeCount;

	if (AnimationCount >= 0.03f)
	{
		AniIndex++;

		if (AniIndex > 1)
		{
			AniIndex = 0;
		}

		std::string TextureName = StarName + "Move" + std::to_string(AniIndex) + ".png";

		StarRender->SetScaleToTexture(TextureName);
		if (Player::GetCurPlayer()->GetLeftRightDir() == "Right")
		{
			float4 Scale = StarRender->GetTransform()->GetLocalScale();
			StarRender->GetTransform()->SetLocalScale({ Scale.x, -Scale.y });
		}

		TransformData RenderData = StarRender->GetTransform()->GetTransDataRef();

		StarCollision->GetTransform()->SetLocalScale(RenderData.LocalScale);
		StarCollision->GetTransform()->SetLocalPosition(RenderData.LocalPosition);
	}
}

void Star::StartTimingCheck(float _DeltaTime)
{
}

void Star::SetStartPos()
{
	StartPos = Player::GetCurPlayer()->GetWeaponPos();
	GetTransform()->AddLocalPosition(StartPos); 
}

void Star::Move(float _DeltaTime)
{
	if(isSet == false)
	{
		TimingTimeCount += TimeCount;

		if (TimingTimeCount < TimingTime)
		{
			return;
		}			

		StarRender->On();
		StarCollision->On();
		isSet = true;
	}
	else
	{
		if (Target != nullptr)
		{
			Dir = Target->GetTransform()->GetWorldPosition() - StarRender->GetTransform()->GetWorldPosition();
			Dir.z = 0.0f;
			Dir.Normalize();
		}

		float4 MoveDis = Dir * /*투척속도*/ 400.0f * _DeltaTime;

		GetTransform()->AddLocalPosition(MoveDis);

		StarRender->GetTransform()->SetLocalRotation({ 0, 0, (180.0f - Dir.GetAnagleDegZ())});
		float4 Pos = GetTransform()->GetLocalPosition();

		AttackDistance -= abs(MoveDis.x);

		if (AttackDistance <= 0.0f)
		{
			Death();
		}
	}

	BasicAnimationUpdate();
	Damage();
}

void Star::AvengerMove(float _DeltaTime)
{
	if(isSet == false)
	{
		TimingTimeCount += TimeCount;

		if (TimingTimeCount < TimingTime)
		{
			return;
		}

		StarRender->SetScaleToTexture("Avenger.png");
		StarCollision->GetTransform()->SetLocalScale(StarRender->GetTransform()->GetLocalScale());
		StarRender->On();
		StarCollision->On();
		isSet = true;
	}
	else
	{
		float4 MoveDis = Dir * 700.0f * _DeltaTime;

		GetTransform()->AddLocalPosition(MoveDis);
		StarRender->GetTransform()->AddLocalRotation({ 0, 0, Dir.x * -1260.0f * _DeltaTime });

		AttackDistance -= abs(MoveDis.x);

		if (AttackDistance <= 0.0f)
		{
			Death();
		}

		AvengerDamage();
	}
}

void Star::Damage()
{
	std::shared_ptr<GameEngineCollision> _Collision;
	if (_Collision = StarCollision->Collision(static_cast<int>(CollisionOrder::Monster), ColType::AABBBOX2D, ColType::AABBBOX2D), _Collision != nullptr)
	{
		int Damage = 150;
	
		std::shared_ptr<DamageRender> NewDR = GetLevel()->CreateActor<DamageRender>();
		NewDR->PushDamageToQueue(Damage);
		NewDR->GetTransform()->SetWorldPosition(_Collision->GetTransform()->GetWorldPosition() + float4{-16.0f, 5.0f});

		_Collision->GetActor()->DynamicThis<MonsterBasicFunction>()->Hit(Damage, isRealAttack);

		std::shared_ptr<StarHitEffect> _Effect = GetLevel()->CreateActor< StarHitEffect>();
		_Effect->SetSkillType("LuckySeven");
		_Effect->SetFrame();
		_Effect->GetTransform()->SetLocalPosition(_Collision->GetTransform()->GetWorldPosition());
		
		Death();
	}
}

void Star::AvengerDamage()
{
	//한대만 쳐야됨
	//맞은 애들 VECTOR에 넣어놓고 있는 애들은 안때리기

	std::shared_ptr<GameEngineCollision> _Collision;
	if (_Collision = StarCollision->Collision(static_cast<int>(CollisionOrder::Monster), ColType::AABBBOX2D, ColType::AABBBOX2D), _Collision != nullptr)
	{
		_Collision->GetActor()->DynamicThis<MonsterBasicFunction>()->Hit(50, true);
	}
}