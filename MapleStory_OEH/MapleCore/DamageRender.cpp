#include "PrecompileHeader.h"
#include "DamageRender.h"

DamageRender::DamageRender()
{
}

DamageRender::~DamageRender()
{
	std::list<std::vector<std::shared_ptr<GameEngineSpriteRenderer>>*>::iterator Start = DamageRenderList.begin();
	std::list<std::vector<std::shared_ptr<GameEngineSpriteRenderer>>*>::iterator End = DamageRenderList.end();

	for (; Start != End;)
	{
		std::vector<std::shared_ptr<GameEngineSpriteRenderer>>* Vec = *Start;

		float Alpha = (*Vec)[0]->ColorOptionValue.MulColor.a;

			for (int i = 0; i < Vec->size(); i++)
			{
				(*Vec)[i]->Death();
			}

			delete (Vec);
			Start = DamageRenderList.erase(Start);
	}
}

void DamageRender::Start()
{
}

void DamageRender::Update(float _DeltaTime) 
{
	RenderUpdate(_DeltaTime);
}

void DamageRender::Render(float _DeltaTime)
{
}

void DamageRender::PushDamageToQueue(int _Damage)
{
	std::vector<std::shared_ptr<GameEngineSpriteRenderer>>* Vec = new std::vector<std::shared_ptr<GameEngineSpriteRenderer>>();
	
	int NumArr[9] = {0,};
	int Digit;

	for (Digit = 0; _Damage > 0; Digit++)
	{
		NumArr[Digit] = _Damage % 10;
		_Damage /= 10;
	}

	Vec->reserve(Digit);

	float LastNumYPos;
	if (DamageRenderList.size() > 0)
	{
		LastNumYPos = (*DamageRenderList.back())[0]->GetTransform()->GetLocalPosition().y;
	}
	else
	{
		LastNumYPos = 0.0f;
	}

	for (int i = Digit; i > 0; i--)
	{
		std::string TextureName = "BasicDamage" + std::to_string(NumArr[i - 1]) + ".png";
		
		std::shared_ptr<GameEngineSpriteRenderer> NewNumberRender = CreateComponent<GameEngineSpriteRenderer>();
		NewNumberRender->SetScaleToTexture(TextureName);
		NewNumberRender->GetTransform()->SetLocalPosition({ ((Digit / 2) - (i - 1)) * 32.0f + (16.0f * (Digit % 2)), LastNumYPos + 18.0f});
		Vec->push_back(NewNumberRender);
	}

	DamageRenderList.push_back(Vec);
}

void DamageRender::RenderUpdate(float _DeltaTime)
{
	if (DamageRenderList.size() <= 0)
	{
		return;
	}

	std::list<std::vector<std::shared_ptr<GameEngineSpriteRenderer>>*>::iterator Start = DamageRenderList.begin();
	std::list<std::vector<std::shared_ptr<GameEngineSpriteRenderer>>*>::iterator End = DamageRenderList.end();

	//std::vector<std::shared_ptr<GameEngineSpriteRenderer>>* Vec

	for (; Start != End; Start++)
	{
		std::vector<std::shared_ptr<GameEngineSpriteRenderer>>* Vec = *Start;

		for (int i = 0; i < (*Start)->size(); i++)
		{
			(*Vec)[i]->GetTransform()->AddLocalPosition({ 0, 30.0f * _DeltaTime });
			(*Vec)[i]->ColorOptionValue.MulColor.a -= 1.0f * _DeltaTime;
		}
	}

	DeleteDamage();
}

void DamageRender::DeleteDamage()
{
	if (DamageRenderList.size() <= 0)
	{
		return;
	}

	std::list<std::vector<std::shared_ptr<GameEngineSpriteRenderer>>*>::iterator Start = DamageRenderList.begin();
	std::list<std::vector<std::shared_ptr<GameEngineSpriteRenderer>>*>::iterator End = DamageRenderList.end();

	//std::vector<std::shared_ptr<GameEngineSpriteRenderer>>* Vec
	
	for (; Start != End;)
	{
		std::vector<std::shared_ptr<GameEngineSpriteRenderer>>* Vec = *Start;

		float Alpha = (*Vec)[0]->ColorOptionValue.MulColor.a;

		if (Alpha <= 0)
		{
			for (int i = 0; i < (*Start)->size(); i++)
			{
				(*Vec)[i]->Death();
			}

			delete (Vec);
			Start = DamageRenderList.erase(Start);

			continue;
		}
			
		Start++;
	}
}